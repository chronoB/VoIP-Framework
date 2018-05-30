#pragma once
#include "audio_parameter.h"
#include "math.h"

class OverDrive
{
public:
	OverDrive(); // You absolutly need a constructor and destrucktor
	~OverDrive();

	void setParam(int numParam, double Value);

	void processAudio(float* inBlock, float* outBlock, int NumOfSamples);


private:
	void TanhDrive(float *In, float *Out);
	void Tanh3Drive(float *In, float *Out);

	void CopyDummy(float* inBlock, float* outBlock);

	int whichOverdrive = 0;
	int maxOverdrives = 3; //Must be changed, if more Overdrives are added
	int maxGainOverdrive = 40;
	int idx = 0;
	double Gain = 1;
};