/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

// Audio Parameter used by CWavHandling and CPortaudioPlus (global constants)
#pragma once
#define SAMPLE_RATE			(48000)
#define FRAMES_PER_BUFFER	(1024)
#define NUM_CHANNELS_IN		(1)
#define NUM_CHANNELS_OUT	(2)
#define DITHER_FLAG			(0) 
#define CLEAR(a) memset(a, 0, sizeof a)