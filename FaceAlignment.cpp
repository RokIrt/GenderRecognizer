#include "FaceAlignment.h"


FaceAlignment::FaceAlignment()
{
	model = flandmark_init("data\\flandmark_model.dat");
	
}


FaceAlignment::~FaceAlignment(void)
{
}


Mat FaceAlignment::alignFace(Mat &image,Point righteye)
{
  try{
	 FaceAlignment::img=image;
	 vector<Point> features=findLandmarks();
     if(features.size()==3){
		///affine transform of image
		float angle;
		if(features[0].y!=features[1].y)
			angle = atan ( float(features[1].y-features[0].y) / float(features[1].x-features[0].x) );
		else angle=0;
		angle=57.2957795*angle;
		Mat rot_mat = getRotationMatrix2D(features[0], angle, 1.0);
		warpAffine(img, img, rot_mat, img.size());
		Point delta = Point((righteye.x-features[0].x), (righteye.y-features[0].y));
		cv::Mat M = (cv::Mat_<float>(2, 3) << 1,  0,  delta.x, 
											  0,  1,  delta.y); 
		warpAffine(img,img,M,img.size());
		
    }

	return img;
 }catch( cv::Exception& e ){
	const char* err_msg = e.what();
	std::cout << "exception caught: " << err_msg << std::endl;
 }
}


vector<Point> FaceAlignment::findLandmarks()
{
 try{
	vector<Point> features;
	IplImage* image=cvCloneImage(&(IplImage)img);
	IplImage *img_grayscale = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
	if(img.type()!=CV_8UC1){
		cvCvtColor(image, img_grayscale, CV_BGR2GRAY);
	}else img_grayscale=cvCloneImage(image);

	int * bbox = (int*)malloc(4*sizeof(int));
	bbox[0] =int(image->width/10);
    bbox[1] =int(image->height/10);
    bbox[2] = int(image->width-image->width/10);
    bbox[3] = int(image->height-image->height/10);
	Point lefteye;Point righteye;Point mouth;
	lefteye=cvPoint(0,0);
	righteye=cvPoint(0,0);
	mouth=cvPoint(0,0);
	double * d_landmarks = (double*)malloc(2*model->data.options.M*sizeof(double));
    if(!flandmark_detect(img_grayscale, bbox, model, d_landmarks)){
		std::vector<cv::Point> pts;
		for (int i = 2; i < 2*model->data.options.M; i +=2 ){
			pts.push_back(cvPoint(int(d_landmarks[i]),int(d_landmarks[i+1])));
		}
		std::sort(pts.begin(), pts.end(), pointsYASC);
		std::sort(pts.begin(),  pts.begin()+4, pointsXASC);
		righteye.x=int((pts[1].x+pts[0].x)/2);
		righteye.y=int((pts[1].y+pts[0].y)/2);
		lefteye.x=int((pts[3].x+pts[2].x)/2);
		lefteye.y=int((pts[3].y+pts[2].y)/2);
		mouth.x=int((pts[6].x+pts[5].x)/2);
		mouth.y=int((pts[6].y+pts[5].y)/2);
		features.push_back(righteye);
		features.push_back(lefteye);
		features.push_back(mouth);
    }
	return features;
 }catch( cv::Exception& e ){
	const char* err_msg = e.what();
	std::cout << "exception caught: " << err_msg << std::endl;
 }
}
