#include <spinnaker/Spinnaker.h>

class CameraCapture{
public:
    bool init();
    Spinnaker::ImagePtr getNextImage();
    ~CameraCapture();

private:
    Spinnaker::SystemPtr system;
    Spinnaker::CameraPtr camera;
    bool isInit = false;
};