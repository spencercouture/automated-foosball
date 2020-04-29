#include "Capture.h"

class FileCapture: public Capture{
public:
    FileCapture(char* filename, int fps = -1);
    cv::Mat* nextFrame();
    void reset();
private:
    cv::VideoCapture capture;
    char* _filename;
};