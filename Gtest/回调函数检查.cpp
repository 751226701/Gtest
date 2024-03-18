#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include "SgpApi.h"
#include  "SgpParam.h"
using namespace std;

static void GetIrRtsp(unsigned char* outdata, int w, int h, void* pUser)
{
    //printf("outdata is %s\n", outdata);
    printf("w is %d, h is %d\n", w, h);
    cout << pUser << endl;
    Sleep(2000);
}
static void GetRecordStatus(int state, void* pUser)
{
    //printf("Current record status is %d\n", state);
    //Sleep(2000);
}
static void GetAccessNotify(SGP_ACCESSVIOLATIONNOTIFY notify, void* pUser)
{
    printf("�쳣��¼�û�����%s\n", notify.user);
    printf("�쳣��¼IP��%s\n", notify.ip);
    printf("�쳣��¼ʱ����%s\n", notify.time);
}
static void MemoryFull(SGP_MEMORYFULLNOTIFY notify, void* pUser)

{
    printf("�ܴ洢��%dG\n", notify.total);
    printf("���ô�С%dM\n", notify.free);
    printf("������ֵ%dM\n", notify.limit);
}
static void NetworkError(SGP_NETWORKERRORNOTIFY notify, void* pUser)

{
    //std::string ip(notify.ip);
    cout << "���ͣ�" << notify.type << endl;
    cout << "ip:" << notify.ip << endl;
}
static void GetTempNotify(SGP_TEMPALARMNOTIFY notify, void* pUser)
{
    cout << "ʱ�䣺" << notify.time << "  ����£�" << notify.high_temp <<
        "  ƽ���£�" << notify.avg_temp << "  ����£�" << notify.low_temp << endl;
    cout << "������ͼ��ַ��" << notify.ir_image_url << endl;
    cout << "������Ƶ��ַ��" << notify.ir_video_url << endl;
    cout << "���ƣ�" << notify.name << endl;
    if (notify.temp_flag == 0) { cout << "�������ͣ�ƽ���±�����" << endl; }
    if (notify.temp_flag == 1) { cout << "�������ͣ����±�����" << endl; }
    if (notify.temp_flag == 2) { cout << "�������ͣ����±�����" << endl; }
    if (notify.temp_flag == 3) { cout << "�������ͣ��ߵ��±�����" << endl; }
    if (notify.temp_flag == 5) { cout << "�������ͣ�����������" << endl; }
    if (notify.temp_flag == 6) { cout << "�������ͣ��²����" << endl; }
    if (notify.type == 1) { cout << "�¶ȱ�����" << endl; }
    if (notify.type == 2) { cout << "�ȵ㱨����" << endl; }
    if (notify.type == 3) { cout << "��㱨����" << endl; }
    cout << notify.name << endl;
    cout << endl;
    notify.config.type = 3;
    notify.config.condition = 1;
    notify.config.avg_temp = 33;
    notify.config.high_temp = 33;
    notify.config.low_temp = 33;
    notify.config.objtype = 2;
    notify.config.points[0].x = 1;
    notify.config.points[0].y = 1;
    notify.config.points[1].x = 100;
    notify.config.points[1].y = 100;
}
static void GetFocusResult(int result, void* pUser)
{
    printf("Focus result is %d\n", result);
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

    const char* server = "192.168.21.143";
    const char* username = "root";
    const char* password = "guide123";
    int port = 80;

    int ret1 = SGP_Login(handle, server, username, password, port);
    if (ret1 == SGP_OK)
    {
        cout << "��½�ɹ���" << endl;

        //��Ƶ�ص�
        for (int i = 1; i <= 1; i++)
        {
            int result = SGP_OpenIrVideo(handle, GetIrRtsp, 0);
            printf("��%d��SGP_OpenIrVideo�ӿڷ���ֵ��%d\n", i, result);
            Sleep(5000);
            std::string IRFile = "1234.mp4";
            int startResult = SGP_StartRecord(handle, SGP_IR_VIDEO, IRFile.c_str(), GetRecordStatus, 0);
            printf("SGP_StartRecord�ӿں��ⷵ��ֵ��%d\n", startResult);
            Sleep(30000);
            SGP_StopRecord(handle, SGP_IR_VIDEO);
            //�ر���Ƶ��
            SGP_CloseIrVideo(handle);
        }

        //�Ƿ����ʻص�
        SGP_RegisterAccessViolationCallback(handle, GetAccessNotify, 0);

        //�ڴ������ص�
        SGP_RegisterMemoryFullCallback(handle, MemoryFull, 0);

        //�����쳣�ص�
        SGP_RegisterNetworkErrorCallback(handle, NetworkError, 0);

        //�¶ȸ澯�ص�
        SGP_RegisterTempAlarmCallback(handle, GetTempNotify, 0);

        //�Զ������ص�
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






















