/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include "Delay.h"

// Constructor
Delay::Delay(int max_delay)
{
	//Initialize values
	sizeOfRingbuffer = max_delay+1;
	readPointer = 0;
	writePointer = 0;;

	// fill buffer with zeros
	ringBuffer = new float[sizeOfRingbuffer];
	for (int idx = 0; idx < sizeOfRingbuffer; idx++)
	{
		ringBuffer[idx] = 0.0f;
	}
}


Delay::~Delay()
{
	delete[] ringBuffer;
}

//Writes a sample into buffer
void Delay::WriteSample(float sample)// Sample Value
{
	//write sample
	ringBuffer[writePointer] = sample;
	//update write position
	writePointer = (writePointer + 1) % sizeOfRingbuffer;
}

//Reads a sample from buffer
float Delay::ReadSample()
{
	//read sample
	retVal = ringBuffer[readPointer];
	//update read pointer
	readPointer = (readPointer + 1) % sizeOfRingbuffer;
	return retVal;
}

//Process a given sample
float Delay::Process(float sample) 
{
	WriteSample(sample);
	outputSample = ReadSample();
	return outputSample;
}

// setter for delay
void Delay::setDelay(int delayInMs)
{
	delayInSamplesNew = int(double(delayInMs) / 1000.0 * double(SAMPLE_RATE));
	newReadPointer = readPointer + (delayInSamples - delayInSamplesNew);
	if (newReadPointer < 0)
		readPointer = sizeOfRingbuffer + newReadPointer;
	else
		readPointer = newReadPointer % sizeOfRingbuffer;
	delayInSamples = delayInSamplesNew;
}
