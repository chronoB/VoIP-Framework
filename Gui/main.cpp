/*
This file is part of the project "Schiffe-Versenken", a Voice-over-IP chat with disturbance algorithms.
The software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule).
This project is released under the terms of the MIT-license.
For license details see the license file.

Copyright (c) 2016	Finn Bayer			(finn.bayer@gmx.de)
Michael Schaffert	(pieter.michael.schaffert@googlemail.com)
Nils L. Westhausen	(n.westhausen@web.de)
*/

// main to start the GUI

#include "SchiffeVersenkenGui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SchiffeVersenkenGui w;
	w.show();
	return a.exec();
}



