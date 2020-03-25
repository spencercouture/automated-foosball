#include <iostream>
#include <opencv2/video/tracking.hpp>
#include "Capture/FileCapture.h"
#include "ImageProcessing/ImageProcessor.h"

// default to camera ON
#ifndef HAS_SPINNAKER_CAMERA
#define HAS_SPINNAKER_CAMERA 1
#endif
#if HAS_SPINNAKER_CAMERA
#include "Capture/CameraCapture.h"
#endif


class Main{
public:
    Main(Capture* cap);
    void processLoop();
private:
    void processKeypress(char keycode);

    Capture* capture;
    ImageProcessor imgProc;
    const char* vidWindow = "vidWindow";
    const char* maskWindow = "maskWindow";
    const char* controlWindow = "controlWindow";
    bool useKalman = false;
    bool trackBall = true;
    double playbackSpeed = 1.0;
    bool paused = false;
};