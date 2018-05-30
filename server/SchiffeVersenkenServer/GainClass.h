/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

// class to apply gain to the signal with interpolation between the steps
#pragma once
#include <cmath>
#include "audio_parameter.h"


class GainClass
{
public:
	// constructor
	GainClass();
	// destructor
	~GainClass();
	// function to apply gain to one block
	void applyGain(float* block, int gain);
	// function to apply gain to one sample
	float apllyGain(float frame, int gain);
	// function to return gain
	double getGain(int gain);

private:
	// function to return the current gain value
	double getGain(void);
	// array of gain values
	double* gainVec;
	// function to calculate the gain value array
	void calculateGainVec(void);
	// some values
	int gainRange = 80;
	int minGain = -60;
	int lastGain = -60;
	int factor = 100;
	int counter = 0;
	// enum states for state machine
	enum states{actual, rise, fall};
	states GainState = actual;
	
};

