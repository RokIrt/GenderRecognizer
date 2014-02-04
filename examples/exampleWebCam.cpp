#include <opencv2/opencv.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "../GenderRecognizer.h"


using namespace cv;
String face_cascade_name = "data/haarcascade_frontalface_default.xml";
CascadeClassifier face_cascade;
vector<Rect> detectAndDisplay(Mat frame)
{
  vector<Rect> facesRect;
  Mat frame_gray;
  Mat faceROI=cv::Mat::zeros(0, 0, CV_32F);
  if(frame.channels()>1)
	cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );
//-- Detect faces
  face_cascade.detectMultiScale( frame_gray, facesRect, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
//	faceROI = frame_gray( Rect(faces[i].x-(faces[i].width*0.1),faces[i].y-(faces[i].height*0.1),faces[i].width*1.2,faces[i].height*1.2) );
//ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
	return facesRect;
}

int main (int argc, const char * argv[])
{
  	if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
	VideoCapture cap("http://192.168.1.101:8080/videofeed?something.mjpeg");
	GenderRecognizer GR;
	//get webcam stream or path to video stream (argc[1])
	if(argc<2)
		VideoCapture cap("http://192.168.1.101:8080/videofeed?something.mjpeg");
	else
		VideoCapture cap(argv[1]);
	Mat img;
	namedWindow("video capture", CV_WINDOW_AUTOSIZE);
	Scalar color=Scalar(0,0,0);
	int counter=31;
	String text="";
				
	while (true){
		cap >> img; 
		vector<Rect> faces=detectAndDisplay(img);
		for( size_t i = 0; i < faces.size(); i++ )
			  {
				int gender=1;
				counter++;
				Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
				cv::Rect face(faces[i].x, faces[i].y,faces[i].width,faces[i].height);
				if(counter>10){
				  int gender=GR.predict(img(faces[i]));
				  counter=0;
				  if(gender==0){   ///male
						color=Scalar(255,0,0);
						text="male";
				  
				  }else{           //female
					    color=Scalar(255,100,255);
						text="female";
						
				  }
				}
				cv::putText(img, text, center, FONT_HERSHEY_SCRIPT_SIMPLEX, 2,color, 2,8);
				rectangle(img,face,color,3);

			  }
		
		imshow("video capture",img);
		waitKey(10);
	}
}

 