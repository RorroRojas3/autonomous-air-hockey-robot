// Library Declaration Section
#include "stdafx.h"
#include "PSEyeDemo.h"
#include <stdlib.h>


// Namespace Declaration Section
using namespace std; 
using namespace cv; 

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
RNG rng(12345);


// Typedefs
typedef vector<Point2f> Point2fVector;

// Global Variables
int low_H = 0, low_S = 0, low_V = 0;
int high_H = MAX_VALUE_H, high_S = MAX_VALUE, high_V = MAX_VALUE;
int erosion_val = 0;
int dilation_val = 0;
int minThresh = 0;
int maxTresh = 255;
int i = 0;
Mat frame;
Mat current_frame;
Mat hsv_frame;
Mat frame_threshold;
Mat blur_frame;
Mat unwarp_frame;
Mat binary;
Mat contour_out;
vector <vector<Point>> contour;
vector<Vec4i> hierarchy;
Mat drawing;
Mat_<double> H;
Moments moment;
Point2f centroid;
Point2fVector points;
Point2fVector points2;
vector<Vec3f> circles;


#define FRAME_RATE 60
#define RESOLUTION CLEYE_VGA

// Structure Definition Section
typedef struct
{
	CLEyeCameraInstance CameraInstance;
	Mat *frame;
	unsigned char *FramePtr;
	int Threshold;
} CAMERA_AND_FRAME;

/*** UDP PACKAGE STRUCTS ***/
struct PACKIN
{
	float flt1;
	float flt2;
};
struct PACKOUT
{
	float flt1;
	float flt2;
};

static DWORD WINAPI CaptureThread(LPVOID ThreadPointer);

/*** HSV TRACKBAR CALLBACK FUNCTIONS ***/
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

/*** ERODE CALLBACK FUNCTION ***/
static void erode_video(int , void *)
{
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2 * erosion_val + 1, 2 * erosion_val + 1), Point(erosion_val, erosion_val));
	erode(binary, binary, element);
}

/*** DILUTE CALLBACK FUNCTION ***/
static void dilute_video(int, void *)
{
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2 * dilation_val + 1, 2 * dilation_val + 1), Point(dilation_val, dilation_val));
	dilate(binary, binary, element);
}

/*** CREATES TRACKBARS FOR HSV VALUES ***/
void hsv_trackbars()
{
	namedWindow(HSV_WINDOW_NAME, CV_WINDOW_NORMAL);
	resizeWindow(HSV_WINDOW_NAME, 400, 400);
	createTrackbar("Low H", HSV_WINDOW_NAME, &low_H, MAX_VALUE_H, low_H_callBack);
	createTrackbar("High H", HSV_WINDOW_NAME, &high_H, MAX_VALUE_H, high_H_callBack);
	createTrackbar("Low S", HSV_WINDOW_NAME, &low_S, MAX_VALUE, low_S_callBack);
	createTrackbar("High S", HSV_WINDOW_NAME, &high_S, MAX_VALUE, high_S_Callback);
	createTrackbar("Low V", HSV_WINDOW_NAME, &low_V, MAX_VALUE, low_V_callBack);
	createTrackbar("High V", HSV_WINDOW_NAME, &high_V, MAX_VALUE, high_V_callBack);
}

/*** CREATES TRACKBAR FOR EROSION VALUE ***/
void erosion_trackbars()
{
	namedWindow(EROSION_WINDOW_NAME, CV_WINDOW_NORMAL);
	createTrackbar("Kernel Size [2n + 1]", EROSION_WINDOW_NAME, &erosion_val, MAX_KERNEL_SIZE, erode_video);
}

/*** CREATES DILATION FOR EROSION VALUE ***/
void dilation_trackbars()
{
	namedWindow(DILUTION_WINDOW_NAME, CV_WINDOW_NORMAL);
	createTrackbar("Kernel Size [2n + 1]", DILUTION_WINDOW_NAME, &erosion_val, MAX_KERNEL_SIZE, dilute_video);
}

/*** ALLOWS USER TO PICK FOUR POINTS FROM PS3 CAMERA FRAME ***/
void MousCallback(int mEvent, int x, int y, int flags, void* param)
{
	Point2fVector* pPointVec = (Point2fVector*)param;
	if (mEvent == CV_EVENT_LBUTTONDOWN)
	{
		pPointVec->push_back(Point2f(float(x), float(y)));
	}
}

/*** CALCULATES HOMOGRAPHY  ***/
void calc_homography(CLEyeCameraInstance *ps3_camera)
{
	// Get current frame from PS3 camera
	for (int i = 0; i < 5; i++)
	{
		CLEyeCameraGetFrame(*ps3_camera, frame.data);
	}

	// Create a window and display the PS3 current frame
	namedWindow("Homography Camera", CV_WINDOW_AUTOSIZE);
	imshow("Homography Camera", frame);

	// Asks user to pick four points from Homography window (top-left, top-right, bottom-right, bottom-left)
	//MessageBoxA(NULL, "Please click four corners of the table", "Click", MB_OK);
	cvSetMouseCallback("Homography Camera", MousCallback, (void *)&points);

	// Waits until the user has clicked the four points
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
	points2.push_back(Point2f(0, 0));
	points2.push_back(Point2f(0, 480));
	points2.push_back(Point2f(640, 480));
	points2.push_back(Point2f(640, 0));

	// Calculate homography
	H = findHomography((points), (points2));
}

/*** TERMINATES PS3 CAMERA ***/
void terminate_ps3camera(CLEyeCameraInstance *ps3_camera)
{
	CLEyeCameraStop(ps3_camera);
	CLEyeDestroyCamera(ps3_camera);
	ps3_camera = NULL;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Variable Declaration Section
	int width, height;
	int press_key;
	CLEyeCameraInstance ps3_camera = NULL;
	CAMERA_AND_FRAME ThreadPointer;
	HANDLE _hThread;
	CLEyeCameraParameter CamCurrentParam=(CLEyeCameraParameter)0;
	bool CamParam=0;

	/*** PS3 CAMERA SETUP ***/
	ps3_camera = StartCam(FRAME_RATE,RESOLUTION);//this does all the commented out code

	// Get camera frame dimensions;
	CLEyeCameraGetFrameDimensions(ps3_camera, width, height);

	// Create a window in which the captured images will be presented
	namedWindow("PS3 Camera", CV_WINDOW_AUTOSIZE);
	namedWindow("Threshold Camera", CV_WINDOW_AUTOSIZE);
	namedWindow("Drawing", CV_WINDOW_AUTOSIZE);

	//Make a image to hold the frames captured from the camera
	frame = Mat(height, width, CV_8UC4);//8 bit unsiged 4 channel image for Blue Green Red Alpa (8 bit elements per channel)
	
	//Start the eye camera
	CLEyeCameraStart(ps3_camera);

	/*** ALGORITHM STARTS HERE ***/

	// Pick four points on Homography 
	calc_homography(&ps3_camera);

	// Copies variables for the new thread to be created 
	ThreadPointer.CameraInstance = ps3_camera;
	ThreadPointer.frame = &frame;
	ThreadPointer.Threshold = 0;

	//Creates a new thread which continously works with the PS3 camera frames
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
		press_key = waitKey(1);
		switch (press_key)
		{
			case 27: //escape pressed
				return 0;
				break;
			default: //do nothing
				break;
		}

		imshow("PS3 Camera", frame);
		imshow("Threshold Camera", binary);
		imshow("Drawing", unwarp_frame);
	}
	
	/*** CLOSES CAMERA  ***/
	terminate_ps3camera(&ps3_camera);

	return 0;
}

//for high frame rates you will process images here the main function will allow interactions and display only
static DWORD WINAPI CaptureThread(LPVOID ThreadPointer)
{
	CAMERA_AND_FRAME *Instance=(CAMERA_AND_FRAME*)ThreadPointer; //type cast the void pointer back to the proper type so we can access its elements

	int FramerCounter=0;
	Mat CamImg=Mat(*(Instance->frame)).clone();
	clock_t StartTime, EndTime; 

	while(1)
	{
		//Get frame From Camera
		CLEyeCameraGetFrame(Instance->CameraInstance, CamImg.data);

		// Homography frame
		warpPerspective(CamImg, unwarp_frame, H, CamImg.size());

		// DO YOUR IMAGE PROCESSING HERE
		cvtColor(unwarp_frame, hsv_frame, CV_BGR2HSV);
		//cvtColor(CamImg, hsv_frame, CV_RGB2HSV);

		// Changes value of HSV video
		inRange(hsv_frame, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);

		// Blurr video
		//GaussianBlur(frame_threshold, blur_frame, Size(9, 9), 2, 2);
		threshold(frame_threshold, binary, minThresh, maxTresh, THRESH_BINARY);

		// Starting point to erode video
		erode_video(0, 0);

		// Starting point to dilute video
		dilute_video(0, 0);

		// Find the puck and draw contour on it
		findContours(binary.clone(), contour, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		
		if (contour.size() == 1)
		{
			//contour_out = Mat(binary.clone().size(), CV_8UC3);
			moment = moments(contour[0], false);
			centroid = Point2f(moment.m10 / moment.m00, moment.m01 / moment.m00);
			//centroid coordinates
			printf("%.2f %.2f\n", centroid.x, centroid.y);
			for (i = 0; i < contour.size(); i++)
			{
				Scalar color = Scalar(255, 0, 0);
				drawContours(unwarp_frame, contour, i, color, 2, 8, hierarchy, 0, Point());
			}
		}

		//copy it to main thread image.
		*(Instance->frame) = CamImg;

		// Track FPS
		if (FramerCounter == 0)
		{
			StartTime = clock();
		}
		FramerCounter++;
		EndTime=clock();
		if((EndTime-StartTime)/CLOCKS_PER_SEC>=1)
		{
			cout << "FPS:" << FramerCounter << endl;
			FramerCounter=0;
		}

	}
	return 0;
}

