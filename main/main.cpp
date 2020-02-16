#include "main.h"


double stateMatrixArr[] = {0, 0, 0, 0};
cv::Mat stateMatrix( cv::Size(1, 4), CV_64F, stateMatrixArr );

double hArr[] = {1,0,1,0};
cv::Mat h( cv::Size(4, 1), CV_64F, hArr);

double procCovarArr[4][4] = {
    {0.2, 0, 0, 0},
    {0, 0.2, 0, 0},
    {0, 0, 0.2, 0},
    {0, 0, 0, 0.2}
};
cv::Mat procCovar( cv::Size(4, 4), CV_64F, procCovarArr );


double stateTransArr[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};
cv::Mat stateTrans( cv::Size(4, 4), CV_64F, stateTransArr);

double pArr[4][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};
cv::Mat p( cv::Size(4, 4), CV_64F, pArr);

double obsCovarArr[] = {64,0, 64,0};
cv::Mat obsCovar( cv::Size(1, 4), CV_64F, obsCovarArr);

cv::Mat gain;

cv::Vec3f kalman( cv::Vec3f ball, std::chrono::microseconds delta){
    
    stateMatrix.at<double>(0, 0) = ball[0];
    stateMatrix.at<double>(0, 2) = ball[1];
    // set ball velocities here too   

    // set delta values in stateTrans
    stateTrans.at<double>(0, 1) = delta.count();
    stateTrans.at<double>(2, 3) = delta.count();

    // update prediction matrix
    p = stateTrans*p*stateTrans.t() + procCovar;
    // update gain matrix
    cv::Mat smc = h.t();
    std::cout << "t: " << std::endl << smc << std::endl;

    cv::Mat tmp = p * h.t();
    std::cout << "abc1" << std::endl;
    cv::Mat tmp2 = (h*p*h.t());
    std::cout << "abc2" << std::endl;
    tmp2 = tmp2 + obsCovar;
    std::cout << "abc3" << std::endl;
    tmp = tmp * tmp2;
    std::cout << "abc4" << std::endl;
    gain = p * h.t() * (h*p*h.t() + obsCovar);
    std::cout << "SMC: " << std::endl << tmp << std::endl;
    gain = tmp.inv();
    
    // update state matrix
    stateMatrix = (stateTrans*stateMatrix) + (gain*((h*stateMatrix + obsCovar)-h*stateMatrix));

    // new ball
    cv::Vec3f newBall( stateMatrix.at<double>(0, 0), stateMatrix.at<double>(0, 1), ball[2] );

    // update p for next time
    p = (cv::Mat::eye(4, 4, CV_64F) - gain*h)*p;

    return newBall;
}





bool foundBall = false;

void mouseHandler(int event,int x,int y, int flags,void* param){
    if( event == cv::EVENT_LBUTTONDOWN ){
        cv::Vec3f ball(x, y, 8);
        kalman(ball, std::chrono::microseconds(0));
    }
}



int main( int argc, char** argv ){
    ImageProcessor proc;
    CameraCapture cam;
    while( !cam.init() );

    Spinnaker::CameraPtr camera = cam.camera;

    //std::cout << camera->AcquisitionFrameRate.GetValue() << std::endl;
    
    //cv::namedWindow("hsv", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("imgOg", cv::WINDOW_NORMAL);
    cv::setMouseCallback("imgOg", mouseHandler);
    //cv::namedWindow("black", cv::WINDOW_NORMAL);
    
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
        cv::Mat blackImg(288, 512, CV_8UC3, cv::Scalar(0,0,0));
        if( !img ) continue;
        unsigned int xpad = img->GetXPadding();
        unsigned int ypad = img->GetYPadding();
        unsigned int r = img->GetWidth();
        unsigned int c = img->GetHeight();
        imgOg = cv::Mat(c + ypad, r+xpad, CV_8UC3, img->GetData(), img->GetStride());
        cv::resize(imgOg, imgOg, cv::Size(512, 288));
        std::vector<cv::Vec3f> balls = proc.detectBall(imgOg, hsvImg);
        for( unsigned int i = 0; i < balls.size(); i++ ){
            cv::Scalar col(0, 0, 255);
            //if( i == 0 ) col = cv::Scalar(255, 0, 0);
            if( i == balls.size() - 1) col = cv::Scalar(255, 0, 0);
            cv::Vec3f ball = balls.at(i);            
//cv::circle(imgOg, cv::Point((int)(*ball)[0], (int)(*ball)[1]), (int)(*ball)[2], cv::Scalar(0, 0, 255), 3),
    
            // get kalman ball
            if( foundBall ){
                ball = kalman(ball, cam.captureDelta);
            }

            cv::circle(imgOg, cv::Point((int)(ball)[0], (int)(ball)[1]), (int)(ball)[2], col, 3);


        //std::cout << (ball)[2] << std::endl;
    //cv::circle(blackImg, cv::Point((int)(ball)[0], (int)(ball)[1]), (int)(ball)[2], col, cv::FILLED);
        //std::cout << (ball)[2] << std::endl; 
        //cv::circle(hsvImg, cv::Point((int)(ball)[0], (int)(ball)[1]), (int)(ball)[2], col, 3);
        //std::cout << (ball)[2] << std::endl; 



        }
//                        delete ball;

        //std::cout << cam.captureDelta.count() << std::endl;

        /*cv::createTrackbar("lowH", "hsv", &lowH, 179);
        cv::createTrackbar("highH", "hsv", &hiH, 179);
        cv::createTrackbar("lowS", "hsv", &lowS, 255);
        cv::createTrackbar("highS", "hsv", &hiS, 255);
        cv::createTrackbar("lowV", "hsv", &lowV, 255);
        cv::createTrackbar("highV", "hsv", &hiV, 255);
        cv::createTrackbar("treshVal", "hsv", &proc.threshVal, 100);
        cv::createTrackbar("dpi", "hsv", &proc.dpi, 50);*/

        //cv::imshow("hsv", hsvImg);
        cv::imshow("imgOg", imgOg);
        //cv::imshow("black", blackImg);
        escKey = cv::waitKey(1);
    }
    

}



