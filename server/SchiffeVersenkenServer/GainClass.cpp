/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include "GainClass.h"


// constructor
GainClass::GainClass()
{
	// initializes GainVec
	calculateGainVec();
}

// destructor
GainClass::~GainClass()
{
	delete gainVec;
}

// function to apply gain to audio block
void GainClass::applyGain(float* block, int gain)
{
	if (gain != lastGain)
	{
		if (gain < lastGain)
		{
			GainState = fall;
		}
		else
		{
			GainState = rise;
		}
	}
	lastGain = gain;
	for (auto idx = 0; idx < FRAMES_PER_BUFFER; idx++)
	{
		block[idx] = block[idx] * float(getGain());
	}
}

// function to apply gain to a single sample
float GainClass::apllyGain(float frame, int gain)
{
	if (gain != lastGain)
	{
		if (gain < lastGain)
		{
			GainState = fall;
		}
		else
		{
			GainState = rise;
		}
	}
	lastGain = gain;
	return frame = frame * float(getGain());
}

// function to just return the gain value
double GainClass::getGain(int gain)
{
	if (gain != lastGain)
	{
		if (gain < lastGain)
		{
			GainState = fall;
		}
		else
		{
			GainState = rise;
		}
	}
	lastGain = gain;
	return getGain();
}

// state machine to return gain value
double GainClass::getGain()
{
	switch (GainState)
	{
	case actual:
	{
		return gainVec[counter];
	}
	case rise:
	{
		if (((lastGain -minGain) * factor) == counter)
		{
			GainState = actual;
		}
		else counter++;
		return  gainVec[counter];
	}
	case fall:
	{
		if (((lastGain - minGain) * factor) == counter)
		{
			GainState = actual;
		}
		else counter--;
		return  gainVec[counter];
	}
	}
	return 0.0;

}

// calculates logarithmic gain values in an array
void GainClass::calculateGainVec()
{
	gainVec = new double[gainRange * factor + 1];
	for (auto idx = 0; idx < gainRange * factor + 1; idx++)
	{
		gainVec[idx] = pow(10.0, (double(idx) / 100 + double(minGain))/20.0);
	}
}
