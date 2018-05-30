/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include "PASupplier.h"

// constructor
PASupplier::PASupplier()
{	
}
// destructor
PASupplier::~PASupplier()
{
}

// function to control how much blocks red from sound card
void PASupplier::controlRead(int* running)
{
	// waiting for the start of the communication
	while (*running == 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	int counter_here;
	// starting controlling
	while (*running == 1)
	{
		controlCounterRead = 0;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 * measureTime));
		counter_here = controlCounterRead;
		double frames_per_second = double(counter_here) * double(FRAMES_PER_BUFFER) / double(measureTime);
		printf("Read from Soundcard: Fs = %f\n", frames_per_second);
		printf("Blocks read: %d\n\n", counter_here);
	}

}

// function to control how much blocks written to sound card
void PASupplier::controlWrite(int* running)
{
	// waiting for the start of the communication
	while (*running == 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	int counter_here;
	// starting controlling
	while (*running == 1)
	{
		controlCounterWrite = 0;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 * measureTime));
		counter_here = controlCounterWrite;
		double frames_per_second = double(counter_here) * double(FRAMES_PER_BUFFER) / double(measureTime);
		printf("Write to Soundcard: Fs = %f\n", frames_per_second);
		printf("Blocks written: %d\n\n", counter_here);
	}

}

// function to give block to portaudio
void PASupplier::block2Speaker(CPortaudioPlus * AudioHandle, Buffer * recv2paBuf, int * running)
{
	auto* tmpBuf = new float[FRAMES_PER_BUFFER];
	CLEAR(tmpBuf);
	// waiting for the start of the communication
	while (*running == 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	// start writing
	while (*running == 1)
	{
		if (recv2paBuf->getStatus() != BUFFEREMPTY)
		{
			recv2paBuf->getBlock(tmpBuf);
			AudioHandle->writeBlock(tmpBuf);
			controlCounterWrite++;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
	printf("Shutting down PASpeakerHandler.\n");
	delete[] tmpBuf;
}

// function to get block from portaudio
void PASupplier::microfone2Block(CPortaudioPlus * AudioHandle, Buffer * pa2sendBuf, int * running)
{
	auto* tmpBuf = new float[FRAMES_PER_BUFFER];
	CLEAR(tmpBuf);
	// waiting for the start of the communication
	while (*running == 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	// start reading
	while (*running == 1)
	{
		if (pa2sendBuf->getStatus() != BUFFERFULL)
		{
			AudioHandle->readBlock(tmpBuf, 1);
			pa2sendBuf->setBlock(tmpBuf);
			controlCounterRead++;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
	printf("Shutting down PAMicrophoneHandler.\n");
	delete[] tmpBuf;
}





