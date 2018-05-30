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
ipAddr -> the ip addr of the server
port -> port that is opened by the server*/
NetworkReciever::NetworkReciever(const char* ipAddr, int port)
{
	ret = startWinsock();
	if (ret != 0)
		throw NETWORKRECIEVERERROR;
	ret = initSocket();
	if (ret != 0)
		throw NETWORKRECIEVERERROR;
	ret = connectSocket(ipAddr, port);
	if (ret != 0)
		throw NETWORKRECIEVERERROR;
	

}
/*
Destructor*/
NetworkReciever::~NetworkReciever(void)
{
	cleanup(networkSocket);
}

/*
Function that is continously called in a thread to call the recieveData function an save the recieved Block into a Buffer
recv2paBuf -> Buffer that is used to store the recieved Block before it will be used by the audioframework
running -> variable that is used to shutdown the threads properly*/
void NetworkReciever::recvData(controlBuffer *recv2paBuf, int* running)
{
	float tmpBuf[NETWORKBLOCKLENGTH];//1 for checksum
	float checksum = 0;

	ret = recieveData(tmpBuf);//recv the startcode
	if (tmpBuf[0] == float(2.0))
	{
		printf("Communication started!\n");
		*running = 1;
	}
	else
	{
		*running = 0;
		printf("Error: Startcode was wrong!\n");
	}
	while (*running == 1)
	{
		if (recv2paBuf->getStatus() != BUFFERFULL)
		{
			ret = recieveData(tmpBuf);
			if (ret != 0)
				*running = 0;
			
			//check Checksum 
			for (int i = 0; i < BLOCKLENGTH; i++)
				checksum += tmpBuf[i];
			if (checksum == tmpBuf[BLOCKLENGTH])
				recv2paBuf->controlledSetBlock(tmpBuf);
			else
				printf("-------------------\nChecksum invalid!\nRecieved Checksum: %f\nCalculated Checksum: %f\n----------------\n", tmpBuf[BLOCKLENGTH], checksum);
		}
		else
			printf("Warning: recv2paBuf is full.\n");
		checksum = 0;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	printf("Shutting down Reciever.\n");
}

/*
Function to recieve a block through the winsock lib
recvBuffer -> Array that is used to save the recieved Block*/
int NetworkReciever::recieveData(float *recvBuffer)
{
	ret = recv(networkSocket, recv_buf, sizeof(recv_buf), MSG_WAITALL);
	if (ret == 0)
	{
		printf("Server has closed the connection..\n");
		return -1;
	}
	else if (ret == SOCKET_ERROR)
	{
		printf("Error: recv, error code: %d\n", WSAGetLastError());
		return -1;
	}
	memcpy(recvBuffer, recv_buf, sizeof(recv_buf));
	controlCounter++;
	return 0;
}
/*
Function to shutdown the Winsocket properly*/
void NetworkReciever::cleanup(void)
{
	WSACleanup();
}

/*
Function to shutdown the Winsocket and the created socket correct properly
sock1 -> socket that should be closed*/
void NetworkReciever::cleanup(SOCKET sock1)
{
	try
	{
		closesocket(sock1);
	}//if socket is already closed, do nothing
	catch (int) {}

	WSACleanup();
}
/*
Function to start the WINSOCK
returns -1 if something went wrong
*/
int NetworkReciever::startWinsock(void)
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
int NetworkReciever::initSocket()
{
	networkSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (networkSocket == INVALID_SOCKET) {
		printf("Error: Socket cannot be created, error code: %d\n", WSAGetLastError());
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
int NetworkReciever::connectSocket(const char* ip, int port)
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
Function to control number of Blocks recieved (only for debug)
running -> variable to correctly shut down the threads*/
void NetworkReciever::controlBlocks(int* running)
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
		printf("Blocks recieved: %d\n\n", counter_here);
	}

}