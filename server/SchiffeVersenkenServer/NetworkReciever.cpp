/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include "NetworkReciever.h"

/*
Constructor
port -> port that should be opened to incomming connections*/
NetworkReciever::NetworkReciever(int port)
{
	ret = startWinsock();
	if (ret != 0)
		throw NETWORKRECIEVERERROR;
	ret = initSocket(port);
	if (ret != 0)
		throw NETWORKRECIEVERERROR;
	ret = listenToConnection();
	if (ret != 0)
		throw NETWORKRECIEVERERROR;
}

/*
Destructor*/
NetworkReciever::~NetworkReciever(void)
{
	cleanup(acceptSocket, connectedSocket);
}

/*
Function to continuously call the function to recv data over the network
*/
void NetworkReciever::recvData(Buffer *recv2paBuf, int *running)
{
	float tmpBuf[NETWORKBUFFERLENGTH*sizeof(float)]; // the length has to equal the length of the recv buffer defined as a privat member variable
	float checksum = 0;
	while (*running == 1)
	{
		if (recv2paBuf->getStatus() != BUFFERFULL)
		{
			ret = recieveData(tmpBuf);
			if (ret != 0)
				*running = 0;

			//check checksum
			for (int i = 0; i < BUFFERLENGTH; i++)
				checksum += tmpBuf[i];
			if (checksum == tmpBuf[BUFFERLENGTH])
				recv2paBuf->setBlock(tmpBuf);
			else
				printf("-------------------\nChecksum invalid!\nRecieved Checksum: %f\nCalculated Checksum: %f\n----------------\n", tmpBuf[BUFFERLENGTH], checksum);

		}
		else
			printf("Warning: recv2paBuf is full");
		checksum = 0;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	printf("Shutting down Reciever.\n");

}
/*
Function to recieve the Data through the Winsock API
recvBuffer -> Array that stores the recieved samples
*/
int NetworkReciever::recieveData(float *recvBuffer)
{
	ret = recv(connectedSocket, recvBlock, sizeof(recvBlock), MSG_WAITALL);
	if (ret == 0)
	{
		printf("Server has closed the connection...\n");
		return -1;
	}
	else if (ret == SOCKET_ERROR)
	{
		printf("Error: recv, error code: %d\n", WSAGetLastError());
		return -1;
	}
	memcpy(recvBuffer, recvBlock, sizeof(recvBlock));
	controlCounter++;
	return 0;
}

/*
Function to listen to connections
*/
int NetworkReciever::listenToConnection(void)
{
	//listen to incomming connections
	ret = listen(acceptSocket, 0);
	if (ret == SOCKET_ERROR)
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
int NetworkReciever::acceptConnection()
{
	//if a connection is incomming, accept it and assign it to a socket
	connectedSocket = accept(acceptSocket, NULL, NULL);
	if (connectedSocket == INVALID_SOCKET)
	{
		printf("Error: accept, error code: %d\n", WSAGetLastError());
		cleanup(acceptSocket, connectedSocket);
		return -1;
	}
	else
	{
		printf("New connection accepted.\n----------------------\n");
		closesocket(acceptSocket);
	}
	return 0;
}


//Function to start the winsock
int NetworkReciever::startWinsock(void)
{
	WSADATA wsa;
	ret = WSAStartup(MAKEWORD(2, 0), &wsa);
	if (ret != 0)
	{
		printf("error: startWinsock, error code: %d\n", ret);
		return -1;
	}
	return 0;


}

/*
Cleanup Function to close the Winsock.
*/
void NetworkReciever::cleanup()
{
	WSACleanup();
}

/*
Cleanup Function to close the Winsock object and an additional Socket.
sock1 -> socket that should be closed
*/
void NetworkReciever::cleanup(SOCKET sock1)
{
	try
	{
		closesocket(sock1);
	}
	catch (...) {}

	WSACleanup();
}


/*
Cleanup Function to close the Winsock object and an additional Socket.
sock1 -> socket that should be closed
sock2 -> socket that should be closed
*/
void NetworkReciever::cleanup(SOCKET sock1, SOCKET sock2)
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
int NetworkReciever::initSocket(int port)
{
	SOCKADDR_IN addr;
	// create socket to accept connections
	acceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (acceptSocket == INVALID_SOCKET)
	{
		printf("Error: Accept socket cannot be created, error code: %d\n", WSAGetLastError());
		cleanup(acceptSocket);
		return -1;
	}

	//bind the socket to a port so the client can reach it
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	ret = bind(acceptSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));
	if (ret == SOCKET_ERROR)
	{
		printf("Fehler: bind, fehler code: %d\n", WSAGetLastError());
		cleanup(acceptSocket);
		return -1;
	}
	return 0;
}

/*
Function to control number of Blocks recieved (only for debug)
running -> variable to correctly shut down the threads
numReciever -> id to check which reciever it is*/
void NetworkReciever::controlBlocks(int* running, int numReciver)
{
	while (*running == 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	int counter_here = 0;
	while (*running == 1)
	{
		controlCounter = 0;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 * measureTime));
		counter_here = controlCounter;
		double frames_per_second = double(counter_here) * double(FRAMES_PER_BUFFER) / double(measureTime);
		//printf("Write to Soundcard: Fs = %f\n", frames_per_second);
		printf("Reciever %d: Blocks recieved: %d\n\n", numReciver, counter_here);
	}

}