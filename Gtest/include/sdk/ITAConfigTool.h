#ifndef ITA_ITA_CONFIG_TOOL_H
#define ITA_ITA_CONFIG_TOOL_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "ERROR.h"
#include "ITADTD.h"

typedef struct ITA_CONFIG_BUFFER{
    
    const char *data;  // ITA �����ļ��������ļ�����, �ڴ���ITA����/�ͷ�
    int         len;   // buf�ĳ���
} ITAConfigBuffer;

//�����Ϣ
typedef struct ITA_PACKAGE_PARAM
{
	float iBlackBodyTemp[15];//�����¶ȵ�
	int AllY16[200];       //�ɼ�ȫ�����µ�Y16
	int Y16[15];          //�ɼ��������µ�Y16
	unsigned char iSampleNumber;//�����������
	float FocusArray[10];        //��������
	short sDistanceArray[5];        //��������
	unsigned char FocusNumber;   //���¸���
	unsigned char mtType;    //��������
	unsigned char fieldType;  //��ͷ����
	short iMinTemp;//��Ϳɲ����¶�
	short iMaxTemp;//��߿ɲ����¶�
	unsigned short iCurveLength;          //�������߳���
	unsigned short width;                 //ͼ���
	unsigned short height;                //ͼ���
	char cDate[10];                    //�ɼ�����
	char cTime[10];                      //�ɼ�ʱ��
	char cModuleMtMark[60];               //��Ʒ����
	char cModuleCode[24];                 //�豸SN��
	char cLiaoHao[12];                    //�ɼ�����
	unsigned char cSheBeiBianHao;         //�ɼ��豸���
	unsigned char cZhiJuHao;             //�ξߺ�
	float fCorrectionDistance;              //У�¾���
	char cSoftVersion[10] = {};            //����汾��
	char fCorrectError[9] = {};            //У�����
	unsigned short usMTPointX;            //�ɼ������X
	unsigned short usMTPointY;             //�ɼ������Y
}ITAPackageParam;

/**
* @brief: �����ļ����뵼��ģ���ʼ��
* @return: ����ֵ���ɹ�������ʵ��ָ�룬ʧ�ܷ���NULL(0)
*/
ITA_API HANDLE_T ITA_ConfigToolInit();

/**
* @brief:  �ͷ������ļ����뵼��ģ��ʵ����Դ
* @param: HANDLE_T instance [in] �����ļ����뵼��ģ��ʵ��
* @return: ��
*/
ITA_API void ITA_ConfigToolUninit(HANDLE_T instance);

/**
* @brief: �����ļ�����
* @param: HANDLE_T instance   [in]       ITA�����ļ�ʵ��
* @param: ITAConfig *config   [int]      ITAConfig�ṹ��,�ڲ��������������û����
* @param: ITAConfigBuffer buffer [out]   ͨ��config���ɵ������ļ�����(�Ѽ���),�ڲ���bufָ����ڴ���ITA����/�ͷ�,�ڵ���ʱ���ͷ���һ�η�����ڴ�
* @return: ����ֵ���ͣ�ITA_RESULT���ɹ�������ITA_OK��ʧ�ܣ�����ֵ<0���ο�ERROR.h��
*/
ITA_API ITA_RESULT ITA_ConfigToolExport(HANDLE_T instance, const ITAConfig *config, ITAConfigBuffer *buffer);

/**
* @brief: �����ļ�����
* @param: HANDLE_T instance   [in]       ITA�����ļ�ʵ��
* @param: const char *confStr [in]       �����ļ��ַ�������
* @param: int len             [in]       �����ļ��ַ������ݳ���
* @param: ITAConfig *config   [out]      ITAConfig�ṹ��, �ڲ�ָ��ָ����ڴ���ITA����/�ͷ�,�ڵ���ʱ���ͷ���һ�η�����ڴ�
* @return: ����ֵ���ͣ�ITA_RESULT���ɹ�������ITA_OK��ʧ�ܣ�����ֵ<0���ο�ERROR.h��
*/
ITA_API ITA_RESULT ITA_ConfigToolImport(HANDLE_T instance, const char* confStr, int len, ITAConfig *config);

/**
* @brief: ���²���������
* @param: HANDLE_T instance		[in]       ITA�����ļ�ʵ��
* @param: ITAPackageParam param [in]       ���²�������Ҫ�Ľṹ�����
* @param: char* packageName		[in]       ���²��������ļ�·��������/home/app/lowPackage.raw�����Ȳ�Ҫ����128���������ͣ��ַ������� \0 ������
* @return: ����ֵ���ͣ�ITA_RESULT���ɹ�������ITA_OK��ʧ�ܣ�����ֵ<0���ο�ERROR.h��
*/
ITA_API ITA_RESULT ITA_GenerateTempPackage(HANDLE_T instance, ITAPackageParam param,char* packageName);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ITA_ITA_CONFIG_TOOL_H
