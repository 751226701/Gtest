#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include "SgpApi.h"
#include "SgpParam.h"
using namespace std;

SGP_HANDLE handle = 0;

static void GetFocusResult(int result, void* pUser)
{
    //printf("时间%s 调焦结果是%d\n", dt::currentSystemTimeStr().c_str(),result);
    printf("Focus result is %d\n", result);
}
static void NetworkError(SGP_NETWORKERRORNOTIFY notify, void* pUser)

{
    printf("类型是%d\n", notify.type);
    printf("IP是%s\n", notify.ip);
    cout << "网络异常，再次聚焦！" << endl;
    Sleep(2000);
    SGP_FOCUS_TYPE type = SGP_FOCUS_AUTO;
    int value = 0;
    int ret = SGP_SetFocus(handle, type, value);
    if (ret == SGP_OK)
    {
        cout << "调焦成功" << endl;
    }
    else
    {
        cout << "调焦失败" << endl;
        cout << "ret is" << ret << endl;
    }
    cout << endl;
}

int main()
{
    handle = SGP_InitDevice();   // 初始化成功返回设备对象句柄
    /*if (handle != 0)
    {
        cout << "初始化成功" << endl;
    }
    else
    {
        cout << "初始化失败" << endl;
    }*/
    //cout << handle << endl;

    const char* server = "192.168.21.4";
    const char* username = "root";
    const char* password = "guide123";
    int port = 80;

    int ret1 = SGP_Login(handle, server, username, password, port);
    if (ret1 == SGP_OK)
    {
        cout << "登陆成功！" << endl;

        
        SGP_RegisterNetworkErrorCallback(handle, NetworkError, 0);
        SGP_RegisterAutoFocusCallback(handle, GetFocusResult, 0);
        Sleep(3000000);




        int rets = SGP_Logout(handle);
        if (rets == SGP_OK)
        {
            cout << "用户登出成功！" << endl;
        }
        else
        {
            cout << "用户登出失败！" << endl;
        }
        SGP_UnInitDevice(handle);
        //cout << handle << endl;           

    }

    else
    {
        printf("登陆失败");
        SGP_UnInitDevice(handle);
    }


}
