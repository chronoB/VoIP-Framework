#pragma once

// Allpass filter declaration
//
// Written by Jezar at Dreampoint, June 2000
// http://www.dreampoint.co.uk
// This code is public domain

#pragma once
//#include "denormals.h"

class CAllpass
{
public:
	CAllpass(int Size, float feedback);
	~CAllpass(void);
	inline  float	process(float inp);
	void	mute();
	void	setfeedback(float val);
	float	getfeedback();

private:
	float	m_feedback;
	float	*m_buffer;
	int		m_bufsize;
	int		m_bufidx;
};


// Big to inline - but crucial for speed

inline float CAllpass::process(float input)
{
	float output;
	float bufout;

	bufout = m_buffer[m_bufidx];
//	undenormalise(bufout);

	output = -input + bufout;
	m_buffer[m_bufidx] = input + (bufout*m_feedback);

	if (++m_bufidx >= m_bufsize) m_bufidx = 0;

	return output;
}

//ends

