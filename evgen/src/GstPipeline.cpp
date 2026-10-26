#include <iostream>

#include <gst/app/gstappsink.h>



// Structure to pass our h264parse element into the callback
struct CustomData
{
    GstElement *h264parse;
};


// Callback to handle the dynamic pad from qtdemux
void on_pad_added(GstElement *src, GstPad *new_pad, gpointer user_data)
{
    CustomData *data = (CustomData *)user_data;
    GstPad *sink_pad = gst_element_get_static_pad(data->h264parse, "sink");

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


GstFlowReturn on_new_sample(GstAppSink *appsink, gpointer user_data)
{
    GstSample *sample = nullptr;
    g_signal_emit_by_name(appsink, "pull-sample", &sample);

    GstCaps *caps = gst_sample_get_caps(sample);
    GstStructure *s = gst_caps_get_structure(caps, 0);
    int width, height;
    gst_structure_get_int(s, "width", &width);
    gst_structure_get_int(s, "height", &height);

    GstBuffer *buf = gst_sample_get_buffer(sample);
    GstMapInfo map;
    gst_buffer_map(buf, &map, GST_MAP_READ);

    // Zero-copy view of the frame. Valid only until unmap.
    cv::Mat frame(height, width, CV_8UC3, map.data);

    cv::imshow("image", frame);
    cv::waitKey(15);
    // ---- your image processing here ----
    // If you need the data beyond this callback: cv::Mat copy = frame.clone();

    gst_buffer_unmap(buf, &map);
    gst_sample_unref(sample);

    return GST_FLOW_OK;
}


int main(int argc, char *argv[])
{
    /* Initialize gstreamer */
    gst_init(&argc, &argv);

    /* Inform user about correct usage */
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <path_to_mp4_file>" << std::endl;
        return -1;
    }

    CustomData data;

    GstElement *pipeline = gst_pipeline_new("test-pipeline");
    GstElement *source = gst_element_factory_make("filesrc", "source");
    GstElement *demux = gst_element_factory_make("qtdemux", "qtdemux");
    data.h264parse = gst_element_factory_make("h264parse", "h264parse");
    GstElement *decoder = gst_element_factory_make("avdec_h264", "avdec_h264");
    GstElement *convert = gst_element_factory_make("videoconvert", "videoconvert");
    GstElement *sink = gst_element_factory_make("appsink", "sink");
    GstCaps *caps = gst_caps_from_string("video/x-raw,format=BGR");
    g_object_set(sink, "caps", caps, "emit-signals", TRUE, "max-buffers", 2, "drop", TRUE, NULL);
    gst_caps_unref(caps);

    if (!pipeline || !source || !demux || !data.h264parse || !decoder || !convert || !sink)
    {
        std::cerr << "Failed to create elements." << std::endl;
        return -1;
    }

    // Set the file path
    g_object_set(G_OBJECT(source), "location", argv[1], NULL);

    gst_bin_add_many(GST_BIN(pipeline), source, demux, data.h264parse, decoder, convert, sink, NULL);

    // Link filesrc -> qtdemux
    if (!gst_element_link(source, demux))
    {
        std::cerr << "Failed to link filesrc to qtdemux." << std::endl;
        gst_object_unref(pipeline);
        return -1;
    }

    // Link h264parse -> decoder -> videoconvert -> autovideosink
    if (!gst_element_link_many(data.h264parse, decoder, convert, sink, NULL))
    {
        std::cerr << "Failed to link downstream decoding elements." << std::endl;
        gst_object_unref(pipeline);
        return -1;
    }

    // Connect the dynamic signal for qtdemux
    g_signal_connect(demux, "pad-added", G_CALLBACK(on_pad_added), &data);

    // Connect on_new_sample callback to appsink.
    g_signal_connect(sink, "new-sample", G_CALLBACK(on_new_sample), nullptr);

    // Set to playing
    std::cout << "Starting playback..." << std::endl;
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    // A proper way to block without burning CPU is waiting on the GstBus message stream:
    GstBus *bus = gst_element_get_bus(pipeline);
    GstMessage *msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                                 (GstMessageType)(GST_MESSAGE_EOS | GST_MESSAGE_ERROR));

    if (msg)
        gst_message_unref(msg);
    gst_object_unref(bus);

    // Cleanup
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
}