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
#include	"portaudio.h"
#include	<time.h>
#include	<string>
#include	<stdio.h>
#include	"pa_win_waveformat.h"
#include 	"pa_win_wasapi.h"

// audio parameters like fs and block size
#include "audio_parameter.h"

// sample formate
#define PA_SAMPLE_TYPE  paFloat32
#define SAMPLE_SIZE 4
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
//constant that will be throwed if a error in the init occurs
#define PortaudioPlusError -3
#define PaNoDevice -1


class CPortaudioPlus
{
public:
	// Constructor:  MODE 1 (In), MODE 2 (Out), MODE 3 (InOut)
	CPortaudioPlus(int audioMode, const char* device, const char* deviceApi, double latency);
	CPortaudioPlus(int audioMode, const char * inDevice, const char* deviceApiIn, const char * outDevice, const char* deviceApiOut, double InLatency, double OutLatency);
	
	
	// read one Block from audio stream
	void readBlock(float* audio_block);
	// read blcok interleaved for wasapi devices with two channels
	void readBlock(float* audio_block, int Channel);
	// write one block to audio stream
	void writeBlock(float* audio_block);
	// write stereo output
	void writeBlock(float* audio_block1, float* audio_block2);
	// Destructor: terminates portaudio
	~CPortaudioPlus();

private:
	// portaudio pointers and variables
	PaStream *stream = NULL;
	PaError err;
	PaStreamParameters inputParameters;
	PaStreamParameters outputParameters;
	struct PaWasapiStreamInfo wasapiInfo;
	int WasapiFlag = 0;
	int deviceIDin = PaNoDevice;
	int deviceIDout = PaNoDevice;
	PaTime inLatency = NULL;
	PaTime outLatency = NULL;

	// stereo out buffer
	float out_buffer[FRAMES_PER_BUFFER][NUM_CHANNELS_OUT];
	// stereo interleaved in buffer
	float inBuffer[FRAMES_PER_BUFFER*NUM_CHANNELS_OUT];
	
	// Fuction to set device
	void set_device(const char * devName, const char * ApiName, int audioMode);
	// function to generate form a float* block a stereo float frame channel block
	static void mono2Stereo(float* In, float Out[FRAMES_PER_BUFFER][NUM_CHANNELS_OUT], int Len);
	// stereo output: generate output buffer
	static void twoBlocks2Stereo(float* In1, float* In2, float Out[FRAMES_PER_BUFFER][NUM_CHANNELS_OUT], int Len);
	// interleaved to one mono block
	void Buffer2Floatp(float* In, float *Out, int Chn);
	// different initializations of portaudio
	void init_InSound(void);
	void init_OutSound(void);
	void init_InOutSound(void);
	// set params
	void setInParam(void);
	void setOutParam(void);
	// init portaudio and gen wasapi info when needed
	void initPaAndGenWasapiSpecificInfo(const char* HostApi);
	// function to return errors
	void pa_error(int code);
	// function to print warning
	void pa_warning(int code);
};

