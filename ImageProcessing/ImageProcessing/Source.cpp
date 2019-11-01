#include<opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>//GUI
#include <opencv2/imgcodecs.hpp> 
#include "opencv2/imgproc.hpp" 

#include <iostream>
#include <stdint.h>
using namespace cv;
using namespace std;


#define MAXCHANNEL 2
#define SLIDERMAXVALUE 23


char Ch_dephWindow[] = "Channel depth change";
char InputFileWay[] = "test.jpg";
char MainWindow[] = "Butterfly's effect";

Mat image, dst;

int DELAY_BLUR = 150; //makes possible to create a delay for bluring
int MAX_KERNEL_LENGTH = 31;

int curByte = 1;
int channel = 0;

//uint8_t - unsigned char  0 to 256 range 2 channels for grayscale only
//Vec3b - 3 channels 1 byte bgr




void ch_deph(int, void*); //channel deph change
int display_dst(int delay);


int main() {

	image = imread(InputFileWay, IMREAD_ANYCOLOR);
	dst = image.clone();

	//interface 
	//Button for applying file to program

	if (!image.data) //if image not found
	{
		cout << "Error opening image" << endl;
		return -1;
	}


	int userInput;
	cout << "1 - channel deph change " << endl;
	cout << "2 - blur filters " << endl;
	cin >> userInput;

	namedWindow(MainWindow, WINDOW_AUTOSIZE);
	moveWindow(MainWindow, 400, 200);


	switch (userInput)
	{
	case 1:
		namedWindow(Ch_dephWindow, WINDOW_AUTOSIZE);

		resizeWindow(Ch_dephWindow, 400, 80);
		moveWindow(Ch_dephWindow, 0, 300);

		createTrackbar("channel", Ch_dephWindow, &channel, MAXCHANNEL, ch_deph);
		createTrackbar("byte", Ch_dephWindow, &curByte, SLIDERMAXVALUE, ch_deph); //change channel deph by manupulating trackbar
		imshow(MainWindow, dst);
		waitKey();
	case 2:


		for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
		{
			blur(image, dst, Size(i, i), Point(-1, -1));
			if (display_dst(DELAY_BLUR) != 0)
			{
				return 0;
			}
		}

		waitKey();

		for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
		{
			GaussianBlur(image, dst, Size(i, i), 0, 0);
			if (display_dst(DELAY_BLUR) != 0)
			{
				return 0;
			}
		}

		waitKey();

		for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
		{
			medianBlur(image, dst, i);
			if (display_dst(DELAY_BLUR) != 0)
			{
				return 0;
			}
		}

		waitKey();

		for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
		{
			bilateralFilter(image, dst, i, i * 2, i / 2);
			if (display_dst(DELAY_BLUR) != 0)
			{
				return 0;
			}
		}

		waitKey();

	default:
		break;
	}

	waitKey();

	return 0;
}


void ch_deph(int, void*) {

	for (int r = 0; r < dst.rows; r++)
	{
		for (int c = 0; c < dst.cols; c++)
		{
			dst.at<cv::Vec3b>(r, c)[channel] = dst.at<cv::Vec3b>(r, c)[channel] + curByte;
		}
	}
	imshow(MainWindow, dst);
}

int display_dst(int delay)
{
	imshow(MainWindow, dst);// Delay in milliseconds
	int c = waitKey(delay);
	if (c >= 0) { return -1; }
	return 0;
}





/*imwrite("outputGray.jpg", image); //writing file down the folder

namedWindow("Color", WINDOW_FREERATIO);
namedWindow("Fixed", WINDOW_FREERATIO);

imshow("Color", image);
imshow("Fixed", cimage);

resizeWindow("Color", image.cols / 2, image.rows / 2);
resizeWindow("Fixed", cimage.cols / 2, cimage.rows / 2);

moveWindow("Color", 0, 200);
moveWindow("Fixed", image.cols+1, 200);*/





/*for (int r = 0; r < image.rows; r++)  for grayscale only
{
	for (int c = 0; c < image.cols; c++)
	{
		image.at<uint8_t>(r , c) = image.at<uint8_t>(r , c) * 0.9f;
	}
}*/