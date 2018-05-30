/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

// class to parse audio to portaudio

#pragma once

#include "audio_parameter.h"
#include "PortaudioPlus.h"
#include "Buffer.h"
#include <mutex>
#include <thread>

class PASupplier
{
public:
	// constructor
	PASupplier();
	// destructor
	~PASupplier();
	//Thread to continuously send Data to PortAudio
	std::thread PASpeakerThread(CPortaudioPlus * AudioHandle, Buffer *soundBufOperator1, Buffer *soundBufOperator2, int *running) {
		return std::thread([=] {block2Speaker(AudioHandle, soundBufOperator1, soundBufOperator2, running); });//Thread der demandData ausführt. Dadurch ist eine remoteZugriff von der main funktion möglich
	}
	
private:
	// function to parse audio to portaudio
	void block2Speaker(CPortaudioPlus *, Buffer *, Buffer *, int *);
};