/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include "controlBuffer.h"

/*constructor that calls the constructor of the parent class*/
controlBuffer::controlBuffer(int lengthOfBuffer) : Buffer(lengthOfBuffer)
{

}

/*destructor*/
controlBuffer::~controlBuffer()
{
}
/*
Function to set Blocks to the buffer
It dismisses Blocks if the Buffer is to full. Therefor no overflow is possible.*/
int controlBuffer::controlledSetBlock(float* inputBlock)
{
	if (getCount() > 5)
	{
		readPtr += 3; //3 Blocks will be dismissed
		count -= 3;
		printf("Info: Three Blocks were dismissed.\n");
	}
	for (int i = 0; i < FRAMES_PER_BUFFER; i++)
	{
		buf[writePtr] = inputBlock[i];
		writePtr = (writePtr + 1) % (this->length*FRAMES_PER_BUFFER);
	}
	count++;
	if (count >= length)
		status = BUFFERFULL;
	else
		status = 0;
	return 0;
	
}
