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

#define _WINSOCK_DEPRECATED_NO_WARNINGS //to useinet_addr
#define _CRT_SECURE_NO_WARNINGS //to use sprintf

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include "audio_parameter.h"
#include "Buffer.h"
#include <thread>

#pragma comment(lib, "Ws2_32.lib")

//renamed to improve the readability of the code
#define BLOCKLENGTH FRAMES_PER_BUFFER
//plus 1 for the checksum
#define NETWORKBLOCKLENGTH (BLOCKLENGTH+1)
//used for the connection to search for open Ports. The higher the estimated number, the more ports are searched
#define ESTIMATED_NUM_CLIENTS 2 
// constant that will be thrown if an error in the init occurs
#define NETWORKSENDERERROR -1


class NetworkSender
{
public:
	NetworkSender(const char*, int);
	~NetworkSender(void);
	
	//Thread to continuously call the demandData function
	std::thread demandDataThread(Buffer* buffer, int *running) {
		return std::thread([=] {demandData(buffer, running); });//Thread that runs demandData to access the main function remotely
	}

	std::thread BlockControler(int* running) {
		return std::thread([=] {controlBlocks(running); });//Thread that runs demandData to access the main function remotely
	}
private:

	//checkVariable
	int ret;
	//Socket that connects to the Server
	SOCKET networkSocket;
	//buffer were the incoming message is temporarily saved
	char recv_buf[NETWORKBLOCKLENGTH*sizeof(float)]; //buffer in der die ankommende nachricht abgespeichert wird

	//function to call the sendData function continuously
	void demandData(Buffer*, int*);
	//function to send the data to the server
	void sendData(float*, int);
	//function to start the winsock used for the sockets
	int startWinsock(void);
	//function to start the socket
	int initSocket(void);
	//function to connect the socket to the socket of the server specified by the args
	int connectSocket(const char*, int);
	//cleanup function
	void cleanup(void);
	//cleanup funktion
	void cleanup(SOCKET);

	//DEBUG
	int measureTime = 60 * 1;
	int controlCounter = 0;
	void controlBlocks(int* running);
};
