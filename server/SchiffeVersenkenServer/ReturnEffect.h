/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

// class to implement the return effect

#pragma once
#include "Delay.h"
#include "GainClass.h"
#include <cmath>
#include <cstdio>

class ReturnEffect
{
public:
	// constructor
	ReturnEffect();
	// destructor
	~ReturnEffect();
	// function to process audio
	void processAudio(float* inputBlock, float* returnBlock, float* outputBlock);
	// function to set parameters
	void setParam(int numParam, double Value);

private:
	// some parameters
	double maxDelay = 1000.0;
	double gainRange = 80.0;
	double lowestGain = -60.0;
	int paramGain = - 60;
	int paramDelay = 0;
	// function to calculate parameters
	void calcParam(int numParam, double Value);
	// initialization of gain and delay object
	Delay *ReturnDelay = new Delay(int(maxDelay));
	GainClass *ReturnGain = new GainClass();
};

