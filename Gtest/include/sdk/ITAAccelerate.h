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

//图像处理加速类型，支持多种类型组合使用。
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
    ITA_ALGOR_ZOOMY16,      //ZoomY16放大算法
    ITA_ALGOR_SRBICUBIC,    //超分放大算法
}ITA_ALGOR_TYPE;

//红外图像各算法耗时,单位ms
typedef struct ITAAlgorCostTime
{
	float nuc;//NUC校正
	float rpbp;//坏点替换
	float tff;//时域滤波
	float rvs;//去竖纹
	float rhs;//去横纹
	float hsm;//气体检测
	float rn;//空域滤波
	float flip;//翻转
	float rotate;//旋转
	float iie;//细节增强
	float drt;//调光
	float gmc;//Gamma校正
	float sp;//锐化
	float y8adjustbc; //Y8亮度对比度调节
	float zoom_y8;//缩放
	float psdclr;//伪彩
	float total;//单帧图像处理总耗时
}ITA_AlgorCostTime;

typedef struct ITAAlgorCostPara
{
	int startTime;
	int endTime;
}ITA_AlgorCostPara;

/**
* @brief:	获取单帧各个处理算法的耗时与单帧总耗时情况，单位ms。
* @param:	HANDLE_T instance	 			实例句柄。
* @param:	ITA_AlgorCostTime* costTime		获取单帧算法耗时。
**/
ITA_API ITA_RESULT ITA_GetCurrentAlgorCostTime(HANDLE_T instance, ITA_AlgorCostTime* costTime);

/**
* @brief:	设置图像处理加速类型。在ITA_ISP之前调用。用户根据所用平台的特性选择恰当的加速类型。只支持设置一次，不支持动态设置。
* @param:	HANDLE_T instance			                ITA实例。
* @param:	ITA_ACCELERATE_TYPE accelerateType			加速类型
* @return:	返回值类型：ITA_RESULT。成功，返回ITA_OK；失败，返回值<0，参考ERROR.h。
* @note:	在ITA_ISP之前调用。用户根据所用平台的特性选择恰当的加速类型。只支持设置一次，不支持动态设置。
**/
ITA_API ITA_RESULT ITA_Accelerate(HANDLE_T instance, ITA_ACCELERATE_TYPE accelerateType);

/**
* @brief:	设置应用算法加速类型。
* @param:	HANDLE_T instance			ITA实例。
* @param:	ITA_ALGOR_TYPE algorType            应用算法类型。
* @param:	ITA_ACCELERATE_TYPE accelerateType  加速类型。
* @return:	返回值类型：ITA_RESULT。成功，返回ITA_OK；失败，返回值<0，参考ERROR.h。
**/
ITA_API ITA_RESULT ITA_SetAlgorAccelerate(HANDLE_T instance, ITA_ALGOR_TYPE algorType, ITA_ACCELERATE_TYPE accelerateType);

ITA_LIB_END
#endif // !ITA_ALGORCOSTTIME_H