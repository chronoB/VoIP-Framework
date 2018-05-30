#include "Allpass.h"
// Allpass filter implementation
//
// Written by Jezar at Dreampoint, June 2000
// http://www.dreampoint.co.uk
// This code is public domain

// slightly changed by J. Bitzer

CAllpass::CAllpass(int Size, float feedback)
:m_bufsize(Size),
m_feedback(feedback)
{
	m_buffer = new float[Size];
	m_bufidx = 0;
	mute();
}
CAllpass::~CAllpass(void)
{
	delete[] m_buffer;
}

void CAllpass::mute()
{
	for (int i = 0; i<m_bufsize; i++)
		m_buffer[i] = 0;
}

void CAllpass::setfeedback(float val)
{
	m_feedback = val;
}

float CAllpass::getfeedback()
{
	return m_feedback;
}

