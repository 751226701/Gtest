#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <ctime>
#include <Windows.h>
#include "SgpApi.h"
#include "SgpParam.h"
#include "stdio.h"
using namespace std;

SGP_HANDLE handle = 0;
std::mutex mtx;   //互斥锁
std::condition_variable cv;  //条件变量
bool executeBlockA = true;
bool shouldSwitch = false;
int enterCount = 0;

void BlockA()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return shouldSwitch && executeBlockA; });
        std::cout << "低温档！" << std::endl;

        SGP_GENERAL_INFO info;
        memset(&info, 0x00, sizeof(SGP_GENERAL_INFO));
        int ret = SGP_GetGeneralInfo(handle, &info);
        if (ret == SGP_OK)
        {
            int range = info.range_num;
            ret = SGP_SetRange(handle, 0);
        }

        shouldSwitch = false;
        executeBlockA = false;
        cv.notify_one();
    }
}

void BlockB()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return shouldSwitch && !executeBlockA; });
        std::cout << "高温档！" << std::endl;
        
        SGP_GENERAL_INFO info;
        memset(&info, 0x00, sizeof(SGP_GENERAL_INFO));
        int ret = SGP_GetGeneralInfo(handle, &info);
        if (ret == SGP_OK)
        {
            int range = info.range_num;
            ret = SGP_SetRange(handle, 1);
        }

        shouldSwitch = false;
        executeBlockA = true;
        cv.notify_one();
    }
}



int main()
{
    handle = SGP_InitDevice();

    if (handle != 0)
    {
        cout << "初始化成功" << endl;
    }
    else
    {
        cout << "初始化失败" << endl;
    }
    
    cout << "Please enter the device:";
    char server[64];
    scanf("%s", server);
    //const char* server = "192.168.21.153";
    const char* username = "root";
    const char* password = "guide123";
    int port = 80;
    int ret1 = SGP_Login(handle, server, username, password, port);

    if (ret1 == SGP_OK)
    {
        cout << "登陆成功！请按回车键切换测温档位：" << endl;
        bool pause = false;


      
        std::thread threadA(BlockA);
        std::thread threadB(BlockB);
        std::this_thread::sleep_for(std::chrono::seconds(1));


        while (true)
        {
            /*std::cin.get();
            {
                std::lock_guard<std::mutex> lock(mtx);   
                shouldSwitch = true;
                enterCount++;
                cout << "第" << enterCount << "次切档" << endl;
            }
            cv.notify_all();*/

            Sleep(6000);
            std::lock_guard<std::mutex> lock(mtx);
            shouldSwitch = true;
            enterCount++;
            cout << "第" << enterCount << "次切档" << endl;
            cv.notify_all();

        }

        threadA.join();
        threadB.join();
                       
        int retl = SGP_Logout(handle);
        if (retl == SGP_OK)
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

}