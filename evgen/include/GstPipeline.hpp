#ifndef GST_PIPELINE_HPP
#define GST_PIPELINE_HPP

#include <chrono>

#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


namespace spikestack
{

// Structure to pass our h264parse element into the callback
struct CustomData
{
    GstElement *h264parse;
};


class GstPipeline
{
public:
    /**
     * @param [in] path - path to an video file
     */
    GstPipeline(std::string path);

    ~GstPipeline();

    /**
     * @brief this is a default pipeline, hardcoded and used for early testing
     * and proof of concept.
     */
    void Run();
    void AttachCallback(std::function<void(cv::Mat)> function);


private: // functions
    static GstFlowReturn on_new_sample(GstAppSink *appsink, gpointer user_data);
    static void on_pad_added(GstElement *src, GstPad *new_pad, gpointer user_data);
private: // members
    std::vector<std::function<void(char*, size_t)>> m_callbacks;
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


} //namespace spikestack

#endif // GST_PIPELINE_HPP