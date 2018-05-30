/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include "NetworkSender.h"

/*
Constructor
port -> port that should be opened to incomming connections*/
NetworkSender::NetworkSender(int port)
{
	ret = startWinsock();
	if (ret != 0)
		throw NETWORKSENDERERROR;
	ret = initSocket(port);
	if (ret != 0) 
		throw NETWORKSENDERERROR;
	ret = listenToConnection();
	if (ret != 0)
		throw NETWORKSENDERERROR;
}
/*
Destructor*/
NetworkSender::~NetworkSender()
{
	cleanup(acceptSocket,connectedSocket);
	delete[] tmpBuf;
}

/*
Function to listen to connections
*/
int NetworkSender::listenToConnection(void)
{
	//Listen to incomming connections
	rc = listen(acceptSocket, 0);
	if (rc == SOCKET_ERROR)
	{
		printf("Error: listen, error code: %d\n", WSAGetLastError());
		cleanup(acceptSocket);
		return -1;
	}
	else
		return acceptConnection();
}
/* 
Function to accept connections on the socket*/
int NetworkSender::acceptConnection()
{
	//if a connection is requested, accept it in another socket
	connectedSocket = accept(acceptSocket, NULL, NULL);
	if (connectedSocket == INVALID_SOCKET)
	{
		printf("Error: accept, error code: %d\n", WSAGetLastError());
		cleanup(acceptSocket,connectedSocket);
		return -1;
	}
	else
	{
		printf("New connection accepted.\n----------------------\n");
		closesocket(acceptSocket);
	}
	return 0;
}

/*
Sending Data.
send_buf -> Buffer with the data which should be send
BUFFERSIZE -> size of the float objects in the send_buf buffer
*/
void NetworkSender::sendData(float *sendBlock, int BUFFERSIZE)
{
	ret = send(connectedSocket, (char*)sendBlock, sizeof(sendBlock)*BUFFERSIZE, 0);
	if (ret == SOCKET_ERROR)
		printf("Error in NetworkSender sendData Function: %d", WSAGetLastError());
	controlCounter++;
}

/*
Function to demand the data from a foreign process
*pa2sendBuf -> pointer to a buffer that stores the data from the audioprocessor that should be send to the client 
running -> variable to correctly shut down the threads
*/
void NetworkSender::demandData(Buffer* pa2sendBuf,int *running)
{
	float tmpBuf[NETWORKBUFFERLENGTH];
	float  checksum = 0;
	while (*running == 1)
	{
		if (pa2sendBuf->getStatus() != BUFFEREMPTY)
		{
			ret = pa2sendBuf->getBlock(tmpBuf);
			//Calculation of the checksum
			for (int i = 0; i < BUFFERLENGTH; i++)
				checksum += tmpBuf[i];
			tmpBuf[BUFFERLENGTH] = checksum;
			
			sendData(tmpBuf, NETWORKBUFFERLENGTH);
		}
		checksum = 0;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	printf("Shutting down Sender.\n");
}

/*
Function to send the Startcode to the clients
Should only be called once
*/
void NetworkSender::sendingStartcode(void)
{
	for (int idx = 0; idx < NETWORKBUFFERLENGTH; idx++)
	{
		tmpBuf[idx] = 0.0f;
	}
	tmpBuf[0] = float(2.0);//startcode should be greater than 1 because the audio won't be bigger than 1 so it's clear thats it's the startcode.
	sendData(tmpBuf, NETWORKBUFFERLENGTH);
	printf("Startcode send!\n");
}

/*
Function to start the Winsock
*/
int NetworkSender::startWinsock(void)
{
	WSADATA wsa;
	rc = WSAStartup(MAKEWORD(2, 0), &wsa);

	if (rc != 0)
	{
		printf("WinsockError happend. Code: %d\n", rc);
		return -1;
	}
	return 0;
}


/*
Cleanup Function to close the Winsock.
*/
void NetworkSender::cleanup()
{
	WSACleanup();
}

/*
Cleanup Function to close the Winsock object and an additional Socket.
sock1 -> socket that should be closed
*/
void NetworkSender::cleanup(SOCKET sock1)
{
	try
	{
		closesocket(sock1);
	}
	catch (...) {}

	WSACleanup();
}

/*
Cleanup Function to close the Winsock object and two additional Sockets.
sock1 -> socket that should be closed
sock2 -> socket that should be closed
*/
void NetworkSender::cleanup(SOCKET sock1, SOCKET sock2)
{
	try
	{
		closesocket(sock1);
	}
	catch (...) {}
	try
	{
		closesocket(sock2);
	}
	catch (...) {}
	WSACleanup();
}


/*
Initialisation of the Socket
port -> port on which the socket should be opened 
*/
int NetworkSender::initSocket(int port)
{
	SOCKADDR_IN addr;
	// create socket to accept connections
	acceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (acceptSocket == INVALID_SOCKET)
	{
		printf("Fehler: Der Socket konnte nicht erstellt werden, Fehler Code: %d\n", WSAGetLastError());
		cleanup(acceptSocket);
		return -1;
	}

	//Bind socket to a port so a client can reach it
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	rc = bind(acceptSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));
	if (rc == SOCKET_ERROR)
	{
		printf("Fehler: bind, Fehler Code: %d\n", WSAGetLastError());
		cleanup(acceptSocket);
		return -1;
	}
	return 0;
}

/*
Function to control number of Blocks sent (only for debug)
running -> variable to correctly shut down the threads
numSender -> id to check which sender it is*/
void NetworkSender::controlBlocks(int* running, int NumSender)
{
	while (*running == 0)
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	
	int counter_here = 0;
	while (*running == 1)
	{
		controlCounter = 0;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 * measureTime));
		counter_here = controlCounter;
		double frames_per_second = double(counter_here) * double(FRAMES_PER_BUFFER) / double(measureTime);
		//printf("Write to Soundcard: Fs = %f\n", frames_per_second);
		printf("Sender %dBlocks sended: %d\n\n",NumSender, counter_here);
	}

}