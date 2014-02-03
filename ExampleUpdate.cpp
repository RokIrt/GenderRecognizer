#include <opencv2/opencv.hpp>
#include "GenderRecognizer.h"
using namespace cv;

int main3 (int argc, const char * argv[])
{
			if (argc == 2){
				Mat img=imread(argv[1]);
			}
			Mat img  = imread("data\\test1_.jpg");
			GenderRecognizer GR;
			double confidence;
			for(int i=0;i<10;i++){
 				int a=GR.update(img);
			}
			
			return 1;
}