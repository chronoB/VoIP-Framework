#include "overdrive.h"

OverDrive::OverDrive()
{
}

OverDrive::~OverDrive()
{
}

void OverDrive::TanhDrive(float *In, float *Out) //uses a tanh(x) as Overdrive function
{

	for (idx = 0; idx < FRAMES_PER_BUFFER; idx++)
	{
		Out[idx] = float(tanh(Gain*In[idx])/Gain); //Sample is multiplied with the gain and then put in the tanh function
	};
};


void OverDrive::Tanh3Drive(float *In, float *Out) //uses a tanh^3(x) as Overdrive function
{

	for (idx = 0; idx < FRAMES_PER_BUFFER; idx++)
	{
		Out[idx] = float(pow(tanh(Gain*In[idx]), 3.0)/Gain); //Sample is multiplied with the gain and then put in the tanh^3 function
	};
}

void OverDrive::CopyDummy(float* inBlock, float* outBlock)
{
	for (idx = 0; idx < FRAMES_PER_BUFFER; idx++)
	{
		outBlock[idx] = inBlock[idx];
	};
}

void OverDrive::setParam(int numParam, double Value)
{
	switch (numParam)
	{
	case 1:
	{
		whichOverdrive = int(Value * double(maxOverdrives)); //Checks which Overdrive is selected
		return;
	}
	case 2:
	{
		Gain = pow(10.0, double(maxGainOverdrive) * Value / 10.0); //implements the selected Gain between 0 and 40dB
		return;
	}
	}
}

void OverDrive::processAudio(float* inBlock, float* outBlock, int NumOfSamples)
{
	switch (whichOverdrive)
	{
	case 0: 
	{
		TanhDrive(inBlock, outBlock);
		return;
	}
	case 1:
	{
		Tanh3Drive(inBlock, outBlock);
		return;
	}
	case 2:
	{
		CopyDummy(inBlock, outBlock);
		return;
	}
	case 3:
	{
		CopyDummy(inBlock, outBlock);
		return;
	}
	}
};
