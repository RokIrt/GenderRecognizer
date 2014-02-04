#include <opencv2/opencv.hpp>
#include "GenderRecognizer.h"
using namespace cv;


int main (int argc, const char * argv[])
{
	if (argc == 2)
		Mat img=imread(argv[1]);
	else
		Mat img  = imread("data\\face.jpg");
	GenderRecognizer GR;
	int gender=GR.predict(img);	
}