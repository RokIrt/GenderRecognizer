#include <opencv2/opencv.hpp>
#include "lib/flandmark_detector.h"

using namespace std;
using namespace cv;

class FaceAlignment
{
public:
	FaceAlignment();
	~FaceAlignment(void);
	Mat alignFace( Mat &image, Point righteye=Point(40,40));
	Mat img;
private:
	vector<Point> findLandmarks(); //returns center coordinates(x,y) for lefteye, righteye, mouth respectively
	struct PointsYASC{
    bool operator() (cv::Point pt1, cv::Point pt2) { return (pt1.y < pt2.y);}
	} pointsYASC;
	struct PointsXASC{
    bool operator() (cv::Point pt1, cv::Point pt2) { return (pt1.x < pt2.x);}
	} pointsXASC;
};

