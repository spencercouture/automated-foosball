#include <vector>

#include "ImageProcessor.h"


// return nullptr if ball not found
cv::Vec3f* ImageProcessor::detectBall(cv::Mat frame){
    // create scalars for color mask
    cv::Scalar lowScalar(System::mask.lowH, System::mask.lowS, System::mask.lowV);
    cv::Scalar highScalar(System::mask.highH, System::mask.highS, System::mask.highV);

    // resize frame
    cv::resize(frame, frame, resizeValue);

    // blur, dilate, and erode image
    cv::GaussianBlur(frame, frame, cv::Size(3, 3), 0);
    cv::dilate(frame, frame, 0);
    cv::erode(frame, frame, 0);

    // detect the circles
    std::vector<cv::Vec3f> circles; // circles found in the frame
    cv::HoughCircles(frame, circles, cv::HOUGH_GRADIENT, 2, frame.rows / 3, 100,
        20, ballRadiusMin, ballRadiusMax);

    // if vector is empty, return nullptr
    if( circles.size() == 0 ) return nullptr;

    return new cv::Vec3f(circles.at(0));
}