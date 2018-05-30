/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include "EffectMixerClass.h"
// class to mix the effects from the state on and back

// constructor with window calculation
EffectMixerClass::EffectMixerClass()
{
	calculateWin();
}

// destructor
EffectMixerClass::~EffectMixerClass()
{
	// deleting array with window
	delete[] gainVec;
}

// function to do the mixing
void EffectMixerClass::mixForEffects(float* processedBlock, float* unprocessedBlock, float* outBlock, int Status)
{
	// checks if value has changed
	if (setStatus != Status)
	{
		if (Status == 1) actualStatus = rise;
		else actualStatus = fall;
		setStatus = Status;
	}
	// processing of samples
	for (auto idx = 0; idx < FRAMES_PER_BUFFER; idx++)
	{
		outBlock[idx] = processedBlock[idx] * float(calculateGain(counter)) + unprocessedBlock[idx] * float((1.0-calculateGain(counter)));
		if (actualStatus == rise)
		{
			if (counter == lengthOfFade) actualStatus = atOne;
			else counter++;
		}
		if (actualStatus == fall)
		{
			if (counter == 0) actualStatus = atZero;
			else counter--;
		}
	}
}

// determine state return value
double EffectMixerClass::calculateGain(int count)
{
	switch (actualStatus)
	{
	case atZero:
	{
		return 0.0;
	}
	case rise:
	{
		return gainVec[count];
	}
	case atOne:
	{
		return 1.0;
	}
	case fall:
	{
		return gainVec[count];
	}
	}
	return 0.0;
}

// function to calculate window
void EffectMixerClass::calculateWin()
{
	gainVec = new double[lengthOfFade];
	memset(gainVec, 0, sizeof(gainVec));
	for (auto idx = 1; idx < sizeof(gainVec); idx++)
	{
		gainVec[idx] = sin(idx*((0.5*M_PI) / lengthOfFade - 1));
	}
}

