// OpenCVCam.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PSEyeDemo.h"

using namespace std; //allows aceess to all std lib functions without using the namespace std::
using namespace cv; // allows ... without using namespace cv::

// Constant Variable Declaration Section
const int MAX_VALUE_H = 180;
const int MAX_VALUE = 255;
const String HSV_WINDOW_NAME = "HSV Values";
const String EROSION_WINDOW_NAME = "Erosion Values";
const String DILUTION_WINDOW_NAME = "Dilusion Values";
const String DILUTE_WINDOW_NAME = "Dilute Values";
const String CAMERA_WINDOW_NAME = "PS3 Camera";
int const MAX_KERNEL_SIZE = 21;
double const scale = 5.0;
int erosion_val = 0;
int dilation_val = 0;

// Typedefs
typedef vector<Point2f> Point2fVector;

// Global Variables
int low_H = 0, low_S = 0, low_V = 0;
int high_H = MAX_VALUE_H, high_S = MAX_VALUE, high_V = MAX_VALUE;
Mat current_frame;
Mat hsv_frame;
Mat frame_threshold;
Mat blur_frame;
Mat unwarp_frame;
Mat_<double> H;
Point2fVector points;
Point2fVector points2;
Mat Frame;

#define FRAME_RATE 60
#define RESOLUTION CLEYE_VGA

typedef struct
{
	CLEyeCameraInstance CameraInstance;
	Mat *Frame;
	unsigned char *FramePtr;
	int Threshold;
} CAMERA_AND_FRAME;

static DWORD WINAPI CaptureThread(LPVOID ThreadPointer);

static void low_H_callBack(int, void *)
{
	low_H = min(high_H - 1, low_H);
	setTrackbarPos("Low H", HSV_WINDOW_NAME, low_H);
}
static void high_H_callBack(int, void *)
{
	high_H = max(high_H, low_H + 1);
	setTrackbarPos("High H", HSV_WINDOW_NAME, high_H);
}
static void low_S_callBack(int, void *)
{
	low_S = min(high_S - 1, low_S);
	setTrackbarPos("Low S", HSV_WINDOW_NAME, low_S);
}
static void high_S_Callback(int, void *)
{
	high_S = max(high_S, low_S + 1);
	setTrackbarPos("High S", HSV_WINDOW_NAME, high_S);
}
static void low_V_callBack(int, void *)
{
	low_V = min(high_V - 1, low_V);
	setTrackbarPos("Low V", HSV_WINDOW_NAME, low_V);
}
static void high_V_callBack(int, void *)
{
	high_V = max(high_V, low_V + 1);
}

static void erode_video(int , void *)
{
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2 * erosion_val + 1, 2 * erosion_val + 1), Point(erosion_val, erosion_val));
	erode(frame_threshold, frame_threshold, element);
}

static void dilute_video(int, void *)
{
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2 * dilation_val + 1, 2 * dilation_val + 1), Point(dilation_val, dilation_val));
	dilate(frame_threshold, frame_threshold, element);
}

// Creates HSV video Trackbars
void hsv_trackbars()
{
	namedWindow(HSV_WINDOW_NAME);
	createTrackbar("Low H", HSV_WINDOW_NAME, &low_H, MAX_VALUE_H, low_H_callBack);
	createTrackbar("High H", HSV_WINDOW_NAME, &high_H, MAX_VALUE_H, high_H_callBack);
	createTrackbar("Low S", HSV_WINDOW_NAME, &low_S, MAX_VALUE, low_S_callBack);
	createTrackbar("High S", HSV_WINDOW_NAME, &high_S, MAX_VALUE, high_S_Callback);
	createTrackbar("Low V", HSV_WINDOW_NAME, &low_V, MAX_VALUE, low_V_callBack);
	createTrackbar("High V", HSV_WINDOW_NAME, &high_V, MAX_VALUE, high_V_callBack);
}

// Creates Erosion video Trackbars
void erosion_trackbars()
{
	namedWindow(EROSION_WINDOW_NAME);
	createTrackbar("Kernel Size [2n + 1]", EROSION_WINDOW_NAME, &erosion_val, MAX_KERNEL_SIZE, erode_video);
}

// Creates Dilusion video Trackbars
void dilation_trackbars()
{
	namedWindow(DILUTION_WINDOW_NAME);
	createTrackbar("Kernel Size [2n + 1]", DILUTION_WINDOW_NAME, &erosion_val, MAX_KERNEL_SIZE, dilute_video);
}

void MousCallback(int mEvent, int x, int y, int flags, void* param)
{
	Point2fVector* pPointVec = (Point2fVector*)param;
	if (mEvent == CV_EVENT_LBUTTONDOWN)
	{
		pPointVec->push_back(Point2f(float(x), float(y)));
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Variable Declaration Section
	int Width,Height;
	int KeyPress;
	CLEyeCameraInstance EyeCamera=NULL;
	CAMERA_AND_FRAME ThreadPointer;
	HANDLE _hThread;
	CLEyeCameraParameter CamCurrentParam=(CLEyeCameraParameter)0;
	bool CamParam=0;
	

	//////////////////////

	//////////////////// EYE CAMERA SETUP///////////////////////////////////
	// all of this code and more is included in my header file CameraControl.h hence why its commented out
	// I left it here simply for your reference
	EyeCamera=StartCam(FRAME_RATE,RESOLUTION);//this does all the commented out code

	// Get camera frame dimensions;
	CLEyeCameraGetFrameDimensions(EyeCamera, Width, Height);
	// Create a window in which the captured images will be presented
	namedWindow( "Camera", CV_WINDOW_AUTOSIZE );
	namedWindow("Threshold", CV_WINDOW_AUTOSIZE);
	//Make a image to hold the frames captured from the camera
	Frame = Mat(Height, Width, CV_8UC4);//8 bit unsiged 4 channel image for Blue Green Red Alpa (8 bit elements per channel)
	//Start the eye camera
	CLEyeCameraStart(EyeCamera);

	/////////////////////////////////////MAIN CODE//////////////////////////////////////
	

	//Need to copy vars into one var to launch the second thread
	ThreadPointer.CameraInstance = EyeCamera;
	ThreadPointer.Frame = &Frame;
	ThreadPointer.Threshold = 0;

	//Launch thread and confirm its running
	_hThread = CreateThread(NULL, 0, &CaptureThread, &ThreadPointer, 0, 0);
	if(_hThread == NULL)
	{
		printf("Failed to create thread...");
		getchar();
		return false;
	}

	/* CREATE TRACK BAR FOR HSV THRESHOLD VALUES*/
	hsv_trackbars();

	/* CREATE TRACK BAR FOR EROSION THRESHOLD VALUES*/
	erosion_trackbars();

	/* CREATE TRACK BAR FOR DILUSION THRESHOLD VALUES*/
	dilation_trackbars();
	
	while( 1 ) 
	{
		
		//This will capture keypresses and do whatever you want if you assign the appropriate actions to the right key code
		KeyPress = waitKey(1);
		switch (KeyPress)
		{
			case 27: //escape pressed
				return 0;
				break;
			default: //do nothing
				break;
		}

		imshow("Camera", Frame);
		imshow("Threshold", frame_threshold);
	}
	
	CLEyeCameraStop(EyeCamera);
	CLEyeDestroyCamera(EyeCamera);
	EyeCamera = NULL;

	return 0;
}

///////////////////////SUB THREAD///////////////////////////
//for high frame rates you will process images here the main function will allow interactions and display only
static DWORD WINAPI CaptureThread(LPVOID ThreadPointer)
{
	CAMERA_AND_FRAME *Instance=(CAMERA_AND_FRAME*)ThreadPointer; //type cast the void pointer back to the proper type so we can access its elements

	int FramerCounter=0;
	Mat CamImg=Mat(*(Instance->Frame)).clone();

	clock_t StartTime, EndTime; 

	// Pick four points on Homography 
	/*namedWindow("Homography Camera", CV_WINDOW_AUTOSIZE);
	cvShowImage("Homography Camera", &(IplImage)CamImg);
	MessageBoxA(NULL, "Please click four corners of the table", "Click", MB_OK);
	cvSetMouseCallback("Homography Camera", MousCallback, &points);

	while (1)
	{
		// wait for mouse clicks
		waitKey(10);
		if (points.size() == 4)
		{
			break;
		}
	}

	// Calculate Homography matrix
	points2.push_back(Point2f(0.0, 2000.0 / scale));
	points2.push_back(Point2f(1200.0 / scale, 2000.0 / scale));
	points2.push_back(Point2f(1200.0 / scale, 0.0));
	points2.push_back(Point2f(0.0, 0.0));
	H = findHomography(Mat(points), Mat(points2));*/

	while(1)
	{
		//if (points.size() == 4)
		//{
			//Get Frame From Camera
			CLEyeCameraGetFrame(Instance->CameraInstance, CamImg.data);

			// Homography frame
			//warpPerspective(CamImg, unwarp_frame, H, Size(1200.0 / scale, 2000.0 / scale));

			// DO YOUR IMAGE PROCESSING HERE
			cvtColor(CamImg, hsv_frame, CV_RGB2HSV);

			inRange(hsv_frame, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);

			// Starting point to erode video
			erode_video(0, 0);

			// Starting point to dilute video
			dilute_video(0, 0);

			GaussianBlur(frame_threshold, blur_frame, Size(9, 9), 2, 2);
			vector<Vec3f> circles;

			HoughCircles(blur_frame, circles, CV_HOUGH_GRADIENT, 1, frame_threshold.rows / 8, 200, 15, 125, 130);

			if (circles.size() == 1)
			{
				cout << "Circle size: " << circles.size() << endl;
				Point center(cvRound(circles[0][0]), cvRound(circles[0][1]));
				int radius = cvRound(circles[0][2]);
				circle(CamImg, center, 3, Scalar(0, 0, 255), -1, 8, 0);
				circle(CamImg, center, radius, Scalar(0, 0, 255), 3, 8, 0);
			}

			//copy it to main thread image.
			*(Instance->Frame) = CamImg;
		//}

		// Track FPS
		if (FramerCounter == 0)
		{
			StartTime = clock();
		}
		FramerCounter++;
		EndTime=clock();
		if((EndTime-StartTime)/CLOCKS_PER_SEC>=1)
		{
			//cout << "FPS:" << FramerCounter << endl;
			FramerCounter=0;
		}

	}
	return 0;
}

