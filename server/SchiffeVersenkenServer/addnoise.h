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
#include "stdlib.h"
#include <math.h>
#include "GainClass.h"


class AddNoise
{
public:

	AddNoise();
	~AddNoise();
	void setParam(int numParam, double Value);
	void processAudio(float* inBlock, float* outBlock, int NumOfSamples);


private:

	void WhiteNoise(float *In, float *Out);
	void PinkNoise(float *In, float *Out);
	void BrownNoise(float *In, float *Out);
	void filterPink();
	void filterBrown();
	void genWhiteNoise();

	void CopyDummy(float* inBlock, float* outBlock);

	//Noise parameter
	int whichNoise = 0;
	int maxNoises = 3;			//Must be updated if more Noise-Algorithms are implemented
	int maxGainNoise = 20;
	int idx = 0;
	int Gain = -60;
	GainClass *noiseGain = new GainClass();
	int i = 0;
	float white_noise = 0.0;
	float pink_noise = 0.0;
	float brown_noise = 0.0;

	//Pink Noise (1/f) coefs from matlab help dsp.ColoredNoise
	int alpha_pink = 1;
	float a0_pink = 1;
	float a1_pink = (1 - 1 - alpha_pink / 2)*(a0_pink / 1);
	float a2_pink = (2 - 1 - alpha_pink / 2)*(a1_pink / 2);
	float a3_pink = (3 - 1 - alpha_pink / 2)*(a2_pink / 3);
	float a4_pink = (4 - 1 - alpha_pink / 2)*(a3_pink / 4);
	float a5_pink = (5 - 1 - alpha_pink / 2)*(a4_pink / 5);

	float pink_state_1 = 0;
	float pink_state_2 = 0;
	float pink_state_3 = 0;
	float pink_state_4 = 0;
	float pink_state_5 = 0;

	//Brown Noise (1/(f²)) coefs from matlab help dsp.ColoredNoise
	int alpha_brown = 2;
	float a0_brown = 1;
	float a1_brown = (1 - 1 - alpha_brown / 2)*(a0_brown / 1);
	float a2_brown = (2 - 1 - alpha_brown / 2)*(a1_brown / 2);
	float a3_brown = (3 - 1 - alpha_brown / 2)*(a2_brown / 3);
	float a4_brown = (4 - 1 - alpha_brown / 2)*(a3_brown / 4);
	float a5_brown = (5 - 1 - alpha_brown / 2)*(a4_brown / 5);

	float brown_state_1 = 0;
	float brown_state_2 = 0;
	float brown_state_3 = 0;
	float brown_state_4 = 0;
	float brown_state_5 = 0;
};