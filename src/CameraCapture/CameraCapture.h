#include <spinnaker/Spinnaker.h>
#include <chrono> 

class CameraCapture{
public:
    bool init();
    Spinnaker::ImagePtr getNextImage();
    ~CameraCapture();
    Spinnaker::CameraPtr camera;
    std::chrono::microseconds captureDelta;
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> lastCaptureTime;
    Spinnaker::SystemPtr system;
    bool isInit = false;
    bool isCapturing = false;
};