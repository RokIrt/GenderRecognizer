#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
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
  for(int i=0; i<facesRect.size(); i++)
	  try{
		facesRect[i] = ( Rect(facesRect[i].x-(facesRect[i].width*0.1),facesRect[i].y-(facesRect[i].height*0.1),facesRect[i].width*1.2,facesRect[i].height*1.2) );
		}catch (int e) {
						cout << "An exception occurred. Exception Nr. " << e << '\n';
		};
  
//ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
	return facesRect;
}

int main (int argc, const char * argv[])
{
  	if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
	VideoCapture cap("http://192.168.1.100:8080/videofeed?something.mjpeg");
	//get webcam stream or path to video stream (argc[1])
	if (!cap.isOpened())  // if not success, exit program
    {
	    cout  << "Cannot open the video file" << endl;
		return -1;
    }
	Mat img;
	namedWindow("video capture", CV_WINDOW_AUTOSIZE);
	Scalar color=Scalar(0,0,0);
	int counter=11;
	String text="";
	GenderRecognizer GR;
	vector<Rect> tagedFaces;
	vector<Scalar> tagedFacesColor;
	while (true){
		cap >> img;
		//img=imread("data\\testimages\\faces.jpg");
		if(!img.data)
		{
			  printf("Error: no frame data.\n");
			  break;
		}
		vector<Rect> faces;
		counter++;
		if(counter%10==0){
			counter=0;
			faces=detectAndDisplay(img);
			tagedFaces.clear();
			tagedFacesColor.clear();
			if(faces.size()>0)
				for( size_t i = 0; i < faces.size(); i++ )
					if((faces[i].x>0) && (faces[i].y>0))
						if((img.cols>faces[i].x+faces[i].width) && (img.rows>faces[i].y+faces[i].height)){
						int gender=GR.predict(img(faces[i]));
						if(gender==0){   ///male
								color=Scalar(255,0,0);
								text="male";
				  
						  }else{           //female
								color=Scalar(255,100,255);
								text="female";
						
						  }
						//////////////////
						Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
						cv::Rect face(faces[i].x, faces[i].y,faces[i].width,faces[i].height);
						tagedFaces.push_back(face);
						tagedFacesColor.push_back(color);
					}

		}
		Mat displayImg=img;
		for(int i=0;i<tagedFaces.size();i++){
			cv::rectangle(displayImg,tagedFaces[i],tagedFacesColor[i],3);
			}
		imshow("video capture",displayImg);
		waitKey(20);
	}
	return 1;
}

 