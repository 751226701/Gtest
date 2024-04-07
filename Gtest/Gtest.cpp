#include "COMMON.h"

//连续获取热图间隔时间
void getHeatMapIntervalTime(SGP_HANDLE handle) {
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
}
//单帧温度矩阵成像
void matrixToImage(SGP_HANDLE handle) {
    SGP_GENERAL_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetGeneralInfo(handle, &info);
    if (ret == SGP_OK)
    {
        int height = info.ir_model_h;
        int width = info.ir_model_w;
        int length = height * width;
        int type = 1;
        float* output = (float*)calloc(length, sizeof(float));
        if (output != NULL)
        {
            ret = SGP_GetImageTemps(handle, output, length * 4, type);
            if (ret != SGP_OK)
            {
                return;
            }

            float* matrix = (float*)malloc(640 * 512 * sizeof(float));
            memcpy(matrix, output, length * sizeof(float));
            getMaxMinTemp(matrix);

            while (true) {
                matrixToVideo(matrix, output);
                if (GetAsyncKeyState(VK_UP) & 0x8000) {
                    gloableY -= 1;
                }
                if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                    gloableY += 1;
                }
                if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                    gloableX -= 1;
                }
                if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                    gloableX += 1;
                }
                if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                    break;
                }
                Sleep(200);
            }
            free(output);
            output = NULL;
        }
        free(output);
        output = NULL;
    }
}

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
        
        
        matrixToImage(handle);

        
        
        

        

        








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



