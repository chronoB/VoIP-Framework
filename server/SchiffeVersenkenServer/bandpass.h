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
#include <math.h>
#include <iostream>
#include "audio_parameter.h"

class BandPass
{
public:

	BandPass();
	~BandPass();
	void setParam(int numParam, double Value);
	void processAudio(float* inBlock, float* outBlock, int NumOfSamples);

private:

	void BandFilt(float *In, float* Out);
	void designFiltHigh(void);
	void designFiltLow(void);

	//general variables
	int idx;
	int k;
	float pi = float(M_PI);
	int whichFilt = 0;
	//int GainBandFilt = XX;		//if Output correction is needed

	//LowCut variables
	int max_f_low = SAMPLE_RATE / 2 - 10;
	float f_low = float((SAMPLE_RATE / 2 - 10));
	float Q_low = float(0.707);
	int Q_low_max = 1;

	float w0_low;
	float alpha_low;

	float a0_low;
	float a1_low;
	float a2_low;
	float b0_low;
	float b1_low;
	float b2_low;

	float low_aState1;
	float low_aState2;
	float low_bState1;
	float low_bState2;

	//HighCut variables
	float f_high = 5.0f;
	int min_f_high = 5;
	int max_f_high = SAMPLE_RATE / 2 - 10;
	float Q_high = float(0.707);
	int Q_high_max = 1;

	float w0_high;
	float alpha_high;

	float a0_high;
	float a1_high;
	float a2_high;
	float b0_high;
	float b1_high;
	float b2_high;

	float high_aState1;
	float high_aState2;
	float high_bState1;
	float high_bState2;
};
