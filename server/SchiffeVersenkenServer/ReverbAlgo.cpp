#include "ReverbAlgo.h"



CReverbAlgo::CReverbAlgo(float fs, float Mix, float ReverbTime)
:m_fs(fs),
m_Mix(Mix)
{

	const int allpasstuningL1 = int(556.f / 44100.f*m_fs);
	const int allpasstuningL2 = int(441.f / 44100.f*m_fs);
	const int allpasstuningL3 = int(341.f / 44100.f*m_fs);
	const int allpasstuningL4 = int(225.f / 44100.f*m_fs);

	m_NrOfAllpass = 4;

	m_allpass = new CAllpass*[m_NrOfAllpass];

	m_NrOfComb = 8;

	m_comb = new CComb*[m_NrOfComb];

	int kk;
	
	for (kk = 0; kk < m_NrOfAllpass; kk++)
	{
		if (kk == 0)
			m_allpass[kk] = new CAllpass(allpasstuningL1, 0.5);
		if (kk == 1)
			m_allpass[kk] = new CAllpass(allpasstuningL2, 0.5);
		if (kk == 2)
			m_allpass[kk] = new CAllpass(allpasstuningL3, 0.5);
		if (kk == 3)
			m_allpass[kk] = new CAllpass(allpasstuningL4, 0.5);

	}

	const int combtuningL1 = int (1116.f/44100.f*m_fs);
	const int combtuningL2 = int (1188.f / 44100.f*m_fs);
	const int combtuningL3 = int(1277.f / 44100.f*m_fs);
	const int combtuningL4 = int(1356.f / 44100.f*m_fs);
	const int combtuningL5 = int(1422.f / 44100.f*m_fs);
	const int combtuningL6 = int(1491.f / 44100.f*m_fs);
	const int combtuningL7 = int(1557.f / 44100.f*m_fs);
	const int combtuningL8 = int(1617.f / 44100.f*m_fs);



	for (kk = 0; kk < m_NrOfComb; kk++)
	{
		if (kk == 0)
			m_comb[kk] = new CComb(combtuningL1, 0.25, 0.9);

		if (kk == 1)
			m_comb[kk] = new CComb(combtuningL2, 0.25, 0.9);
		if (kk == 2)
			m_comb[kk] = new CComb(combtuningL3, 0.25, 0.9);
		if (kk == 3)
			m_comb[kk] = new CComb(combtuningL4, 0.25, 0.9);
		if (kk == 4)
			m_comb[kk] = new CComb(combtuningL5, 0.25, 0.9);
		if (kk == 5)
			m_comb[kk] = new CComb(combtuningL6, 0.25, 0.9);
		if (kk == 6)
			m_comb[kk] = new CComb(combtuningL7, 0.25, 0.9);
		if (kk == 7)
			m_comb[kk] = new CComb(combtuningL8, 0.25, 0.9);
	}


	setReverbTime(ReverbTime);
	reset();
}

float CReverbAlgo::processOneSample(float In)
{
	float Out;
	float Processed(0.f);

	// First Comb filter in parallel
	int kk;
	for (kk = 0; kk < m_NrOfComb; kk++)
		Processed += m_comb[kk]->process(In);

	// Second allpass filter in series
	for (kk = 0; kk < m_NrOfAllpass; kk++)
		Processed = m_allpass[kk]->process(Processed);

	Processed = m_Mix * Processed;
	Out = ((1.0f - m_Mix) * In + Processed);

	return Out;
}
void CReverbAlgo::setDryWet(float Mix)
{
	m_Mix = Mix;
}
void CReverbAlgo::setReverbTime(float RverbTime)
{
	float feedback = 0.28f*RverbTime + 0.7f;

	(feedback <= 0.99f) ? feedback : 0.99f;

	if (feedback > 0.99f)
		feedback = 0.99f;


	int kk;
	for (kk = 0; kk < m_NrOfComb; kk++)
		m_comb[kk]->setfeedback(feedback);

}
void CReverbAlgo::reset(void)
{
	int kk;
	for (kk = 0; kk < m_NrOfAllpass; kk++)
		m_allpass[kk]->mute();

	for (kk = 0; kk < m_NrOfComb; kk++)
		m_comb[kk]->mute();

}


CReverbAlgo::~CReverbAlgo()
{
	int kk;
	for (kk = 0; kk < m_NrOfAllpass; kk++)
	{
		delete m_allpass[kk];
		m_allpass[kk] = nullptr;
	}
	delete[] m_allpass;
	m_allpass = nullptr;

	for (kk = 0; kk < m_NrOfComb; kk++)
	{
		delete m_comb[kk];
		m_comb[kk] = nullptr;
	}
	delete[] m_comb;
	m_comb = nullptr;
}