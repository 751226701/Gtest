#pragma once
#include "SDK_TEST.h"

#define WIDTH 640
#define HEIGHT 512

#define DLT_PICTUERE_PATH "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpg"
#define FIR_PICTUERE_PATH "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.fir"


//�����¶Ⱦ���
void saveTempMatrix(ITATempMatrixInfo* tempMatrixInfo);

//��ȡ�¶Ⱦ�������¡�����¡�ƽ����
void getTempMatrixMaxMinTemp(ITATempMatrixInfo* tempMatrixInfo);

//����Y16����
void saveY16Matrix(ITAY16MatrixInfo* y16Info);

//����RGB����
void saveRGBasRaw(const char* filename, unsigned char* rgbData, int dataSize);

//����ɫ��������
void saveColorStripData(const char* filename, unsigned char* colorStripData, int len);

//����JPG��Ƭ
void saveJpgPicture(const char* filename, unsigned char* jpgBuf, int jpgBufLen);

// �� short �������ݸ��Ƶ� unsigned char ���͵��ڴ���
void ConvertShortToUnsignedChar2(const short* srcData, unsigned char* dstData, int height, int width);
void ConvertShortToUnsignedChar1(const short* srcData, unsigned char* dstData, int length);

vector<pair<ITA_PALETTE_TYPE, string>> GenerateColorData();