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
std::ofstream logFile("C:\\Users\\gd09186\\Desktop\\test.log", std::ios::app);  // 打开文件时使用追加模式
CoutTeeBuffer teeBuffer(std::cout.rdbuf(), logFile.rdbuf());
std::ostream tee(&teeBuffer);

//创建日志记录器
std::ostream& initTee(const std::string& logFilePath) {
    static std::ofstream logFile(logFilePath, std::ios::app); 
    static CoutTeeBuffer teeBuffer(std::cout.rdbuf(), logFile.rdbuf());
    static std::ostream tee(&teeBuffer);
    return tee;
}
//设置测温点坐标点
int setPoint(int x, int y) {
    return x + y * 640;
}
//测试指定点的温度
void testPointTemp(SGP_HANDLE handle)
{
    float standTemp = 250;      //基准温度
    float tempE = 20;           //误差范围  
    int counts = 0;             //异常温度次数
    int rounds = 1;             //测温轮次

    while (1) {
        tee << "第" << rounds << "轮测温" << endl;
        SGP_SHUTTER_ENUM type = SGP_SHUTTER;
        int ret = SGP_DoShutter(handle, type);
        if (ret == SGP_OK)
        {
            tee << "打快门，8S后开始测温！" << endl;
        }
        else
        {
            tee << "返回失败\n" << "ret的返回值为：" << ret << endl;
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
                            tee << fixed << setprecision(1) << "第" << i + 1 << "个点实时温度：" << temp[i] << "   比较标准：" << standTemp
                                << "   差值：" << dif << "   误差范围：" << tempE << "   异常温度次数" << counts << endl;
                        }
                    }
                    else
                    {
                        tee << "获取温度失败！ret is:" << ret << endl;
                    }
                }
                free(temp);
                temp = NULL;
            }
            else
            {
                tee << "设置索引失败！ret is:" << ret << endl;
            }
            free(index);
            index = NULL;
            Sleep(500);
        }
        rounds++;
        tee << endl;
    }
}
//获取设备版本信息
void GetVersionInfo(SGP_HANDLE handle) {
    SGP_VERSION_INFO info1;
    memset(&info1, 0x00, sizeof(info1));
    SGP_GetVersionInfo(handle, &info1);
    cout << "获取的系统信息为：" << endl;
    cout << "设备型号：" << info1.model << endl;
    cout << "系统版本：" << info1.version << endl;
    cout << "序列号：  " << info1.serial << endl;
    cout << "FPGA版本：" << info1.fpga_version << endl;
    cout << "测温版本：" << info1.measure_version << endl;
    cout << "SDK版本： " << info1.sdk_version << endl;
    cout << "****************************************" << endl;
    cout << endl;
}