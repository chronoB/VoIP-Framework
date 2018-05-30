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
#include <stdio.h>


// Change these Parameters to allow status messages. 
//0-> this shouldnt be showed
//1-> this should be showed if the corresponding value is 1 as well
//2-> this will be shown even if the corresponding value is 0 (e.g. Errors should be shown anytime: set the error parameter to 2)

#define T_NETWORK 0
#define T_PA 0
#define T_GUI 0
#define T_EFFECT 0
#define T_MAIN 0

#define R_INFORMATION 0
#define R_WARNING 0
#define R_ERROR 2


inline void debugPrint(const char* text, int type, int rank)
{
	if (type + rank >= 2)
	{
		printf(text);
	}
}