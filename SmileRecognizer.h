#pragma once
#include "genderrecognizer.h"
class SmileRecognizer :
	public GenderRecognizer
{
public:
	SmileRecognizer(void);
	~SmileRecognizer(void);
private:
	Ptr<FaceRecognizer> model;
};

