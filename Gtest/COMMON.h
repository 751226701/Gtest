#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <chrono>
#include <iomanip>
#include <fstream>
#include "SgpApi.h"
#include "SgpParam.h"
#include "ITAHeatmap.h"
#include "ERROR.h"
#include "ITA.h"
using namespace std;

string getTime()
{
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    return tmp;
}
static void TempCall(short* temp, int w, int h, void* pUser)
{
    cout << *temp << endl;
    cout << w << endl;
    cout << h << endl;
}
class CoutTeeBuffer : public std::streambuf
{
public:
    CoutTeeBuffer(std::streambuf* buffer1, std::streambuf* buffer2) : buffer1(buffer1), buffer2(buffer2) {}

    int overflow(int c) {
        if (c != EOF) {
            if (atLineStart) {
                addTimestamp();
                atLineStart = false;
            }
            if (c == '\n')
                atLineStart = true;

            if (buffer1 != nullptr)
                buffer1->sputc(c);
            if (buffer2 != nullptr)
                buffer2->sputc(c);
        }
        return c;
    }

    void addTimestamp() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        char timestamp[26];
        std::strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S] ", std::localtime(&now_c));
        if (buffer1 != nullptr)
            buffer1->sputn(timestamp, std::strlen(timestamp));
        if (buffer2 != nullptr)
            buffer2->sputn(timestamp, std::strlen(timestamp));
    }

    std::streambuf* buffer1;
    std::streambuf* buffer2;
    bool atLineStart = true;
};
std::ofstream logFile("C:\\Users\\gd09186\\Desktop\\test.log", std::ios::app);  // ���ļ�ʱʹ��׷��ģʽ
CoutTeeBuffer teeBuffer(std::cout.rdbuf(), logFile.rdbuf());
std::ostream tee(&teeBuffer);

//������־��¼��
std::ostream& initTee(const std::string& logFilePath) {
    static std::ofstream logFile(logFilePath, std::ios::app); 
    static CoutTeeBuffer teeBuffer(std::cout.rdbuf(), logFile.rdbuf());
    static std::ostream tee(&teeBuffer);
    return tee;
}
//���ò��µ������
int setPoint(int x, int y) {
    return x + y * 640;
}
//����ָ������¶�
void testPointTemp(SGP_HANDLE handle)
{
    float standTemp = 250;      //��׼�¶�
    float tempE = 20;           //��Χ  
    int counts = 0;             //�쳣�¶ȴ���
    int rounds = 1;             //�����ִ�

    while (1) {
        tee << "��" << rounds << "�ֲ���" << endl;
        SGP_SHUTTER_ENUM type = SGP_SHUTTER;
        int ret = SGP_DoShutter(handle, type);
        if (ret == SGP_OK)
        {
            tee << "����ţ�8S��ʼ���£�" << endl;
        }
        else
        {
            tee << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }

        Sleep(8000);

        for (int i = 0; i < 3; i++)
        {
            const int pointNum = 10;
            int* index = (int*)malloc(pointNum * sizeof(int));
            index[0] = 151371;
            index[1] = 136658;
            index[2] = 140416;
            index[3] = 189050;
            index[4] = 102659;
            index[5] = 210872;
            index[6] = 182810;
            index[7] = 217981;
            index[8] = 231370;
            index[9] = 215302;


            int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
            if (ret == SGP_OK)
            {
                float* temp = (float*)malloc(pointNum * sizeof(float));
                memset(temp, 0x00, pointNum * sizeof(float));
                if (temp != NULL)
                {
                    int ret = SGP_GetTempPoints(handle, temp, pointNum, 1);
                    if (ret == SGP_OK)
                    {
                        for (int i = 0; i < pointNum; i++)
                        {
                            float dif = std::abs(temp[i] - standTemp);
                            if (dif > tempE)
                            {
                                counts++;
                            }
                            tee << fixed << setprecision(1) << "��" << i + 1 << "����ʵʱ�¶ȣ�" << temp[i] << "   �Ƚϱ�׼��" << standTemp
                                << "   ��ֵ��" << dif << "   ��Χ��" << tempE << "   �쳣�¶ȴ���" << counts << endl;
                        }
                    }
                    else
                    {
                        tee << "��ȡ�¶�ʧ�ܣ�ret is:" << ret << endl;
                    }
                }
                free(temp);
                temp = NULL;
            }
            else
            {
                tee << "��������ʧ�ܣ�ret is:" << ret << endl;
            }
            free(index);
            index = NULL;
            Sleep(500);
        }
        rounds++;
        tee << endl;
    }
}
//��ȡ�豸�汾��Ϣ
void GetVersionInfo(SGP_HANDLE handle) {
    SGP_VERSION_INFO info1;
    memset(&info1, 0x00, sizeof(info1));
    SGP_GetVersionInfo(handle, &info1);
    cout << "��ȡ��ϵͳ��ϢΪ��" << endl;
    cout << "�豸�ͺţ�" << info1.model << endl;
    cout << "ϵͳ�汾��" << info1.version << endl;
    cout << "���кţ�  " << info1.serial << endl;
    cout << "FPGA�汾��" << info1.fpga_version << endl;
    cout << "���°汾��" << info1.measure_version << endl;
    cout << "SDK�汾�� " << info1.sdk_version << endl;
    cout << "****************************************" << endl;
    cout << endl;
}