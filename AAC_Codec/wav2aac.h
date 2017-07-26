#include <windows.h>
#include "faac.h"
#include <mbstring.h>
#include <stdio.h>

int wav2aac(char* strWavFile, char* strAACFile)
{
	ULONG nSampleRate = 44100;  // ������
	UINT nChannels = 2;         // ������
	UINT nPCMBitSize = 16;      // ������λ��
	ULONG nInputSamples = 0;
	ULONG nMaxOutputBytes = 0;

	int nRet;
	faacEncHandle hEncoder;
	faacEncConfigurationPtr pConfiguration;

	int nBytesRead;
	int nPCMBufferSize;
	BYTE* pbPCMBuffer;
	BYTE* pbAACBuffer;

	// WAV file for input
	FILE* fpIn = fopen(strWavFile, "rb");
	if (!fpIn)
	{
		printf("open wav file(%s) failed.", strWavFile);
		return 0;
	}
	// AAC file for output
	FILE* fpOut = fopen(strAACFile, "wb");
	if (!fpOut)
	{
		printf("open aac file(%s) failed.", strAACFile);
		return 0;
	}

	// (1) Open FAAC engine
	hEncoder = faacEncOpen(nSampleRate, nChannels, &nInputSamples, &nMaxOutputBytes);
	if (hEncoder == NULL)
	{
		printf("[ERROR] Failed to call faacEncOpen()\n");
		return -1;
	}

	nPCMBufferSize = nInputSamples * nPCMBitSize / 8;
	pbPCMBuffer = new BYTE[nPCMBufferSize];
	pbAACBuffer = new BYTE[nMaxOutputBytes];

	// (2.1) Get current encoding configuration
	pConfiguration = faacEncGetCurrentConfiguration(hEncoder);
	pConfiguration->inputFormat = FAAC_INPUT_16BIT;

	// (2.2) Set encoding configuration
	nRet = faacEncSetConfiguration(hEncoder, pConfiguration);

	for (int i = 0; 1; i++)
	{
		// �����ʵ���ֽ�������󲻻ᳬ��nPCMBufferSize��һ��ֻ�ж����ļ�βʱ�Ų������ֵ
		nBytesRead = fread(pbPCMBuffer, 1, nPCMBufferSize, fpIn);

		// ��������������ʵ�ʶ����ֽ������㣬һ��ֻ�ж����ļ�βʱ�Ų���nPCMBufferSize/(nPCMBitSize/8);
		nInputSamples = nBytesRead / (nPCMBitSize / 8);

		// (3) Encode
		nRet = faacEncEncode(hEncoder, (int*)pbPCMBuffer, nInputSamples, pbAACBuffer, nMaxOutputBytes);

		fwrite(pbAACBuffer, 1, nRet, fpOut);

		printf("%d: faacEncEncode returns %d\n", i, nRet);

		if (nBytesRead <= 0)
		{
			break;
		}
	}

	// (4) Close FAAC engine
	nRet = faacEncClose(hEncoder);

	delete[] pbPCMBuffer;
	delete[] pbAACBuffer;
	fclose(fpIn);
	fclose(fpOut);

	return 1;
}