#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <vector>
#include <iostream>
// Author: Spencer Couture

/*
    This is the hello-world example of the ball tracking abilities of OpenCV.
*/

int main(int argc, char** argv){
    if( argc < 2 ){
        std::cout << "need video file" << std::endl;
        return -1;
    }

    // load the video file
    std::string filename = argv[1];
    cv::VideoCapture cap(filename);
    
    // exit if cannot read file
    if( !cap.isOpened() ){
        std::cerr << "Could not open video file" << std::endl;
        exit(-1);
    }

    cv::Mat imgOriginal;  // Input image
    cv::Mat hsvImg;    // HSV Image
    cv::Mat threshImg;   // Thresh Image

    std::vector<cv::Vec3f> v3fCircles;  // 3 element vector of floats, this will be the pass by reference output of HoughCircles()

    char charCheckForEscKey = 0;

/*    int lowH = 0;       // Set Hue
    int highH = 179;

    int lowS = 48;       // Set Saturation
    int highS = 255;

    int lowV = 211;       // Set Value
    int highV = 255;
    */

    int lowH = 0;       // Set Hue
    int highH = 12;

    int lowS = 89;       // Set Saturation
    int highS = 138;

    int lowV = 134;       // Set Value
    int highV = 234;   

    bool paused = false;
    // HUE for YELLOW is 21-30.
    // Adjust Saturation and Value depending on the lighting condition of the environment as well as the surface of the object.
    cap >> imgOriginal;
    cv::Mat tmp;
    while (charCheckForEscKey != 27) {    // until the Esc is pressed or webcam connection is lost
        if( charCheckForEscKey == 32 ){
            paused = !paused;
        }
        if( !paused )
            cap >> imgOriginal;
        if(imgOriginal.empty())
            break;

        cv::Size s(960, 540);
        cv::resize(imgOriginal, imgOriginal, s);
        imgOriginal.copyTo(tmp);

        cv::cvtColor(imgOriginal, hsvImg, cv::COLOR_BGR2HSV);      // Convert Original Image to HSV Thresh Image

        cv::inRange(hsvImg, cv::Scalar(lowH, lowS, lowV), cv::Scalar(highH, highS, highV), threshImg);

        cv::GaussianBlur(threshImg, threshImg, cv::Size(3, 3), 0);   //Blur Effect
        cv::dilate(threshImg, threshImg, 0);        // Dilate Filter Effect
        cv::erode(threshImg, threshImg, 0);         // Erode Filter Effect

        // fill circles vector with all circles in processed image
        cv::HoughCircles(threshImg,v3fCircles,cv::HOUGH_GRADIENT,2,threshImg.rows / 4,100,20,8,18);  // algorithm for detecting circles  


        //for (int i = 0; i < v3fCircles.size(); i++) {      // for each circle       
        if( v3fCircles.size() > 0 ){
            int i = 0;    
        std::cout << "Ball position X = "<< v3fCircles[i][0]   // x position of center point of circle
                <<",\tY = "<< v3fCircles[i][1]        // y position of center point of circle
                <<",\tRadius = "<< v3fCircles[i][2]<< "\n";     // radius of circle

            // draw small green circle at center of object detected
            cv::circle(imgOriginal,            // draw on original image
            cv::Point((int)v3fCircles[i][0], (int)v3fCircles[i][1]),  // center point of circle
                3,                // radius of circle in pixels
                cv::Scalar(0, 255, 0),           // draw green
                cv::FILLED);              // thickness

            // draw red circle around object detected 
            cv::circle(imgOriginal,            // draw on original image
            cv::Point((int)v3fCircles[i][0], (int)v3fCircles[i][1]),  // center point of circle
                (int)v3fCircles[i][2],           // radius of circle in pixels
                cv::Scalar(0, 0, 255),           // draw red
                3);                // thickness
        } 
        v3fCircles.clear();
        // declare windows
        cv::namedWindow("imgOriginal", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("threshImg", cv::WINDOW_AUTOSIZE); 

        cv::createTrackbar("LowH", "threshImg", &lowH, 179); //Hue (0 - 179)
        cv::createTrackbar("HighH", "threshImg", &highH, 179);

        cv::createTrackbar("LowS", "threshImg", &lowS, 255); //Saturation (0 - 255)
        cv::createTrackbar("HighS", "threshImg", &highS, 255);

        cv::createTrackbar("LowV", "threshImg", &lowV, 255); //Value (0 - 255)
        cv::createTrackbar("HighV", "threshImg", &highV, 255);

        cv::imshow("imgOriginal", imgOriginal);     // show windows
        cv::imshow("threshImg", threshImg);

        tmp.copyTo(imgOriginal);

        charCheckForEscKey = cv::waitKey(100);     // delay and get key press
    }

 return(0);          
    }
