/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/
					
#include "FaerbungDummy.h"

FaerbungDummy::FaerbungDummy()
{
}


FaerbungDummy::~FaerbungDummy()
{
}

void FaerbungDummy::processAudio(float* in, float* out, int numOfSamples)
{
	for (int idx = 0; idx < numOfSamples; idx++)
	{
		out[idx] = in[idx];
	}
}

void FaerbungDummy::setParam(int NumParam, double Value)
{
	printf("Parameter wurde gesetzt(Farbe)");
}
