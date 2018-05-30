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
ipAddr -> the ip addr of the server
port -> port that is opened by the server*/
NetworkSender::NetworkSender(const char * ipAddr, int port)
{
	ret = startWinsock();
	if (ret != 0)
		throw NETWORKSENDERERROR;
	ret = initSocket();
	if (ret != 0)
		throw NETWORKSENDERERROR;
	ret = connectSocket(ipAddr, port);
	if (ret != 0)
		throw NETWORKSENDERERROR;

}

/*
Destructor*/
NetworkSender::~NetworkSender(void)
{
	cleanup(networkSocket);
}

/*
Sending Data.
send_buf -> Buffer with the data which should be send
BUFFERSIZE -> size of the float objects in the send_buf buffer
*/
void NetworkSender::sendData(float *sendBlock, int Buffersize)
{
	ret = send(networkSocket, (char*)sendBlock, sizeof(float)*Buffersize, 0);
	if (ret == SOCKET_ERROR)
		printf("Error in NetworkSender sendData Function: %d", WSAGetLastError());
	controlCounter++;
}
/*
Function to demand the data from a foreign process
*/
void NetworkSender::demandData(Buffer *pa2sendBuf, int * running)
{
	float tmpBuf[NETWORKBLOCKLENGTH*sizeof(float)];//1 for checksum
	float checksum = 0;
	while (*running == 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

	}
	while (*running == 1)
	{
		if (pa2sendBuf->getStatus() != BUFFEREMPTY)
		{
			ret = pa2sendBuf->getBlock(tmpBuf);
			//Calculation of the checksum
			for (int i = 0; i < BLOCKLENGTH; i++)
				checksum += tmpBuf[i];
			tmpBuf[BLOCKLENGTH] = checksum;
			
			sendData(tmpBuf, NETWORKBLOCKLENGTH);
		}
		checksum = 0;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	printf("Shutting down Sender.\n");
}



/*
Cleanup Function to close the Winsock.
*/
void NetworkSender::cleanup(void)
{
	WSACleanup();
}

/*
Cleanup Function to close the Winsock object and an additional Socket.
*/
void NetworkSender::cleanup(SOCKET sock1)
{
	try
	{
		closesocket(sock1);
	}
	catch (int) {}

	WSACleanup();
}
/*
Function to start the WINSOCK
returns -1 if something went wrong
*/
int NetworkSender::startWinsock(void)
{
	WSADATA wsa;
	ret = WSAStartup(MAKEWORD(2, 0), &wsa);
	if (ret != 0)
	{
		printf("Error: startWinsock, error code: %d\n", ret);
		cleanup();
		return -1;
	}
	return 0;

}
/*
Initialization of the socket */
int NetworkSender::initSocket()
{
	networkSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (networkSocket == INVALID_SOCKET) {
		printf("Error: Socket can't be created, error code: %d\n", WSAGetLastError());
		cleanup(networkSocket);
		return -1;
	}
	return 0;
}

/*
Function to connect the socket to the socket of the server.
ip-> IP of the servers
port -> Port of the server you want to connect to
return -> 0 if correct, -1 if something went wrong*/
int NetworkSender::connectSocket(const char* ip, int port)
{
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);

	ret = connect(networkSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));
	int counter = 0;
	while (ret == SOCKET_ERROR && counter < ESTIMATED_NUM_CLIENTS * 2)
	{
		counter = counter + 2;
		printf("Port blocked. Trying Port %d now!\n", port + counter);
		addr.sin_port = htons(port + counter);
		ret = connect(networkSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));
	}
	if (ret != 0)
	{
		printf("Error: connect failed, error code: %d\n", WSAGetLastError());
		cleanup(networkSocket);
		return -1;
	}
	return 0;
}

/*
Function to control number of Blocks sent (only for debug)
running -> variable to correctly shut down the threads*/
void NetworkSender::controlBlocks(int* running)
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
		printf("Blocks send: %d\n\n", counter_here);
	}

}