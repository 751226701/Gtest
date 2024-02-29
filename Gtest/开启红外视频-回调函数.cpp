#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include "SgpApi.h"
#include  "SgpParam.h"
using namespace std;

void* pUser = NULL;

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

int main()
{
    SGP_HANDLE handle = 0;
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

    const char* server = "192.168.21.232";
    const char* username = "root";
    const char* password = "guide123";
    int port = 80;
    int ret1 = SGP_Login(handle, server, username, password, port);

    if (ret1 == SGP_OK)
    {
        cout << "登陆成功！" << endl;

        
        for (int i = 1; i <= 1; i++)
        {
            int result = SGP_OpenIrVideo(handle, GetIrRtsp, 0);
            printf("第%d次SGP_OpenIrVideo接口返回值是%d\n", i, result);
            Sleep(5000);
            std::string IRFile = "1234.mp4";
            int startResult = SGP_StartRecord(handle, SGP_IR_VIDEO, IRFile.c_str(), GetRecordStatus, 0);
            printf("SGP_StartRecord接口红外返回值是%d\n", startResult);
            Sleep(30000);
            SGP_StopRecord(handle, SGP_IR_VIDEO);
            //关闭视频流
            SGP_CloseIrVideo(handle);          
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
        //cout << handle << endl;

    }

    else
    {
        printf("登陆失败");
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






















