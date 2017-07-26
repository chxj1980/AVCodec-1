#include "WAVEncoder.h"

CWAVEncoder::CWAVEncoder()
{
	m_bStop = true;
	m_pCallBack = NULL;
}

CWAVEncoder::~CWAVEncoder()
{
}

void CWAVEncoder::SetAudioBack(OnGetAudioBuff pCallBack)
{
	m_pCallBack = pCallBack;
}

void CWAVEncoder::SetAudioInfo(const AudioInfo& info)
{
	m_audioInfo = info;
}

int CWAVEncoder::Start()
{
	memset(&waveform, 0, sizeof(WAVEFORMATEX));
	int iChannels = m_audioInfo.iChannels;
	int iBitsPerSample = m_audioInfo.iBitsPerSample;
	waveform.wFormatTag = WAVE_FORMAT_PCM;						// ������ʽΪPCM;
	waveform.nSamplesPerSec = m_audioInfo.iSamplesPerSec;		// ������;
	waveform.wBitsPerSample = iBitsPerSample;					// �������أ�16bits/��;
	waveform.nChannels = iChannels;								// ������������2����;  
	waveform.nAvgBytesPerSec = m_audioInfo.iAvgBytesPerSec;		// ÿ��������ʣ�����ÿ���ܲɼ������ֽڵ�����;  
	waveform.nBlockAlign = (iChannels * iBitsPerSample) / 8;	// һ����Ĵ�С������bit��bits������������/8;
	waveform.cbSize = 0;										// ��������Ϣ��С, һ��Ϊ0;

	// ���豸;
	MMRESULT iRes = waveInOpen(&hWaveIn, WAVE_MAPPER, &waveform, (DWORD)(WaveInProc), (DWORD)this, CALLBACK_FUNCTION);
	if (iRes != 0)
	{
		printf("open waveIn err!\n");
		exit(0);
	}
	unsigned int iWaveID = -1;
	waveInGetID(hWaveIn, &iWaveID);	// ����ʹ�õ������豸ID��-1ΪĬ��;
	printf("you use waveid: %d \n", iWaveID);

	for (int i = 0; i < AUDIO_BUFF_MAXCOUNT; i++)			// �����ڴ���ʽ;
	{
		wHdr[i].lpData = chBuff[i];
		wHdr[i].dwBufferLength = AUDIO_BUFF_MAXSIZE;
		wHdr[i].dwBytesRecorded = 0;
		wHdr[i].dwUser = i;
		wHdr[i].dwFlags = 0;
		waveInPrepareHeader(hWaveIn, &wHdr[i], sizeof(WAVEHDR));	// ׼���ڴ��¼��;
		waveInAddBuffer(hWaveIn, &wHdr[i], sizeof(WAVEHDR));		// �����ڴ��;
	}

	m_bStop = false;
	waveInStart(hWaveIn);	//��ʼ¼��;

	return 0;
}

int CWAVEncoder::Stop()
{
	// �˴������ͷ�, ȥ�߳̽���ʱ�ͷ�;
	m_bStop = true;

	return 0;
}

DWORD CALLBACK CWAVEncoder::WaveInProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	CWAVEncoder* pThis = reinterpret_cast<CWAVEncoder*>(dwInstance);
	assert(pThis);

	if (uMsg == WIM_DATA)
	{
		WAVEHDR* p = (WAVEHDR*)dwParam1;	// dwParam1ָ��WAVEHDR�ĵ�ַ;
		printf("getdate id: %d size:%d timestemp:%d\n", p->dwUser, p->dwBytesRecorded, clock());
		int iIndex = p->dwUser;
		if (pThis->m_bStop) //0��ʾֹͣ��
		{
			waveInUnprepareHeader(pThis->hWaveIn, p, sizeof(WAVEHDR)); // �ͷ�;
			return 0;
		}
		else
		{
			if (pThis->m_pCallBack)
			{
				pThis->m_pCallBack(pThis->chBuff[iIndex], p->dwBytesRecorded);
			}
			waveInUnprepareHeader(pThis->hWaveIn, p, sizeof(WAVEHDR)); // �ͷ�;
		}
		p->lpData = pThis->chBuff[iIndex];
		p->dwBufferLength = AUDIO_BUFF_MAXSIZE;
		p->dwBytesRecorded = 0;
		p->dwUser = iIndex;
		p->dwFlags = 0;
		waveInPrepareHeader(pThis->hWaveIn, p, sizeof(WAVEHDR));	// ׼���ڴ��¼��;
		waveInAddBuffer(pThis->hWaveIn, p, sizeof(WAVEHDR));		// �����ڴ��;
	}
	if (uMsg == WIM_OPEN)
	{
		printf("open\n");
	}
	if (uMsg == WIM_CLOSE)
	{
		printf("close\n");
	}
	return 0;
}

int CWAVEncoder::Clear()
{
	printf("Start Stop\n");
	waveInStop(hWaveIn);
	printf("Start Reset\n");
	waveInReset(hWaveIn);
	printf("Start Close\n");
	waveInClose(hWaveIn);

	return 1;
}