#include "COMMON.h"

int main()
{
    std::ostream& log = initTee("C:\\Users\\gd09186\\Desktop\\test.log");
    SGP_HANDLE handle = 0;
    handle = SGP_InitDevice(); 
    
    /*char server[16];
    cout << "Please enter the device IP: " << endl;
    scanf("%s", server);
    int n;
    cout << "Please enter the interval time(ms): " << endl;
    cin>>n;*/
    const char* server = "192.168.21.4";
    const char* username = "root";
    const char* password = "guide123";
    int port = 80;
    int ret1 = SGP_Login(handle, server, username, password, port);
    if (ret1 == SGP_OK)
    {
        cout << "登录成功" << endl;
        GetVersionInfo(handle);
        
        std::chrono::steady_clock::time_point last_success_time;

        while (true)
        {
            const char* path = "./testPicture/screenpic.jpg";
            int ret = SGP_GetHeatMap(handle, path);
            if (ret == SGP_OK)
            {
                auto current_time = std::chrono::steady_clock::now();
                std::cout << getTime() << " 获取热图成功" << std::endl;
                std::cout << "距离上一次成功获取热图的时间间隔为：" << getTimeInterval(last_success_time, current_time) << std::endl;
                last_success_time = current_time; 
            }
            else
            {
                std::cout << "返回失败\n" << "ret的返回值为：" << ret << std::endl;
            }
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



