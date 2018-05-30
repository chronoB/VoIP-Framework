/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

// dummy class without any affect to the signal

#pragma once
#include <cstdio>
class FaerbungDummy
{
public:
	FaerbungDummy();
	~FaerbungDummy();
	void processAudio(float* in, float* out, int numOfSamples);
	void setParam(int NumParam, double Value);
};

