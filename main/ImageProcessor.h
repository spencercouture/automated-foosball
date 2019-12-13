#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "common.h"
#include "System.h"

/**
 * Class to handle the image processing tasks
**/
class ImageProcessor{
    // amount to resize the frame to
    cv::Size resizeValue = cv::Size(resizeX, resizeY);
    // given a frame, find the ball
    cv::Vec3f* detectBall(cv::Mat frame);
};