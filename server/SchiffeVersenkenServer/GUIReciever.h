/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

// class to receive and parse the messages from the GUI

#pragma once

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <thread>
#include "audio_parameter.h"
#include "Audioprocessor.h"
#include "json.hpp"
using json = nlohmann::json;
#pragma comment(lib, "Ws2_32.lib")
#define GUIRECIEVERERROR -4

class GUIReciever
{
public:
	// constructor
	GUIReciever(int);
	// destructor
	~GUIReciever(void);
	// function to receive data from the network
	void recvData(int*, Audioprocessor*, Audioprocessor*);
	// thread do receive date from the network
	std::thread recvDataThread(int *running, Audioprocessor *client1, Audioprocessor *client2) 
	{
		return std::thread([=] {recvData(running, client1, client2); });//Thread that runs demandData. that enables you to remotely access the main function
	}
private:
	// function to parse the j-son message
	void parseMessage(char* Message, Audioprocessor *client1, Audioprocessor *client2);
	// functions and variables required for the socket
	int recieveData(char*);
	int startWinsock(void);
	int listenToConnection(void);
	int acceptConnection();
	void cleanup(void);
	void cleanup(SOCKET);
	void cleanup(SOCKET, SOCKET);
	int initSocket(int);
	int ret;
	long rc;
	SOCKET acceptSocket; //SOCKET acceptSocket; //Socket to accept connections
	SOCKET connectedSocket; //Socket to save the incomming message
	char recvBlock[CHAR_PER_BUF]; //block to save the incomming message
	int localStatus = 1;
	// char buffer
	char* tmpBuf = new char[CHAR_PER_BUF];
};