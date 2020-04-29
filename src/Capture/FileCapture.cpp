#include "FileCapture.h"
#include <iostream>

// open the file and create a capture object
FileCapture::FileCapture(char* filename, int fps){
    _filename = filename;
    // create capture
    capture = cv::VideoCapture(_filename);
    // throw error if couldn't open
    if( !capture.isOpened() ) throw "could not open file for capture";
    
    // determine fps
    double realfps = (fps != -1) ? fps : capture.get(cv::CAP_PROP_FPS);
    waittime = (1000)/realfps;
    std::cout << "detected FPS of " << realfps << std::endl;
    std::cout << "calculated waittime of " << waittime << std::endl;
}

cv::Mat* FileCapture::nextFrame(){
    cv::Mat* newFrame = new cv::Mat();
    capture >> (*newFrame);
    return newFrame;
}

void FileCapture::reset(){
    capture.release();
    capture = cv::VideoCapture(_filename);
    // throw error if couldn't open
    if( !capture.isOpened() ) throw "could not open file for capture";
}