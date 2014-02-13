#include <opencv2/opencv.hpp>
#include "..\GenderRecognizer.h"
using namespace cv;


int main (int argc, const char * argv[])
{
	Mat img;
	if (argc == 2)
		img=imread(argv[1]);
	else
		img  = imread("data\\face.jpg");
	GenderRecognizer GR;
	int gender=GR.predict(img);	
}