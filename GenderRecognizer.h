#include <opencv2/opencv.hpp>
#include "FaceAlignment.h"
using namespace std;
using namespace cv;

class GenderRecognizer
{
public:
	GenderRecognizer(void);
	~GenderRecognizer(void);
	int predict(Mat img);
	int predict(Mat img, CV_OUT double &confidence);
	int update(Mat img, CV_OUT double &confidence);
	int update(Mat img);
	Mat img;
	Vector<Point> gender_confidence;
private:
	int align();
	int calculateConfidence();
	Ptr<FaceRecognizer> model;
	FaceAlignment faceAlignment;
public:
	int update();
};

