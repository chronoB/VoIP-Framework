/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include "AudioOutMixer.h"

// constructor with window calculation
AudioOutMixer::AudioOutMixer()
{
	calculateWin();
}

// destructor
AudioOutMixer::~AudioOutMixer()
{
	// delete window array
	delete[] gainVec;
}

// apply Gain with two state machines
void AudioOutMixer::mixForOutput(float* processedBlock, float* unprocessedBlock, float* outBlock, int Status)
{
	if (lastStatus != Status)
	{   
		switch (Status)
		{
		case 0: //mute
		{
			actualStatusProcesssed = fall;
			actualStatusUnprocessed = fall;
			break;
		}
		case 1: // pre
		{
			actualStatusProcesssed = fall;
			actualStatusUnprocessed = rise;
			break;
		}
		case 2: // post
		{
			actualStatusProcesssed = rise;
			actualStatusUnprocessed = fall;
			break;
		}
		}
		
	}
	// processing audio block
	for (auto idx = 0; idx < FRAMES_PER_BUFFER; idx++)
	{
		outBlock[idx] = processedBlock[idx] * float(calculateGainProcessed()) + unprocessedBlock[idx] * float(calculateGainUnprocessed());
	}
	lastStatus = Status;
}

// function to calculate gain dependent on the state
double AudioOutMixer::calculateGainUnprocessed()
{
	switch (actualStatusUnprocessed)
	{
	case atZero:
	{
		return 0.0;
	}
	case rise:
	{
		if (counterUnprocessed == lengthOfFade) actualStatusUnprocessed = atOne;
		else counterUnprocessed++;
		return gainVec[counterUnprocessed];
	}
	case atOne:
	{
		return 1.0;
	}
	case fall:
	{
		if (counterUnprocessed == 0) actualStatusUnprocessed = atZero;
		else counterUnprocessed--;
		return gainVec[counterUnprocessed];
	}
	}
	return 0.0;
}

// function to calculate gain dependent on the state
double AudioOutMixer::calculateGainProcessed()
{
	switch (actualStatusProcesssed)
	{
	case atZero:
	{
		return 0.0;
	}
	case rise:
	{
		if (counterProcessed == lengthOfFade) actualStatusProcesssed = atOne;
		else counterProcessed++;
		return gainVec[counterProcessed];
	}
	case atOne:
	{
		return 1.0;
	}
	case fall:
	{
		if (counterProcessed == 0) actualStatusProcesssed = atZero;
		else counterProcessed--;
		return gainVec[counterProcessed];
	}
	}
	return 0.0;
}

// calculates gains in a sin curve
void AudioOutMixer::calculateWin()
{
	gainVec = new double[lengthOfFade];
	memset(gainVec, 0, sizeof(gainVec));
	for (auto idx = 1; idx < sizeof(gainVec); idx++)
	{
		gainVec[idx] = sin(idx*((0.5*M_PI)/lengthOfFade-1));
	}
}
