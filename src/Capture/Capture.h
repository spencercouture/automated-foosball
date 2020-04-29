#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <chrono> 

// simple interface to handle captures nicely
class Capture{
public:
    virtual cv::Mat* nextFrame() = 0;
    virtual void reset() = 0; // used for file captures mainly
    double waittime; // time until next frame: 0 for live footage, fps for file
};