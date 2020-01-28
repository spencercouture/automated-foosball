#include "main.h"


int main(){
    CameraCapture cam;
    while( !cam.init() );

    cv::namedWindow("test", cv::WINDOW_AUTOSIZE);

    while(true){
        Spinnaker::ImagePtr img = cam.getNextImage();
        unsigned int xpad = img->GetXPadding();
        unsigned int ypad = img->GetYPadding();
        unsigned int r = img->GetWidth();
        unsigned int c = img->GetHeight();
        cv::Mat frame(c + ypad, r+xpad, CV_8UC3, img->GetData(), img->GetStride());
        cv::imshow("test", frame);
        cv::waitKey(1);
    }

}