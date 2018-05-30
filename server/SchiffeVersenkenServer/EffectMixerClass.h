/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

// Class to Switch between processed and unprocessed audio

#pragma once
#include "audio_Parameter.h"
#include <cstring>
#include <math.h>


class EffectMixerClass
{
public:
	// constructor
	EffectMixerClass();
	// destructor
	~EffectMixerClass();
	// function to do the mixing
	void mixForEffects(float* processedBlock, float * unprocessedBlock, float* outBlock,int Status);

private:
	// enum for the states
	enum GainStatus{atZero, rise, atOne, fall};
	GainStatus actualStatus = atZero;
	// function to calculate the multiplicative gain
	double calculateGain(int count);
	// counter to access the right gain in the window array
	int counter = 0;
	// steps of the window
	int lengthOfFade = SAMPLE_RATE / 16;
	// variable to safe last status
	int setStatus = 0;
	// array for window
	double* gainVec;;
	// function to calculate the window
	void calculateWin(void);

};


