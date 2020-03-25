#include <spinnaker/Spinnaker.h>
#include <chrono> 
#include "Capture.h"

class CameraCapture: Capture{
public:
    CameraCapture();
    bool init();
    cv::Mat* nextFrame();
    ~CameraCapture();
    Spinnaker::CameraPtr camera;
    std::chrono::microseconds captureDelta;
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> lastCaptureTime;
    Spinnaker::SystemPtr system;
    bool isInit = false;
    bool isCapturing = false;
};