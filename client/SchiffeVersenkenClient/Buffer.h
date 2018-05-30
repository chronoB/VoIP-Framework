/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#pragma once
#include <stdio.h>
#include <ctime>
#include "audio_parameter.h"
#include <thread>


#define BUFFEREMPTY 1
#define BUFFERFULL 2

class Buffer
{
public:
	Buffer(int);
	~Buffer(void);
	//Function to get the Status (BUFFERFULL; BUFFEREMPTY)
	int getStatus(void);
	//Function to get a block from the buffer. Returns the status. (if empty, -1)
	int getBlock(float*);
	//Function to set a block to the buffer. Returns the status. (if full, -1)
	int setBlock(float*);
	//function to get the cur Count of the buf
	int getCount(void);

	std::thread BlockControlerSet(int* running, int id) {
		return std::thread([=] {controlBlocksSet(running, id); });//Thread that runs demandData to access the main function remotely
	}
	std::thread BlockControlerGet(int* running, int id) {
		return std::thread([=] {controlBlocksGet(running, id); });//Thread that runs demandData to access the main function remotely
	}


protected:
	//number of blocks that can be saved in the buffer
	int length;
	//status of the buffer
	int status;
	//helpVariable to check the status of the buffer
	int count;
	//variable to save the position of the read Pointer
	int readPtr;
	//variable to save the position of the write Pointer
	int writePtr;
	//helpBuffer to temporarily save data
	float* buf;
	void controlBlocksGet(int *running,int id);
	void controlBlocksSet(int *running, int id);
	
	//DEBUG
	int measureTime = 60 * 1;
	int controlCounterSet = 0;
	int controlCounterGet = 0;
	int buffer_id = 0;

};