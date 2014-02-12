
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../SmileRecognizer.h"


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
            images.push_back(imread("data\\testimages\\"+path, 0));
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
        fn_csv = "data\\testimages\\all.ext";
	}else{
		fn_csv = string(argv[1]);
	}
	// Get the path to your CSV.
    vector<Mat> testimages;
    vector<int>  testlabels;
	try {
        read_csv(fn_csv, testimages, testlabels);
	} catch (cv::Exception& e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }
	GenderRecognizer GR;
	int counter =0;
	
	for(int i=0;i<testimages.size();i++)
	{
		double conf=0;
		if(testimages[i].cols>0){
			int prediction=GR.predict(testimages[i],conf);
	
			if(prediction==testlabels[i]){
				counter++;
				string result_message = format("true. confidence= %f %i", conf, i);
				cout << result_message << endl;
			}else{
				string result_message = format("FALSE. CONFIDENCE= %f", conf);
				cout << result_message << endl;
			}
		}
	}
	float ratio=float(counter)/float(testimages.size());

	string result_message = format("true= %d, all=%d, ratio is= %f", counter,testlabels.size(),ratio);
    cout << result_message << endl;
 	waitKey(0);
}

