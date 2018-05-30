/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

// function to handle wav files

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sndfile.h"
#include <ctime>
#include <fstream>
#include <string>
#include <Windows.h>

// audio parameters like fs and block size
#include "audio_parameter.h"


class CWavHandling
{
public:
	// constructor, use NULL if you want only one mode
	CWavHandling(const char* InFilename, const char* OutFilename);
	// read one block from file
	void readBlock(float* audio_block);
	// write one block to file 
	void writeBlock(float* audio_block);
	// return length in seconds
	int getFileLength(void);
	// stops the recording
	void startRecording(const char*,int);
	// manages the recording
	void manageRecording(float*);
	// stops the recording
	void stopRecording(void);
	// destructor (closes files)
	~CWavHandling();

private:
	// initialize .wav file for reading
	void init_InFile(const char* InFilename);
	// initialize .wav file for writing
	void init_OutFile(const char* OutFilename);
	// function to handle errors
	void WavHandlingError(int ErrCode);
	//function to construct the dateTime
	void constructDateTime(tm *ltm);

	//clock Timer
	clock_t startTime = 0;
	//checkVariable for audiRecording
	int isRecording = 0;
	//char array to store the current time and date in yyyymmdd_hhmmss structure
	std::string date_time;
	//max Length of the fileName
	int maxLengthFileName = 50;
	//Length of the current fileName
	int curLengthFileName = 0;
	//fileName to close and reopen files
	std::string fileName;
	//fileName to save the complete audiofile
	std::string endFileName;
	//fileName to rename the files
	std::string tempFileName;
	//counter for the fileNames
	int fileCounter = 1;
	// pointer to sound file
	SNDFILE	*audioFileRead = NULL;
	// SoundFileStructure
	SF_INFO	sfinfoRead;
	// pointer to audio file
	SNDFILE	*audioFileWrite = NULL;
	// SoundFileStructure
	SF_INFO	sfinfoWrite;
};

