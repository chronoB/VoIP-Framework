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
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include "Buffer.h"
#include <thread>

#pragma comment(lib, "Ws2_32.lib")

#define BUFFERLENGTH FRAMES_PER_BUFFER 
#define NETWORKBUFFERLENGTH (BUFFERLENGTH+1) //+1 for the checksum 
#define NETWORKSENDERERROR -1

class NetworkSender
{
public:
	NetworkSender(int);
	~NetworkSender(void);
	void demandData(Buffer*,int*); //hier müssen die Daten von der Main gefordert werden
	std::thread demandDataThread(Buffer* sendBuf,int *running) {//Thread der demandData ausführt. Dadurch ist eine remoteZugriff von der main funktion möglich
		return std::thread([=] {demandData(sendBuf,running); });
	}
	void sendingStartcode(void);

	std::thread BlockControler(int* running, int numSender) {
		return std::thread([=] {controlBlocks(running, numSender); });//Thread der demandData ausführt. Dadurch ist eine remoteZugriff von der main funktion möglich
	}

private:
	int ret = 0;
	long rc;
	SOCKET acceptSocket; //Socket to accept connections
	SOCKET connectedSocket; //Socket in dem die ankommende verbindung abgespeichert wird
	float* tmpBuf = new float[NETWORKBUFFERLENGTH]; //temporary array to store the data that should be send
	

	void sendData(float*, int);
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