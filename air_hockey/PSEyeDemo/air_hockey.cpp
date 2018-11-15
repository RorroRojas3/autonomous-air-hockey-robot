/* LIBRARY DECLARATION SECTION*/
#include "stdafx.h"
#include <winsock2.h>
#include "PSEyeDemo.h"
#include <math.h>
#include <stdlib.h>
#include "xPCUDPSock.h"

/* UDP STRUCTURES */
#pragma pack(push,1) 

struct PACKIN
{
	float flt1;
	float flt2;
	float flt3;
	float flt4;
	float flt5;
	float flt6;
};

struct PACKOUT
{
	float flt1;
	float flt2;
	float flt3;
	float flt4;
	float flt5;
	float flt6;
};

#pragma pack(pop) 

/* NAMESPACE DECLARATION SECTION */
using namespace std;
using namespace cv;

/* CONSTANT VARIABLE DECLARATION SECTION*/
const int MAX_VALUE_H = 180;
const int MAX_VALUE = 255;
const float	STEPS_WIDTH_X = 70;										// Number of steps to move across board in x-direction
const float STEPS_LENGTH_Y = 60;											// Number of steps to move across board in y-direction
const float BOARD_WIDTH = 26;												// board width in inches
const float	BOARD_LENGTH = 53;												// board length in inches
const String CAMERA_WINDOW_NAME = "PS3 Camera";
int const MAX_KERNEL_SIZE = 21;
double const scale = 5.0;
RNG rng(12345);

/* TYPEDEF DECLARATION SECTION */
typedef vector<Point2f> Point2fVector;
// Global Variables
int minThresh = 0;
int maxTresh = 255;
int i = 0;
Mat frame;
Mat hsv_frame;
Mat frame_threshold;
Mat unwarp_frame;
vector<Vec4i> hierarchy;
Mat drawing;
Mat_<double> H;
Moments moment;
Point2f centroid;
Point2fVector points;
Point2fVector points2;
vector<Vec3f> circles;
float xSteps_per_pixel = STEPS_WIDTH_X / ((26.0 / BOARD_WIDTH)*480.0);
float ySteps_per_pixel = STEPS_LENGTH_Y / ((19.0 / BOARD_LENGTH)*640.0);
float xPixels_per_inch = 480.0 / BOARD_WIDTH;
float yPixels_per_inch = 640.0 / BOARD_LENGTH;

/* DEFINES DECLARATION SECTION*/
#define FRAME_RATE 60
#define RESOLUTION CLEYE_VGA
#define M_PI   3.14159265358979323846264338327950288
#define PUCK_HUE_INIT {94, 53}
#define PUCK_SATURATION_INIT {140, 42}
#define PUCK_VALUE_INIT {255, 50}
#define PUCK_ERODE 1
#define PUCK_DILUTE 5

#define PADDLE_HUE_INIT {112, 99}
#define PADDLE_SATURATION_INIT {140, 54}
#define PADDLE_VALUE_INIT {227, 0}
#define PADDLE_ERODE 1
#define PADDLE_DILUTE 1
#define BLUE_LINE 17
#define OFFENSIVE_LINE 10

/* CAMERA STRCUTS (GIVEN TO US) */
typedef struct
{
	CLEyeCameraInstance CameraInstance;
	Mat *frame;
	unsigned char *FramePtr;
	int Threshold;
} CAMERA_AND_FRAME;

static DWORD WINAPI CaptureThread(LPVOID ThreadPointer);

typedef struct track_bar_parameters
{
	int high_value;
	int low_value;
}hsv_params;

/* STRUCTURE FOR TRACKBARS VALUES */
struct image_info
{
	Mat binary;
	Mat unwarp_frame;
	vector <vector<Point>> contour;
	hsv_params hue;
	hsv_params sat;
	hsv_params value;
	int erode_val = 0;
	int dilate_val = 0;
};
struct image_info puck;
struct image_info paddle;

/*** ERODE CALLBACK FUNCTION ***/
static void erode_video(Mat binary, int erosion_val)
{
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2 * erosion_val + 1, 2 * erosion_val + 1), Point(erosion_val, erosion_val));
	erode(binary, binary, element);
}

/*** DILUTE CALLBACK FUNCTION ***/
static void dilute_video(Mat binary, int dilation_val)
{
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2 * dilation_val + 1, 2 * dilation_val + 1), Point(dilation_val, dilation_val));
	dilate(binary, binary, element);
}

/* CREATES TRACKBAR FOR HSV VALUES*/
static void create_hsv_trackbars(const char* window_name, struct image_info *block)
{
	namedWindow(window_name, CV_WINDOW_NORMAL);
	resizeWindow(window_name, 400, 400);
	createTrackbar("Low H", window_name, &block->hue.low_value, MAX_VALUE_H, NULL);
	createTrackbar("High H", window_name, &block->hue.high_value, MAX_VALUE_H, NULL);
	createTrackbar("Low S", window_name, &block->sat.low_value, MAX_VALUE, NULL);
	createTrackbar("High S", window_name, &block->sat.high_value, MAX_VALUE, NULL);
	createTrackbar("Low V", window_name, &block->value.low_value, MAX_VALUE, NULL);
	createTrackbar("High V", window_name, &block->value.high_value, MAX_VALUE, NULL);
	createTrackbar("Erosion", window_name, &block->erode_val, MAX_KERNEL_SIZE, NULL);
	createTrackbar("Dilation", window_name, &block->dilate_val, MAX_KERNEL_SIZE, NULL);
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
		if (points.size() == 5)
		{
			break;
		}
	}
	double x_point = 4.0 + (7.0 / 16.0);
	double y_point = 9.5;

	// Calculate Homography matrix
	points2.push_back(Point2f((y_point / BOARD_LENGTH) * 640, (x_point / BOARD_WIDTH) * 480));
	points2.push_back(Point2f((y_point / BOARD_LENGTH) * 640, ((BOARD_WIDTH - x_point) / BOARD_WIDTH) * 480));
	points2.push_back(Point2f(((BOARD_LENGTH - y_point) / BOARD_LENGTH) * 640, ((BOARD_WIDTH - x_point) / BOARD_WIDTH) * 480));
	points2.push_back(Point2f(((BOARD_LENGTH - y_point) / BOARD_LENGTH) * 640, (x_point / BOARD_WIDTH) * 480));
	points2.push_back(Point2f((26.0 / BOARD_LENGTH) * 640, (13.0 / BOARD_WIDTH) * 480));

	// Calculate homography
	H = findHomography((points), (points2));
}

/* SETS PACKET VALUES IN UDP PACKET IN ORDER TO RESET MOTORS */
void reset_motor(CUDPSender sender, PACKOUT *pkout)
{
	pkout->flt1 = 2;
	pkout->flt2 = 2;
	pkout->flt3 = 0; // steps
	pkout->flt4 = 2;
	pkout->flt5 = 2;
	pkout->flt6 = 0; // steps
}

/* SETS PACKET VALUES IN UDP IN ORDER TO MOVE MOTORS IN STEPS*/
void set_motor_steps(PACKOUT *pkout, int steps, char axis)
{
	if (axis == 'x')
	{
		// direction
		pkout->flt1 = steps < 0 ? 0 : 1;
		pkout->flt2 = steps < 0 ? 1 : 0;
		// value of steps
		pkout->flt3 = abs(steps) + 1;
	}
	else if (axis == 'y')
	{
		//y - direction
		if (steps == 0)
		{
			pkout->flt4 = 2;
			pkout->flt5 = 2;
			pkout->flt6 = 0;
		}
		else
		{
			pkout->flt4 = steps < 0 ? 1 : 0;
			pkout->flt5 = steps < 0 ? 0 : 1;
			// y steps
			pkout->flt6 = abs(steps) + 1;
		}

	}
	else
	{
		printf("Please specify which axis to set (X or Y)\n");
	}
}

/* DETERMINES THE X-VALUE COORDINATE OF THE PUCK */
float find_x_position(float angle, float target_y, float current_x, float current_y, FILE * fpt)
{
	float LEFT_WALL = 20.0 / xPixels_per_inch;
	float RIGHT_WALL = 460.0 / xPixels_per_inch;
	float x_diff, y_diff, y_wall, new_x;
	Point start, predicted;
	do
	{
		x_diff = (target_y - current_y) / tanf(angle);
		new_x = current_x + x_diff;
		fprintf(fpt, "New x:  %f  Current x: %f Current y: %f x_diff:  %f Angle %.2f\n", new_x, current_x, current_y, x_diff, angle);

		// is the new x off of the table
		if (new_x < LEFT_WALL || new_x > RIGHT_WALL)
		{
			start.x = current_y * yPixels_per_inch;
			start.y = current_x * xPixels_per_inch;
			if (new_x < LEFT_WALL)
			{
				y_diff = (LEFT_WALL - current_x) * tanf(angle);
				y_wall = current_y + y_diff;
				fprintf(fpt, "Hit the left wall at %f\n", y_wall);
				current_x = LEFT_WALL;
			}
			else if (new_x > RIGHT_WALL)
			{
				y_diff = (RIGHT_WALL - current_x) * tanf(angle);
				y_wall = current_y + y_diff;
				fprintf(fpt, "Hit the right wall at %f\n", y_wall);
				current_x = RIGHT_WALL;
			}
			angle = -M_PI - angle;
			current_y = y_wall;

			predicted.x = current_y * yPixels_per_inch;
			predicted.y = current_x * xPixels_per_inch;
			//printf("Angle %.2f AvG_Angle %.2f Dist: %.3f Curr_X %.2f Curr_Y %.2f Pred. Position %.2f Avg Pred %.2f\n", angle, avg_angle, dist, puckX_in, puckY_in, predicted_puckX, avg_prediction);
			line(unwarp_frame, start, predicted, Scalar(0, 255, 0), 2, 8, 0);
		}

	} while (new_x < LEFT_WALL || new_x > RIGHT_WALL);

	return new_x;
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
	CLEyeCameraParameter CamCurrentParam = (CLEyeCameraParameter)0;
	bool CamParam = 0;

	/*** PS3 CAMERA SETUP ***/
	ps3_camera = StartCam(FRAME_RATE, RESOLUTION);

	// Get camera frame dimensions;
	CLEyeCameraGetFrameDimensions(ps3_camera, width, height);

	// Create a window in which the captured images will be presented
	namedWindow("PS3 Camera", CV_WINDOW_AUTOSIZE);
	namedWindow("Paddle Binary Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Puck Binary Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Paddle/Puck Contours", CV_WINDOW_AUTOSIZE);

	//Make a image to hold the frames captured from the camera
	frame = Mat(height, width, CV_8UC4);

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
	if (_hThread == NULL)
	{
		printf("Failed to create thread...");
		getchar();
		return false;
	}

	// Sets value of Puck and Paddle structures and creates it's trackbars
	puck.hue = PUCK_HUE_INIT;
	puck.sat = PUCK_SATURATION_INIT;
	puck.value = PUCK_VALUE_INIT;
	puck.erode_val = PUCK_ERODE;
	puck.dilate_val = PUCK_DILUTE;
	paddle.hue = PADDLE_HUE_INIT;
	paddle.sat = PADDLE_SATURATION_INIT;
	paddle.value = PADDLE_VALUE_INIT;
	paddle.erode_val = PADDLE_ERODE;
	paddle.dilate_val = PADDLE_DILUTE;
	create_hsv_trackbars("Puck Values", &puck);
	create_hsv_trackbars("Paddle Values", &paddle);

	while (1)
	{
		press_key = waitKey(1);
		switch (press_key)
		{
		case 27:
			return 0;
			break;
		default:
			break;
		}

		// SHOWS CURRENT VIDEO FOR DIFFERENT FRAMES
		imshow("PS3 Camera", frame);
		imshow("Puck Binary Image", puck.binary);
		imshow("Paddle Binary Image", paddle.binary);

	}

	/*** CLOSES CAMERA  ***/
	terminate_ps3camera(&ps3_camera);

	return 0;
}

//for high frame rates you will process images here the main function will allow interactions and display only
static DWORD WINAPI CaptureThread(LPVOID ThreadPointer)
{
	// Variable Declaration Section
	CAMERA_AND_FRAME *Instance = (CAMERA_AND_FRAME*)ThreadPointer; //type cast the void pointer back to the proper type so we can access its elements
	int FramerCounter = 0;
	int num_frames = 0;
	float x, y, x_in, y_in;
	int matches = 0;
	int not_found = 0;
	int too_many = 0;
	x = y = 0;
	float centroidx;
	float centroidy;
	int count_print = 0;
	int moving = 0;
	int xPaddle_position_steps = STEPS_WIDTH_X / 2;
	int yPaddle_position_steps = 20;
	float paddleX_pix, paddleY_pix, puckX_pix, puckY_pix, puckX_in, puckY_in;
	int wait = 0;
	int enable_udp = 1;
	int defense_mode = 1;
	float x_motor_steps = 0, y_motor_steps = 0;
	int new_move_values;
	float avg_angle = 0;
	int total_angles = 0;
	float angle_sum = 0, avg_prediction, prediction_sum;
	int total_predictions;
	float paddleX_steps, paddleY_steps, puckX_steps, puckY_steps;
	double velocity, y_diff, x_diff, xDiff, yDiff;
	float angle, target_yy, predicted_puckX, predicted_puckX_steps, dist, paddle_area, paddle_perimeter, puck_area, puck_perimeter;
	FILE *fpt;
	Point start, predicted;
	float avg_xdiff, avg_ydiff, total_ydiff, total_xdiff;
	vector<Point> points;
	Mat outputLine;
	int go_home = 0;

	fpt = fopen("debug_output.txt", "w");

	// puck xrange (24.5 -26) - (456-460)
	//paddle xrange (

	Mat CamImg = Mat(*(Instance->frame)).clone();
	clock_t StartTime, EndTime;
	clock_t motor_start, motor_end;

	/* INITIALIZES UDP CONNECTION */
	if (!InitUDPLib())
	{
		printf("Error, UDP could not be initialized\n\r");
		exit(1);
	}

	// Create receiver, with packet size equal to that of PACKIN and port at 12403 or the output port for the Tiva in virtual port 3
	CUDPReceiver receiver(sizeof(PACKIN), 12403);

	// Create sender, with packet size equal to that of PACKOUT and port at port is 12302 or input port for the Tiva in virtual port 2, 
	// and remote address 127.0.0.1(localhost)
	CUDPSender sender(sizeof(PACKOUT), 12302, "127.0.0.1");

	// Define buffers for input and output
	PACKIN pkin;
	PACKOUT pkout;

	while (1)
	{

		//Get frame From Camera
		CLEyeCameraGetFrame(Instance->CameraInstance, CamImg.data);

		// Homography frame
		warpPerspective(CamImg, unwarp_frame, H, CamImg.size());
		cvtColor(unwarp_frame, hsv_frame, CV_BGR2HSV);

		// Changes value of HSV of Puck 
		inRange(hsv_frame, Scalar(puck.hue.low_value,
			puck.sat.low_value,
			puck.value.low_value),
			Scalar(puck.hue.high_value,
				puck.sat.high_value,
				puck.value.high_value), frame_threshold);
		// Blurr video
		threshold(frame_threshold, puck.binary, minThresh, maxTresh, THRESH_BINARY);
		// Starting point to erode video
		erode_video(puck.binary, puck.erode_val);
		// Starting point to dilute video
		dilute_video(puck.binary, puck.dilate_val);
		// Find the puck and draw contour on it
		findContours(puck.binary.clone(), puck.contour, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		// Changes HSV values of the Paddle
		inRange(hsv_frame, Scalar(paddle.hue.low_value,
			paddle.sat.low_value,
			paddle.value.low_value),
			Scalar(paddle.hue.high_value,
				paddle.sat.high_value,
				paddle.value.high_value), frame_threshold);
		// Blurr video
		threshold(frame_threshold, paddle.binary, minThresh, maxTresh, THRESH_BINARY);
		// Starting point to erode video
		erode_video(paddle.binary, paddle.erode_val);
		// Starting point to dilute video
		dilute_video(paddle.binary, paddle.dilate_val);
		// Find the puck and draw contour on it
		findContours(paddle.binary.clone(), paddle.contour, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		// If Paddle found
		if (paddle.contour.size() >= 1)
		{
			//centroid coordinates
			//printf("%.2f %.2f\n", centroid.x, centroid.y);
			for (i = 0; i < paddle.contour.size(); i++)
			{

				paddle_area = contourArea(paddle.contour[i], false);
				paddle_perimeter = arcLength(paddle.contour[i], true);

				if ((paddle_area > 500) && (paddle_perimeter > 120))
				{
					// DRAW CONTOUR AND GET CENTROID
					moment = moments(paddle.contour[i], false);
					centroid = Point2f(moment.m10 / moment.m00, moment.m01 / moment.m00);
					Scalar color = Scalar(255, 0, 0);
					drawContours(unwarp_frame, paddle.contour, i, color, 2, 8, hierarchy, 0, Point());
					paddleX_pix = centroid.y;
					paddleY_pix = centroid.x;

					// DETERMINE LOCATION OF PADDLE 
					paddleX_steps = paddleX_pix * xSteps_per_pixel;
					paddleY_steps = paddleY_pix * ySteps_per_pixel;
				}

			}
		}

		// If Puck found
		if (puck.contour.size() >= 1)
		{
			//centroid coordinates
			//printf("%.2f %.2f\n", centroid.x, centroid.y);
			for (i = 0; i < puck.contour.size(); i++)
			{
				puck_area = contourArea(puck.contour[i], false);
				puck_perimeter = arcLength(puck.contour[i], true);
				//printf("Area: %.2f, Perimeter: %.2f\r\n", puck_area, puck_perimeter);
				if ((puck_area > 800) && (puck_perimeter > 100))
				{

					moment = moments(puck.contour[i], false);
					centroid = Point2f(moment.m10 / moment.m00, moment.m01 / moment.m00);

					// Draws red contour around Puck
					Scalar color = Scalar(255, 0, 0);
					drawContours(unwarp_frame, puck.contour, i, color, 2, 8, hierarchy, 0, Point());

					// Gets the X-Y centroid values of the Puck
					puckX_pix = centroid.y;
					puckY_pix = centroid.x;
					puckY_in = puckY_pix / yPixels_per_inch;
					puckX_in = puckX_pix / xPixels_per_inch;

					// Displays Puck information every 15 Frames
					if (count_print == 60)
					{
						//	printf("[X: %f Y: %f] Area: %.2f, Perimeter: %.2f\r\n", puckX_in, puckY_in, puck_area, puck_perimeter);
						count_print = 0;
					}
					count_print++;

					if (abs(9.5 - puckY_in) < 0.5)
					{
						fprintf(fpt, "CROSSED THE LINE AT [%.2f, %.2f]\n\n", puckX_in, puckY_in);
						//printf("CROSSED THE LINE AT [%.2f, %.2f]\n\n", puckX_in, puckY_in);
					}

					// Resets X and Y value at start of new FPS
					if (num_frames == 0)
					{
						x_in = puckX_in;
						y_in = puckY_in;
					}
					points.push_back(Point(puckY_in, puckX_in));

					total_xdiff += (puckX_in - x_in);
					total_ydiff += (puckY_in - y_in);
					x_diff = (puckX_in - x_in);
					y_diff = (puckY_in - y_in);
					x_in = puckX_in;
					y_in = puckY_in;

					// DETERMINES NUMBER OF STEPS TO PUCK 
					puckX_steps = puckX_pix * xSteps_per_pixel;
					puckY_steps = puckY_pix * ySteps_per_pixel;

					// LOGIC AFTER 5 FRAMES 
					if (num_frames > 5)
					{
						avg_xdiff = total_xdiff / ((float)num_frames - 1);
						avg_ydiff = total_ydiff / ((float)num_frames - 1);
						dist = sqrt(pow((avg_xdiff), 2) + pow((avg_ydiff), 2));
						total_xdiff = 0;
						total_ydiff = 0;

						//printf("puckx %.3f, pucky %.3f\n Paddlex %.3f, Paddley %.3f\n", puckX_pix, puckY_pix, paddleX_pix, paddleY_pix);
						if (dist > 0.01)
						{
							//printf("Avg Xdiff vs xdiff %.2f\t %.2f\n", avg_xdiff, x_diff);
							//printf("Avg Ydiff vs ydiff %.2f\t%.2f\n", avg_ydiff, y_diff);
							angle = atan2(avg_ydiff, avg_xdiff);
							//printf("Avg Angle %.2f\t", angle);

							
							//angle = atan2((float)y_diff, (float)x_diff)*180.0 / M_PI;
							//printf("Angle %.2f\n", angle);
							

							// IN THE ZONE TO HIT PUCK
							if ((puckY_in < BLUE_LINE) && (puckY_in > OFFENSIVE_LINE))
							{
								// PUCK MOVING TOWARDS GOAL
								if (angle < 0)
								{
									total_angles++;
									angle_sum += angle;
									avg_angle = angle_sum / (float)total_angles;
									target_yy = 9.5; //inches
									predicted_puckX = find_x_position(angle, target_yy, puckX_in, puckY_in, fpt);
									total_predictions++;
									prediction_sum += predicted_puckX;
									avg_prediction = prediction_sum / (float)total_predictions;

									velocity = (double)dist / (double)((num_frames) / 61.0);
									start.x = puckY_pix;
									start.y = puckX_pix;
									predicted.x = target_yy * yPixels_per_inch;
									predicted.y = predicted_puckX * xPixels_per_inch;

									line(unwarp_frame, start, predicted, Scalar(0, 255, 0), 2, 8, 0);
									fitLine(points, outputLine, CV_DIST_L1, 0, 0.1, 0.1);

									line(unwarp_frame, Point(outputLine.data[2] * yPixels_per_inch, outputLine.data[3] * xPixels_per_inch), Point((outputLine.data[2] + outputLine.data[0] * 10)*yPixels_per_inch, (outputLine.data[3] + outputLine.data[1] * 10)*xPixels_per_inch), Scalar(0, 0, 255), 2, 8, 0);
									points.clear();

									predicted_puckX_steps = predicted_puckX * xPixels_per_inch * xSteps_per_pixel;

									xDiff = predicted_puckX_steps - paddleX_steps;
									yDiff = puckY_steps - paddleY_steps;

								}
								// PUCK MOVING AWAY FROM GOAL
								else
								{								
									x_motor_steps = puckX_steps - paddleX_steps;
									set_motor_steps(&pkout, x_motor_steps, 'x');
									y_motor_steps = puckY_steps - paddleY_steps;
									set_motor_steps(&pkout, y_motor_steps, 'y');
									motor_start = clock();
									sender.SendData(&pkout);
								}
							}
							// PUCK IS BEHIND OUR PADDLE 
							else if (puckY_in < OFFENSIVE_LINE)
							{

							}
							// PUCK ON OTHER SIDE OF TABLE, FOLLOW X-DIRECTION ONLY 
							else
							{
								x_motor_steps = puckX_steps - paddleX_steps;
								set_motor_steps(&pkout, x_motor_steps, 'x');
								y_motor_steps = 0;
								set_motor_steps(&pkout, y_motor_steps, 'y');
								motor_start = clock();
								sender.SendData(&pkout);
							}

							// IF PUCK IS COMING TOWARDS OUR DIRECTION
							/*if (angle < 0)
							{
								total_angles++;
								angle_sum += angle;
								avg_angle = angle_sum / (float)total_angles;
								target_yy = 9.5; //inches
								predicted_puckX = find_x_position(angle, target_yy, puckX_in, puckY_in, fpt);
								total_predictions++;
								prediction_sum += predicted_puckX;
								avg_prediction = prediction_sum / (float)total_predictions;
								//fprintf(fpt, "[%.2f, %.2f] -> [%.2f, %.2f] Dist: %.3f  Angle: %.2f  Prediction: %.2f\n", x_in, y_in, puckX_in, puckY_in, dist, angle, predicted_puckX);
								//printf("Angle %.2f AvG_Angle %.2f Dist: %.3f Curr_X %.2f Curr_Y %.2f Pred. Position %.2f Avg Pred %.2f\n", angle, avg_angle, dist, puckX_in, puckY_in, predicted_puckX, avg_prediction);
								//float velocity = dist / ((num_frames-reference_frame)/60);
								velocity = (double)dist / (double)((num_frames) / 61.0);
								start.x = puckY_pix;
								start.y = puckX_pix;
								predicted.x = target_yy * yPixels_per_inch;
								predicted.y = predicted_puckX * xPixels_per_inch;
								//printf("Angle %.2f AvG_Angle %.2f Dist: %.3f Curr_X %.2f Curr_Y %.2f Pred. Position %.2f Avg Pred %.2f\n", angle, avg_angle, dist, puckX_in, puckY_in, predicted_puckX, avg_prediction);
								line(unwarp_frame, start, predicted, Scalar(0, 255, 0), 2, 8, 0);
								fitLine(points, outputLine, CV_DIST_L1, 0, 0.1, 0.1);
								//printf("vx %f, vy %f. x0 %f, y0 %f\n", outputLine.data[0], outputLine.data[1], outputLine.data[2], outputLine.data[3]);
								line(unwarp_frame, Point(outputLine.data[2] * yPixels_per_inch, outputLine.data[3] * xPixels_per_inch), Point((outputLine.data[2] + outputLine.data[0] * 10)*yPixels_per_inch, (outputLine.data[3] + outputLine.data[1] * 10)*xPixels_per_inch), Scalar(0, 0, 255), 2, 8, 0);
								points.clear();
								//Danger zone x > 8 && x < 18 x <  && y < 4.5
								
								//predicted.x = target_yy * yPixels_per_inch;
								//predicted.y = avg_prediction * xPixels_per_inch;
								//line(unwarp_frame, start, predicted, Scalar(255, 0, 0), 2, 8, 0);
								

								// DETERMINES X-Y VALUES OF WHERE PUCK WILL BE
								predicted_puckX_steps = predicted_puckX * xPixels_per_inch * xSteps_per_pixel;

								// DETERMINES X-Y VALUES FOR MOTOR TO BE SENT THROUGH UDP 
								xDiff = predicted_puckX_steps - paddleX_steps;
								yDiff = puckY_steps - paddleY_steps;

								// PROTECTS FROM GOING TO FAR IN THE Y-DIRECTION 
								if (puckY_steps > 70 || puckY_steps < 15)
								{
									yDiff = 0;
								}

								// DETERMINES IF MOTOR IS DONE MOVING TO ITS POSITION
								if (abs(xDiff) > 0.5 || abs(yDiff) > 0.5)
								{
									//check to see if motor is still moving
									if (clock() - motor_start <= wait)
									{
										// if the puck has changed positions since last move
										if ((xDiff <= 0) != (x_motor_steps <= 0)
											|| (yDiff <= 0) != (y_motor_steps <= 0))
										{
											new_move_values = 1;
											//printf("Changed puck Position!\n");
										}
										else
										{
											//printf("Same Position!\n");
											new_move_values = 0;
										}
									}
									else
									{
										//printf("Timer expired!\n");
										new_move_values = 1;
									}
								}

								// if we need to update the motor moving values
								if (new_move_values)
								{
									// RESET MOTOR
									pkout.flt1 = 2;
									pkout.flt2 = 2;
									pkout.flt3 = 0; // steps
									pkout.flt4 = 2;
									pkout.flt5 = 2;
									pkout.flt6 = 0; // steps
									sender.SendData(&pkout);

									if (puckY_in > 17)
									{
										defense_mode = 1;
									}
									else
									{
										defense_mode = 0;
									}


									if (defense_mode)
									{
										// MOVES ONLY ON X-DIRECTION ON DEFENSE MODE								
										x_motor_steps = puckX_steps  - paddleX_steps;
										printf("Move X: %.2f\n", x_motor_steps);
										set_motor_steps(&pkout, x_motor_steps, 'x');
										y_motor_steps = 0;
										set_motor_steps(&pkout, y_motor_steps, 'y');
										//wait = abs(x_motor_steps);
										//printf("SENT: X: %.2f %.2f %.2f, Y: %.2f %.2f %.2f\n", pkout.flt1, pkout.flt2, pkout.flt3, pkout.flt4, pkout.flt5, pkout.flt6);
										//printf("Wait: %d\n", wait);
										motor_start = clock();
										sender.SendData(&pkout);
									}
									else
									{
										// GO TO predicted X-VALUE
										x_motor_steps = xDiff;
										set_motor_steps(&pkout, x_motor_steps, 'x');
										y_motor_steps = yDiff + 10;
										set_motor_steps(&pkout, y_motor_steps, 'y');
										printf("Move Y %.3f Steps\n", yDiff);
										motor_start = clock();
										sender.SendData(&pkout);
										Sleep(50);

										x_motor_steps = xDiff;
										set_motor_steps(&pkout, x_motor_steps, 'x');
										y_motor_steps = yDiff - 20;
										set_motor_steps(&pkout, y_motor_steps, 'y');
										printf("Move Y %.3f Steps\n", yDiff);
										motor_start = clock();
										sender.SendData(&pkout);
									}
								}
								else
								{
									//count_print++;
									if (count_print == 15)
									{
										printf("No movement Needed\n");
										//printf("No distance traveled. x,y (inches): %.2f %.2f\t\tx,y (pixels): %.2f %.2f\n", centroidx / xPixels_per_inch, centroidy / yPixels_per_inch, centroidx, centroidy);
										//printf("Paddle Position x,y (steps): %d %d\t\t\tSteps/Pixel x,y: %f %f\n", xPaddle_position_steps, yPaddle_position_steps, xSteps_per_pixel, ySteps_per_pixel);
										//printf("Motor movement to puck x,y: %d %d\n", xDiff, yDiff);
										//count_print = 0;
									}
								}
							}
							// PUCK IS ON THE OTHER SIDE OF THE TABLE OR BEHIND US 
							else
							{

							}



						}*/

						// RESET VALUES
						num_frames = 0;
						x = 0;
						y = 0;
						x_in = puckX_in;
						y_in = puckY_in;
					}
					num_frames++;
				}

			}
		}

		imshow("Paddle/Puck Contours", unwarp_frame);
		//copy it to main thread image.
		*(Instance->frame) = CamImg;

		// Track FPS
		if (FramerCounter == 0)
		{
			StartTime = clock();
		}
		FramerCounter++;
		EndTime = clock();

		if ((EndTime - StartTime) / CLOCKS_PER_SEC >= 1)
		{
			//cout << "FPS:" << FramerCounter << endl;
			FramerCounter = 0;
		}


		//X-DIRECTION 
		/*

		*/

	}
	return 0;
}
