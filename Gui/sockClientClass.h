// Header to sockClientClass, a class to establish a connection to the server

/*
This file is part of the project "Schiffe-Versenken", a Voice-over-IP chat with disturbance algorithms.
The software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule).
This project is released under the terms of the MIT-license.
For license details see the license file.

Copyright (c) 2016	Finn Bayer			(finn.bayer@gmx.de)
					Michael Schaffert	(pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen	(n.westhausen@web.de)
*/
#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS // to use inet_addr
#define _CRT_SECURE_NO_WARNINGS //to use sprintf

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>


#pragma comment(lib, "Ws2_32.lib")

#define ESTIMATED_NUM_CLIENTS 3 //used for the connection to search for open Ports. The higher the estimated number, the more ports are searched

class sockClient
{
public:
	// constructor
	sockClient();
	// destructor
	~sockClient(void);
	// function to send char array
	void sendCharData(const char*) const;
	// connect function to use externally
	int conect_to_server(const char*, int);
	
private:
	long rc;
	int counter = 1;
	int ret = 0;
	SOCKET s;
	SOCKADDR_IN addr;
	// function to start socket
	static int startWinsock(void);
	// functions to cleanup
	static void cleanup(void);
	static void cleanup(SOCKET);
};
