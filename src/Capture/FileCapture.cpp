#include "FileCapture.h"

// open the file and create a capture object
FileCapture::FileCapture(char* filename){
    // create capture
    capture = cv::VideoCapture(filename);
    // throw error if couldn't open
    if( !capture.isOpened() ) throw "could not open file for capture";
    
    // determine fps
    waittime = (1000)/capture.get(cv::CAP_PROP_FPS);
}

cv::Mat* FileCapture::nextFrame(){
    cv::Mat* newFrame = new cv::Mat();
    capture >> (*newFrame);
    return newFrame;
}