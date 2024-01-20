#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <thread>
#include <iomanip>
#include <time.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include "SgpApi.h"
#include "SgpParam.h"
#include "stdio.h"
using namespace std;

SGP_HANDLE handle = 0;
void getTempMatrix(short* y16);
string getTime()
{
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    return tmp;
}
class TeeStream {
public:
    TeeStream(std::ostream& stream1, std::ostream& stream2) : stream1(stream1), stream2(stream2) {}

    template <typename T>
    TeeStream& operator<<(const T& value)
    {
        addTimestamp();
        stream1 << value;
        stream2 << value;
        return *this;
    }

    // 函数模板重载，用于处理 manipulators（如 std::endl）
    TeeStream& operator<<(std::ostream& (*manipulator)(std::ostream&))
    {
        addTimestamp();
        stream1 << manipulator;
        stream2 << manipulator;
        return *this;
    }

private:
    std::ostream& stream1;
    std::ostream& stream2;

    void addTimestamp() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        char timestamp[26];
        std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now_c));
        stream1 << "[" << timestamp << "] ";
        stream2 << "[" << timestamp << "] ";
    }
};
class CoutTeeBuffer : public std::streambuf {
public:
    CoutTeeBuffer(std::streambuf* buffer1, std::streambuf* buffer2) : buffer1(buffer1), buffer2(buffer2) {}

    int overflow(int c) {
        if (c != EOF) {
            if (atLineStart) {
                addTimestamp();
                atLineStart = false;
            }
            if (c == '\n')
                atLineStart = true;

            if (buffer1 != nullptr)
                buffer1->sputc(c);
            if (buffer2 != nullptr)
                buffer2->sputc(c);
        }
        return c;
    }

    void addTimestamp() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        char timestamp[26];
        std::strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S] ", std::localtime(&now_c));
        if (buffer1 != nullptr)
            buffer1->sputn(timestamp, std::strlen(timestamp));
        if (buffer2 != nullptr)
            buffer2->sputn(timestamp, std::strlen(timestamp));
    }

    std::streambuf* buffer1;
    std::streambuf* buffer2;
    bool atLineStart = true;
};
static void TempCall(short* temp, int w, int h, void* pUser)
{


}
static void GetIrRtsp(unsigned char* outdata, int w, int h, void* pUser)
{
    //printf("outdata is %s\n", outdata);
    //printf("w is %d, h is %d\n", w, h);
   // Sleep(2000);
}
static void GetY16Data(short* y16, int length, void* ptr)
{
    //cout << getTime() << endl;
    //cout << *y16 << endl;
    getTempMatrix(y16);
}
void getTempMatrix(short* y16)
{
    if (!y16)
    {
        return;
    }

    float* matrix = (float*)malloc(640 * 512 * sizeof(float));
    int ret = SGP_GetTempMatrixEx(handle, matrix, y16, 640, 512);

    if (ret == -1)
    {

        if (matrix)
        {
            free(matrix);
            matrix = nullptr;
        }
        return;
    }

    float max = 0, min = 100, avg = 0, sum = 0;
    //max = matrix[0],  min = matrix[0];
    for (int i = 0; i < 640 * 512; i++)
    {
        if (matrix[i] >= max)
        {
            max = matrix[i];
        }

        if (min >= matrix[i])
        {
            min = matrix[i];
        }
        sum += matrix[i];
    }

    cout << getTime() << "  "
        << "maxTemp:" << fixed << setprecision(2) << max << "  "
        << "minTemp:" << fixed << setprecision(2) << min << "  "
        << "avgTemp:" << fixed << setprecision(2) << sum / (640 * 512) << endl;

    if (matrix)
    {
        free(matrix);
        matrix = nullptr;
    }
}
void threadFunction()
{
    SGP_OpenIrVideo(handle, GetIrRtsp, 0);
    SGP_GetY16(handle, GetY16Data, 0);
    Sleep(99999999999);
}
void Test();

int main()
{
    std::ofstream logFile("test.log", std::ios::app);  // 打开文件时使用追加模式
    CoutTeeBuffer teeBuffer(std::cout.rdbuf(), logFile.rdbuf());
    std::ostream tee(&teeBuffer);

    handle = SGP_InitDevice();

    if (handle != 0)
    {
        cout << "初始化成功" << endl;
    }
    else
    {
        cout << "初始化失败" << endl;
    }
    /*tee << "Please enter the device:";
    char server[64];
    scanf("%s", server);
    int n;
    tee << endl;
    tee << "Please enter the testing time:";
    cin >> n;*/
    const char* server = "192.168.21.153";
    const char* username = "root";
    const char* password = "guide123";
    int port = 80;
    int ret1 = SGP_Login(handle, server, username, password, port);

    if (ret1 == SGP_OK)
    {
        cout << "登陆成功！" << endl;
        bool pause = false;

        /* thread myThread(threadFunction);
         myThread.join();    */

         /*int j = 1;
         while (j<=360*n)
         {
             tee << "第" << j << "轮" << endl;
             Sleep(2000);
             SGP_IMAGE_TYPE type = SGP_IR_IMAGE;
             char path[] = "./testPicture/screencap.jpg";
             int retc = SGP_GetScreenCapture(handle, type, path);
             if (retc == SGP_OK)
             {
                 tee << "获取屏幕截图成功" << endl;
             }
             else
             {
                 tee << "获取屏幕截图失败\n" << "ret的返回值为：" << retc << endl;
                 break;
             }
             tee << endl;

             Sleep(1000);
             const char* paths = "screenpic.jpg";
             int retg = SGP_GetHeatMap(handle, paths);
             if (retg == SGP_OK)
             {
                 tee << "获取热图成功" << endl;
             }
             else
             {
                 tee << "获取热图失败\n" << "ret的返回值为：" << retg << endl;
                 break;
             }
             tee << endl;

             Sleep(2000);
             SGP_FOCUS_TYPE types = SGP_FOCUS_AUTO;
             int value = 750;
             int retj = SGP_SetFocus(handle, types, value);
             if (retj == SGP_OK)
             {
                 tee << "聚焦成功" << endl;
             }
             else
             {
                 tee << "聚焦失败\n" << "ret的返回值为：" << retj << endl;
                 break;
             }
             tee << endl;

             Sleep(3000);
             SGP_SHUTTER_ENUM typek = SGP_SHUTTER;
             int retk = SGP_DoShutter(handle, typek);
             if (retk == SGP_OK)
             {
                 tee << "打快门成功！" << endl;
             }
             else
             {
                 tee << "打快门失败\n" << "ret的返回值为：" << retk << endl;
             }

             Sleep(2000);
             tee << endl;
             SGP_GENERAL_INFO info;
             memset(&info, 0x00, sizeof(info));
             int rett = SGP_GetGeneralInfo(handle, &info);
             if (rett == SGP_OK)
             {
                 int height = info.ir_model_h;
                 int width = info.ir_model_w;
                 int length = height * width;
                 int type = 1;
                 float* output = (float*)calloc(length, sizeof(float));
                 if (output != NULL)
                 {
                     rett = SGP_GetImageTemps(handle, output, length * 4, type);
                     if (rett == SGP_OK)
                     {
                         tee << "获取温度矩阵成功" << endl;
                     }

                     float max = 0, min = 100, sum = 0;
                     for (int i = 0; i < length; i++)
                     {
                         if (max < output[i])
                         {
                             max = output[i];
                         }
                         if (min > output[i])
                         {
                             min = output[i];
                         }
                         sum += output[i];
                     }

                     tee << "获取的最高温为：" << setprecision(3) << max << endl;
                     tee << "获取的最低温为：" << setprecision(3) << min << endl;
                     tee << "获取的平均温为：" << setprecision(3) << sum / length << endl;
                 }
                 free(output);
                 output = NULL;
             }

             tee << endl; tee << endl;
             j++;
         }*/


        thread myTest(
            [&pause]() {
                while (true)
                {
                    if (!pause)
                    {
                        Test();
                       
                    }

                }
            }
        );

        while (true)
        {
            if (cin.get() == '\n')
            {
                pause = !pause;
            }
        }
        myTest.join();


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
        logFile.close();
    }

    else
    {
        printf("登陆失败");
        SGP_UnInitDevice(handle);
    }

}

void Test()
{
    SGP_FOCUS_TYPE type = SGP_FOCUS_PLACE;
    int value1 = 200;
    int value2 = 600;
    int ret = SGP_SetFocus(handle, type, value1);
    cout << "ret is:" << ret << endl;

    Sleep(1500);
    int retq = SGP_SetFocus(handle, type, value2);
    cout << "ret is:" << retq << endl;
    Sleep(1500);

    /*cout << "第" << j-1 << "次打快门" << endl;
    SGP_FOCUS_TYPE type = SGP_FOCUS_AUTO;
    int value1 = 340;
    int ret = SGP_SetFocus(handle, type, value1);
    cout << "ret is:" << ret << endl;
    Sleep(3000);*/
}





