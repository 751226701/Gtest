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

//保存温度矩阵
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
		printf("温度矩阵信息已保存到文件：%s\n", filePath);
	}
	else 
	{
		printf("无法打开文件进行写入操作。\n");
	}
}
//获取温度矩阵最高温、最低温、平均温
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
//保存Y16矩阵
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
		printf("Y16矩阵信息已保存到文件：%s\n", filePath);
	}
	else
	{
		printf("无法打开文件进行写入操作。\n");
	}
}
//保存RGB数据
void saveRGBasRaw(const char* filename, unsigned char* rgbData, int dataSize) 
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);

	if (file.is_open()) 
	{
		file.write(reinterpret_cast<char*>(rgbData), dataSize);
		file.close();
		std::cout << "RGB数据保存成功: " << filename << std::endl;
	}
	else {
		std::cerr << "文件创建失败!" << std::endl;
	}
}
//保存色带条数据
void saveColorStripData(const char* filename, unsigned char* colorStripData, int len)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);

	if (file.is_open())
	{
		file.write(reinterpret_cast<char*>(colorStripData), len);
		file.close();
		std::cout << "色带条数据保存成功: " << filename << std::endl;
	}
	else {
		std::cerr << "文件创建失败!" << std::endl;
	}
}
//保存JPG照片
void saveJpgPicture(const char* filename, unsigned char* jpgBuf, int jpgBufLen)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);

	if (file.is_open())
	{
		file.write(reinterpret_cast<char*>(jpgBuf), jpgBufLen);
		file.close();
		std::cout << "热图保存成功: " << filename << std::endl;
	}
	else {
		std::cerr << "文件创建失败!" << std::endl;
	}
}
// 将 short 类型数据复制到 unsigned char 类型的内存中
void ConvertShortToUnsignedChar2(const short* srcData, unsigned char* dstData, int height, int width) 
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			int offset = (i * width + j) * sizeof(short);
			dstData[offset] = static_cast<unsigned char>(srcData[i * width + j] & 0xFF); // 取 short 数据的低八位
			dstData[offset + 1] = static_cast<unsigned char>((srcData[i * width + j] >> 8) & 0xFF); // 取 short 数据的高八位
		}
	}
}
void ConvertShortToUnsignedChar1(const short* srcData, unsigned char* dstData, int length) 
{
	for (int i = 0; i < length; ++i) {
		int offset = i * sizeof(short);
		dstData[offset] = static_cast<unsigned char>(srcData[i] & 0xFF); // 取 short 数据的低八位
		dstData[offset + 1] = static_cast<unsigned char>((srcData[i] >> 8) & 0xFF); // 取 short 数据的高八位
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
		cout << "获取色带条数据成功！" << endl;
		saveColorStripData("蓝热.raw", colorStripData, len);
	}
	else
	{
		cout << "获取色带条数据失败！result is：" << result << endl;
	}

	

	ITA_HeatmapUninit(instance);
	system("pause");
	return 0;
}

























