/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

// mixer to mix the output for client and Operator

#pragma once
#include "audio_parameter.h"
#include <cstring>
#include <math.h>

class AudioOutMixer
{
public:
	// constructor
	AudioOutMixer();
	// destructor
	~AudioOutMixer();
	// function to mix outputs
	void mixForOutput(float* processedBlock, float * unprocessedBlock, float* outBlock, int Status);
private:
	// enum for different states
	enum gainStatus{atZero,rise,atOne,fall};
	gainStatus actualStatusProcesssed = atZero;
	gainStatus actualStatusUnprocessed = atZero;
	// one counter for each state machine
	int counterProcessed = 0;
	int counterUnprocessed = 0;
	// time to fade in other state
	int lengthOfFade = SAMPLE_RATE / 16;
	// variable to check if status has changed
	int lastStatus = 0;
	double* gainVec;
	// functions to return the gain and calculate the gain vector
	double calculateGainProcessed();
	double calculateGainUnprocessed();
	void calculateWin(void);
};

