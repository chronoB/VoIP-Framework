/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

// class to handle the communication between buffer and portaudio

#pragma once
#include "audio_parameter.h"
#include "PortaudioPlus.h"
#include <stdio.h>
#include <thread>
#include "Buffer.h"

class PASupplier
{
public:
	// constructor
	PASupplier();
	// destructor
	~PASupplier();
	//Thread to continuously send Data to the AudioHandle
	std::thread PASpeakerThread(CPortaudioPlus * AudioHandle,Buffer *recv2paBuf,int *running) {
		return std::thread([=] {block2Speaker(AudioHandle, recv2paBuf,running); });//Thread that runs demandData to access the main function remotely
	}
	//Thread to continuously get Data from the AudioHandle
	std::thread PAMicrophoneThread(CPortaudioPlus * AudioHandle, Buffer *pa2sendBuf, int *running) {
		return std::thread([=] {microfone2Block(AudioHandle, pa2sendBuf, running); });//Thread that runs demandData to access the main function remotely
	}
	// threads for controlling the amount of blocks
	std::thread ReadControler(int* running) {
		return std::thread([=] {controlRead(running);});//Thread that runs demandData to access the main function remotely
	}
	std::thread WriteControler(int* running) {
		return std::thread([=] {controlWrite(running); });//Thread that runs demandData to access the main function remotely
	}

	
private:
	// counter and time for controlling
	int controlCounterWrite = 0;
	int controlCounterRead = 0;
	int measureTime = 60 * 1;
	// controller functions
	void controlRead(int* running);
	void controlWrite(int* running);
	// functions which handle audio
	void block2Speaker(CPortaudioPlus *, Buffer *, int *);
	void microfone2Block(CPortaudioPlus *, Buffer *, int *);
	
};