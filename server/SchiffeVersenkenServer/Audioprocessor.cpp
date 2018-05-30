/*
This file is part of the project "Schiffe-Versenken" a Voice-over-IP chat with disturbance algorithms.
This software package was developed as a practical project in the 6th semester at the TGM (@Jade-Hochschule)
This project is released under the terms of the MIT-License.
For license details see the License file.
Copyright <c> 2016	Finn Bayer (finn.bayer@gmx.de)
					Michael Schaffert (pieter.michael.schaffert@googlemail.com)
					Nils L. Westhausen (n.westhausen@web.de)
*/

#include "Audioprocessor.h"

// constructor
Audioprocessor::Audioprocessor(void)
{
}

// destructor
Audioprocessor::~Audioprocessor(void)
{
	// delete Blocks
	delete[] returnBlock;
	delete[] cleanBlock;
	delete[] slot1Block;
	delete[] slot2Block;
	delete[] slot3Block;
	delete[] slot4Block;
	delete[] outEffectBlock;
	delete[] outOperatorBlock;
	delete[] outClientBlock;
	
	// delete Mixer
	delete mixerSlot1;
	delete mixerSlot2;
	delete mixerSlot3;
	delete mixerSlot4;

	// delete Other Mixer
	delete mixerClient;
	delete mixerOperator;

	// delete Slots and return
	delete slotEffect1;
	delete slotEffect2;
	delete slotEffect3;
	delete slotReturn;

	// delte gain Objects
	delete applyOperatorGain;
	delete applyClientGain;
}

/*
The function is called in a thread and is managing the audiosignal. It gets the audioblock from a buffer, calls the processAudio Function and distributes it to several Buffers
*/
void Audioprocessor::manageData(Buffer *recvBuf, Buffer *sendBuf, Buffer *ownReturnBuf,Buffer *otherReturnBuffer , controlBuffer *soundBufOperator,int *running)
{
	while (*running == 1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		if (recvBuf->getStatus() != BUFFEREMPTY && sendBuf->getStatus() != BUFFERFULL)
		{
			//managing the data which was recieved by the Networkreciever
			ret = recvBuf->getBlock(cleanBlock);
			if (ret == -1)
			{
				printf("Warning: recvBuffer is empty. Check the Buffer before calling the function.\n");
			}
			//sending the incoming audio data to the wavHandler to save it 
			wavHandler->manageRecording(cleanBlock);
			if (ownReturnBuf->getStatus() != BUFFERFULL)
			{
				ownReturnBuf->setBlock(cleanBlock);
			}
			if (otherReturnBuffer->getStatus() != BUFFEREMPTY)
			{
				otherReturnBuffer->getBlock(returnBlock);
			}
			else
			{
				CLEAR(returnBlock);
			}
			
			//process the Audio.
			processAudio();

			//putting the Block for the Operator Sound in the soundBufOperator
			ret = soundBufOperator->controlledSetBlock(outOperatorBlock);
			if (ret == -1)
				printf("Warning: soundBufOperator is full. Check the Status before calling the setBlock Function\n");

			//putting the Block for the Operator in the sendBuffer
			ret = sendBuf->setBlock(outClientBlock);
			if (ret == -1)
				printf("Warning: sendBuffer is full. Check the Buffer before calling the function.\n");
			
		}
	}
	printf("Shutting down AudioProcessor.\n");
}

// setter to direct the parameter to the slots
void Audioprocessor::setParam(int numSlot, int numEffect, int NumParam, double Value)
{
	switch (numSlot)
	{
	case 1:
	{
		slotEffect1->setParam(numEffect, NumParam, Value);
		return;
	}
	case 2:
	{
		slotEffect2->setParam(numEffect, NumParam, Value);
		return;
	}
	case 3:
	{
		slotEffect3->setParam(numEffect, NumParam, Value);
		return;
	}
	case 4:
	{
		slotReturn->setParam(NumParam, Value);
		return;
	}
	}
}

// setter for audioOutput
void Audioprocessor::setAudioAudioOut(int position, int Status)
{
	switch (position)
	{
	case 0: // Operator
	{
		StatusOpeator = Status;
		return;
	}
	case 1: // Client
	{
		StatusClient = Status;
		return;
	}
	}
}

// setter for the status of the slots
void Audioprocessor::setEffectStatus(int numSlot, int numEffect, int Status)
{
	switch (numSlot)
	{
	case 1:
	{
		slotEffect1->setEffectStatus(numEffect);
		StatusSlot1 = Status;
		return;
	}
	case 2:
	{
		slotEffect2->setEffectStatus(numEffect);
		StatusSlot2 = Status;
		return;
	}
	case 3:
	{
		slotEffect3->setEffectStatus(numEffect);
		StatusSlot3 = Status;
		return;
	}
	case 4:
	{
		StatusSlot4 = Status;
		return;
	}
	}
}

// setter for operator-gain
void Audioprocessor::setGainOperator(double Value)
{
	operatorGain = int(80.0 * Value - 60.0);
}

// function to start recording
void Audioprocessor::startRecording(const char * name, int lengthFileName)
{
	wavHandler->startRecording(name, lengthFileName);
}

// function to stop recording
void Audioprocessor::stopRecording(void)
{
	wavHandler->stopRecording();
}

// the heart of processing
void Audioprocessor::processAudio()
{
	// processing of slot 1
	slotEffect1->processAudio(cleanBlock, slot1Block);
	mixerSlot1->mixForEffects(slot1Block, cleanBlock, tempslot1Block, StatusSlot1);
	// processing of slot 2
	slotEffect2->processAudio(tempslot1Block, slot2Block);
	mixerSlot2->mixForEffects(slot2Block, tempslot1Block, tempslot2Block, StatusSlot2);
	// processing of slot 3
	slotEffect3->processAudio(tempslot2Block, slot3Block);
	mixerSlot3->mixForEffects(slot3Block, tempslot2Block, tempslot3Block, StatusSlot3);
	// processing of return
	slotReturn->processAudio(tempslot3Block, returnBlock, slot4Block);
	mixerSlot4->mixForEffects(slot4Block, tempslot3Block, outEffectBlock, StatusSlot4);
	// mix for output
	mixerClient->mixForOutput(outEffectBlock, cleanBlock, outClientBlock, StatusClient);
	mixerOperator->mixForOutput(outEffectBlock, cleanBlock, outOperatorBlock, StatusOpeator);
	// apply gain to output
	applyOperatorGain->applyGain(outOperatorBlock, operatorGain);
	applyClientGain->applyGain(outClientBlock, clientGain);
}

