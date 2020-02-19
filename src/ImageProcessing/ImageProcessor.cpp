#include "ImageProcessor.h"

// return nullptr if ball not found
std::vector<cv::Vec3f> ImageProcessor::detectBall(cv::Mat img, cv::Mat& hsv){
    cv::Mat frame;
    // create scalars for color mask
    cv::Scalar lowScalar(mask.lowH, mask.lowS, mask.lowV);
    cv::Scalar highScalar(mask.highH, mask.highS, mask.highV);

    // resize frame
    //cv::resize(img, frame, resizeValue);

    cv::cvtColor(img, frame, cv::COLOR_BGR2HSV);
    cv::inRange(frame, lowScalar, highScalar, frame);

    // blur, dilate, and erode image
    cv::GaussianBlur(frame, frame, cv::Size(3, 3), 0);
    cv::dilate(frame, frame, 0);
    cv::erode(frame, frame, 0);

    hsv = frame;

    // detect the circles
    std::vector<cv::Vec3f> circles; // circles found in the frame
    
    cv::HoughCircles(frame, circles, cv::HOUGH_GRADIENT, dpi, frame.rows / 5, 100,
        threshVal, ballRadiusMin, ballRadiusMax);

    // if vector is empty, return nullptr
//    if( circles.size() == 0 ) return nullptr;

    return circles;
}
