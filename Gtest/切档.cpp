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
std::mutex mtx;   //������
std::condition_variable cv;  //��������
bool executeBlockA = true;
bool shouldSwitch = false;
int enterCount = 0;

void BlockA()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return shouldSwitch && executeBlockA; });
        std::cout << "���µ���" << std::endl;

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
        std::cout << "���µ���" << std::endl;
        
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
        cout << "��ʼ���ɹ�" << endl;
    }
    else
    {
        cout << "��ʼ��ʧ��" << endl;
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
        cout << "��½�ɹ����밴�س����л����µ�λ��" << endl;
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
                cout << "��" << enterCount << "���е�" << endl;
            }
            cv.notify_all();*/

            Sleep(6000);
            std::lock_guard<std::mutex> lock(mtx);
            shouldSwitch = true;
            enterCount++;
            cout << "��" << enterCount << "���е�" << endl;
            cv.notify_all();

        }

        threadA.join();
        threadB.join();
                       
        int retl = SGP_Logout(handle);
        if (retl == SGP_OK)
        {
            cout << "�û��ǳ��ɹ���" << endl;
        }
        else
        {
            cout << "�û��ǳ�ʧ�ܣ�" << endl;
        }


        SGP_UnInitDevice(handle);
    }

    else
    {
        printf("��½ʧ��");
        SGP_UnInitDevice(handle);
    }

}