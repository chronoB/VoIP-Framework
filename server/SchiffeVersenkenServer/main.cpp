/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#define _WINSOCKAPI_ //damit aus windows.h nicht die winsock 1.1 api geladen wird

#include <stdio.h>
#include <ctime>
#include <thread>

#include "Buffer.h"
#include "NetworkSender.h"
#include "NetworkReciever.h"
#include "Audioprocessor.h"
#include "WavHandling.h"
#include "GUIReciever.h"
#include "PASupplier.h"
#include "debugPrint.h"
#include "controlBuffer.h"

//Length of the Buffers used
#define BUFFERLENGTH1 50
#define AUDIO_MODE 2

int main(void)
{
	//ports used for the connections
	int portGui = 12344;
	int portSendClient1 = 12345;
	int portRecvClient1 = 12346;
	int portSendClient2 = 12347;
	int portRecvClient2 = 12348;

	//Buffer between the Audioprocessor and the send routine for Client 1
	Buffer *sendBufClient1 = new Buffer(BUFFERLENGTH1);
	//Buffer between the recieve routine for Client 1 and the Audioprocessor
	Buffer *recvBufClient1 = new Buffer(BUFFERLENGTH1);
	//Buffer between the Audioprocessor and the send routine for Client 2
	Buffer *sendBufClient2 = new Buffer(BUFFERLENGTH1);
	//Buffer between the recieve routine for Client 2 and the Audioprocessor
	Buffer *recvBufClient2 = new Buffer(BUFFERLENGTH1);
	//Buffer that stores the audio signal that should be routed back from Client 1 to Client 1
	Buffer *returnBufClient1 = new Buffer(BUFFERLENGTH1);
	//Buffer that stores the audio signal that should be routed back from Client 2 to Client 2
	Buffer *returnBufClient2 = new Buffer(BUFFERLENGTH1);
	//Buffer that stores the audio signal from Client 1 that should be heard by the operator
	controlBuffer *soundBufOperator1 = new controlBuffer(BUFFERLENGTH1);
	//Buffer that stores the audio signal from Client 2 that should be heard by the operator
	controlBuffer *soundBufOperator2 = new controlBuffer(BUFFERLENGTH1);

	//Audioprocessor that processes the audio coming from the Client 1;
	Audioprocessor *audioProcessorClient1 = new Audioprocessor();
	//Audioprocessor that processes the audio coming from the Client 2;
	Audioprocessor *audioProcessorClient2 = new Audioprocessor();
	
	//Supplier for the PA that uses the audio signal from the soundBufOperators
	PASupplier *pasupplier = new PASupplier();
	//AudioHandle to work with the Soundcard
	CPortaudioPlus *AudioHandle;

	//Handle to recv data from the GUI and route them to the Audioprocessor
	GUIReciever *GuiRecieverHandle;
	//Object to handle the data that should be send to the client 1 from the sendBufClient1
	NetworkSender *netSendClient1;
	//Object to handle the data that should be recieved from the client 1 and stored in the recvBufClient1
	NetworkReciever *netRecvClient1;
	//Object to handle the data that should be send to the client 2 from the sendBufClient2
	NetworkSender *netSendClient2;
	//Object to handle the data that should be recieved from the client 2 and stored in the recvBufClient2
	NetworkReciever *netRecvClient2;
	try
	{
		AudioHandle = new CPortaudioPlus(AUDIO_MODE, "Scarlett", "WASAPI", 0.2);
		GuiRecieverHandle = new GUIReciever(portGui);
		netSendClient1 = new NetworkSender(portSendClient1);
		netRecvClient1 = new NetworkReciever(portRecvClient1);
		netSendClient2 = new NetworkSender(portSendClient2);
		netRecvClient2 = new NetworkReciever(portRecvClient2);
	}
	catch (int e)
	{
		std::string errormessage = "Error in initalization of ";
		switch (e)
		{
		case NETWORKSENDERERROR:
			errormessage.append("NetworkSender");
		case NETWORKRECIEVERERROR:
			errormessage.append("NetworkReciever");
		case PortaudioPlusError:
			errormessage.append("Portaudio");
		case GUIRECIEVERERROR:
			errormessage.append("GuiReciever");
		}
		debugPrint(errormessage.c_str(),T_MAIN,R_ERROR);
		Sleep(10000);
		return -1;
	}

	int running = 1; //parameter for the while loops inside the threads. used for save shutdown
	netSendClient1->sendingStartcode();//sending the Startcode to the clients
	netSendClient2->sendingStartcode();//sending the Startcode to the clients
	
	//starting the threads
	std::thread threadRecvClient1 = netRecvClient1->recvDataThread(recvBufClient1,&running);
	std::thread threadRecvClient2 = netRecvClient2->recvDataThread(recvBufClient2, &running);
	std::thread processClient1 = audioProcessorClient1->manageDataThread(recvBufClient2, sendBufClient1, returnBufClient1, returnBufClient2, soundBufOperator1, &running);
	SetThreadPriority(processClient1.native_handle(), THREAD_PRIORITY_HIGHEST);
	std::thread processClient2 = audioProcessorClient2->manageDataThread(recvBufClient1, sendBufClient2, returnBufClient2, returnBufClient1, soundBufOperator2, &running);
	SetThreadPriority(processClient2.native_handle(), THREAD_PRIORITY_HIGHEST);
	std::thread threadSendClient1 = netSendClient1->demandDataThread(sendBufClient1,&running);
	std::thread threadSendClient2 = netSendClient2->demandDataThread(sendBufClient2, &running);
	
	std::thread threadNetworking = GuiRecieverHandle->recvDataThread(&running, audioProcessorClient1, audioProcessorClient2);
	std::thread threadPASupplier = pasupplier->PASpeakerThread(AudioHandle, soundBufOperator1, soundBufOperator2, &running);
	SetThreadPriority(threadPASupplier.native_handle(), THREAD_PRIORITY_TIME_CRITICAL);
	
	

	/*std::thread ControlReciever1 = netRecvClient1->BlockControler(&running, 1);
	std::thread ControlReciever2 = netRecvClient2->BlockControler(&running, 2);
	std::thread ControlSender1 = netSendClient1->BlockControler(&running, 1);
	std::thread ControlSender2 = netSendClient2->BlockControler(&running, 2);*/
	
	threadRecvClient1.join();
	threadRecvClient2.join();
	processClient1.join();
	processClient2.join();
	threadSendClient1.join();
	threadSendClient2.join();
	threadNetworking.join();
	threadPASupplier.join();

	/*ControlReciever1.join();
	ControlReciever2.join();
	ControlSender1.join();
	ControlSender2.join();*/

	printf("Waiting 3 Seconds...\n");
	Sleep(3000);

	
	delete sendBufClient1;
	delete sendBufClient2;
	delete recvBufClient1;
	delete recvBufClient2;
	delete returnBufClient1;
	delete soundBufOperator1;
	delete soundBufOperator2;
	delete audioProcessorClient1;
	delete audioProcessorClient2;
	delete netSendClient1;
	delete netRecvClient1;
	delete GuiRecieverHandle;

	return 0;
}

