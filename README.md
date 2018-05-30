# Schiffe versenken - a VoIP framework as an experimental environment for lombard-effect testing
"Schiffe versenken" is the german translation of the game "Battleships". The purpose of this framework was to implement an experimental environmont to test the lombard-effect and one possible test situation was this game. The software makes no claim to be perfect or completely finished. We hope that the code can help people that are trying to accomplish something similar. Please feel free to contact us if you have any questions regarding the project. 

### Overview
This C++-Framework can be used to create a Voice-over-IP-Chat between two clients.
Therefore two client application as well as one server application and a GUI application has to be started. On Server side the voice chat can be saved in a .wav file. You can also disturb the communication by adding effects like e.g. noise or reverb. The operator is able to preview the disturbed soundsignals and listen to the clean soundsignals.
General Structure:
* client -> contains the code used for the client application. Start the client through the SchiffeVersenkenClient.exe in the "Release" folder.
* server -> contains the code used for the server application. Start the server through the SchiffeVersenkenServer.exe in the "Release" folder.
* GUI -> contains the code for the gui. Start the gui through SchiffeVersenkenGui.exe ind the "gui_exe" folder
* LICENSE.txt
* README.md
* gitignore.txt


### Dependencies
* PortAudio
* libsndfile

### Getting Started
* clone the project
* make sure that three computer are connected in a network
* make sure that all computers are connected with a Scarlett 2i2 soundcard (you need three soundcards, one for each computer)
* make sure that the used sound card is set to the sample rate specified in the audio_parameter.h file
* start the gui.exe and the SchiffeVersenkenServer.exe on one computer
* connect the gui.exe to the server
* start two instances of the SchiffeVersenkenClient.exe on separate computer and connect to the server
* set the "Audio Out" Buttons for both clients to "Pre" or "Post"
* communicate through microphone and speakers on the client ends

### Version History
* 0.1 first beta (15.07.2016)

### Known Issues
* If the sound card isn't set to the sample rate implemented in the audio_parameter.h file on server and client side, the code crashes.
* If the used operating system is not Win10 lacks in the communication can occur due to network issues.
* If the starting procedure is not executed in the right order, the connection between the clients and the server can fail


### Special Thanks to...
Prof. Joerg Bitzer for the reverb algorithms and his constant support in the creation of this framework.
