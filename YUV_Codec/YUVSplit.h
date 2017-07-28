#pragma once
#include <windows.h>
#include "stdio.h"

class YUVSplit
{
public:
	YUVSplit();
	~YUVSplit();

	// �ָ�YUV444�ļ���Y��U��V���ݵ� strFileY�� strFileU�� strFileV�ļ�;
	static int YUV444_Split(const char* strFileYUV, const int iWidth, const int iHeight, const int iFrameNum,
		const char* strFileY, const char* strFileU, const char* strFileV);

	// �ָ�YUV420�ļ���Y��U��V���ݵ� strFileY�� strFileU�� strFileV�ļ�;
	static int YUV420_Split(const char* strFileYUV, const int iWidth, const int iHeight, const int iFrameNum,
		const char* strFileY, const char* strFileU, const char* strFileV);

	// ��YUV420�ļ�������Y���ݼ���;
	static int YUV420_Half(const char* strFileYUV, const int iWidth, const int iHeight, const int iFrameNum, const char* strFileHalf);

	// ��YUV420ͼ����лҴ���(����UV����Ϊ128);
	static int YUV420_Gray(const char* strFileYUV, const int iWidth, const int iHeight, const int iFrameNum, const char* strFileGray);

	// ��YUV420ͼ����б߿�Χ����;
	static int YUV420_Border(const char* strFileYUV, const int iWidth, const int iHeight, const int iFrameNum, 
		const char* strFileBorder, const int iBorder);

	// RGB24->BMP;
	static int RGB24_To_BMP(const char* strFileRGB24, const int iWidth, const int iHeight, const char* strFileBmp);

};