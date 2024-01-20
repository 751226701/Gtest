#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <io.h>
#include <thread>
#include <direct.h>
#include "SgpApi.h"
#include "SgpParam.h"
using namespace std;

int i = 1;
SGP_HANDLE handle = 0;
int value = 0;
SGP_FOCUS_TYPE type = SGP_FOCUS_PLACE;

long long lastCallbackTime = 0;
const long long TIMEOUT_THRESHOLD = 10000;

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
static void GetFocusResult(int result, void* pUser)
{  
    long long currentTime = GetTickCount64();
    cout << "第" << i << "次聚焦" << endl;       
    printf("Focus result is %d\n", result);
    lastCallbackTime = currentTime;

    if (result == 1)
    {
        string heatmap, firmap;
        string prefix = "D:/Testpicture";  //判断文件夹是否存在，不存在则创建
        if (_access(prefix.c_str(), 0) == -1)
            _mkdir(prefix.c_str());

        /*Sleep(2000);*/
        /*heatmap = "D:/Testpicture/heatmap_" + std::to_string(i) + ".jpg";
        int rets = SGP_GetHeatMap(handle, heatmap.c_str());
        if (rets == SGP_OK)
        {
            cout << "获取热图成功" << endl;
        }
        else
        {
            cout << "获取热图失败" << endl;
        }*/

        i++;

        SGP_FOCUS_TYPE type = SGP_FOCUS_AUTO;
        int value = 0;
        int retf = SGP_SetFocus(handle, type, value);
        if (retf == SGP_OK)
        {
            cout << "调焦成功" << endl;
        }
        else
        {
            cout << "调焦失败" << endl;
            cout << "retf is" << retf << endl;
        }

              
        cout << endl;
    }

     
    else if (result == 2)
    {
        /*Sleep(6000);
        string heatmap, firmap;
        heatmap = "D:/Testpicture/heatmap_" + std::to_string(i) + ".jpg";
        int rets = SGP_GetHeatMap(handle, heatmap.c_str());
        if (rets == SGP_OK)
        {
            cout << "获取热图成功" << endl;
        }
        else
        {
            cout << "获取热图失败" << endl;
        }*/
      
        i++;


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
}
void threadfun()
{
    SGP_RegisterNetworkErrorCallback(handle, NetworkError, 0);
    SGP_RegisterAutoFocusCallback(handle, GetFocusResult, 0);
    Sleep(999999999999);
}

int main()
{  
    handle = SGP_InitDevice();   // 初始化成功返回设备对象句柄  

    char server[16];
    cout << "Please enter the device IP: " << endl;
    scanf("%s", server);
   /* int n = 0;
    cout << "Please enter the interval time:" << endl;
    cin >> n;*/

    //const char* server = "192.168.21.150";
    const char* username = "root";
    const char* password = "guide123";
    int port = 80;

    int ret1 = SGP_Login(handle, server, username, password, port);
    if (ret1 == SGP_OK)
    {
        cout << "登陆成功！" << endl;
                    
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
        }

        

        /*SGP_RegisterNetworkErrorCallback(handle, NetworkError, 0);
        SGP_RegisterAutoFocusCallback(handle, GetFocusResult, 0);
        Sleep(999999999999);*/

        thread mythread(threadfun);
        mythread.detach(); 
        Sleep(5000);
        while (true)
        {         
            while ((GetTickCount64() - lastCallbackTime) > TIMEOUT_THRESHOLD)
            {
                cout << "已超时，重新聚焦" << endl;
                int r= SGP_SetFocus(handle, type, value);
                if (r == SGP_OK)
                {
                    cout << "重新聚焦成功！" << endl;
                }
                else
                {
                    cout << "重新聚焦失败！" << endl;
                }
                Sleep(3000);
            }                  
        }
        
       
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
    }
    else
    {
        printf("登陆失败");
        SGP_UnInitDevice(handle);
    }

    system("pause");
    return 0;
}


