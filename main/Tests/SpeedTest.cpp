
#include "../ImageProcessing/ImageProcessor.h"
#include <iostream>
#include <algorithm> 
#include <chrono> 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>


// processes the frames of the image and detects the ball
void processImages( std::string filename ){
    // get capture and ensure its opened
    cv::VideoCapture capture(filename);
    if( !capture.isOpened() ){
        std::cerr << "could not open file" << std::endl;
        exit(-1);
    }

    // processor    
    ImageProcessor proc;
    cv::Mat frame;
    capture >> frame;
    while( !frame.empty() ){
        //proc.detectBall(frame);
        capture >> frame;
    }
}

int main( int argc, char** argv ){
    // throw error if no video is supplied
    if( argc < 2 ){
        std::cerr << "video file argument required" << std::endl;
        exit(-1);
    }

    // get start time
    auto start = std::chrono::high_resolution_clock::now(); 
    processImages(argv[1]);
    // get completion time
    auto stop = std::chrono::high_resolution_clock::now(); 


    // calculate total runtime
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 
    
    std::cout << "Total completion time: " << duration.count() << " microseconds" << std::endl; 
}
