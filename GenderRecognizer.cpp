#include "GenderRecognizer.h"


GenderRecognizer::GenderRecognizer(void)
{
	model = createFisherFaceRecognizer();
	model->load("data\\gender_classifier.xml");
	
}


GenderRecognizer::~GenderRecognizer(void)
{
}

int GenderRecognizer::predict(Mat img){
		double conf=0;
		return predict(img, conf);
}


int GenderRecognizer::predict(Mat img, double &confidence)
{
	if(img.channels()!=1){
		cvtColor( img, img, CV_BGR2GRAY );
	}
	GenderRecognizer::img=img;
	int size=img.size().height;
	if(size==0) return 0;
	if((img.rows<116)||(img.cols<116)){
		resize(img,img,Size(115,115));
		align();
	}else{
			align();
			img=img(Rect(0,0,116,116));
			resize(img,img,Size(115,115));
			
			
	}
	int theType = img.type();
	int predictedLabel = -1;
    double conf = 0.0;
	double maxConf=9999;
	Mat tmpImg=img;
	int tmpGender;
	try{
			for(int i=-1; i<2; i++)
				for(int j=-1; j<2; j++){
					Point delta = Point((i), (j));
					cv::Mat M = (cv::Mat_<float>(2, 3) << 1,  0,  delta.x, 0,  1,  delta.y);
					warpAffine(img,img,M,img.size());
					model->predict(tmpImg, predictedLabel, conf);
					if(maxConf>conf) {
						tmpGender=predictedLabel;
						maxConf=conf;
					}
			}
			conf=maxConf;
			predictedLabel=tmpGender;
		
	
	}catch( cv::Exception& e ){
		const char* err_msg = e.what();
		std::cout << "exception caught: " << err_msg << std::endl;
	}
	confidence=conf;
	return predictedLabel;
}


int GenderRecognizer::align()
{
	faceAlignment.alignFace(img);
	return 1;
	
}

int GenderRecognizer::update(Mat img)
{
	GenderRecognizer::img=img;
	double confidence=0;
	int gender=predict(img, confidence);
	gender_confidence.push_back(Point(gender,confidence));
	gender=calculateConfidence();
	return gender;
}
//
// 
// SUM[gender/confidence]/n
// gender={-1,1;, n:number of sample
// -1 male
// +1 female
//
int GenderRecognizer::calculateConfidence(){
	float confidence=0;
	if(gender_confidence.size()>0){
		for( int i = 0; i < gender_confidence.size(); i++ ) {
			int gender=gender_confidence[i].x;
			double conf=gender_confidence[i].y;
			if(gender==0) gender=-1;
			if(conf<1) conf=1;
			conf=1/conf;
			confidence+=gender*conf;
		}
		confidence=confidence/gender_confidence.size();
		int gender;
		if(confidence>0) gender=1;  //female 
		else gender=0; //male if negative
		return gender;
	}

}
int GenderRecognizer::update()
{
	return 0;
}
