#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include "SgpApi.h"
#include "SgpParam.h"
using namespace std;

static void GetTempNotify(SGP_TEMPALARMNOTIFY notify, void* pUser)
{
    cout << "时间：" << notify.time <<"  最高温：" << notify.high_temp<<
    "  平均温：" << notify.avg_temp <<"  最低温：" << notify.low_temp << endl;
    cout << "报警截图地址：" << notify.ir_image_url << endl;
    cout << "报警视频地址：" << notify.ir_video_url << endl;
    cout << "名称：" << notify.name << endl;
    if (notify.temp_flag == 0) { cout << "报警类型：平均温报警！" << endl; }
    if (notify.temp_flag == 1) { cout << "报警类型：高温报警！" << endl; }
    if (notify.temp_flag == 2) { cout << "报警类型：低温报警！" << endl; }
    if (notify.temp_flag == 3) { cout << "报警类型：高低温报警！" << endl; }
    if (notify.type == 1) { cout << "温度报警！" << endl; }
    if (notify.type == 2) { cout << "热点报警！" << endl; }
    if (notify.type == 3) { cout << "冷点报警！" << endl; }
    cout << notify.name << endl;
    cout << endl;
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

    const char* server = "192.168.21.4";
    const char* username = "root";
    const char* password = "guide123";
    int port = 80;

    int ret1 = SGP_Login(handle, server, username, password, port);
    if (ret1 == SGP_OK)
    {
        cout << "登陆成功！" << endl;


        
        SGP_RegisterTempAlarmCallback(handle, GetTempNotify, 0);
        Sleep(30000000);


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






















