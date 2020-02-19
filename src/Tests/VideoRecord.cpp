#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <spinnaker/Spinnaker.h>
#include "../ImageProcessing/ImageProcessor.h"
#include "../CameraCapture/CameraCapture.h"


/**
 * A file to handle the recording of live footage
**/
int main(){

    ImageProcessor proc;
    CameraCapture cam;

    while( !cam.init() );

    cv::namedWindow("mainView", cv::WINDOW_NORMAL);
    char keyVal = 0;

    cv::Mat frame;

    cv::VideoWriter writer("output.mp4", 
        cv::VideoWriter::fourcc('M','P','4','V'), 60, cv::Size(512, 288));

    bool recording = false;

    // ESC to quit
    while( keyVal != 27 ){
        Spinnaker::ImagePtr img = cam.getNextImage();
        if( !img ) continue;

        unsigned int xpad = img->GetXPadding();
        unsigned int ypad = img->GetYPadding();
        unsigned int r = img->GetWidth();
        unsigned int c = img->GetHeight();

        frame = cv::Mat(c + ypad, r+xpad, CV_8UC3, img->GetData(), img->GetStride());
        cv::resize(frame, frame, cv::Size(512, 288));

        cv::Mat displayFrame = frame.clone();

        if( recording ){
            cv::circle(displayFrame, cv::Point(25, 25), 8, cv::Scalar(255, 0, 0), cv::FILLED);
            writer.write(frame);
        }

        cv::imshow("mainView", displayFrame);

        keyVal = cv::waitKey(1);

        if( keyVal == ' ' ){
            recording = !recording;
        }


    }

    writer.release();
}