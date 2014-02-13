#include <opencv2/opencv.hpp>
#include "../GenderRecognizer.h"
using namespace cv;

int main (int argc, const char * argv[])
{
	Mat img;
	if (argc == 2){
		img=imread(argv[1]);
	}else
		img  = imread("data\\face.jpg");
	GenderRecognizer GR;
	for(int i=0;i<10;i++){
		//double confidence;
		//int gender=GR.update(img, confidence);
 		int gender=GR.update(img);
	}
}