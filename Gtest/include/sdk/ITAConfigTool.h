#ifndef ITA_ITA_CONFIG_TOOL_H
#define ITA_ITA_CONFIG_TOOL_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "ERROR.h"
#include "ITADTD.h"

typedef struct ITA_CONFIG_BUFFER{
    
    const char *data;  // ITA 配置文件导出的文件数据, 内存由ITA申请/释放
    int         len;   // buf的长度
} ITAConfigBuffer;

//拟合信息
typedef struct ITA_PACKAGE_PARAM
{
	float iBlackBodyTemp[15];//黑体温度点
	int AllY16[200];       //采集全部焦温的Y16
	int Y16[15];          //采集单条焦温的Y16
	unsigned char iSampleNumber;//拟合样本点数
	float FocusArray[10];        //焦温数组
	short sDistanceArray[5];        //距离数组
	unsigned char FocusNumber;   //焦温个数
	unsigned char mtType;    //测温类型
	unsigned char fieldType;  //镜头类型
	short iMinTemp;//最低可测量温度
	short iMaxTemp;//最高可测量温度
	unsigned short iCurveLength;          //单条曲线长度
	unsigned short width;                 //图像宽
	unsigned short height;                //图像高
	char cDate[10];                    //采集日期
	char cTime[10];                      //采集时间
	char cModuleMtMark[60];               //产品名称
	char cModuleCode[24];                 //设备SN号
	char cLiaoHao[12];                    //采集方案
	unsigned char cSheBeiBianHao;         //采集设备编号
	unsigned char cZhiJuHao;             //治具号
	float fCorrectionDistance;              //校温距离
	char cSoftVersion[10] = {};            //软件版本号
	char fCorrectError[9] = {};            //校验误差
	unsigned short usMTPointX;            //采集坐标点X
	unsigned short usMTPointY;             //采集坐标点Y
}ITAPackageParam;

/**
* @brief: 配置文件导入导出模块初始化
* @return: 返回值：成功，返回实例指针，失败返回NULL(0)
*/
ITA_API HANDLE_T ITA_ConfigToolInit();

/**
* @brief:  释放配置文件导入导出模块实例资源
* @param: HANDLE_T instance [in] 配置文件导入导出模块实例
* @return: 无
*/
ITA_API void ITA_ConfigToolUninit(HANDLE_T instance);

/**
* @brief: 配置文件导出
* @param: HANDLE_T instance   [in]       ITA配置文件实例
* @param: ITAConfig *config   [int]      ITAConfig结构体,内部的配置数据由用户填充
* @param: ITAConfigBuffer buffer [out]   通过config生成的配置文件数据(已加密),内部的buf指向的内存由ITA申请/释放,在调用时会释放上一次分配的内存
* @return: 返回值类型：ITA_RESULT。成功，返回ITA_OK；失败，返回值<0，参考ERROR.h。
*/
ITA_API ITA_RESULT ITA_ConfigToolExport(HANDLE_T instance, const ITAConfig *config, ITAConfigBuffer *buffer);

/**
* @brief: 配置文件导入
* @param: HANDLE_T instance   [in]       ITA配置文件实例
* @param: const char *confStr [in]       配置文件字符串内容
* @param: int len             [in]       配置文件字符串内容长度
* @param: ITAConfig *config   [out]      ITAConfig结构体, 内部指针指向的内存由ITA申请/释放,在调用时会释放上一次分配的内存
* @return: 返回值类型：ITA_RESULT。成功，返回ITA_OK；失败，返回值<0，参考ERROR.h。
*/
ITA_API ITA_RESULT ITA_ConfigToolImport(HANDLE_T instance, const char* confStr, int len, ITAConfig *config);

/**
* @brief: 测温参数包生成
* @param: HANDLE_T instance		[in]       ITA配置文件实例
* @param: ITAPackageParam param [in]       测温参数包需要的结构体参数
* @param: char* packageName		[in]       测温参数包的文件路径，例如/home/app/lowPackage.raw。长度不要超过128。参数类型：字符串，以 \0 结束。
* @return: 返回值类型：ITA_RESULT。成功，返回ITA_OK；失败，返回值<0，参考ERROR.h。
*/
ITA_API ITA_RESULT ITA_GenerateTempPackage(HANDLE_T instance, ITAPackageParam param,char* packageName);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ITA_ITA_CONFIG_TOOL_H
