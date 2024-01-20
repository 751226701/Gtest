#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include "include/sdk/ITAHeatmap.h"
#include "include/sdk/ITA.h"
#include "include/sdk/ERROR.h"
#include "include/sdk/ITAToolBox.h"
#include "include/sdk/ITAConfigTool.h"
#include <string>
#include "SgpApi.h"
#include "SgpParam.h"
using namespace std;

//�����¶Ⱦ���
void saveTempMatrix(ITATempMatrixInfo* tempMatrixInfo) 
{
	char filePath[] = "temp_matrix.txt"; 

	FILE* file = fopen(filePath, "w"); 
	if (file != NULL) 
	{
		for (int i = 0; i < 640*512; ++i) 
		{
				fprintf(file, "%.2f ", tempMatrixInfo->tempMatrix[i]);
		}

		fclose(file); 
		printf("�¶Ⱦ�����Ϣ�ѱ��浽�ļ���%s\n", filePath);
	}
	else 
	{
		printf("�޷����ļ�����д�������\n");
	}
}
//��ȡ�¶Ⱦ�������¡�����¡�ƽ����
void getTempMatrixMaxMinTemp(ITATempMatrixInfo* tempMatrixInfo)
{
	float max = tempMatrixInfo->tempMatrix[0], min = tempMatrixInfo->tempMatrix[0], avg = 0, sum = 0;
	for (int i = 0; i < 640 * 512; i++)
	{
		if (tempMatrixInfo->tempMatrix[i] >= max)
		{
			max = tempMatrixInfo->tempMatrix[i];
		}

		if (min >= tempMatrixInfo->tempMatrix[i])
		{
			min = tempMatrixInfo->tempMatrix[i];
		}
		sum += tempMatrixInfo->tempMatrix[i];
	}
	avg = sum/(640 * 512);
	cout << "MaxTemp: " << fixed << setprecision(1) << max << endl;
	cout << "MinTemp: " << fixed << setprecision(1) << min << endl;
	cout << "AvgTemp: " << fixed << setprecision(1) << avg << endl;
}
//����Y16����
void saveY16Matrix(ITAY16MatrixInfo* y16Info)
{
	char filePath[] = "y16_matrix.txt";

	FILE* file = fopen(filePath, "w");
	if (file != NULL)
	{
		for (int i = 0; i < 640 * 512; ++i)
		{
			fprintf(file, "%hd ", y16Info->y16Matrix[i]);
		}

		fclose(file);
		printf("Y16������Ϣ�ѱ��浽�ļ���%s\n", filePath);
	}
	else
	{
		printf("�޷����ļ�����д�������\n");
	}
}
//����RGB����
void saveRGBasRaw(const char* filename, unsigned char* rgbData, int dataSize) 
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);

	if (file.is_open()) 
	{
		file.write(reinterpret_cast<char*>(rgbData), dataSize);
		file.close();
		std::cout << "RGB���ݱ���ɹ�: " << filename << std::endl;
	}
	else {
		std::cerr << "�ļ�����ʧ��!" << std::endl;
	}
}
//����ɫ��������
void saveColorStripData(const char* filename, unsigned char* colorStripData, int len)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);

	if (file.is_open())
	{
		file.write(reinterpret_cast<char*>(colorStripData), len);
		file.close();
		std::cout << "ɫ�������ݱ���ɹ�: " << filename << std::endl;
	}
	else {
		std::cerr << "�ļ�����ʧ��!" << std::endl;
	}
}
//����JPG��Ƭ
void saveJpgPicture(const char* filename, unsigned char* jpgBuf, int jpgBufLen)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);

	if (file.is_open())
	{
		file.write(reinterpret_cast<char*>(jpgBuf), jpgBufLen);
		file.close();
		std::cout << "��ͼ����ɹ�: " << filename << std::endl;
	}
	else {
		std::cerr << "�ļ�����ʧ��!" << std::endl;
	}
}
// �� short �������ݸ��Ƶ� unsigned char ���͵��ڴ���
void ConvertShortToUnsignedChar2(const short* srcData, unsigned char* dstData, int height, int width) 
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			int offset = (i * width + j) * sizeof(short);
			dstData[offset] = static_cast<unsigned char>(srcData[i * width + j] & 0xFF); // ȡ short ���ݵĵͰ�λ
			dstData[offset + 1] = static_cast<unsigned char>((srcData[i * width + j] >> 8) & 0xFF); // ȡ short ���ݵĸ߰�λ
		}
	}
}
void ConvertShortToUnsignedChar1(const short* srcData, unsigned char* dstData, int length) 
{
	for (int i = 0; i < length; ++i) {
		int offset = i * sizeof(short);
		dstData[offset] = static_cast<unsigned char>(srcData[i] & 0xFF); // ȡ short ���ݵĵͰ�λ
		dstData[offset + 1] = static_cast<unsigned char>((srcData[i] >> 8) & 0xFF); // ȡ short ���ݵĸ߰�λ
	}
}

int main()
{
	
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();

	ITA_PALETTE_TYPE Index = ITA_BLUE_HOT;
	const int len = 1024;
	unsigned char* colorStripData = new unsigned char[len];
	result = ITA_GetColorStripData(instance, Index, colorStripData, len);
	if (result == ITA_OK)
	{
		cout << "��ȡɫ�������ݳɹ���" << endl;
		saveColorStripData("����.raw", colorStripData, len);
	}
	else
	{
		cout << "��ȡɫ��������ʧ�ܣ�result is��" << result << endl;
	}

	

	ITA_HeatmapUninit(instance);
	system("pause");
	return 0;
}

























