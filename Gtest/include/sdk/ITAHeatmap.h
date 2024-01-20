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

/*  �¶Ⱦ�����Ϣ�ṹ�� */
typedef struct ITA_TEMPMATRIX_INFO
{
	float* tempMatrix;								//�¶Ⱦ�������
	int w;											//��
	int h;											//��
}ITATempMatrixInfo;

/*  Y16������Ϣ�ṹ�� */
typedef struct ITA_Y16MATRIX_INFO
{
	short* y16Matrix;								//y16��������
	int w;											//��
	int h;											//��
}ITAY16MatrixInfo;

typedef enum ITAHeatMapType
{
	ITA_DLT,
	ITA_FIR
}ITA_HEATMAP_TYPE;

typedef struct ITA_HEATMAP_INPUT_INFO {
	int w;
	int h;
	float* tempMatrix;		//�ڴ����û����롣���봫�롣
	int tempMatrixLen;		// w*h*sizeof(float)
	short* y16data;			// �ڴ����û����롣��ѡ���Դ��롣
	int y16dataLen;			// w*h*sizeof(short)
	unsigned char* rgb;		//�ڴ����û����롣���봫�롣
	int rgbLen;				// w*h*3
}ITAHeatMapInputInfo;

typedef struct ITA_HEATMAP_OUTPUT {
	unsigned char* jpgBuf;			//�ڴ���ITA�����ͷš�
	int jpgBufLen;					
}ITAHeatMapOutput;

/**
* @brief: ��ʼ��һ��ITA Heatmap��ͼʵ��
* @return: ����ֵ���ɹ�������ʵ��ָ�룬ʧ�ܷ���NULL(0)
*/
ITA_API HANDLE_T ITA_HeatmapInit();

/**
* @brief:  �ͷ�һ��ITA Heatmap��ͼʵ����Դ
* @param: HANDLE_T instance [in] ITA Heatmap��ͼʵ��
* @return: ��
*/
ITA_API void ITA_HeatmapUninit(HANDLE_T instance);

/**
* @brief:	��ͼ��ȡ�¶Ⱦ�����Ϣ
* @param:	HANDLE_T instance	[in]									ITA������ʵ����
* @param:	char* filename	[in]										��ͼ�ļ�:����·�����ļ�����
* @param:	ITA_HEATMAP_TYPE heatMapType	[in]						��ͼ��ʽ���͡�
* @param:	ITATempMatrixInfo* tempMatrixInfo	[out]					����������¶Ⱦ�����Ϣ��tempMatrix���ڴ���ITA���룬�ͷš�
* @return:	����ֵ���ͣ�ITA_RESULT���ɹ�������ITA_OK��ʧ�ܣ�����ֵ<0���ο�ERROR.h��
**/
ITA_API ITA_RESULT ITA_GetTempMatrixInfo(HANDLE_T instance, char* filename, ITA_HEATMAP_TYPE heatMapType, ITATempMatrixInfo* tempMatrixInfo);


/**
* @brief:	��ͼ��ȡY16������Ϣ
* @param:	HANDLE_T instance	[in]									ITA������ʵ����
* @param:	char* filename	[in]										��ͼ�ļ�:����·�����ļ���
* @param:	ITA_HEATMAP_TYPE heatMapType	[in]						��ͼ��ʽ���͡�
* @param:	ITAY16MatrixInfo* y16Info	[out]							���������Y16������Ϣ��y16Matrix���ڴ���ITA���룬�ͷš�
* @return:	����ֵ���ͣ�ITA_RESULT���ɹ�������ITA_OK��ʧ�ܣ�����ֵ<0���ο�ERROR.h��
**/
ITA_API ITA_RESULT ITA_GetY16MatrixInfo(HANDLE_T instance, char* filename, ITA_HEATMAP_TYPE heatMapType, ITAY16MatrixInfo* y16Info);

/**
* @brief:	�¶Ⱦ�����ת
* @param:	HANDLE_T instance	[in]									ITA������ʵ����
* @param:	ITATempMatrixInfo* tempMatrixInfo	[in]					�¶Ⱦ�����Ϣ��tempMatrix�������ڴ����û�������ͷš�
* @param:	ITA_ROTATE_TYPE rotateType	[in]							��ת���͡�
* @param:	float* dstMatrix	[out]									�����������ת����¶Ⱦ������ݡ��ڴ����û�������ͷš�
* @param:	int* dstW int* dstH		[out]								�����������ת��Ŀ��ߡ�
* @return:	����ֵ���ͣ�ITA_RESULT���ɹ�������ITA_OK��ʧ�ܣ�����ֵ<0���ο�ERROR.h��
**/
ITA_API ITA_RESULT ITA_TempMatrixRotation(HANDLE_T instance, ITATempMatrixInfo* tempMatrixInfo, ITA_ROTATE_TYPE rotateType, float* dstMatrix, int* dstW, int* dstH);

/**
* @brief:	��ͼ�е��¶Ⱦ���ת��ΪRGB����
* @param:	HANDLE_T instance	[in]									ITA������ʵ����
* @param:	ITATempMatrixInfo* tempMatrixInfo	[in]					�¶Ⱦ�����Ϣ��tempMatrix�������ڴ����û�������ͷš�
* @param:	ITA_PALETTE_TYPE paletteIndex	[in]						α����š�
* @param:	unsigned char* rgbData	[out]								���������rgb���ݡ��ڴ����û����롣
* @param:	int len	[in]												�������������rgb���ݵ��ڴ泤�ȡ�
* @return:	����ֵ���ͣ�ITA_RESULT���ɹ�������ITA_OK��ʧ�ܣ�����ֵ<0���ο�ERROR.h��
**/
ITA_API ITA_RESULT ITA_TempMatrix2Rgb(HANDLE_T instance, ITATempMatrixInfo* tempMatrixInfo, ITA_PALETTE_TYPE paletteIndex, unsigned char* rgbData, int len);

/**
* @brief:	��ȡ�¶Ⱦ����е������С�¶�
* @param:	HANDLE_T instance	[in]									ITA������ʵ����
* @param:	ITATempMatrixInfo* tempMatrixInfo	[in]					�¶Ⱦ�����Ϣ��tempMatrix�������ڴ����û�������ͷš�
* @param:	float* maxT	[out]											�������������¶�
* @param:	float* minT	[out]											�����������С�¶�
* @return:	����ֵ���ͣ�ITA_RESULT���ɹ�������ITA_OK��ʧ�ܣ�����ֵ<0���ο�ERROR.h��
**/
ITA_API ITA_RESULT ITA_GetTempMatrixMaxMinT(HANDLE_T instance, ITATempMatrixInfo* tempMatrixInfo, float* maxT, float* minT);

/**
* @brief:	����α�ʺŻ�ȡ��Ӧɫ��������
* @param:	HANDLE_T instance	[in]									ITA������ʵ����
* @param:	ITA_PALETTE_TYPE paletteIndex	[in]						α����š�
* @param:	unsigned char* colorStripData	[out]						���������ɫ�������ݣ��ڴ����û����롣
* @param:	int len	[in]												�������������ɫ�������ݵ��ڴ泤�ȣ�����ɫ������1024�ֽڡ�
* @return:	����ֵ���ͣ�ITA_RESULT���ɹ�������ITA_OK��ʧ�ܣ�����ֵ<0���ο�ERROR.h��
**/
ITA_API	ITA_RESULT ITA_GetColorStripData(HANDLE_T instance, ITA_PALETTE_TYPE paletteIndex, unsigned char* colorStripData, int len);

/**
* @brief:	������ͼ��jpgͼƬ
* @param:	HANDLE_T instance	[in]									ITA������ʵ����
* @param:	ITAHeatMapInfo* info	[in]								�û��������ͼ�ṹ�����ݡ��ڴ����û������ͷš�
* @param:	ITAHeatMapOutput* outputInfo 	[out]						�����������ͼjpg buf������ݡ��ڴ���ITA���롣�û����浽�Զ���λ�á�
* @return:	����ֵ���ͣ�ITA_RESULT���ɹ�������ITA_OK��ʧ�ܣ�����ֵ<0���ο�ERROR.h��
**/
ITA_API ITA_RESULT ITA_GenerateHeapMapJpg(HANDLE_T instance, ITAHeatMapInputInfo* inputInfo, ITAHeatMapOutput* outputInfo);


ITA_HEATMAP_END

#endif // !ITA_HEATMAP_H
