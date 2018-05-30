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

#include "audio_parameter.h"
#include "Buffer.h"

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <thread>

#pragma comment(lib, "Ws2_32.lib")


#define BUFFERLENGTH FRAMES_PER_BUFFER //renamed to improve the readability of the code
#define NETWORKBUFFERLENGTH (BUFFERLENGTH+1) //+1 for the checksum 
#define NETWORKRECIEVERERROR -2

class NetworkReciever
{
public:
	NetworkReciever(int);
	~NetworkReciever(void);

	//Function to recieve the data from the network and save it to the buffer
	void recvData(Buffer*,int*);
	//Thread to continiusly call the recvData function
	std::thread recvDataThread(Buffer* buffer,int *running) {
		return std::thread([=] {recvData(buffer,running); });//thread that runs demand data so you can access the main function
	}
	
	std::thread BlockControler(int* running, int numReciver) {
		return std::thread([=] {controlBlocks(running, numReciver); });//thread that runs demand data so you can access the main function
	}

private:

	//checkVariable for the dataRecieving
	int ret;
	//Socket to accept connections
	SOCKET acceptSocket; 
	//socket to save the incomming message
	SOCKET connectedSocket; 
	//block to save the incomming message
	char recvBlock[NETWORKBUFFERLENGTH*sizeof(float)]; 

	//Function to recieve the data
	int recieveData(float*);
	//Function to start the Winsocket
	int startWinsock(void);
	//Function to listen to incomming connections
	int listenToConnection(void);
	//Function to accept incomming connections
	int acceptConnection();
	//Function to close the Winsocket
	void cleanup(void);
	//Function to close the Winsocket and a connected Socket
	void cleanup(SOCKET);
	//Function to close the Winsocket and two connected Sockets
	void cleanup(SOCKET, SOCKET);
	//Function to initialize a Socket
	int initSocket(int);

	int measureTime = 60 * 1;
	int controlCounter = 0;
	void controlBlocks(int* running, int numReciver);
};