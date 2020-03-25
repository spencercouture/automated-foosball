#include "Capture.h"

class FileCapture: public Capture{
public:
    FileCapture(char* filename);
    cv::Mat* nextFrame();
private:
    cv::VideoCapture capture;
};