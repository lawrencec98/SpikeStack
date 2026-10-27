#include <iostream>
#include <stdexcept>

#include "gstPipeline.hpp"


gstPipeline::gstPipeline(std::string path)
{
    gst_init(NULL, NULL); // don't want to process command line arguments

    m_pipeline = gst_pipeline_new("test-pipeline");
    m_source = gst_element_factory_make("filesrc", "source");
    m_demux = gst_element_factory_make("qtdemux", "qtdemux");
    m_custom_data.h264parse = gst_element_factory_make("h264parse", "h264parse");
    m_decoder = gst_element_factory_make("avdec_h264", "avdec_h264");
    m_convert = gst_element_factory_make("videoconvert", "videoconvert");
    m_sink = gst_element_factory_make("appsink", "sink");
    m_caps = gst_caps_from_string("video/x-raw,format=BGR");
    g_object_set(m_sink, "caps", m_caps, "emit-signals", TRUE, "max-buffers", 2, "drop", TRUE, NULL);
    gst_caps_unref(m_caps);

    if (!m_pipeline || !m_source || !m_demux || !m_custom_data.h264parse || !m_decoder || !m_convert || !m_sink)
    {
        throw std::runtime_error("Failed to create elements.");
    }

    // Set the file path
    g_object_set(G_OBJECT(m_source), "location", path.c_str(), NULL);

    gst_bin_add_many(GST_BIN(m_pipeline), m_source, m_demux, m_custom_data.h264parse, m_decoder, m_convert, m_sink, NULL);

    // Link filesrc -> qtdemux
    if (!gst_element_link(m_source, m_demux))
    {
        std::cerr << "Failed to link filesrc to qtdemux." << std::endl;
        gst_object_unref(m_pipeline);
    }

    // Link h264parse -> decoder -> videoconvert -> autovideosink
    if (!gst_element_link_many(m_custom_data.h264parse, m_decoder, m_convert, m_sink, NULL))
    {
        std::cerr << "Failed to link downstream decoding elements." << std::endl;
        gst_object_unref(m_pipeline);
    }

    // Connect the dynamic signal for qtdemux
    g_signal_connect(m_demux, "pad-added", G_CALLBACK(on_pad_added), &m_custom_data);

    // Connect on_new_sample callback to appsink.
    g_signal_connect(m_sink, "new-sample", G_CALLBACK(on_new_sample), this);
}

gstPipeline::~gstPipeline()
{
    // Cleanup
    gst_element_set_state(m_pipeline, GST_STATE_NULL);
    gst_object_unref(m_pipeline);
}

// Callback to handle the dynamic pad from qtdemux
void gstPipeline::on_pad_added(GstElement* src, GstPad* new_pad, gpointer user_data)
{
    CustomData* data = (CustomData*)user_data;
    GstPad* sink_pad = gst_element_get_static_pad(data->h264parse, "sink");

    if (gst_pad_is_linked(sink_pad))
    {
        gst_object_unref(sink_pad);
        return;
    }

    // Link the dynamic pad to h264parse
    if (gst_pad_link(new_pad, sink_pad) != GST_PAD_LINK_OK)
    {
        std::cerr << "Failed to link qtdemux dynamic pad to h264parse." << std::endl;
    }
    else
    {
        std::cout << "Successfully linked qtdemux to h264parse!" << std::endl;
    }

    gst_object_unref(sink_pad);
}

GstFlowReturn gstPipeline::on_new_sample(GstAppSink* appsink, gpointer user_data)
{
    gstPipeline* self = static_cast<gstPipeline*>(user_data);

    GstSample* sample = nullptr;
    g_signal_emit_by_name(appsink, "pull-sample", &sample);

    GstCaps* caps = gst_sample_get_caps(sample);
    GstStructure* s = gst_caps_get_structure(caps, 0);
    int width, height;
    gst_structure_get_int(s, "width", &width);
    gst_structure_get_int(s, "height", &height);

    GstBuffer* buf = gst_sample_get_buffer(sample);
    GstMapInfo map;
    gst_buffer_map(buf, &map, GST_MAP_READ);

    {
        std::lock_guard<std::mutex> lock(self->m_callbacks_mutex);

        for (auto& cb : self->m_callbacks)
        {
            cb(map.data, height, width);
        }
    }

    gst_buffer_unmap(buf, &map);
    gst_sample_unref(sample);

    return GST_FLOW_OK;
}

void gstPipeline::Run()
{
    // Set to playing
    std::cout << "Starting playback..." << std::endl;
    gst_element_set_state(m_pipeline, GST_STATE_PLAYING);

    // A proper way to block without burning CPU is waiting on the GstBus message stream:
    GstBus* bus = gst_element_get_bus(m_pipeline);
    GstMessage* msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
        (GstMessageType)(GST_MESSAGE_EOS | GST_MESSAGE_ERROR));

    if (msg)
        gst_message_unref(msg);
    gst_object_unref(bus);
}


void gstPipeline::AttachCallback(std::function<void(unsigned char*, long unsigned int, long unsigned int)> function)
{
    std::lock_guard<std::mutex> lock(m_callbacks_mutex);

    m_callbacks.push_back(function);
}


void OpenCVCallback(unsigned char* buffer, long unsigned int height, long unsigned int width)
{
    cv::Mat frame(height, width, CV_8UC3, buffer);

    cv::imshow("image", frame);
    cv::waitKey(15);
}


int main(int argc, char* argv[])
{
    gstPipeline pipeline(argv[1]);

    pipeline.AttachCallback(OpenCVCallback);

    /* Inform user about correct usage */
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <path_to_mp4_file>" << std::endl;
        return -1;
    }

    pipeline.Run();

    return 0;
}