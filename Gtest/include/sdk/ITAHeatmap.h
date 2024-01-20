/*************************************************************
Copyright (C), 2022--2023, Wuhan Guide Sensmart Tech Co., Ltd
File name   : ITAFireDRC.h
Author      : Guide Sensmart RD. wangyan
Version     : 1.0
Date        : 2023/09/25
Description : ITA SDK interface definition for fire  heat map analysis.
*************************************************************/
#ifndef ITA_HEATMAP_H
#define ITA_HEATMAP_H

#ifdef __cplusplus
#    define ITA_HEATMAP_START  extern "C" {
#    define ITA_HEATMAP_END    };
#else
#    define ITA_HEATMAP_START
#    define ITA_HEATMAP_END
#endif

ITA_HEATMAP_START

#include "ERROR.h"
#include "ITADTD.h"

/*  温度矩阵信息结构体 */
typedef struct ITA_TEMPMATRIX_INFO
{
	float* tempMatrix;								//温度矩阵数据
	int w;											//宽
	int h;											//高
}ITATempMatrixInfo;

/*  Y16矩阵信息结构体 */
typedef struct ITA_Y16MATRIX_INFO
{
	short* y16Matrix;								//y16矩阵数据
	int w;											//宽
	int h;											//高
}ITAY16MatrixInfo;

typedef enum ITAHeatMapType
{
	ITA_DLT,
	ITA_FIR
}ITA_HEATMAP_TYPE;

typedef struct ITA_HEATMAP_INPUT_INFO {
	int w;
	int h;
	float* tempMatrix;		//内存由用户申请。必须传入。
	int tempMatrixLen;		// w*h*sizeof(float)
	short* y16data;			// 内存由用户申请。可选择性传入。
	int y16dataLen;			// w*h*sizeof(short)
	unsigned char* rgb;		//内存由用户申请。必须传入。
	int rgbLen;				// w*h*3
}ITAHeatMapInputInfo;

typedef struct ITA_HEATMAP_OUTPUT {
	unsigned char* jpgBuf;			//内存由ITA申请释放。
	int jpgBufLen;					
}ITAHeatMapOutput;

/**
* @brief: 初始化一个ITA Heatmap热图实例
* @return: 返回值：成功，返回实例指针，失败返回NULL(0)
*/
ITA_API HANDLE_T ITA_HeatmapInit();

/**
* @brief:  释放一个ITA Heatmap热图实例资源
* @param: HANDLE_T instance [in] ITA Heatmap热图实例
* @return: 无
*/
ITA_API void ITA_HeatmapUninit(HANDLE_T instance);

/**
* @brief:	热图获取温度矩阵信息
* @param:	HANDLE_T instance	[in]									ITA工具箱实例。
* @param:	char* filename	[in]										热图文件:包括路径和文件名。
* @param:	ITA_HEATMAP_TYPE heatMapType	[in]						热图格式类型。
* @param:	ITATempMatrixInfo* tempMatrixInfo	[out]					输出参数：温度矩阵信息，tempMatrix的内存由ITA申请，释放。
* @return:	返回值类型：ITA_RESULT。成功，返回ITA_OK；失败，返回值<0，参考ERROR.h。
**/
ITA_API ITA_RESULT ITA_GetTempMatrixInfo(HANDLE_T instance, char* filename, ITA_HEATMAP_TYPE heatMapType, ITATempMatrixInfo* tempMatrixInfo);


/**
* @brief:	热图获取Y16矩阵信息
* @param:	HANDLE_T instance	[in]									ITA工具箱实例。
* @param:	char* filename	[in]										热图文件:包括路径和文件名
* @param:	ITA_HEATMAP_TYPE heatMapType	[in]						热图格式类型。
* @param:	ITAY16MatrixInfo* y16Info	[out]							输出参数：Y16矩阵信息，y16Matrix的内存由ITA申请，释放。
* @return:	返回值类型：ITA_RESULT。成功，返回ITA_OK；失败，返回值<0，参考ERROR.h。
**/
ITA_API ITA_RESULT ITA_GetY16MatrixInfo(HANDLE_T instance, char* filename, ITA_HEATMAP_TYPE heatMapType, ITAY16MatrixInfo* y16Info);

/**
* @brief:	温度矩阵旋转
* @param:	HANDLE_T instance	[in]									ITA工具箱实例。
* @param:	ITATempMatrixInfo* tempMatrixInfo	[in]					温度矩阵信息，tempMatrix的数据内存由用户申请和释放。
* @param:	ITA_ROTATE_TYPE rotateType	[in]							旋转类型。
* @param:	float* dstMatrix	[out]									输出参数：旋转后的温度矩阵数据。内存由用户申请和释放。
* @param:	int* dstW int* dstH		[out]								输出参数：旋转后的宽，高。
* @return:	返回值类型：ITA_RESULT。成功，返回ITA_OK；失败，返回值<0，参考ERROR.h。
**/
ITA_API ITA_RESULT ITA_TempMatrixRotation(HANDLE_T instance, ITATempMatrixInfo* tempMatrixInfo, ITA_ROTATE_TYPE rotateType, float* dstMatrix, int* dstW, int* dstH);

/**
* @brief:	热图中的温度矩阵转换为RGB数据
* @param:	HANDLE_T instance	[in]									ITA工具箱实例。
* @param:	ITATempMatrixInfo* tempMatrixInfo	[in]					温度矩阵信息，tempMatrix的数据内存由用户申请和释放。
* @param:	ITA_PALETTE_TYPE paletteIndex	[in]						伪彩序号。
* @param:	unsigned char* rgbData	[out]								输出参数：rgb数据。内存由用户申请。
* @param:	int len	[in]												输入参数：申请rgb数据的内存长度。
* @return:	返回值类型：ITA_RESULT。成功，返回ITA_OK；失败，返回值<0，参考ERROR.h。
**/
ITA_API ITA_RESULT ITA_TempMatrix2Rgb(HANDLE_T instance, ITATempMatrixInfo* tempMatrixInfo, ITA_PALETTE_TYPE paletteIndex, unsigned char* rgbData, int len);

/**
* @brief:	获取温度矩阵中的最大最小温度
* @param:	HANDLE_T instance	[in]									ITA工具箱实例。
* @param:	ITATempMatrixInfo* tempMatrixInfo	[in]					温度矩阵信息，tempMatrix的数据内存由用户申请和释放。
* @param:	float* maxT	[out]											输出参数：最大温度
* @param:	float* minT	[out]											输出参数：最小温度
* @return:	返回值类型：ITA_RESULT。成功，返回ITA_OK；失败，返回值<0，参考ERROR.h。
**/
ITA_API ITA_RESULT ITA_GetTempMatrixMaxMinT(HANDLE_T instance, ITATempMatrixInfo* tempMatrixInfo, float* maxT, float* minT);

/**
* @brief:	根据伪彩号获取相应色带条数据
* @param:	HANDLE_T instance	[in]									ITA工具箱实例。
* @param:	ITA_PALETTE_TYPE paletteIndex	[in]						伪彩序号。
* @param:	unsigned char* colorStripData	[out]						输出参数：色带条数据，内存由用户申请。
* @param:	int len	[in]												输入参数：申请色带条数据的内存长度，单条色带长度1024字节。
* @return:	返回值类型：ITA_RESULT。成功，返回ITA_OK；失败，返回值<0，参考ERROR.h。
**/
ITA_API	ITA_RESULT ITA_GetColorStripData(HANDLE_T instance, ITA_PALETTE_TYPE paletteIndex, unsigned char* colorStripData, int len);

/**
* @brief:	产生热图的jpg图片
* @param:	HANDLE_T instance	[in]									ITA工具箱实例。
* @param:	ITAHeatMapInfo* info	[in]								用户传入的热图结构体数据。内存由用户申请释放。
* @param:	ITAHeatMapOutput* outputInfo 	[out]						输出参数：热图jpg buf输出数据。内存由ITA申请。用户保存到自定义位置。
* @return:	返回值类型：ITA_RESULT。成功，返回ITA_OK；失败，返回值<0，参考ERROR.h。
**/
ITA_API ITA_RESULT ITA_GenerateHeapMapJpg(HANDLE_T instance, ITAHeatMapInputInfo* inputInfo, ITAHeatMapOutput* outputInfo);


ITA_HEATMAP_END

#endif // !ITA_HEATMAP_H
