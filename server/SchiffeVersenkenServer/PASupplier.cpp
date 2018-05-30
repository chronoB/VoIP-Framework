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

//Function to distribute the incomming Audio to the PortAudio class
void PASupplier::block2Speaker(CPortaudioPlus * AudioHandle, Buffer * soundBufOperator1, Buffer * soundBufOperator2, int * running)
{
	float* tmpBuf1 = new float[FRAMES_PER_BUFFER];
	float* tmpBuf2 = new float[FRAMES_PER_BUFFER];
	// waiting for the start of communication
	while (*running == 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	// satrting to play audio
	while (*running == 1)
	{
		if (soundBufOperator1->getStatus() != BUFFEREMPTY || soundBufOperator2->getStatus() != BUFFEREMPTY)
		{
			if (soundBufOperator1->getStatus() != BUFFEREMPTY)
				soundBufOperator1->getBlock(tmpBuf1);
			else
				CLEAR(tmpBuf1);
			if (soundBufOperator2->getStatus() != BUFFEREMPTY)
				soundBufOperator2->getBlock(tmpBuf2);
			else  
				CLEAR(tmpBuf2);
			AudioHandle->writeBlock(tmpBuf1, tmpBuf2);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
	printf("Shutting down PASpeakerHandler.\n");
}
