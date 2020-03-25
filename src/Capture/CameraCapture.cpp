#include "Capture.h"
#include "CameraCapture.h"

bool CameraCapture::init(){
    try{
        // intialize the system
        system = Spinnaker::System::GetInstance();
        
        // find the camera
        Spinnaker::CameraList camList = system->GetCameras();
        // if no cameras, return false
        if( camList.GetSize() < 1 ) return false;

        camera = camList.GetByIndex(0);
	camera->Init();
	camera->BeginAcquisition();
    }
    catch( Spinnaker::Exception e ){
        std::cout << "Spinnaker error: " << e.what();
        return false;
    }
    isInit = true;
    return true;
}

cv::Mat* CameraCapture::nextFrame(){
    if( !isInit ) return nullptr;
    

    Spinnaker::ImagePtr img = camera->GetNextImage();
    if( img->IsIncomplete() ) return nullptr;
    img = img->Convert(Spinnaker::PixelFormat_BGR8, Spinnaker::NEAREST_NEIGHBOR);

    std::chrono::time_point<std::chrono::high_resolution_clock> newTime = std::chrono::high_resolution_clock::now();
    if( isCapturing )
        captureDelta = std::chrono::duration_cast<std::chrono::microseconds>( newTime - lastCaptureTime);
    else
        isCapturing = true;
    
    lastCaptureTime = newTime;

    return nullptr;
}

CameraCapture::~CameraCapture(){
    if( isInit ){
        system->ReleaseInstance();
    }
}
