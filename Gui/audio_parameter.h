/*
This file is part of the project "Schiffe-Versenken", a Voice-over-IP chat with disturbance algorithms.
The software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule).
This project is released under the terms of the MIT-license.
For license details see the license file.

Copyright (c) 2016	Finn Bayer			(finn.bayer@gmx.de)
					Michael Schaffert	(pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen	(n.westhausen@web.de)
*/

// audio parameter used by by all parts of the project
#pragma once
#define SAMPLE_RATE			(48000)
#define FRAMES_PER_BUFFER	(1024)
#define NUM_CHANNELS_IN		(1)
#define NUM_CHANNELS_OUT	(2)
#define DITHER_FLAG			(0) 
#define CHAR_PER_BUF        (512)
#define CLEAR(a) memset(a, 0, sizeof a)

#define M_PI           3.14159265358979323846
// effect identification					
# define NOISE 0
# define BANDPASS 10
# define DISTORTION 20
# define REVERB 30
# define COLORIZATION 40
// slot identification
# define L1 1
# define L2 2
# define L3 3
# define R1 5
# define R2 6
# define R3 7
# define ReturnL 4
# define ReturnR 8