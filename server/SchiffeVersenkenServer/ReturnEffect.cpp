/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include "ReturnEffect.h"


// constructor
ReturnEffect::ReturnEffect()
{
}

// destructor
ReturnEffect::~ReturnEffect()
{
}

// function to process an audio block
void ReturnEffect::processAudio(float* inputBlock, float* returnBlock, float* outputBlock)
{
	ReturnGain->applyGain(returnBlock, paramGain);
	for(int idx = 0; idx < FRAMES_PER_BUFFER; idx++)
	{
		outputBlock[idx] = inputBlock[idx] + ReturnDelay->Process(returnBlock[idx]);
	} 
}

// function to set parameters 
void ReturnEffect::setParam(int numParam, double Value)
{
	calcParam(numParam, Value);
}

// calculate parameter
void ReturnEffect::calcParam(int numParam, double Value)
{
	switch (numParam)
	{
	case 1:
	{
		paramGain = int(gainRange * Value) - 60;
	}
	case 2:
	{
		paramDelay = int(maxDelay * Value);
		ReturnDelay->setDelay(paramDelay);
	}
	}
}

