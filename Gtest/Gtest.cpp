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

int main()
{
    SGP_HANDLE handle = 0;
    handle = SGP_InitDevice();   // 初始化成功返回设备对象句柄
    
    /*char server[16];
    cout << "Please enter the device IP: " << endl;
    scanf("%s", server);
    int n;
    cout << "Please enter the interval time(ms): " << endl;
    cin>>n;*/
    const char* server = "192.168.1.151";
    const char* username = "root";
    const char* password = "guide123";
    int port = 80;
    int ret1 = SGP_Login(handle, server, username, password, port);
    if (ret1 == SGP_OK)
    {
        cout << "登录成功" << endl;

        /*SGP_VERSION_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetVersionInfo(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "返回成功，获取的系统信息为：" << endl;
            cout << "设备型号：" << info.model << endl;
            cout << "系统版本：" << info.version << endl;
            cout << "序列号：  " << info.serial << endl;
            cout << "FPGA版本：" << info.fpga_version << endl;
            cout << "测温版本：" << info.measure_version << endl;
            cout << "SDK版本： " << info.sdk_version << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }

        const char* path = "./testPicture/test.jpg";
        ret = SGP_GetHeatMap(handle, path);
        if (ret == SGP_OK)
        {
            cout << "返回成功" << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }
       
        const char* paths = "./testPicture/test.fir";
        ret = SGP_GetFirHeatMap(handle, paths);
        if (ret == SGP_OK)
        {
            cout << "返回成功" << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }*/

        
        SGP_VERSION_INFO info;
        memset(&info, 0x00, sizeof(info));
        SGP_GetVersionInfo(handle, &info);
        cout << "返回成功，获取的系统信息为：" << endl;
        cout << "设备型号：" << info.model << endl;
        cout << "系统版本：" << info.version << endl;
        cout << "序列号：  " << info.serial << endl;
        cout << "FPGA版本：" << info.fpga_version << endl;
        cout << "测温版本：" << info.measure_version << endl;
        cout << "SDK版本： " << info.sdk_version << endl;

        int standTemp = 230;
        int counts = 0;
        
        while (1) {
            const int pointNum = 1;
            int* index = (int*)malloc(pointNum * sizeof(int));
            index[0] = 163840;

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
                            int dif = std::abs(temp[i] - standTemp);
                            if (dif > 30) 
                            {
                                counts++;
                            }
                            tee << getTime() << "  " << fixed << setprecision(1) << temp[i] << "   异常温度次数"
                                << counts << "   比较标准：" << standTemp <<"   差值：" << dif << endl;
                        }
                    }
                    else
                    {
                        cout << "获取温度失败！ret is:" << ret << endl;
                    }
                }
                free(temp);
                temp = NULL;
            }
            else
            {
                cout << "设置索引失败！ret is:" << ret << endl;
            }
            free(index);
            index = NULL;
            Sleep(1000);
        }










        int retqq = SGP_Logout(handle);
        if (retqq == SGP_OK)
        {
            cout << "用户登出成功！" << endl;
        }
        else
        {
            cout << "用户登出失败！" << endl;
        }
        SGP_UnInitDevice(handle);    
    }
    else
    {
        printf("登陆失败%d", ret1);
        SGP_UnInitDevice(handle);
    }
}



