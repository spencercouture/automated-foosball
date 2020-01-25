#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>


#include "../config.h"
#include "Mask.h"

/**
 * Class to handle the image processing tasks
**/
class ImageProcessor{
private:
    // the color mask
    Mask mask;

public:
    // amount to resize the frame to
    cv::Size resizeValue = cv::Size(resizeX, resizeY);
    // given a frame, find the ball
    cv::Vec3f* detectBall(cv::Mat frame);
};
