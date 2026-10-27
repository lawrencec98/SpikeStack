#ifndef GST_PIPELINE_HPP
#define GST_PIPELINE_HPP

#include <chrono>
#include <mutex>

#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>



// Structure to pass our h264parse element into the callback
struct CustomData
{
    GstElement *h264parse;
};


class gstPipeline
{
public:
    // Constructor takes an input video path
    gstPipeline(std::string path);

    ~gstPipeline();

    // This is a default pipeline, hardcoded and used for early testing and proof of concept.
    void Run();
    
    // Allows the user to attach callbacks to do things with the gstreamer video.
    void AttachCallback(std::function<void(unsigned char*, long unsigned int, long unsigned int)> function);


private: // functions
    static GstFlowReturn on_new_sample(GstAppSink *appsink, gpointer user_data);
    static void on_pad_added(GstElement *src, GstPad *new_pad, gpointer user_data);

private: // members
    std::mutex m_callbacks_mutex;
    std::vector<std::function<void(unsigned char*, long unsigned int, long unsigned int)>> m_callbacks;
    std::string m_input_video_path;

    GstElement* m_pipeline;
    GstElement* m_source;
    GstElement* m_demux;
    GstElement* m_decoder;
    GstElement* m_convert;
    GstElement* m_sink;
    GstCaps* m_caps = {};
    CustomData m_custom_data;
    
};


#endif // GST_PIPELINE_HPP