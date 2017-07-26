#pragma once
#include "AudioInfo.h"

// ��ȡAudioBuff�Ļص����� ԭʼPCM����;
typedef int(*OnSetAudioBuff)(char* pBuff, int iBuffSize);

class CWAVDecoder
{
public:
	CWAVDecoder();
	~CWAVDecoder();

	void SetAudioBack(OnSetAudioBuff pCallBack);
	void SetAudioInfo(const AudioInfo& info);

	int Start();
	int Stop();
	int Clear();

	// �ص���������Ҫʱ���ⲿ��������;
	static DWORD CALLBACK WaveOutProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

private:
	bool			m_bStop;
	AudioInfo		m_audioInfo;

	HWAVEOUT		m_hWaveOut;			// ����豸;  
	WAVEFORMATEX	m_waveform;			// �ɼ���Ƶ�ĸ�ʽ���ṹ��;
	WAVEHDR			m_arrHdr[AUDIO_BUFF_MAXCOUNT];	// �ɼ���Ƶʱ�������ݻ���Ľṹ��;
	char			m_BuffOut[AUDIO_BUFF_MAXCOUNT][AUDIO_BUFF_MAXSIZE];
	OnSetAudioBuff	m_pCallBack;
};