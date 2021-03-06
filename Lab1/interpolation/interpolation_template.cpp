// ConsoleApplication1.cpp: 定義主控台應用程式的進入點。
//
//#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>

using namespace std;
using namespace cv;
//using namespace std::piecewise_construct;

void 	bilinear_interpolation(Mat& input, Mat& output, float scalingFactor);

int 	main(int argc, char** argv) {

	Mat inputImg = imread("IU_small.jpg");
	float scalingFactor = 3.0;
	
	int scaledWidth = round(1. * inputImg.cols * scalingFactor);
	int scaledHeight = round(1. * inputImg.rows * scalingFactor);

	Mat outputImg1 = Mat(scaledHeight, scaledWidth, inputImg.type());
	Mat outputImg2; // for opencv build-in function

					// resize the input image by your bilinear_interpolation funcion
	bilinear_interpolation(inputImg, outputImg1, scalingFactor);
	// resize the input image by opencv
	resize(inputImg, outputImg2, Size(scaledWidth, scaledHeight), 0, 0, CV_INTER_LINEAR);

	imshow("My Interpolation", outputImg1);
	imshow("Opencv build-in function", outputImg2);
	waitKey(0);

	imwrite("output.jpg", outputImg1);

	return 0;
}


void 	bilinear_interpolation(Mat& input, Mat& output, float scalingFactor) {

	for (int i = 0; i < output.rows; i++) {
		for (int j = 0; j < output.cols; j++) {
			if ((i / 3 + 1) >= input.rows || (j / 3 + 1) >= input.cols) {
				for (int n = 0; n < 3; n++) {
					if ((i / 3 + 1) >= input.rows && (j / 3 + 1) >= input.cols) {
						output.at<Vec3b>(i, j)[n] = input.at<Vec3b>(i / 3, j / 3)[n];
					}
					else if ((i / 3 + 1) >= input.rows) {
						output.at<Vec3b>(i, j)[n] = input.at<Vec3b>(i / 3, j / 3)[n] * (j / 3 + 1 - j / scalingFactor)
							+ input.at<Vec3b>(i / 3, j / 3 + 1)[n] * (j / scalingFactor - j / 3);
					}
					else if ((j / 3 + 1) >= input.cols) {
						output.at<Vec3b>(i, j)[n] = input.at<Vec3b>(i / 3, j / 3)[n] * (i / 3 + 1 - i / scalingFactor)
							+ input.at<Vec3b>(i / 3+1, j / 3 )[n] * (i / scalingFactor - i / 3);
					}
				}
			}
			else {
				for (int n = 0; n < 3; n++) {
					output.at<Vec3b>(i, j)[n] =
						input.at<Vec3b>(i / 3, j / 3)[n] * (j / 3 + 1 - j / scalingFactor)*(i / 3 + 1 - i / scalingFactor) +
						input.at<Vec3b>(i / 3 + 1, j / 3)[n] * (j / 3 + 1 - j / scalingFactor) *(i / scalingFactor - i / 3) +
						input.at<Vec3b>(i / 3, j / 3 + 1)[n] * (j / scalingFactor - j / 3)*(i / 3 + 1 - i / scalingFactor) +
						input.at<Vec3b>(i / 3 + 1, j / 3 + 1)[n] * (j / scalingFactor - j / 3)*(i / scalingFactor - i / 3);
				}
			}
		}
	}

}