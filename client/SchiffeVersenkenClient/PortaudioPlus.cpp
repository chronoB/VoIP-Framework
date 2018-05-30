/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include "PortaudioPlus.h"

CPortaudioPlus::CPortaudioPlus(int audioMode,const char* device,const char* deviceApi ,double latency)
{
	// Init Portaudio and check Api for WASAPI
	initPaAndGenWasapiSpecificInfo(deviceApi);
	// checking audio mode
	if (audioMode == 1)
	{
		// find device
		set_device(device, deviceApi, 1);
		// set params
		if (latency != NULL) inLatency = PaTime(latency);
		setInParam();
		// start and open stream
		init_InSound();
	}
	else if (audioMode == 2)
	{
		// find device
		set_device(device, deviceApi, 2);
		// set params
		if (latency != NULL) outLatency = PaTime(latency);
		setOutParam();
		// start and open stream
		init_OutSound();
	}
	else if (audioMode == 3)
	{
		printf("Mode 3 not possible with this inputs! \n");
		pa_error(-321);
	}
	else throw PortaudioPlusError;
}
CPortaudioPlus::CPortaudioPlus(int audioMode, const char * inDevice, const char* deviceApiIn, const char * outDevice, const char* deviceApiOut, double InLatency, double OutLatency)
{
	// Init Portaudio and check Api for Portaudio
	initPaAndGenWasapiSpecificInfo(deviceApiIn);
	// checking audio mode
	if (audioMode == 1)
	{
		printf("Mode 1 not possible with this inputs! \n");
		pa_error(-321);
	}
	else if (audioMode == 2)
	{
		printf("Mode 2 not possible with this inputs! \n");
		pa_error(-321);

	}
	else if (audioMode == 3)
	{
		// find device
		set_device(inDevice, deviceApiIn, 1);
		set_device(outDevice, deviceApiOut, 2);
		// set params
		if (OutLatency != NULL) outLatency = PaTime(OutLatency);
		if (InLatency != NULL) inLatency = PaTime(InLatency);
		setInParam();
		setOutParam();
		// start and open stream
		init_InOutSound();
	}
	else throw PortaudioPlusError;
}

CPortaudioPlus::~CPortaudioPlus()
{
	if (stream)
	{
		err = Pa_StopStream(stream);
		if (err != paNoError)
		{
			pa_error(-12);
			printf("destructor");
		}
	}
	// terminating portaudio
	Pa_Terminate();
};

void CPortaudioPlus::init_InSound(void)
{
	// open portaudio stream
	err = Pa_OpenStream(
		&stream,
		&inputParameters,
		NULL,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paClipOff,
		NULL,
		NULL);
	if (err != paNoError)
	{
		return;
	}
	printf("Stream open!\n");

	// start portaudio stream
	err = Pa_StartStream(stream);
	if(err != paNoError)
	{
		printf("InSound after StartStream");
		pa_error(-3);
		return;
	}
	printf("Stream Started!\n");
}
void CPortaudioPlus::init_OutSound(void)
{
	// open portaudio stream
	err = Pa_OpenStream(
		&stream,
		NULL,
		&outputParameters,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paClipOff,
		NULL,
		NULL);
	if (err != paNoError)
	{
		pa_error(-5);
		return;
	}
	printf("Stream open!\n");

	// start portaudio stream
	err = Pa_StartStream(stream);
	if (err != paNoError)
	{
		printf("OutSound after StartStream");
		pa_error(-6);
		return;
	}
	printf("Stream Started! \n");
}
void CPortaudioPlus::init_InOutSound(void)
{
	// Open portaudio stream
	err = Pa_OpenStream(
		&stream,
		&inputParameters,
		&outputParameters,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paClipOff,
		NULL,
		NULL);

	if (err != paNoError)
	{
		printf("InOutSound after OpenStream");
		pa_error(-8);
		return;
	}
	printf("Stream open!\n");

	// start portaudio stream
	err = Pa_StartStream(stream);
	if (err != paNoError)
	{
		printf("InOutSound after StartStream");
		pa_error(-9);
		return;
	}
	printf("Stream Started! \n");
}

// functions to set input params
void CPortaudioPlus::setInParam()
{
	inputParameters.device = PaDeviceIndex(deviceIDin);
	inputParameters.sampleFormat = PA_SAMPLE_TYPE;
	if (WasapiFlag == 1)
	{
		CLEAR(inBuffer);
		inputParameters.channelCount = 2;
		inputParameters.hostApiSpecificStreamInfo = (&wasapiInfo);
	}
	else
	{
		inputParameters.hostApiSpecificStreamInfo = NULL;
		inputParameters.channelCount = NUM_CHANNELS_IN;
	}
	if (inLatency == NULL)
	{
		inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultHighInputLatency;
	}
	else
	{
		inputParameters.suggestedLatency = inLatency;
	}
}

// functions to set output params
void CPortaudioPlus::setOutParam()
{
	CLEAR(out_buffer);
	outputParameters.device = PaDeviceIndex(deviceIDout);
	outputParameters.channelCount = NUM_CHANNELS_OUT;
	outputParameters.sampleFormat = PA_SAMPLE_TYPE;
	if (outLatency == NULL)
	{
		outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
	}
	else
	{
		outputParameters.suggestedLatency = outLatency;
	}
	if (WasapiFlag == 1)
	{
		outputParameters.hostApiSpecificStreamInfo = &wasapiInfo;
	}
	else
	{
		outputParameters.hostApiSpecificStreamInfo = NULL;
	}
}

// init portaudio and check for wasapi
void CPortaudioPlus::initPaAndGenWasapiSpecificInfo(const char* HostApi)
{
	err = Pa_Initialize();
	if (err != paNoError)
	{
		pa_error(-2);
		return;
	}
	printf("Portaudio initialized!\n");
	// check for wasapi
	if (strcmp(HostApi, "WASAPI") == 0)
	{
		WasapiFlag = 1;
		wasapiInfo.size = sizeof(PaWasapiStreamInfo);
		wasapiInfo.hostApiType = paWASAPI;
		wasapiInfo.version = 1;
		wasapiInfo.flags = paWinWasapiExclusive;
		wasapiInfo.channelMask = NULL;
		wasapiInfo.hostProcessorOutput = NULL;
		wasapiInfo.hostProcessorInput = NULL;
		wasapiInfo.threadPriority = eThreadPriorityProAudio;
	}
}

// write mono block
void CPortaudioPlus::writeBlock(float* audio_block)
{
	// generating stereo block
	mono2Stereo(audio_block, out_buffer, FRAMES_PER_BUFFER);
	// sending audio to output device
	err = Pa_WriteStream(stream, out_buffer, FRAMES_PER_BUFFER);
	if (err != paNoError) pa_warning(-10);
}

// write stereo block
void CPortaudioPlus::writeBlock(float* audio_block1, float* audio_block2)
{
	// generating stereo block
	twoBlocks2Stereo(audio_block1, audio_block2, out_buffer, FRAMES_PER_BUFFER);
	// sending audio to output device
	err = Pa_WriteStream(stream, out_buffer, FRAMES_PER_BUFFER);
	if (err != paNoError) pa_warning(-10);
}

// read mono block
void CPortaudioPlus::readBlock(float* audio_block)
{
	if (WasapiFlag == 1)
	{
		err = Pa_ReadStream(stream, inBuffer, FRAMES_PER_BUFFER);
		Buffer2Floatp(inBuffer, audio_block, 1);
	}
	else
	{
		err = Pa_ReadStream(stream, audio_block, FRAMES_PER_BUFFER);
	}
	
	if (err != paNoError) pa_warning(-11);
};

// read interleaved and gen mono block
void CPortaudioPlus::readBlock(float* audio_block, int Channel)
{
	err = Pa_ReadStream(stream, inBuffer, FRAMES_PER_BUFFER);
	if (err != paNoError) pa_warning(-11);
	Buffer2Floatp(inBuffer, audio_block, Channel);
};

// find audio device by name and api
void CPortaudioPlus::set_device(const char* devName,const char* ApiName, int audioMode)
{
	int numDevices;
	numDevices = Pa_GetDeviceCount();
	if (numDevices < 0)
	{
		printf("ERROR: Pa_CountDevices returned 0x%x\n", numDevices);
		pa_error(-123);
	}
	
	std::string tempName;
	std::string tempApiName;
	int chan_in; 
	int chan_out;
	for (auto i = 0; i<numDevices; i++)
	{
		chan_in = Pa_GetDeviceInfo(i)->maxInputChannels;
		chan_out = Pa_GetDeviceInfo(i)->maxOutputChannels;
		tempName = std::string(Pa_GetDeviceInfo(i)->name);
		tempApiName =  std::string(Pa_GetHostApiInfo(Pa_GetDeviceInfo(i)->hostApi)->name); 
		if ((tempName.find(std::string(devName)) != std::string::npos) && (tempApiName.find(std::string(ApiName)) != std::string::npos))
		{
			if (audioMode == 1 && chan_in != 0 )
			{
				deviceIDin = i;
				return;
			}
			else if (audioMode == 2 && chan_out != 0)
			{
				deviceIDout = i;
				return;
			}
		}	
	}
	if (deviceIDin == PaNoDevice && audioMode == 1)
	{
		printf("ERROR: Input Device not found!\n");
		pa_error(-1);
	}
	if (deviceIDout == PaNoDevice && audioMode == 2)
	{
		printf("ERROR: Output Device not found!\n");
		pa_error(-1);
	}	
}

// gen stereo output block from mono input
void CPortaudioPlus::mono2Stereo(float* In, float Out[FRAMES_PER_BUFFER][NUM_CHANNELS_OUT], int Len)
{
	for (auto k = 0; k < Len; k++)
	{
		Out[k][0] = In[k];
		Out[k][1] = In[k];
	}
}

// gen stereo output block from two mono input blocks
void CPortaudioPlus::twoBlocks2Stereo(float * In1, float * In2, float Out[FRAMES_PER_BUFFER][NUM_CHANNELS_OUT], int Len)
{
	for (auto k = 0; k < Len; k++)
	{
		Out[k][0] = In1[k];
		Out[k][1] = In2[k];
	}
}

// gen mono block from interleaved block
void CPortaudioPlus::Buffer2Floatp(float* In, float *Out, int Chn)
{
	for (auto k = 0; k < FRAMES_PER_BUFFER; k++)
	{
		Out[k] = In[2 * k];
		if (Chn > 1)
			Out[k] = In[2 * k + 1];

	}
}

// get Pa Error and throw real error
void CPortaudioPlus::pa_error(int code)
{
	if (stream)
	{
		Pa_AbortStream(stream);
		Pa_CloseStream(stream);
	}
	// terminating portaudio
	Pa_Terminate();
	printf("Error message: %s\n", Pa_GetErrorText(err));
	throw PortaudioPlusError;
}

// only disp warning
void CPortaudioPlus::pa_warning(int code)
{
	time_t  timev;
	time(&timev);
	printf("Error message: %lld\n", timev);
	printf("Code: %d\n", code);
	printf("Error message: %s\n", Pa_GetErrorText(err));
}



