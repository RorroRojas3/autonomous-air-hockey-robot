// OpenCVCam.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// These three header files required by OpenCV 
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "time.h"
#include "iostream"
// Header for the PSEye
#include "CLEyeMulticam.h"

#define FRAME_RATE		60
#define FRAME_SIZE		CLEYE_VGA
#define FRAME_FORMAT	CLEYE_COLOR_RAW

typedef struct{
	CLEyeCameraInstance CameraInstance;
	PBYTE FramePointer;
}CAMERA_AND_FRAME;

static DWORD WINAPI CaptureThread(LPVOID ThreadPointer);

CLEyeCameraInstance setup_camera(int *width, int *height)
{
	// Variable Declaration Section
	CLEyeCameraInstance ps3_camera;
	int number_of_cameras;
	GUID camera_id;
	int temp_width;
	int temp_height;

	number_of_cameras = CLEyeGetCameraCount();
	if (number_of_cameras != 0)
	{
		printf("Number of camera's detected: %d\r\n", number_of_cameras);
	}
	else
	{
		printf("Error, no camera detected, press any key to exit\r\n");
		getchar();
		assert(number_of_cameras != 0);
		return NULL;
	}

	camera_id = CLEyeGetCameraUUID(0);

	ps3_camera = CLEyeCreateCamera(camera_id, FRAME_FORMAT, FRAME_SIZE, FRAME_RATE);
	assert(ps3_camera != NULL);

	CLEyeSetCameraParameter(ps3_camera, CLEYE_EXPOSURE, 511);
	CLEyeSetCameraParameter(ps3_camera, CLEYE_GAIN, 0);

	// Get camera frame dimensions;
	CLEyeCameraGetFrameDimensions(ps3_camera, temp_width, temp_height);
	*width = temp_width;
	*height = temp_height;

	// Create a window in which the captured images will be presented
	cvNamedWindow("PS3 Camera", CV_WINDOW_AUTOSIZE);

	return ps3_camera;
}

int _tmain(int argc, _TCHAR* argv[])
{

	///////MY VARS////////
	PBYTE frame_pointer = NULL;
	int width,height,CameraCount,FramerCounter=0;
	CLEyeCameraInstance ps3_camera=NULL;
	GUID CameraID;
	IplImage *frame;
	clock_t StartTime,EndTime;
	CAMERA_AND_FRAME ThreadPointer;
	HANDLE _hThread;
	//////////////////////

	ps3_camera = setup_camera(&width, &height);
	
	//Make a image to hold the frames captured from the camera
	frame = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 4);

	// GetPointer To Image Data For frame
	cvGetImageRawData(frame, &frame_pointer);

	//Start the eye camera
	CLEyeCameraStart(ps3_camera);

	//Need to copy vars into one var to launch the second thread
	ThreadPointer.CameraInstance= ps3_camera;
	ThreadPointer.FramePointer= frame_pointer;

	//Launch thread and confirm its running
	_hThread = CreateThread(NULL, 0, &CaptureThread, &ThreadPointer, 0, 0);
	if(_hThread == NULL)
	{
		printf("Error, failed to create thread, press any key to terminate program.\r\n");
		getchar();
		return false;
	}


	while( 1 )
	{
		//Display the captured frame
		cvShowImage("PS3 Camera", frame);
		
		// If ESC pressed, programs terminates
		if ((cvWaitKey(1) & 255) == 27)
		{
			break;
		}
	}
	
	CLEyeCameraStop(ps3_camera);
	CLEyeDestroyCamera(ps3_camera);
	ps3_camera = NULL;
	cvDestroyWindow( "Camera" );

	return 0;
}

static DWORD WINAPI CaptureThread(LPVOID ThreadPointer)
{
	CAMERA_AND_FRAME *Instance = (CAMERA_AND_FRAME*)ThreadPointer;
	CLEyeCameraInstance Camera= Instance->CameraInstance;
	PBYTE FramePtr= Instance->FramePointer;
	int FramerCounter=0;
	clock_t StartTime,EndTime;
	while(1)
	{
		//Get Frame From Camera
		CLEyeCameraGetFrame(Camera,FramePtr);

		// put your vision code here

		// Track FPS
		if (FramerCounter == 0)
		{
			StartTime = clock();
		}
		FramerCounter++;
		EndTime=clock();
		if((EndTime-StartTime)/CLOCKS_PER_SEC>=1)
		{
			printf("FPS: %d\n",FramerCounter);
			FramerCounter=0;
		}
	}
	return 0;
}

