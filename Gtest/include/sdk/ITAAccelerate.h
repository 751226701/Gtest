#ifndef ITA_ALGORCOSTTIME_H
#define ITA_ALGORCOSTTIME_H

#ifdef __cplusplus
#    define ITA_LIB_START  extern "C" {
#    define ITA_LIB_END    };
#else
#    define ITA_LIB_START
#    define ITA_LIB_END
#endif

ITA_LIB_START

#include "ITADTD.h"

//ͼ����������ͣ�֧�ֶ����������ʹ�á�
typedef enum ITAAccelerateType
{
    ITA_ACCELERATE_NONE = 0,
    ITA_ACCELERATE_NEON,
    ITA_ACCELERATE_NEON_AARCH64,
    ITA_ACCELERATE_OPENMP,
    ITA_ACCELERATE_GPU,
}ITA_ACCELERATE_TYPE;

typedef enum ITAlgorType
{
    ITA_ALGOR_ZOOMY16,      //ZoomY16�Ŵ��㷨
    ITA_ALGOR_SRBICUBIC,    //���ַŴ��㷨
}ITA_ALGOR_TYPE;

//����ͼ����㷨��ʱ,��λms
typedef struct ITAAlgorCostTime
{
	float nuc;//NUCУ��
	float rpbp;//�����滻
	float tff;//ʱ���˲�
	float rvs;//ȥ����
	float rhs;//ȥ����
	float hsm;//������
	float rn;//�����˲�
	float flip;//��ת
	float rotate;//��ת
	float iie;//ϸ����ǿ
	float drt;//����
	float gmc;//GammaУ��
	float sp;//��
	float y8adjustbc; //Y8���ȶԱȶȵ���
	float zoom_y8;//����
	float psdclr;//α��
	float total;//��֡ͼ�����ܺ�ʱ
}ITA_AlgorCostTime;

typedef struct ITAAlgorCostPara
{
	int startTime;
	int endTime;
}ITA_AlgorCostPara;

/**
* @brief:	��ȡ��֡���������㷨�ĺ�ʱ�뵥֡�ܺ�ʱ�������λms��
* @param:	HANDLE_T instance	 			ʵ�������
* @param:	ITA_AlgorCostTime* costTime		��ȡ��֡�㷨��ʱ��
**/
ITA_API ITA_RESULT ITA_GetCurrentAlgorCostTime(HANDLE_T instance, ITA_AlgorCostTime* costTime);

/**
* @brief:	����ͼ����������͡���ITA_ISP֮ǰ���á��û���������ƽ̨������ѡ��ǡ���ļ������͡�ֻ֧������һ�Σ���֧�ֶ�̬���á�
* @param:	HANDLE_T instance			                ITAʵ����
* @param:	ITA_ACCELERATE_TYPE accelerateType			��������
* @return:	����ֵ���ͣ�ITA_RESULT���ɹ�������ITA_OK��ʧ�ܣ�����ֵ<0���ο�ERROR.h��
* @note:	��ITA_ISP֮ǰ���á��û���������ƽ̨������ѡ��ǡ���ļ������͡�ֻ֧������һ�Σ���֧�ֶ�̬���á�
**/
ITA_API ITA_RESULT ITA_Accelerate(HANDLE_T instance, ITA_ACCELERATE_TYPE accelerateType);

/**
* @brief:	����Ӧ���㷨�������͡�
* @param:	HANDLE_T instance			ITAʵ����
* @param:	ITA_ALGOR_TYPE algorType            Ӧ���㷨���͡�
* @param:	ITA_ACCELERATE_TYPE accelerateType  �������͡�
* @return:	����ֵ���ͣ�ITA_RESULT���ɹ�������ITA_OK��ʧ�ܣ�����ֵ<0���ο�ERROR.h��
**/
ITA_API ITA_RESULT ITA_SetAlgorAccelerate(HANDLE_T instance, ITA_ALGOR_TYPE algorType, ITA_ACCELERATE_TYPE accelerateType);

ITA_LIB_END
#endif // !ITA_ALGORCOSTTIME_H