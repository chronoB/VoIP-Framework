/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include "GUIReciever.h"

// constructor with initialization of the socket
GUIReciever::GUIReciever(int port)
{
	ret = startWinsock();
	if (ret != 0)
		throw GUIRECIEVERERROR;
	ret = initSocket(port);
	if (ret != 0)
		throw GUIRECIEVERERROR;
	ret = listenToConnection();
	if (ret != 0)
		throw GUIRECIEVERERROR;
}

// destructor
GUIReciever::~GUIReciever(void)
{
	// cleanup socket
	cleanup(acceptSocket, connectedSocket);
	// delete tmp message buffer
	delete[] tmpBuf;
}

/*
Function to continuously call the function to recv data over the network
*/
// void NetworkReciever::recvData(CharBuffer *recvBuf, int *running)
void GUIReciever::recvData(int *running, Audioprocessor *client1, Audioprocessor *client2)
{
	while (*running == 1)
	{
		ret = recieveData(tmpBuf);
		if (ret == -1)
			*running = 0;
		else
		{
			try
			{	
				// parse message
				parseMessage(tmpBuf, client1, client2);
			}
			catch (...) // catch error if one occurs
			{	
			}
			CLEAR(tmpBuf);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
	}
	printf("Shutting down GuiReciever.\n");
}

// parses json Messages
void GUIReciever::parseMessage(char* Message, Audioprocessor *client1, Audioprocessor *client2)
{
	auto jMessage = json::parse(Message);
	auto type = jMessage["type"].get<std::string>();
	
	// determine type and parse the message to the right location
	if (type.compare("setParameters") == 0)
	{
		if (jMessage["slot"].get<int>() < R1)
		{
			client1->setParam(jMessage["slot"].get<int>(), jMessage["numEffect"].get<int>(), jMessage["numParameter"].get<int>(), jMessage["value"].get<double>());
		}
		else
		{
			client2->setParam(jMessage["slot"].get<int>()-ReturnL, jMessage["numEffect"].get<int>(), jMessage["numParameter"].get<int>(), jMessage["value"].get<double>());
		}
	}
	else if (type.compare("setRecording") == 0)
	{
		if (jMessage["numClient"].get<int>() == 1)
		{
			if (jMessage["status"].get<int>() == 1)
			{
				client1->startRecording(jMessage["fileName"].get<std::string>().c_str(), jMessage["fileName"].get<std::string>().length());
			}
			else
			{
				client1->stopRecording();
			}
		}
		else
		{
			if (jMessage["status"].get<int>() == 1)
			{
				client2->startRecording(jMessage["fileName"].get<std::string>().c_str(), jMessage["fileName"].get<std::string>().length());
			}
			else
			{
				client2->stopRecording();
			}
		}
	}
	else if (type.compare("setAudioOut") == 0)
	{
		if (jMessage["numLocation"].get<int>() == 1)
		{
			client1->setAudioAudioOut(jMessage["location"].get<int>(), jMessage["status"].get<int>());
		}
		else
		{
			client2->setAudioAudioOut(jMessage["location"].get<int>(), jMessage["status"].get<int>());
		}
	}
	else if (type.compare("setGainOperator") == 0)
	{
		if (jMessage["numOperator"].get<int>() == 1)
		{
			client1->setGainOperator(jMessage["gain"].get<double>());
		}
		else
		{
			client2->setGainOperator(jMessage["gain"].get<double>());
		}
	}
	else if (type.compare("setEffectStatus") == 0)
	{
		if (jMessage["slot"].get<int>() < R1)
		{
			client1->setEffectStatus(jMessage["slot"].get<int>(), jMessage["numEffect"].get<int>(), jMessage["status"].get<int>());
		}
		else
		{
			client2->setEffectStatus(jMessage["slot"].get<int>()-ReturnL, jMessage["numEffect"].get<int>(), jMessage["status"].get<int>());
		}
	}
	
}

// function to receive data from the network
int GUIReciever::recieveData(char *recvBuffer)
{
	rc = recv(connectedSocket, recvBlock, CHAR_PER_BUF, 0);
	
	if (rc == 0)
	{
		printf("Server hat die Verbindung getrennt..\n");
		return -1;
	}
	else if (rc == SOCKET_ERROR)
	{
		printf("Fehler: recv, fehler code: %d\n", WSAGetLastError());
		return -1;
	}
	memcpy(recvBuffer, recvBlock, sizeof(recvBlock));
	CLEAR(recvBlock);
	return 0;
}

int GUIReciever::listenToConnection(void)
{
	//Horchen auf einkommende Verbindungen
	ret = listen(acceptSocket, 0);
	if (ret == SOCKET_ERROR)
	{
		printf("Fehler: listen, fehler code: %d\n", WSAGetLastError());
		cleanup(acceptSocket);
		return -1;
	}
	else
		return acceptConnection();
}

// function to accept connection
int GUIReciever::acceptConnection()
{
	connectedSocket = accept(acceptSocket, NULL, NULL);
	if (connectedSocket == INVALID_SOCKET)
	{
		printf("Fehler: accept, fehler code: %d\n", WSAGetLastError());
		cleanup(acceptSocket, connectedSocket);
		return -1;
	}
	else
	{
		printf("GUI Verbindung wurde hergestellt.\n----------------------\n");
		closesocket(acceptSocket);
	}
	return 0;
}

// function to start socket
int GUIReciever::startWinsock(void)
{
	WSADATA wsa;
	ret = WSAStartup(MAKEWORD(2, 0), &wsa);
	if (ret != 0)
	{
		printf("Fehler: startWinsock, fehler code: %d\n", ret);
		return -1;
	}
	return 0;
}

// clean up functions
void GUIReciever::cleanup()
{
	WSACleanup();
}
void GUIReciever::cleanup(SOCKET sock1)
{
	try
	{
		closesocket(sock1);
	}
	catch (int) {}

	WSACleanup();
}
void GUIReciever::cleanup(SOCKET sock1, SOCKET sock2)
{
	try
	{
		closesocket(sock1);
	}
	catch (int) {}
	try
	{
		closesocket(sock2);
	}
	catch (int) {}
	WSACleanup();
}

// function to initialize socket
int  GUIReciever::initSocket(int port)
{
	SOCKADDR_IN addr;
	// Socket zum akzeptieren von Verbindungen erstellen
	acceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (acceptSocket == INVALID_SOCKET)
	{
		printf("Fehler: Der Socket konnte nicht erstellt werden, fehler code: %d\n", WSAGetLastError());
		cleanup(acceptSocket);
		return -1;
	}

	//Binden des Sockets an einen Port, damit ein Client ihn erreichen kann.
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