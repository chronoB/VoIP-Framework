/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include <stdio.h>
#include <iostream>
#include <thread>

#include "PortaudioPlus.h"
#include "NetworkSender.h"
#include "NetworkReciever.h"
#include "PASupplier.h"
#include "Buffer.h"
#include "controlBuffer.h"


#define AUDIO_MODE 3 // MODE 1 (In), MODE 2 (Out), MODE 3 (InOut)

#define RECIEVE_PORT 12345 //The client will try this port first and than increase the port number continously to find the port set by the server
#define SEND_PORT RECIEVE_PORT+1

//Length of the send and recieve Buffer
#define BUFFERLENGTH 50
#define CONTROLBUFFERLENGTH 10

int main(void)
{
	//Keyboard input for the ip address of the server
	std::string szIP;
	const char* IP_ADRESS;
	std::cout << "Type in IP-address of the server:" << std::endl;
	std::cin >> szIP;
	IP_ADRESS = szIP.c_str();

	//Buffer that is used to store the blocks that are created by the pa and should be send to the operator
	Buffer *pa2sendBuf = new Buffer(BUFFERLENGTH);
	//Buffer that is used to store the blocks recieved by the operator
	controlBuffer *recv2paBuf = new controlBuffer(CONTROLBUFFERLENGTH);

	// Creating CPortaudioPlus object
	CPortaudioPlus *AudioHandle;
	NetworkReciever *networkReciever;
	NetworkSender *networkSender;
	try
	{
		AudioHandle = new CPortaudioPlus(AUDIO_MODE, "Scarlett", "WASAPI", "Scarlett", "WASAPI", 0.2, 0.2);
		networkReciever = new NetworkReciever(IP_ADRESS, RECIEVE_PORT);
		networkSender = new NetworkSender(IP_ADRESS, SEND_PORT);
	}
	catch (int e)
	{
		std::string errormessage = "Error in initalization of ";
		switch (e)
		{
		case NETWORKSENDERERROR:
			errormessage.append("NetworkSender\n");
		case NETWORKRECIEVERERROR:
			errormessage.append("NetworkReciever\n");
		case PortaudioPlusError:
			errormessage.append("Portaudio\n");
		}
		printf(errormessage.c_str());
		printf("Waiting 10 Seconds...\n");
		Sleep(10000);
		return -1;
	}

	PASupplier *paSupplier = new PASupplier();

	//Start all the used threads and set their prioritys
	int running = 0; //parameter for the while loops inside the threads. used for save shutdown
	std::thread threadSend = networkSender->demandDataThread(pa2sendBuf, &running);
	std::thread threadRecv = networkReciever->recvDataThread(recv2paBuf, &running);
	std::thread threadMikro = paSupplier->PAMicrophoneThread(AudioHandle, pa2sendBuf, &running);
	std::thread threadSpeaker = paSupplier->PASpeakerThread(AudioHandle, recv2paBuf, &running);
	SetThreadPriority(threadMikro.native_handle(), THREAD_PRIORITY_TIME_CRITICAL);
	SetThreadPriority(threadSpeaker.native_handle(), THREAD_PRIORITY_TIME_CRITICAL);
	SetThreadPriority(threadRecv.native_handle(), THREAD_PRIORITY_HIGHEST);
	SetThreadPriority(threadSend.native_handle(), THREAD_PRIORITY_HIGHEST);

	
	//Start all the control threads (only used for debug)
	std::thread controlReadThread = paSupplier->ReadControler(&running);
	std::thread controlWriteThread = paSupplier->WriteControler(&running);
	std::thread controlReceave = networkReciever->BlockControler(&running);
	std::thread controlSend = networkSender->BlockControler(&running);
	// std::thread controlBufferPa2SendGet = pa2sendBuf->BlockControlerGet(&running, 1);
	// std::thread controlBufferPa2SendSet = pa2sendBuf->BlockControlerSet(&running, 1);
	// std::thread controlBufferRecv2paGet = recv2paBuf->BlockControlerGet(&running, 2);
	// std::thread controlBufferRecv2SPaSet = recv2paBuf->BlockControlerSet(&running, 2);

	threadRecv.join();
	threadSend.join();
	threadMikro.join();
	threadSpeaker.join();
	controlReadThread.join();
	controlWriteThread.join();
	controlReceave.join();
	controlSend.join();
	// controlBufferPa2SendGet.join();
	// controlBufferPa2SendSet.join();
	// controlBufferRecv2paGet.join();
	// controlBufferRecv2SPaSet.join();

	//If everything is closed...
	printf("Waiting 3 Seconds...\n");
	Sleep(3000);

	// destroy buffer and objects
	delete AudioHandle;
	delete pa2sendBuf;
	delete recv2paBuf;
	delete networkReciever;
	delete networkSender;
	delete paSupplier;

	return 0;
}



