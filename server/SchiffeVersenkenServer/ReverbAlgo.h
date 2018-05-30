#pragma once

#include "Allpass.h"
#include "Comb.h"

class CReverbAlgo
{
public:
	CReverbAlgo(float fs, float Mix, float ReverbTime);
	float processOneSample(float In);
	void setDryWet(float Mix);
	void setReverbTime(float ReverbTime);
	void reset(void);
	~CReverbAlgo();

private:
	float m_fs;
	float m_Mix;

	CAllpass **m_allpass;
	int m_NrOfAllpass;
	CComb	**m_comb;
	int m_NrOfComb;

};

