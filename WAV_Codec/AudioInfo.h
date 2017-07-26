#pragma once
#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

#pragma comment(lib, "winmm.lib")

#define AUDIO_AVGBYTESPERSEC		176400
#define AUDIO_SAMPLESPERSEC			44100
#define AUDIO_CHANNELS				2
#define AUDIO_BITSPERSAMPLE			16

#define  AUDIO_BUFF_MAXCOUNT		3			// 3��������;
#define  AUDIO_BUFF_MAXSIZE			176400		// ÿ�������������¼������(���ֵ);

class AudioInfo
{
public:
	AudioInfo()
	{
		iAvgBytesPerSec = AUDIO_AVGBYTESPERSEC;
		iChannels = AUDIO_CHANNELS;
		iBitsPerSample = AUDIO_BITSPERSAMPLE;
		iSamplesPerSec = AUDIO_SAMPLESPERSEC;
	}

	int		iAvgBytesPerSec;	// ����;
	int		iChannels;			// ͨ����;
	int		iBitsPerSample;		// ����λ��;
	int		iSamplesPerSec;		// ����Ƶ��;
};