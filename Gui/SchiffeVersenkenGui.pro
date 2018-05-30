#-------------------------------------------------
#
# Project created by QtCreator 2016-05-21T19:42:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SchiffeVersenkenGui
TEMPLATE = app


SOURCES += main.cpp\
        SchiffeVersenkenGui.cpp\
        GuiMessaging.cpp\
        sockClientClass.cpp


HEADERS  += SchiffeVersenkenGui.h\
			audio_parameter.h\
			GuiMessaging.h\
			json.hpp\
			sockClientClass.h


FORMS    += SchiffeVersenkenGui.ui
