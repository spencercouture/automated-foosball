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
   cout << "attemping acquisition..." << endl;
   pCamera->BeginAcquisition();
   cout << "completed acquisition" << endl;
   cv::namedWindow("tmp", cv::WINDOW_AUTOSIZE);
   char escKey = 0;
   while(true){
   cout << "grabbing image..." << endl;
   ImagePtr img = pCamera->GetNextImage();//->Convert(PixelFormat_BGR8, NEAREST_NEIGHBOR);
   if( img->IsIncomplete() ){
	cout << "image not complete" << endl;
	continue;
   }
   cout << "image status " << img->GetImageStatus() << endl;
   img = img->Convert(PixelFormat_BGR8, NEAREST_NEIGHBOR);
   cout << "grabbed image" << endl;

   cout << "setting vars..." << endl;
   unsigned int xpad = img->GetXPadding();
   unsigned int ypad = img->GetYPadding();
   unsigned int r = img->GetWidth();
   unsigned int c = img->GetHeight();
   cout << "set vars." << endl;

   cout << "converting image..." << endl;
   cv::Mat cvimg(c + ypad, r+xpad, CV_8UC3, img->GetData(), img->GetStride());
   cout << "converted image." << endl;
   cout << "releasing image..." << endl;
   //img = nullptr;
   cout << "released image." << endl;
   cv::imshow("tmp", cvimg);
   escKey = cv::waitKey(1);
   //escKey = cv::waitKey(20);
   if( escKey == 27 ) break;
   }

}

// Release system
system->ReleaseInstance();

}
