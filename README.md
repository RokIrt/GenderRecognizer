GenderRecognizer
==============
This is a gender recognition library for OpenCV written in C++.
It uses FaceRecognizer class and Facial landmark locator library (http://cmp.felk.cvut.cz/~uricamic/flandmark/).

-------------------
.. Sample code::
   * An example using the GenderRecognizer class can be found at /samples/exampleSimple.cpp

  //// Just create GR class
	//// and call .predict(img) function with CROPED FACE IMAGE as input (optimized for Viola-Jones output) 
	
	GenderRecognizer GR;
	int gender=GR.predict(img);	


------------------
 GenderRecognizer
------------------

class GenderRecognizer{
public:
	// Renturns predicted gender (0=male,1=female)
	// Takes an input as CROPED FACE IMAGE (optimized for Viola-Jones output) 
	int predict(Mat inputImage);
	
	// Renturns predicted gender (0=male,1=female) and confidence (e.g.distance) of prediction
	// Takes an input as croped face image
	int predict(Mat inputImage,double confidence);
	
	// Prediction is updated every time with prediction weighted with confidence: SUM[predicted/confidence]
	// Renturns predicted gender (0=male,1=female) and confidence (e.g.distance) of prediction
	int update(Mat inputImage);
	int update(Mat inputImage,double confidence)
}

------------------
 FaceAlignment
------------------


class FaceAlignment{
public:
{
	//offsets and rotates face, so that eyes are horisontal aligned and right eye is at coordinate "righteye"
	//input: croped face image and x,y of right eye
	// returns align face image
	Mat alignFace( Mat &image, Point righteye=Point(40,51));
}

------------------------

	
