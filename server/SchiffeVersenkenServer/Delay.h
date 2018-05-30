/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

// class for the delay effect of the return

#pragma once
#include "audio_parameter.h"
class Delay
{

public:
	// constructor
	Delay(int max_delay);  
	// destructor
	~Delay();

	//Process one sample
	float Process(float sample); 
	// setter for delay
	void setDelay(int dealyInMs);

private:
	// reads one sample from the ring buffer
	float ReadSample();
	//writes one sample to the ring buffer
	void WriteSample(float sample);
	// size of the ring buffer
	int sizeOfRingbuffer;  
	// read pointer 
	int readPointer;  
	// write pointer
	int writePointer;  
	// buffer
	float* ringBuffer;
	// default values
	int delayInSamples = 0;
	float outputSample = 0.0f;
	float retVal = 0.0;
	int delayInSamplesNew = 0;
	int newReadPointer = 0;

};
