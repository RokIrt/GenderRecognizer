
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "GenderRecognizer.h"


using namespace std;
using namespace cv;

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread("data//"+path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

int main (int argc, const char * argv[])
{
	// Check for valid command line arguments, print usage
    // if no arguments were given.
	 string fn_csv="";
    if (argc < 2) {
        cout << "usage: " << argv[0] << " <csv.ext> <output_folder> " << endl;
        fn_csv = "data/test.ext";
	}else{
		fn_csv = string(argv[1]);
	}
	// Get the path to your CSV.
    vector<Mat> testimages;
    vector<int>  testlabels;
	try {
        read_csv(fn_csv, testimages, testlabels);
	//	read_links("data//link.html", online_images);
    } catch (cv::Exception& e) {
        cerr << "Error opening file \"" << "data//test.ext" << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }
	GenderRecognizer GR;
	int counter =0;
	
	for(int i=0;i<testimages.size();i++)
	{
		//string result_message = format("image: %i",i+1);
		//cout << result_message << endl; 
		
		int prediction=GR.predict(testimages[i]);
		if(prediction==testlabels[i]){
		//	cout << "true"<< endl;   
			counter++;
		}
	//	else cout << "false"<< endl;
	}
	
	float ratio=float(counter)/float(testimages.size());
	
	string result_message = format("true= %d, all=%d, ratio is= %f", counter,testlabels.size(),ratio);
        cout << result_message << endl;

		return 1;
}

