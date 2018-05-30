/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

// class to manage all signal processing

#pragma once
#include "audio_parameter.h"
#include <string.h>
#include <thread>
#include "Buffer.h"
#include "EffectMixerClass.h"
#include "AudioOutMixer.h"
#include "EffectSlot.h"
#include "ReturnEffect.h"
#include "GainClass.h"
#include "WavHandling.h"
#include "controlBuffer.h"

class Audioprocessor
{
public:
	// constructor
	Audioprocessor(void);
	// destructor
	~Audioprocessor(void);
	void manageData(Buffer *recvBuf, Buffer *sendBuf, Buffer *ownReturnBuf, Buffer *otherReturnBuffer, controlBuffer *soundOperator, int *running);
	std::thread manageDataThread(Buffer *recvBuf, Buffer *sendBuf, Buffer *ownReturnBuf, Buffer *otherReturnBuffer, controlBuffer *soundOperator, int *running) {
		return std::thread([=] {manageData(recvBuf, sendBuf, ownReturnBuf, otherReturnBuffer, soundOperator, running); });
	}
	// setter functions
	void setParam(int numSlot, int numEffect, int NumParam, double Value);
	void setAudioAudioOut(int position, int Status);
	void setEffectStatus(int numSlot, int numEffect, int Status);
	void setGainOperator(double Value);
	//Function to start the Recording of the wavHandling object
	void startRecording(const char*, int);
	//Function to stop the Recording of the wavHandling object
	void stopRecording(void);


private:
	//checkVariable for the buffer
	int ret;
	// Gain values for output
	int operatorGain = -60;
	int clientGain = -3;

	// declaration of audio blocks
	float* cleanBlock = new float[FRAMES_PER_BUFFER];
	float* slot1Block = new float[FRAMES_PER_BUFFER];
	float* slot2Block = new float[FRAMES_PER_BUFFER];
	float* slot3Block = new float[FRAMES_PER_BUFFER];
	float* slot4Block = new float[FRAMES_PER_BUFFER];
	float* outEffectBlock = new float[FRAMES_PER_BUFFER];
	float* outOperatorBlock = new float[FRAMES_PER_BUFFER];
	float* outClientBlock = new float[FRAMES_PER_BUFFER];
	float* returnBlock = new float[FRAMES_PER_BUFFER];
	float* tempslot1Block = new float[FRAMES_PER_BUFFER];
	float* tempslot2Block = new float[FRAMES_PER_BUFFER];
	float* tempslot3Block = new float[FRAMES_PER_BUFFER];
	float* tempslot4Block = new float[FRAMES_PER_BUFFER];

	// heart of processing
	void processAudio();

	// Effect Mixer
	EffectMixerClass *mixerSlot1 = new EffectMixerClass;
	EffectMixerClass *mixerSlot2 = new EffectMixerClass;
	EffectMixerClass *mixerSlot3 = new EffectMixerClass;
	EffectMixerClass *mixerSlot4 = new EffectMixerClass;

	// Audio Out Mixer
	AudioOutMixer *mixerClient = new AudioOutMixer;
	AudioOutMixer *mixerOperator = new AudioOutMixer;

	// status ints
	int StatusSlot1 = 0;
	int StatusSlot2 = 0;
	int StatusSlot3 = 0;
	int StatusSlot4 = 0;
	int StatusClient = 0;
	int StatusOpeator = 0;

	// declaration of slots
	EffectSlot *slotEffect1 = new EffectSlot;
	EffectSlot *slotEffect2 = new EffectSlot;
	EffectSlot *slotEffect3 = new EffectSlot;
	ReturnEffect *slotReturn = new ReturnEffect;

	// Gain for Operator
	GainClass *applyOperatorGain = new GainClass;
	GainClass *applyClientGain = new GainClass;

	//Object to save the audio data to a wavFile
	CWavHandling *wavHandler = new CWavHandling(NULL, NULL);
};