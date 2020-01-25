#include <iostream>
#include <spinnaker/Spinnaker.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
using namespace std;
using namespace Spinnaker;

int main(){
// Retrieve singleton reference to system object
SystemPtr system = System::GetInstance();

CameraList camList = system->GetCameras();
unsigned int numCameras = camList.GetSize();
cout << numCameras << endl;
for (unsigned int i = 0; i < numCameras; ++i)
{
   CameraPtr pCamera = camList.GetByIndex(i);

   cout << "starting init..." << endl;
   pCamera->Init();
   cout << "completed init." << endl;
	
   pCamera->BeginAcquisition();
   cv::namedWindow("tmp", cv::WINDOW_AUTOSIZE);
   while(true){
   ImagePtr img = pCamera->GetNextImage()->Convert(PixelFormat_BGR8, NEAREST_NEIGHBOR);

   unsigned int xpad = img->GetXPadding();
   unsigned int ypad = img->GetYPadding();
   unsigned int r = img->GetWidth();
   unsigned int c = img->GetHeight();

   cv::Mat cvimg(c + ypad, r+xpad, CV_8UC3, img->GetData(), img->GetStride());

   cv::imshow("tmp", cvimg);
   cv::waitKey(1);

   }

}

// Release system
//system->ReleaseInstance();

}
