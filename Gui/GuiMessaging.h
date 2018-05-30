/*
This file is part of the project "Schiffe-Versenken", a Voice-over-IP chat with disturbance algorithms.
The software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule).
This project is released under the terms of the MIT-license.
For license details see the license file.

Copyright (c) 2016	Finn Bayer			(finn.bayer@gmx.de)
Michael Schaffert	(pieter.michael.schaffert@googlemail.com)
Nils L. Westhausen	(n.westhausen@web.de)
*/

/* 
Class to generate j-son messages for communication with the server. It although initializes the connection to the server.
*/

#pragma once
#include "json.hpp"
using json = nlohmann::json;
#include "audio_parameter.h"
#include "sockClientClass.h"

class GuiMessaging
{
public:
	// constructor
	GuiMessaging();
	// destructor
	~GuiMessaging();
	// function generate message to set values of the effects
	void genMessage(int messID, int numSlot, int numEffect, int numParam, int Value);
	// function to initialize the sock class and connection to the sever
	int connect_to_server(const char* Ipadress, int SendPort);
	// function to generate message to set effect status
	void genMessage_setEffectStatus(int slot, int numEffect, int status) const; // status 1 = play ; status 0 = stop
	// functions to generate message to set recording status
	void genMessage_setRecording(int numClient, int status, std::string fileName) const; // status 1 = record
	void genMessage_setRecording(int numClient, int status) const; // status 0 = not recording
	// function to generate message to set audio out status
	void genMessage_setAudioOut(int location, int numLocation, int status) const; // location 0 = operator ; location 1 = Client
																			// status 0 = mute; status 1 = pre; status 2 = post
	// function to generate message to set the gain of the operator
	void genMessage_setGainOperator(int numOperator, int gain) const;

private:
	// functions to calculate parameters
	double calcParamNoise(int numParam, int value) const;
	double calcParamReverb(int numParam, int value) const;
	double calcParamBandpass(int value) const;
	double calcParamDistortion(int numParam, int value) const;
	double calcParamReverb(int value) const;
	double calcParamReturn(int numParam, int value) const;

	// function to generate message to set values of the parameters (ID = 3)
	void genMessage_setParameters(int slot, int numEffect, int numParameter, double value) const;
	
	// different parameters
	int numIdxNoise = 3;
	int rangeGain = 80;
	int maxFreqBandpass = SAMPLE_RATE / 2 - 10;
	int maxGainOverdrive = 40;
	int numCharacterization = 3;
	int numReverb = 1;
	int maxMixReverb = 1000;
	int maxTau60Reverb = 2000;
	int numColorization = 3;
	double maxDelayReturn = 1000.0;
	double valueParam = NULL;
	// array for the char message
	char* charMessage = new char[CHAR_PER_BUF];
	// sock client for network communication
	sockClient *NetworkHandle = nullptr;
};

