#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void	bgr2rgb(Mat& input, Mat& output);

int main(int argc, char** argv){

	Mat input_img = imread(argv[1]);
        Mat output_img = input_img.clone();

	bgr2rgb(input_img, output_img);		

	imshow("origin", input_img);
	imshow("bgr2rgb", output_img);
        waitKey(0);
       	
	imwrite("output.jpg", output_img);

	return 0;
}
void	bgr2rgb(Mat& input, Mat& output) {

	// write down your code here
	uchar intensity_red = image.at<Vec3b>(i, j)[2];
	
}
