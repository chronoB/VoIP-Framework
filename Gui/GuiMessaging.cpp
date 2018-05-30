/*
This file is part of the project "Schiffe-Versenken", a Voice-over-IP chat with disturbance algorithms.
The software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule).
This project is released under the terms of the MIT-license.
For license details see the license file.

Copyright (c) 2016	Finn Bayer			(finn.bayer@gmx.de)
Michael Schaffert	(pieter.michael.schaffert@googlemail.com)
Nils L. Westhausen	(n.westhausen@web.de)
*/

// class to generate and sen messages to the server

#include "GuiMessaging.h"

// constructor
GuiMessaging::GuiMessaging()
{	
}

// destructor
GuiMessaging::~GuiMessaging()
{
	// destroy array
	delete[] charMessage;
	// destroy network handle
	delete NetworkHandle;
}

// function to connect to server
int GuiMessaging::connect_to_server(const char* Ipadress, int SendPort)
{
	NetworkHandle = new sockClient();
	return NetworkHandle->conect_to_server(Ipadress, SendPort);
}

// function to generate message
void GuiMessaging::genMessage(int messID, int numSlot, int numEffect, int numParam, int Value)
{
	if (messID == 3)
	{
		// checking for the effect to calculate the right parameters
		if (numEffect == NOISE)
		{
			valueParam = calcParamNoise(numParam, Value);
			genMessage_setParameters(numSlot, numEffect, numParam, valueParam);

		}
		else if (numEffect == BANDPASS)
		{
			valueParam = calcParamBandpass(Value);
			genMessage_setParameters(numSlot, numEffect, numParam, valueParam);

		}
		else if (numEffect == DISTORTION)
		{
			valueParam = calcParamDistortion(numParam, Value);
			genMessage_setParameters(numSlot, numEffect, numParam, valueParam);
		}
		else if (numEffect == REVERB)
		{
			valueParam = calcParamHall(numParam, Value);
			genMessage_setParameters(numSlot, numEffect, numParam, valueParam);
		}
		else if (numEffect == COLORIZATION)
		{
			valueParam = calcParamColorization(Value);
			genMessage_setParameters(numSlot, numEffect, numParam, valueParam);
		}
		else if (numEffect == ReturnL)
		{
			valueParam = calcParamReturn(numParam, Value);
			genMessage_setParameters(numSlot, numEffect, numParam, valueParam);
		}
		else if (numEffect == ReturnR)
		{
			valueParam = calcParamReturn(numParam, Value);
			genMessage_setParameters(numSlot, numEffect, numParam, valueParam);
		}
	}
}

// functions to create messages

void GuiMessaging::genMessage_setEffectStatus(int slot, int numEffect, int status) const
{
	json singleMessage;
	singleMessage["type"] = "setEffectStatus";
	singleMessage["slot"] = slot;
	singleMessage["numEffect"] = numEffect;
	singleMessage["status"] = status;
	NetworkHandle->sendCharData(singleMessage.dump().c_str());
}

void GuiMessaging::genMessage_setParameters(int slot, int numEffect, int numParameter, double value) const
{
	json singleMessage;
	singleMessage["type"] = "setParameters";
	singleMessage["slot"] = slot;
	singleMessage["numEffect"] = numEffect;
	singleMessage["numParameter"] = numParameter;
	singleMessage["value"] = value;
	NetworkHandle->sendCharData(singleMessage.dump().c_str());
}

void GuiMessaging::genMessage_setRecording(int numClient, int status, std::string fileName) const
{
	json singleMessage;
	singleMessage["type"] = "setRecording";
	singleMessage["numClient"] = numClient;
	singleMessage["status"] = status;
	singleMessage["fileName"] = fileName;
	NetworkHandle->sendCharData(singleMessage.dump().c_str());
	
}

void GuiMessaging::genMessage_setRecording(int numClient, int status) const
{
	json singleMessage;
	singleMessage["type"] = "setRecording";
	singleMessage["numClient"] = numClient;
	singleMessage["status"] = status;
	singleMessage["fileName"] = NULL;
	NetworkHandle->sendCharData(singleMessage.dump().c_str());
}

void GuiMessaging::genMessage_setAudioOut(int location, int numLocation, int status) const
{
	json singleMessage;
	singleMessage["type"] = "setAudioOut";
	singleMessage["location"] = location;
	singleMessage["numLocation"] = numLocation;
	singleMessage["status"] = status;
	NetworkHandle->sendCharData(singleMessage.dump().c_str());
}

void GuiMessaging::genMessage_setGainOperator(int numOperator, int gain) const
{
	json singleMessage;
	singleMessage["type"] = "setGainOperator";
	singleMessage["numOperator"] = numOperator;
	singleMessage["gain"] = calcParamNoise(2, gain);
	NetworkHandle->sendCharData(singleMessage.dump().c_str());
}

// functions to calculate parameters
double GuiMessaging::calcParamNoise(int numParam, int value) const
{
	if (numParam == 1) 
	{
		return double(value) / double(numIdxNoise);
	}
	else if (numParam == 2)
	{
		return (double(value) + 60.0) / double(rangeGain);
	}
	return -1;
}

double GuiMessaging::calcParamHall(int numParam, int value) const
{
	if (numParam == 1)
	{
		return double(value) / double(numHall);
	}
	else if (numParam == 2)
	{
		return double(value) / double(maxMixHall);
	}
	else if (numParam == 3)
	{
		return double(value) / double(maxTau60Hall);
	}
	return -1;
}

double GuiMessaging::calcParamBandpass(int value) const
{	
	return double(value) / double(maxFreqBandpass);		
}

double GuiMessaging::calcParamDistortion(int numParam, int value) const
{
	if (numParam == 1)
	{
		return double(value) / double(numCharacterization);
	}
	else if (numParam == 2)
	{
		return double(value) / double(maxGainOverdrive);
	}
	return -1;
	
}

double GuiMessaging::calcParamColorization(int value) const
{
	return double(value) / double(numColorization);
}

double GuiMessaging::calcParamReturn(int numParam, int value) const
{
	if (numParam == 1)
	{
		return (double(value) + 60.0) / double(rangeGain);
	}
	else if (numParam == 2)
	{
		return (double(value)  / maxDelayReturn);
	}
	return -1;
}
