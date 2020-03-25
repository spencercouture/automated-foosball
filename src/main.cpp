#include "main.h"

Main::Main(Capture* cap) {
    capture = cap;
    
    // intialize windows
    cv::namedWindow(vidWindow, cv::WINDOW_NORMAL);
    cv::namedWindow(maskWindow, cv::WINDOW_NORMAL);
    cv::namedWindow(controlWindow, cv::WINDOW_NORMAL);
};

void Main::processLoop(){
    cv::Mat* frame = capture->nextFrame();
    cv::Mat  hsv;

    // check the aspect ratio to scale down
    cv::Size s = frame->size();
    float res_43 = (float)4/3;
    float frameRes = (float)s.width/s.height;    
    // if we're 4:3, update the y width of the resize
    if( frameRes == res_43 ) imgProc.resizeValue = cv::Size(imgProc.resizeValue.width, 384);

    while( !frame->empty() ){

        // detect the ball in the image and draw the first one found
        std::vector<cv::Vec3f> balls = imgProc.detectBall(*frame, hsv);
        if( balls.size() > 0 ){
            cv::Vec3f ball = balls.at(0);
            cv::circle(*frame, cv::Point((int)(ball)[0], (int)(ball)[1]), (int)(ball)[2], cv::Scalar(0, 0, 255), 3);
        }

        cv::imshow(vidWindow, *frame);
        cv::imshow(maskWindow, hsv);

        frame = capture->nextFrame();
        cv::waitKey(capture->waittime);
    }
}

void Main::processKeypress(char keycode){
    
}

int main(int argc, char** argv){
    Capture* capture;

    // setup file or camera capture
    if( argc > 1 && !HAS_SPINNAKER_CAMERA ){
        try{
            capture = new FileCapture(argv[1]);
        }
        catch(const char* err){
            std::cerr << "Error intializing FileCapture with '" << argv[1]
                << "': " << err << std::endl;
            exit(-1);
        }
    }
    else if(!HAS_SPINNAKER_CAMERA){
        std::cerr << "Error: compiled without camera but did not supply video. "
            << "Quitting..." << std::endl;
        exit(-1);
    }
    else{
    #if HAS_SPINNAKER_CAMERA
        try{
            capture = new CameraCapture();
        }
        catch(const char* err){
            std::cerr << "Error intializing CameraCapture: " << err 
                << std::endl;
            exit(-1);
        }
    #endif
    }
    
    Main main(capture);
    main.processLoop();
}