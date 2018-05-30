/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include "bandpass.h"

BandPass::BandPass()
{
	designFiltHigh();
	designFiltLow();
	low_aState1 = 0.0f;
	low_aState2 = 0.0f;
	low_bState1 = 0.0f;
	low_bState2 = 0.0f;
	high_aState1 = 0.0f;
	high_aState2 = 0.0f;
	high_bState1 = 0.0f;
	high_bState2 = 0.0f;
}

BandPass::~BandPass()
{
}

void BandPass::BandFilt(float *In, float* Out) //Implementation of Direct Form I
{
	for (k = 0; k < FRAMES_PER_BUFFER; k++) //DF1 Form of Low-pass filter
	{
		Out[k] = In[k] * b0_low + low_bState1*b1_low + low_bState2*b2_low - low_aState1*a1_low - low_aState2*a2_low;

		low_bState2 = low_bState1;
		low_bState1 = In[k];
		low_aState2 = low_aState1;
		low_aState1 = Out[k];
	};

	for (k = 0; k < FRAMES_PER_BUFFER; k++) //DF1 Form of the High-pass filter
	{
		Out[k] = In[k] * b0_high + high_bState1*b1_high + high_bState2*b2_high - high_aState1*a1_high - high_aState2*a2_high;

		high_bState2 = high_bState1;
		high_bState1 = In[k];
		high_aState2 = high_aState1;
		high_aState1 = Out[k];
	};
};

void BandPass::designFiltHigh() //hpf filter
{

	w0_high = 2 * pi * f_high / SAMPLE_RATE; //omega of set frequency
	alpha_high = sin(w0_high) / (2 * Q_high); //alpha for this High-Pass Filter

	//calculation of High-pass coefs
	a0_high = 1 + alpha_high;
	a1_high = (-2 * cos(w0_high)) / a0_high;
	a2_high = (1 - alpha_high) / a0_high;
	b0_high = ((1 + cos(w0_high)) / 2) / a0_high;
	b1_high = -(1 + cos(w0_high)) / a0_high;
	b2_high = ((1 + cos(w0_high)) / 2) / a0_high;
}

void BandPass::designFiltLow() // lpf filter
{
	w0_low = 2 * pi * f_low / SAMPLE_RATE; //omega of set frequency
	alpha_low = sin(w0_low) / (2 * Q_low); //alpha for this Low-Pass Filter

	//calculation of Low-Pass coefs
	a0_low = 1 + alpha_low;
	a1_low = (-2 * cos(w0_low)) / a0_low;
	a2_low = (1 - alpha_low) / a0_low;
	b0_low = ((1 - cos(w0_low)) / 2) / a0_low;
	b1_low = (1 - cos(w0_low)) / a0_low;
	b2_low = ((1 - cos(w0_low)) / 2) / a0_low;
}

void BandPass::setParam(int numParam, double Value)		//change cases for GUI-params
{
	switch (numParam)
	{
	case 1:
	{
		f_high = float(Value * double(max_f_high)); //Sets the cutoff frequency of high-pass filter
		designFiltHigh();
		return;
	}
	case 2:
	{
		f_low = float(Value * double(max_f_low)); //Sets the cutoff frequency of low-pass filter
		designFiltLow();
		return;
	}
	}
}

void BandPass::processAudio(float* inBlock, float* outBlock, int NumOfSamples)
{
	BandFilt(inBlock, outBlock);
};