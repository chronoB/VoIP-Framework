/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include "EffectSlot.h"

// constructor
EffectSlot::EffectSlot()
{
}

// destructor
EffectSlot::~EffectSlot()
{
	// deleting effects
	delete noiseEffect;
	delete bandpassEffect;
	delete distortionEffect;
//	delete reverbEffect;
	delete colorationEffect;
}

// function to pass the audio to the right effect
void EffectSlot::processAudio(float* inputBlock, float* outputBlock)
{
	switch (whichEffect)
	{
	case NOISE:
	{
		noiseEffect->processAudio(inputBlock, outputBlock, FRAMES_PER_BUFFER);
		return;
	}
	case BANDPASS:
	{
		bandpassEffect->processAudio(inputBlock, outputBlock, FRAMES_PER_BUFFER);
		return;
	}
	case DISTORTION:
	{
		distortionEffect->processAudio(inputBlock, outputBlock, FRAMES_PER_BUFFER);
		return;
	}
	/*case REVERB:
	{
		for (int idx = 0; idx < FRAMES_PER_BUFFER; idx++)
		{
			outputBlock[idx] = reverbEffect->processOneSample(inputBlock[idx]);
		}
		
		return;
	}*/
	case COLORATION:
	{
		colorationEffect->processAudio(inputBlock, outputBlock, FRAMES_PER_BUFFER);
		return;
	}
	}
}

// function to set which effect should be processed 
void EffectSlot::setEffectStatus(int numEffect)
{
	whichEffect = numEffect;
}

// function to set the right parameter to the right effect
void EffectSlot::setParam(int numEffect, int numParam, double Value)
{
	switch (numEffect)
	{
	case NOISE:
	{
		noiseEffect->setParam(numParam, Value);
		return;
	}
	case BANDPASS:
	{
		bandpassEffect->setParam(numParam, Value);
		return;
	}
	case DISTORTION:
	{
		distortionEffect->setParam(numParam, Value);
		return;
	}
	/*case REVERB:
	{
		switch (numParam)
			case 2:
			{
				reverbEffect->setDryWet(float(Value));
				return;
			}
			case 3:
			{
				reverbEffect->setReverbTime(float(Value));
				return;
			}
		return;
	}*/
	case COLORATION:
	{
		colorationEffect->setParam(numParam, Value);
		return;
	}
	}
}
