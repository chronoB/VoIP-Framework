#pragma once

class CComb
{
public:
	CComb(int size, float damp, float feedback);
	~CComb(void);
	inline  float	process(float inp);
	void	mute();
	void	setdamp(float val);
	float	getdamp();
	void	setfeedback(float val);
	float	getfeedback();
private:
	float	m_feedback;
	float	m_filterstore;
	float	m_damp1;
	float	m_damp2;
	float	*m_buffer;
	int		m_bufsize;
	int		m_bufidx;
};


// Big to inline - but crucial for speed

inline float CComb::process(float input)
{
	float output;

	output = m_buffer[m_bufidx];

	m_filterstore = (output*m_damp2) + (m_filterstore*m_damp1);
//	undenormalise(filterstore);

	m_buffer[m_bufidx] = input + (m_filterstore*m_feedback);

	if (++m_bufidx >= m_bufsize) m_bufidx = 0;

	return output;
}
