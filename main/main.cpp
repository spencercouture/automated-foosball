#include "main.h"


int main(){
    ImageProcessor proc;
    CameraCapture cam;
    while( !cam.init() );

    cv::namedWindow("hsv", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("imgOg", cv::WINDOW_NORMAL);
    
    cv::Mat imgOg;
    cv::Mat hsvImg;
    cv::Mat threshImg;

    char escKey = 0;
    
    int lowH = 0;
    int hiH  = 15;
    int lowS = 129;
    int hiS  = 220;
    int lowV = 232;
    int hiV  = 255;
   
    while(escKey != 27){
        
        // TEMP--REMOVE THIS
        proc.mask.lowH = lowH;
        proc.mask.highH = hiH;
        proc.mask.lowS = lowS;
        proc.mask.highS = hiS;
        proc.mask.lowV = lowV;
        proc.mask.highV = hiV;


        Spinnaker::ImagePtr img = cam.getNextImage();
        if( !img ) continue;
        unsigned int xpad = img->GetXPadding();
        unsigned int ypad = img->GetYPadding();
        unsigned int r = img->GetWidth();
        unsigned int c = img->GetHeight();
        imgOg = cv::Mat(c + ypad, r+xpad, CV_8UC3, img->GetData(), img->GetStride());
        cv::resize(imgOg, imgOg, cv::Size(512, 288));
        std::vector<cv::Vec3f> balls = proc.detectBall(imgOg, hsvImg);
        if( balls.size() > 0 ){
            for( unsigned int i = 0; i < balls.size(); i++ ){
                cv::Scalar col(0, 0, 255);
                //if( i == 0 ) col = cv::Scalar(255, 0, 0);
                if( i == balls.size() - 1) col = cv::Scalar(255, 0, 0);
                cv::Vec3f ball = balls.at(i);            
//cv::circle(imgOg, cv::Point((int)(*ball)[0], (int)(*ball)[1]), (int)(*ball)[2], cv::Scalar(0, 0, 255), 3),
cv::circle(imgOg, cv::Point((int)(ball)[0], (int)(ball)[1]), (int)(ball)[2], col, 3),
            std::cout << (ball)[2] << std::endl; 
cv::circle(hsvImg, cv::Point((int)(ball)[0], (int)(ball)[1]), (int)(ball)[2], col, 3),
            std::cout << (ball)[2] << std::endl; 

            }
//                        delete ball;
        }


        cv::createTrackbar("lowH", "hsv", &lowH, 179);
        cv::createTrackbar("highH", "hsv", &hiH, 179);
        cv::createTrackbar("lowS", "hsv", &lowS, 255);
        cv::createTrackbar("highS", "hsv", &hiS, 255);
        cv::createTrackbar("lowV", "hsv", &lowV, 255);
        cv::createTrackbar("highV", "hsv", &hiV, 255);
        cv::createTrackbar("treshVal", "hsv", &proc.threshVal, 100);
        cv::createTrackbar("dpi", "hsv", &proc.dpi, 50);
        cv::imshow("hsv", hsvImg);
        cv::imshow("imgOg", imgOg);
        escKey = cv::waitKey(1);
    }

}
