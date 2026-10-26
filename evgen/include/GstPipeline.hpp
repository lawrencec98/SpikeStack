#ifndef GST_PIPELINE_HPP
#define GST_PIPELINE_HPP


#include <gst/gst.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>



class GstPipeline
{
public:
    GstPipeline();
    ~GstPipeline() = default;

    void AttachCallback(std::function<void(cv::Mat)> function);

private:
}



#endif // GST_PIPELINE_HPP