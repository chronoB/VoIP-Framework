/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/
#include "WavHandling.h"

// constructor
CWavHandling::CWavHandling(const char* InFilename, const char* OutFilename)
{
	init_InFile(InFilename);
	init_OutFile(OutFilename);
}

// destructor
CWavHandling::~CWavHandling()
{
	isRecording = 0; //don't know if necessary
	if (audioFileRead != NULL) sf_close(audioFileRead);
	if (audioFileWrite != NULL) sf_close(audioFileWrite);
}

// initialize with input file
void CWavHandling::init_InFile(const char* InFilename)
{
	if (InFilename == NULL) return;

	CLEAR(&sfinfoRead);
	audioFileRead = sf_open(InFilename, SFM_READ, &sfinfoRead);

	// checking a few things (at this, don't know how in class)

	if (audioFileRead == NULL)
	{
		printf("Error : Not able to open input file.\n");
		WavHandlingError(1); // Error Code 
		return;
	};
	if (sfinfoRead.samplerate != SAMPLE_RATE)
	{
		printf("Error : sample rate of the opened file is not 48 kHz.\n");
		WavHandlingError(2);
		return; // Error Code
	};
	if (sfinfoRead.channels != NUM_CHANNELS_IN)
	{
		printf("Error : The opened file contains more than one channel.\n");
		WavHandlingError(3);
		return; // Error Code
	};
}

// initialize with output file
void CWavHandling::init_OutFile(const char* OutFilename)
{
	if (OutFilename == NULL) return;

	CLEAR(&sfinfoWrite);
	// fill structure 
	sfinfoWrite.samplerate = SAMPLE_RATE;
	sfinfoWrite.channels = NUM_CHANNELS_IN;
	sfinfoWrite.format = (SF_FORMAT_WAV | SF_FORMAT_PCM_16);
	// open file for writing
	audioFileWrite = sf_open(OutFilename, SFM_WRITE, &sfinfoWrite);

	if (audioFileWrite == NULL)
	{
		printf("Error : Not able to open output file.\n");
		WavHandlingError(4);
		return; // Error Code 
	};
}

// read audio block
void CWavHandling::readBlock(float* audio_block)
{
	sf_read_float(audioFileRead, audio_block, FRAMES_PER_BUFFER);
}

// write audio block
void CWavHandling::writeBlock(float* audio_block)
{
	sf_write_float(audioFileWrite, audio_block, FRAMES_PER_BUFFER);
}

// determine file length
int CWavHandling::getFileLength()
{
	auto iNUM_SAMPLES = int(sfinfoRead.frames);
	return iNUM_SAMPLES / SAMPLE_RATE;
}

// error handling
void CWavHandling::WavHandlingError(int ErrCode)
{
	if (audioFileRead != NULL) sf_close(audioFileRead);
	if (audioFileWrite != NULL) sf_close(audioFileWrite);
	throw ErrCode;
}

// function to start recording with small files
void CWavHandling::startRecording(const char * name,int lengthFileName)
{
	isRecording = 1;
	startTime = clock();
	time_t now = time(0);
	tm * ltm = localtime(&now);
	constructDateTime(ltm); //constructing the char array date_time
	CreateDirectory(date_time.c_str(), NULL);
	endFileName = date_time + "/" + name + date_time + ".wav";
	curLengthFileName = date_time.size() + 2 + lengthFileName; //2 for the punctuation mark
	fileName = date_time + "/" + name + "_" + std::to_string(fileCounter);
	//erste initialisierung
	init_OutFile(fileName.c_str());
}

// function to manage recording
void CWavHandling::manageRecording(float* audioBlock)
{
	if (!isRecording)
	{
		//printf("Recording stopped. Restart recording before trying to save Audio!\n");
		return;
	}
	if ((clock()-startTime)/(double)CLOCKS_PER_SEC >=60)
	{
		fileCounter += 1;
		//close the audiofile
		if (audioFileWrite != NULL) sf_close(audioFileWrite);
		_itoa(fileCounter, &fileName[curLengthFileName], 10);
		init_OutFile(fileName.c_str());
		startTime = clock();
	}
	writeBlock(audioBlock);
}

// function to stop recording and generate long file from the short ones
void CWavHandling::stopRecording()
{
	if (audioFileWrite != NULL) sf_close(audioFileWrite);
	isRecording = 0;
	
	try
	{
		init_OutFile(endFileName.c_str());
	}
	catch(...)
	{
		printf("%s\n", endFileName.c_str());
		return;
	}
	float * tmpBlock = new float[FRAMES_PER_BUFFER];
	for (int i = 1; i <= fileCounter;i++ )
	{
		_itoa(i, &fileName[curLengthFileName], 10);
		try
		{
			//printf("FileName: %s\n",fileName.c_str());
			init_InFile(fileName.c_str());
		}
		catch(...)
		{
			printf("file not found\n");
			continue;
		}
		for (int j = 0; j < sfinfoRead.frames / FRAMES_PER_BUFFER;j++)
		{
			readBlock(tmpBlock);
			writeBlock(tmpBlock);
		}
		sf_close(audioFileRead);
		tempFileName = fileName + ".wav";
		std::rename(fileName.c_str(), tempFileName.c_str());
	}
	sf_close(audioFileWrite);
	fileCounter = 1;
}

// function to generate date time as a string
void CWavHandling::constructDateTime(tm *ltm)
{
	date_time = std::to_string(1900 + ltm->tm_year);
	date_time += std::to_string(1 + ltm->tm_mon);
	date_time += std::to_string(ltm->tm_mday);
	date_time += "_";
	date_time += std::to_string(ltm->tm_hour);
	date_time += std::to_string(ltm->tm_min);
	date_time += std::to_string(ltm->tm_sec);
}


