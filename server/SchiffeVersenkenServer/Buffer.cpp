/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include "Buffer.h"
/*
counstructor
lengthOfBuffer -> number of blocks that can be saved in the buffer*/
Buffer::Buffer(int lengthOfBuffer)
{
	length = lengthOfBuffer;
	buf = new float[length*FRAMES_PER_BUFFER];
	status = BUFFEREMPTY; 
	readPtr = 0;
	count = 0;
	writePtr = 0;
}

/*
Destructor*/
Buffer::~Buffer(void)
{
	delete[] buf;
}

/*
Function to return the status of the Buffer
Returns:
BUFFERFULL -> if its full
BUFFEREMPTY -> if its empty
0 -> if everythings ok*/
int Buffer::getStatus(void)
{
	return status;
}
/*
Function to retrieve the block from the buffer
*outputBlock-> pointer to an array where the data should be stored*/

int Buffer::getBlock(float* outputBlock)
{
	if (status != BUFFEREMPTY)
	{
		for (int i = 0; i < FRAMES_PER_BUFFER; i++)
		{
			outputBlock[i] = buf[readPtr];
			readPtr = (readPtr + 1) % (length*FRAMES_PER_BUFFER);
		}
		count--;
		if (count <= 0)
		{
			status = BUFFEREMPTY;
		}
		else
			status = 0;

		return 0;
	}
	else
	{
		return -1;
	}
	
	
	
}

/*
Function to store a block of samples in the buffer
*inputBlock -> pointer to an array that should be stored to the buffer*/
int Buffer::setBlock(float* inputBlock)
{
	if (status != BUFFERFULL)
	{
		for (int i = 0; i < FRAMES_PER_BUFFER; i++)
		{
			buf[writePtr] = inputBlock[i];
			writePtr = (writePtr + 1) % (this->length*FRAMES_PER_BUFFER);
		}
		count++;
		if (count >= length)
		{
			status = BUFFERFULL;
		}
		else
			status = 0;
		return 0;
	}
	else
	{
		return -1;
	}
	
}


/*
Function to return the current number of blocks stored in the buffer*/
int Buffer::getCount(void)
{
	return count;
}

/*
Function to clear the Buffer*/
int Buffer::clearBuffer(void)
{
	readPtr = writePtr = count = 0;
	status = BUFFEREMPTY;
	return 0;
}
