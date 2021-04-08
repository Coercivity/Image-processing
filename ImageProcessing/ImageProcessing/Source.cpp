#include<opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp> 
#include "opencv2/imgproc.hpp" 
#include <iostream>
#include <stdint.h>
using namespace cv;
using namespace std;


#define amount_of_channels 2
#define pixel_max_value 255
#define brightness_slider_max  10
#define contrast_slider_max  10

char Ch_dephWindow[] = "Channel depth change";
char InputFileWay[] = "test.jpg";
char MainWindow[] = "Butterfly's effect";
char Brightness[] = "Brightness";
char Contrast[] = "Contrast";
char Test[] = "Test";


Mat src, dst; //создание матрицы для изображения
Mat kernel; //Матрица для свертки


int DELAY_BLUR = 300; //задержка для блюра
int MAX_KERNEL_LENGTH = 31;
int curByte = 0;
int channel = 0;
int beta_slider = 5;//для яркости
int alpha_slider = 5; //для контраста
double alpha = 1;
double beta;


//uint8_t - unsigned char  0 to 256 range 2 channels for grayscale only
//Vec3b - 3 channels 1 byte bgr


void ch_deph(int, void*); //изменение глубины канала
void fad(int, void*); //random colourgame
int display_dst(int delay);//задержка при фильтровании изображения
void brightness(int, void*);// яркость
void contrast(int, void*);//контраст
void ToGray(Mat);


int main() {
	
	src = imread(InputFileWay, IMREAD_ANYCOLOR);//загрузка изоображения
	
	if (!src.data) //Если картинка не найдена 
	{
		cout << "Error opening image" << endl;
		return -1;
	}

	dst = src.clone();//создание копии для дальнейших манипуляций

	namedWindow(MainWindow, WINDOW_AUTOSIZE);
	moveWindow(MainWindow, 400, 200);
	imshow(MainWindow, dst);
	waitKey();
	
	//Здесь должен быть интерфейс


	int userInput;
	cout << "1 - channel deph change " << endl;
	cout << "2 - blur filter " << endl;
	cout << "3 - Gaussianblur filter " << endl;
	cout << "4 - medianblur filter " << endl;
	cout << "5 - bilateral filter " << endl;
	cout << "6 - random colourgame " << endl;
	cout << "7 - brightness " << endl;
	cout << "8 - contrast " << endl;
	cout << "9 - ToGray " << endl;
	cin >> userInput;

	switch (userInput)
	{
	case 1:
		namedWindow(Ch_dephWindow, WINDOW_AUTOSIZE);

		resizeWindow(Ch_dephWindow, 400, 80);
		moveWindow(Ch_dephWindow, 0, 300);

		createTrackbar("channel", Ch_dephWindow, &channel, amount_of_channels, ch_deph);
		createTrackbar("byte", Ch_dephWindow, &curByte, pixel_max_value, ch_deph); //Изменение глубины канала при использовании слайдера
		imshow(MainWindow, dst);
		waitKey();

	case 2:
	{
		double delta = 0;
		int ddepth = -1;
		for (int i = 0; i < 10; i++)
		{
			int kernel_size = 3 + 2 * (i % 10);
			kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size*kernel_size);//ядро для блюра
			
			filter2D(src, dst, ddepth, kernel, Point(-1, -1), delta, BORDER_DEFAULT);//наложение ядра на изоображение
			if (display_dst(DELAY_BLUR) != 0)//применнеие задержки при выполнении фильтра
			{
				return 0;
			}
		}
	}
		waitKey();
	case 3:
		for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
		{
			GaussianBlur(src, dst, Size(i, i), 0, 0);//блюр Гаусса
			if (display_dst(DELAY_BLUR) != 0)
			{
				return 0;
			}
		}

		waitKey();
	case 4:
		for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
		{
			medianBlur(src, dst, i);
			if (display_dst(DELAY_BLUR) != 0)
			{
				return 0;
			}
		}

		waitKey();
	case 5:
		for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
		{
			bilateralFilter(src, dst, i, i * 2, i / 2);
			if (display_dst(DELAY_BLUR) != 0)
			{
				return 0;
			}
		}

		waitKey();
	case 6:
		namedWindow(Ch_dephWindow, WINDOW_AUTOSIZE);

		resizeWindow(Ch_dephWindow, 400, 80);
		moveWindow(Ch_dephWindow, 0, 300);

		createTrackbar("channel", Ch_dephWindow, &channel, amount_of_channels, fad);
		createTrackbar("byte", Ch_dephWindow, &curByte, 23, fad); 
		
		imshow(MainWindow, dst);
		waitKey();
	case 7:
		namedWindow(Brightness, WINDOW_AUTOSIZE);

		resizeWindow(Brightness, 400, 80);
		moveWindow(Brightness, 0, 300);

		createTrackbar("Brightness", Brightness, &beta_slider, brightness_slider_max, brightness);
		setTrackbarMin("Brightness", Brightness, 1);
		
		waitKey();
		
	case 8:
		namedWindow(Contrast, WINDOW_AUTOSIZE);

		resizeWindow(Contrast, 400, 80);
		moveWindow(Contrast, 0, 300);
		
		createTrackbar("Contrast", Contrast, &alpha_slider, contrast_slider_max, contrast);
		setTrackbarMin("Contrast", Contrast, 1);

		waitKey();
	case 9:
		ToGray(src);
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
			Vec3b& bgr = dst.at<Vec3b>(r, c);
			bgr[channel] = curByte;
		}
	}
	
	imshow(MainWindow, dst);
}

void fad(int, void*) {
	for (int r = 0; r < dst.rows; r++)
	{
		for (int c = 0; c < dst.cols; c++)
		{
			dst.at<cv::Vec3b>(r, c)[channel] = dst.at<cv::Vec3b>(r, c)[channel] * curByte;
		}
	}
	imshow(MainWindow, dst);
}


void brightness(int, void*)
{
	beta = (double)beta_slider * 1.3;
		for (int r = 0; r < dst.rows; r++)
		{
			for (int c = 0; c < dst.cols; c++)
			{
				for (int channel = 0; channel < dst.channels(); channel++)
				{
					if (getTrackbarPos("Brightness", Brightness) >= 5)
					dst.at<cv::Vec3b>(r, c)[channel] = saturate_cast<uchar>(dst.at<cv::Vec3b>(r, c)[channel] + beta);
					else
					dst.at<cv::Vec3b>(r, c)[channel] = saturate_cast<uchar>(dst.at<cv::Vec3b>(r, c)[channel] - beta * 3.25);

				}

			}
		}
	
	imshow(MainWindow, dst);
}

void contrast(int, void*)
{
	alpha = (double)alpha_slider / 6;
	beta = (4 - alpha);
	for (int r = 0; r < dst.rows; r++)
	{
		for (int c = 0; c < dst.cols; c++)
		{
			for (int channel = 0; channel < dst.channels(); channel++)
			{
				if (getTrackbarPos("Contrast", Contrast) >= 5)
					dst.at<cv::Vec3b>(r, c)[channel] = saturate_cast<uchar>(alpha*dst.at<cv::Vec3b>(r, c)[channel] + beta);
				else
					dst.at<cv::Vec3b>(r, c)[channel] = saturate_cast<uchar>(alpha*dst.at<cv::Vec3b>(r, c)[channel] + beta);

			}

		}
	}

	imshow(MainWindow, dst);
}


void ToGray(Mat src) {
	Mat dst(src.size(), CV_8UC1);
	for (int r = 0; r < src.rows; r++)
	{
		for (int c = 0; c < src.cols; c++)
		{
			Vec3b bgr = src.at<cv::Vec3b>(r, c);
			uint8_t gray = (29 * bgr[0] + 150 * bgr[1] + 77 * bgr[2]) >> 8;
			dst.at<uint8_t>(r, c) = gray;
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





