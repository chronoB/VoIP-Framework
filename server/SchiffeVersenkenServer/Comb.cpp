// Comb filter implementation
//
// Written by Jezar at Dreampoint, June 2000
// http://www.dreampoint.co.uk
// This code is public domain

#include "comb.h"

CComb::CComb(int size, float damp, float feedback)
:m_bufsize(size),
m_feedback(feedback)
{
	m_buffer = new float[m_bufsize];
	m_filterstore = 0;
	m_bufidx = 0;
	setdamp(damp);
	mute();
}

CComb::~CComb(void)
{
	delete[] m_buffer;
}


void CComb::mute()
{
	for (int i = 0; i<m_bufsize; i++)
		m_buffer[i] = 0;
}

void CComb::setdamp(float val)
{
	m_damp1 = val;
	m_damp2 = 1 - val;
}

float CComb::getdamp()
{
	return m_damp1;
}

void CComb::setfeedback(float val)
{
	m_feedback = val;
}

float CComb::getfeedback()
{
	return m_feedback;
}

// ends
