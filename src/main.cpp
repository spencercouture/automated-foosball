#include "main.h"

Main::Main(Capture* cap) {
    capture = cap;
    
    // intialize windows
    cv::namedWindow(vidWindow, cv::WINDOW_NORMAL);
    cv::namedWindow(maskWindow, cv::WINDOW_NORMAL);
    cv::namedWindow(controlWindow, cv::WINDOW_NORMAL);
    cv::resizeWindow(controlWindow, cv::Size(700,400));


    // setup trackbars
    cv::createTrackbar("Play", controlWindow, &play, 1);
    cv::createTrackbar("Loop", controlWindow, &loop, 1);
    cv::createTrackbar("Low Hue", controlWindow, &imgProc.mask.lowH, 179);
    cv::createTrackbar("High Hue", controlWindow, &imgProc.mask.highH, 179);
    cv::createTrackbar("Low Saturation", controlWindow, &imgProc.mask.lowS, 255);
    cv::createTrackbar("High Saturation", controlWindow, &imgProc.mask.highS, 255);
    cv::createTrackbar("Low Value", controlWindow, &imgProc.mask.lowV, 255);
    cv::createTrackbar("High Value", controlWindow, &imgProc.mask.highV, 255);    
};

// helper to draw the arrowed line for the direction of the ball
void Main::drawArrow(cv::Vec3f ball, cv::Mat* frame){
    // get equation for the line
    float dx = ball[0] - lastLoc[0];
    float dy = ball[1] - lastLoc[1];
    float nx, ny;

    // if both are 0, just quit--no change
    if( dx == 0 && dy == 0 ) return;

    // if one is zero, then either perfectly horizontal or vertical
    if( dx == 0 ){
        nx = ball[0];
        ny = ball[1] + ((ball[1] > lastLoc[1]) ? arrowLength : -1 * arrowLength);
        //std::cout << "only up/down" << std::endl;
    }
    else if( dy == 0 ){
        nx = ball[0] + ((ball[0] > lastLoc[0]) ? arrowLength : -1 * arrowLength);
        ny = ball[1];
        //std::cout << "only left/right" << std::endl;
    }
    else{
        nx = ball[0] + (arrowLength / sqrt((dy/dx)*(dy/dx) + 1)) * ((ball[0] < lastLoc[0]) ? -1 : 1);
        ny = ball[1] + (dy/dx) * (nx-ball[0]);
    }

    /*std::cout << "bx: " << ball[0] << "\nby: " << ball[1] << std::endl;
    std::cout << "lx: " << lastLoc[0] << "\nly: " << lastLoc[1] << std::endl;
    std::cout << "dx: " << dx << "\ndy: " << dy << std::endl;
    std::cout << "nx: " << nx << "\nny: " << ny << std::endl;
    std::cout << "------------------\n";*/

    cv::arrowedLine(*frame, cv::Point(ball[0], ball[1]), cv::Point(nx, ny), cv::Scalar(0, 0, 255), arrowThickness);
}

void Main::processLoop(){
    cv::Mat* frame = capture->nextFrame();
    cv::Mat  hsv = *frame;
    cv::Mat rawFrame; // used for re-processing
    frame->copyTo(rawFrame);

    // check the aspect ratio to scale down
    cv::Size s = frame->size();
    float res_43 = (float)4/3;
    float frameRes = (float)s.width/s.height;    
    // if we're 4:3, update the y width of the resize
    if( frameRes == res_43 ) imgProc.resizeValue = cv::Size(imgProc.resizeValue.width, 384);

    while( loop ){
        while( !frame->empty() ){
            // create copy of original frame in case we re-process
            frame->copyTo(rawFrame);

            // detect the ball in the image and draw the first one found
            std::vector<cv::Vec3f> balls = imgProc.detectBall(*frame, hsv);
            if( balls.size() > 0 ){
                cv::Vec3f ball = balls.at(0);
                cv::circle(*frame, cv::Point((int)(ball)[0], (int)(ball)[1]), (int)(ball)[2], cv::Scalar(0, 0, 255), 3);
                if( foundBall ) drawArrow(ball, frame);
                foundBall = true;
                lastLoc = ball;
            }

            cv::imshow(vidWindow, *frame);
            cv::imshow(maskWindow, hsv);

            // if paused, use raw frame to reprocess 
            if( !play ) rawFrame.copyTo(*frame);
            else frame = capture->nextFrame();

            cv::waitKey(capture->waittime);
            //cv::waitKey(1000);
        }
        capture->reset();
        frame = capture->nextFrame();
        hsv = *frame;
        frame->copyTo(rawFrame);
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