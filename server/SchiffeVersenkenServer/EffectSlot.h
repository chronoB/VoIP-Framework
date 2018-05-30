/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

// class to inherit and initialize all effects

#pragma once
#include "FaerbungDummy.h"
#include "bandpass.h"
#include "overdrive.h"
#include "addnoise.h"
//#include "ReverbAlgo.h"
#include "audio_parameter.h"

class EffectSlot
{
public:
	// constructor
	EffectSlot();
	// destructor
	~EffectSlot();
	// function to parse audio to the right effect
	void processAudio(float* inputBlock, float* outputBlock);
	// function to set which effect is active
	void setEffectStatus(int numEffect);
	// function to parse parameters to the right effect
	void setParam(int numEffect, int numParam, double Value);

private:
	// variable which effect is active
	int whichEffect = 0;
	// initialization of all effects
	AddNoise *noiseEffect = new AddNoise;
	BandPass *bandpassEffect = new BandPass;
	OverDrive * distortionEffect = new OverDrive;
//	CReverbAlgo *reverbEffect = new CReverbAlgo(SAMPLE_RATE, 0.f, 0.0f);
	FaerbungDummy * colorationEffect = new FaerbungDummy;
};

