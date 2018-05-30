/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include "audio_parameter.h"
#include "addnoise.h"

//using namespace std;

AddNoise::AddNoise()
{
}

AddNoise::~AddNoise()
{
}

void AddNoise::WhiteNoise(float *In, float *Out)
{

	for (idx = 0; idx < FRAMES_PER_BUFFER; idx++)
	{
		genWhiteNoise();
		Out[idx] = In[idx] + noiseGain->apllyGain(white_noise , Gain);
	};
};

void AddNoise::PinkNoise(float *In, float *Out) //can be used, if pink noise coefs are corrected
{

	for (idx = 0; idx < FRAMES_PER_BUFFER; idx++)
	{
		genWhiteNoise();
		filterPink();
		Out[idx] = In[idx] + noiseGain->apllyGain(pink_noise, Gain);
	};

};

void AddNoise::BrownNoise(float *In, float *Out) //can be used, if brown noise coefs are corrected
{

	for (idx = 0; idx < FRAMES_PER_BUFFER; idx++)
	{
		genWhiteNoise();
		filterBrown();
		Out[idx] = In[idx] + noiseGain->apllyGain(brown_noise, Gain);
	};

}

void AddNoise::filterPink() //Filter coeffs for pink noise. MUST BE CHANGED, the coefs do not work correctly
{
	pink_noise = white_noise - a1_pink*pink_state_1 - a2_pink*pink_state_2 - a3_pink*pink_state_3 - a4_pink*pink_state_4 - a5_pink*pink_state_5;
	pink_state_5 = pink_state_4;
	pink_state_4 = pink_state_3;
	pink_state_2 = pink_state_1;
	pink_state_1 = pink_noise;
}

void AddNoise::filterBrown() //Filter coeffs for brown noise. MUST BE CHANGED, the coefs do not work correctly
{
	brown_noise = white_noise - a1_brown*brown_state_1 - a2_brown*brown_state_2 - a3_brown*brown_state_3 - a4_brown*brown_state_4 - a5_brown*brown_state_5;
	brown_state_5 = brown_state_4;
	brown_state_4 = brown_state_3;
	brown_state_2 = brown_state_1;
	brown_state_1 = brown_noise;
}

void AddNoise::genWhiteNoise() //generates the white noise
{
	for (i = 1; i <= 12; i++)
	{
		white_noise = white_noise + ((float)rand() / (float)RAND_MAX - 0.5f);	//Add 12 random numbers between [-0.5 0.5] to Noise. 
																				//Results in a normal distributioncurve cutoff at [-6 6]
	};
	white_noise = white_noise / 6.0f;
};

void AddNoise::CopyDummy(float* inBlock, float* outBlock)
{
	for (idx = 0; idx < FRAMES_PER_BUFFER; idx++)
	{
		outBlock[idx] = inBlock[idx];
	};
}

void AddNoise::setParam(int numParam, double Value)  //Sets the selected parameter
{
	switch (numParam)
	{
	case 1:
	{
		whichNoise = int(Value * double(maxNoises)); //checks, which kind of noise is selected
		return;
	}
	case 2:
	{
		Gain = int(Value * 80.0) - 60; //implements the used Gain between -60dB and 20dB
		return;
	}
	}
}

void AddNoise::processAudio(float* inBlock, float* outBlock, int NumOfSamples)
{
	switch (whichNoise)
	{
	case 0:
	{
		WhiteNoise(inBlock, outBlock);
		return;
	}
	case 1:
	{
		PinkNoise(inBlock, outBlock);
		return;
	}
	case 2:
	{
		BrownNoise(inBlock, outBlock);
		return;
	}
	case 3:
	{
		CopyDummy(inBlock, outBlock);
		return;
	}
	}
};
