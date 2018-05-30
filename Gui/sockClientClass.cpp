/*
This file is part of the project "Schiffe-Versenken", a Voice-over-IP chat with disturbance algorithms.
The software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule).
This project is released under the terms of the MIT-license.
For license details see the license file.

Copyright (c) 2016	Finn Bayer			(finn.bayer@gmx.de)
					Michael Schaffert	(pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen	(n.westhausen@web.de)
*/

#include "sockClientClass.h"
#include "audio_parameter.h"

// constructor
sockClient::sockClient()
{
	// start socket
	rc = startWinsock();
	if (rc != 0)
	{
		if (rc == WSAEINPROGRESS) 
		{
			//a WinSock is already running. There is no need for another one
		}
		else
		{
			cleanup();
			Sleep(10);
		}
	}

	// create TCP/IP socket
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		cleanup(s);
		Sleep(10);
	}
}

// destructor
sockClient::~sockClient(void)
{
	cleanup(s);
}

// function to send char array
void sockClient::sendCharData(const char* send_buf) const
{
	send(s, send_buf, CHAR_PER_BUF, 0);
}

// function to connect to server
int sockClient::conect_to_server(const char* ipAddr, int port)
{
	// establishing socket connection
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ipAddr);

	rc = connect(s, reinterpret_cast<SOCKADDR*>(&addr), sizeof(SOCKADDR));
	counter = 1;
	while (rc == SOCKET_ERROR && counter < ESTIMATED_NUM_CLIENTS * 2)
	{
		addr.sin_port = htons(port);
		rc = connect(s, reinterpret_cast<SOCKADDR*>(&addr), sizeof(SOCKADDR));
		counter++;
	}
	if (rc != 0)
	{
		cleanup(s);
		Sleep(1000);
		return 0;
	}
	else
	{
		return 1;
	}
}

// cleanup functions
void sockClient::cleanup(void)
{
	WSACleanup();
}
void sockClient::cleanup(SOCKET sock1)
{
	try
	{
		closesocket(sock1);
	}
	catch (int) {}

	WSACleanup();
}

// function to start socket
int sockClient::startWinsock(void)
{
	WSADATA wsa;
	return WSAStartup(MAKEWORD(2, 0), &wsa);
}
