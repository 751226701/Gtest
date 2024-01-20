#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include "SgpApi.h"
#include  "SgpParam.h"
using namespace std;

static void MemoryFull(SGP_MEMORYFULLNOTIFY notify, void* pUser)

{    
    printf("�ܴ洢��%dG\n", notify.total);
    printf("���ô�С%dM\n", notify.free);
    printf("������ֵ%dM\n", notify.limit);
}

int main()
{
    SGP_HANDLE handle = 0;
    handle = SGP_InitDevice();   // ��ʼ���ɹ������豸������
    /*if (handle != 0)
    {
        cout << "��ʼ���ɹ�" << endl;
    }
    else
    {
        cout << "��ʼ��ʧ��" << endl;
    }*/

    const char* server = "192.168.21.153";
    const char* username = "root";
    const char* password = "guide123";
    int port = 80;

    int ret1 = SGP_Login(handle, server, username, password, port);
    if (ret1 == SGP_OK)
    {
        cout << "��½�ɹ���" << endl;


        SGP_RegisterMemoryFullCallback(handle, MemoryFull, 0);
        Sleep(30000000);


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


    }

    else
    {
        printf("��½ʧ��");
        SGP_UnInitDevice(handle);
    }


}




































//int Add(int num1, int num2)
//{
//	int sum = num1 + num2;
//	return sum;
//}

//TEST(AddFunc, test_name)
//{
//	int sum = Add(1,2);
//	EXPECT_EQ(3, sum);
//}

//int main(int argc, char* argv[])
//{
//	testing::InitGoogleTest(&argc, argv);
//	//system("pause");
//	return RUN_ALL_TESTS();
//}






















