#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <algorithm> 
#include <chrono> 
#include "../ImageProcessing/ImageProcessor.h"

bool read = false;
bool write = false;
std::ofstream outfile;
std::ifstream infile;

void errQuit(){
    std::cout << "usage: ./kalman <video-file> <read/write> <filename>" << std::endl;
    exit(-1);
}

// entry point, takes video file as parameter
int main( int argc, char** argv ){

    // if not enough args
    if( argc < 2 ) errQuit();

    if( argc > 2 ){
        if( argc != 4 ) errQuit();

        if( strcmp(argv[2], "read") == 0 ){
            read = true;
            infile.open(argv[3]);
        }
        else if( strcmp(argv[2], "write") == 0 ){
            write = true;
            outfile.open(argv[3]);
        }
        else{
            errQuit();
        }
    }

    // create the capture
    cv::VideoCapture cap(argv[1]);

    // throw error if the file can't be found
    if( !cap.isOpened() ){
        std::cout << "could not open " << argv[1] << " for reading" << std::endl;
        std::cout << "Quitting..." << std::endl;
        exit(-1);
    }

    // image processer
    ImageProcessor proc;

    // gets the fps
    double fps = (1000)/cap.get(cv::CAP_PROP_FPS);

    // prepare window
    cv::namedWindow("main", cv::WINDOW_NORMAL);

    // setup keycode for things
    char keyCode = 0;

    cv::Mat frame, hsv;
    cap >> frame;
    auto start = std::chrono::high_resolution_clock::now(); 
    while( !frame.empty() && keyCode != 2 ){
    
        cv::resize(frame, frame, cv::Size(512, 288));

        if( read ){
            double ballx, bally, ballr;
            infile >> ballx;
            infile >> bally;
            infile >> ballr;
            if( ballx != -1 && bally != -1 && ballr != -1)
                cv::circle(frame, cv::Point(ballx, bally), ballr, cv::Scalar(0, 0, 255), 3);
        }
        else{
            std::vector<cv::Vec3f> balls = proc.detectBall(frame, hsv);

            if( balls.size() > 0 ){
                cv::Vec3f ball = balls.at(0);
                cv::circle(frame, cv::Point((int)(ball)[0], (int)(ball)[1]), (int)(ball)[2], cv::Scalar(0, 0, 255), 3);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); 
                if( write ) outfile << ball[0] << "\t" << ball[1] << "\t" << ball[2] << "\t" << duration.count() << std::endl;
                start = std::chrono::high_resolution_clock::now();
            }
            //else if( write ) outfile << "-1\t-1\t-1\t-1" << std::endl;
        }

        cv::imshow("main", frame);
        cap >> frame;
        keyCode = cv::waitKey(fps);
    }

    if( write ) outfile.close();
    if( read ) infile.close();
}