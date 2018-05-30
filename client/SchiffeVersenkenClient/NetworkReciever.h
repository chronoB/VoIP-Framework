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

#define _WINSOCK_DEPRECATED_NO_WARNINGS //to use inet_addr
#define _CRT_SECURE_NO_WARNINGS //to use sprintf

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include "audio_parameter.h"
#include "controlBuffer.h"
#include <thread>

#pragma comment(lib, "Ws2_32.lib")

//renamed to improve the readability of the code
#define BLOCKLENGTH FRAMES_PER_BUFFER
//plus 1 for the checksum
#define NETWORKBLOCKLENGTH (BLOCKLENGTH+1)
//used for the connection to search for open Ports. The higher the estimated number, the more ports are searched
#define ESTIMATED_NUM_CLIENTS 2 
//constant that will be throwed if a error in the init occurs
#define NETWORKRECIEVERERROR -2

class NetworkReciever
{
public:
	NetworkReciever(const char*,int);
	~NetworkReciever(void);
	//Thread to continiusly call the recvData function
	std::thread recvDataThread(controlBuffer* buffer, int *running) {
		return std::thread([=] {recvData(buffer, running); });
	}
	std::thread BlockControler(int* running) {
		return std::thread([=] {controlBlocks(running); });
	}
	

private:

	//checkVariable
	int ret;
	//Socket that connects to the Server
	SOCKET networkSocket;
	//buffer were the incoming message is temporarily saved
	char recv_buf[NETWORKBLOCKLENGTH * sizeof(float)]; 

	//Function to call the recieveData function continously
	void recvData(controlBuffer*, int*);
	//Function to recieve the Data from the socket
	int recieveData(float*);
	//function to start the winsock
	int startWinsock(void);
	//function to initialize the socket used to connect to the server 
	int initSocket();
	//function to connect the socket to the server socket
	int connectSocket(const char*, int);
	//cleanup function for the winsocket
	void cleanup(void);
	//cleanup function for the winsocket and a socket
	void cleanup(SOCKET);
	
	//DEBUG
	int measureTime = 60 * 1;
	int controlCounter = 0;
	void controlBlocks(int* running);
};
