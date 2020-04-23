#include "Capture.h"

class FileCapture: public Capture{
public:
    FileCapture(char* filename);
    cv::Mat* nextFrame();
    void reset();
private:
    cv::VideoCapture capture;
    char* _filename;
};