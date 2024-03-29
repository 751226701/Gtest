﻿#include <iostream>
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


static void TempCall(short* temp, int w, int h, void* pUser)
{
    cout << *temp << endl;
    cout << w << endl;
    cout << h << endl;
}

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
    const char* server = "192.168.23.145";
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



