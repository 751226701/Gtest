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
    //printf("ʱ��%s ���������%d\n", dt::currentSystemTimeStr().c_str(),result);
    printf("Focus result is %d\n", result);
}
static void NetworkError(SGP_NETWORKERRORNOTIFY notify, void* pUser)

{
    printf("������%d\n", notify.type);
    printf("IP��%s\n", notify.ip);
    cout << "�����쳣���ٴξ۽���" << endl;
    Sleep(2000);
    SGP_FOCUS_TYPE type = SGP_FOCUS_AUTO;
    int value = 0;
    int ret = SGP_SetFocus(handle, type, value);
    if (ret == SGP_OK)
    {
        cout << "�����ɹ�" << endl;
    }
    else
    {
        cout << "����ʧ��" << endl;
        cout << "ret is" << ret << endl;
    }
    cout << endl;
}

int main()
{
    handle = SGP_InitDevice();   // ��ʼ���ɹ������豸������
    /*if (handle != 0)
    {
        cout << "��ʼ���ɹ�" << endl;
    }
    else
    {
        cout << "��ʼ��ʧ��" << endl;
    }*/
    //cout << handle << endl;

    const char* server = "192.168.21.4";
    const char* username = "root";
    const char* password = "guide123";
    int port = 80;

    int ret1 = SGP_Login(handle, server, username, password, port);
    if (ret1 == SGP_OK)
    {
        cout << "��½�ɹ���" << endl;

        
        SGP_RegisterNetworkErrorCallback(handle, NetworkError, 0);
        SGP_RegisterAutoFocusCallback(handle, GetFocusResult, 0);
        Sleep(3000000);




        int rets = SGP_Logout(handle);
        if (rets == SGP_OK)
        {
            cout << "�û��ǳ��ɹ���" << endl;
        }
        else
        {
            cout << "�û��ǳ�ʧ�ܣ�" << endl;
        }
        SGP_UnInitDevice(handle);
        //cout << handle << endl;           

    }

    else
    {
        printf("��½ʧ��");
        SGP_UnInitDevice(handle);
    }


}
