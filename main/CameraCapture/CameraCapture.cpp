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

Spinnaker::ImagePtr CameraCapture::getNextImage(){
    if( !isInit ) return nullptr;

    Spinnaker::ImagePtr img = camera->GetNextImage();
    if( img->IsIncomplete() ) return nullptr;
    img = img->Convert(Spinnaker::PixelFormat_BGR8, Spinnaker::NEAREST_NEIGHBOR);
    return img;
}

CameraCapture::~CameraCapture(){
    if( isInit ){
        system->ReleaseInstance();
    }
}
