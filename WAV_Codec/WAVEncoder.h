#pragma once
#include <windows.h>
#include <stdio.h>
#include "AudioInfo.h"

// ��ȡAudioBuff�Ļص����� ԭʼPCM����;
typedef int(*OnGetAudioBuff)(const char* pBuff, const int& iBuffSize);

class CWAVEncoder
{
public:
	CWAVEncoder();
	~CWAVEncoder();

	void SetAudioBack(OnGetAudioBuff pCallBack);
	void SetAudioInfo(const AudioInfo& info);

	int Start();
	int Stop();
	int Clear();

	// �ص���������������¼���ͻ���øú���;
	static DWORD CALLBACK WaveInProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

private:
	bool			m_bStop;
	AudioInfo		m_audioInfo;

	HWAVEIN			hWaveIn;			// �����豸;  
	WAVEFORMATEX	waveform;			// �ɼ���Ƶ�ĸ�ʽ���ṹ��;
	WAVEHDR			wHdr[AUDIO_BUFF_MAXCOUNT];	// �ɼ���Ƶʱ�������ݻ���Ľṹ��;
	char			chBuff[AUDIO_BUFF_MAXCOUNT][AUDIO_BUFF_MAXSIZE];
	OnGetAudioBuff	m_pCallBack;
};