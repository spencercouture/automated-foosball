#include <vector>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include "../ImageProcessing/ImageProcessor.h"



// entry point, takes video file as parameter
int main( int argc, char** argv ){

    // if not enough args
    if( argc < 2 ){
        std::cout << "usage: ./kalman <video-file>" << std::endl;
        exit(-1);
    }

    // create the capture
    cv::VideoCapture cap(argv[1]);

    // throw error if the file can't be found
    if( !cap.isOpened() ){
        std::cout << "could not open " << argv[1] << " for reading" << std::endl;
        std::cout << "Quitting..." << std::endl;
        exit(-1);
    }

    // gets the fps
    double fps = (1000)/cap.get(cv::CAP_PROP_FPS);

    // prepare window
    cv::namedWindow("main", cv::WINDOW_NORMAL);

    // setup keycode for things
    char keyCode = 0;

    cv::Mat frame;
    for( cap >> frame; !frame.empty() && keyCode != 27; keyCode = cv::waitKey(fps) ){

        cv::imshow("main", frame);

        cap >> frame;
    }

}