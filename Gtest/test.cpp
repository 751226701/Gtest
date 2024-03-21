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

static int callbackCount = 0; 
static auto lastSecond = chrono::system_clock::now();

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
void saveY16(string filename,short *y16) {
    ofstream file(filename, ios::out | ios::binary);
    if (file.is_open()) {
        for (int i = 0; i < 640 * 512; i++)
        {
            file << y16[i] << " ";
        }
        file.close();
    }
    else
    {
        cout << "文件打开失败" << endl;
    }
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
class CoutTeeBuffer : public std::streambuf 
{
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
std::ofstream logFile("test.log", std::ios::app);  
CoutTeeBuffer teeBuffer(std::cout.rdbuf(), logFile.rdbuf());
std::ostream tee(&teeBuffer);
void callbackCounts()
{
    callbackCount++;
    //cout << "callbackCount:" << callbackCount << endl;
    auto now = chrono::system_clock::now();
    auto currentSecond = chrono::duration_cast<chrono::seconds>(now.time_since_epoch()).count();
    auto lastSecondCount = chrono::duration_cast<chrono::seconds>(lastSecond.time_since_epoch()).count();
    if (currentSecond != lastSecondCount)
    {
        tee << getTime() << "  " << "CallbacksPerSecond: " << callbackCount << endl;
        callbackCount = 0;
        lastSecond = now;
    }
    if (currentSecond - lastSecondCount > 1)
    {
        tee << "回调缺失：" << currentSecond - lastSecondCount - 1 << "秒" << endl;
    }
}
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
    getTempMatrix(y16);
    //callbackCounts();
}
void getTempMatrix(short* y16)
{
    if (!y16)
    {
        return;
    }
    
    float* matrix = (float*)malloc(640 * 512 * sizeof(float));
    int ret = SGP_GetTempMatrixEx(handle, matrix, y16, 640, 512);

    if (ret != 0)
    {
        cout << "转温度矩阵异常！！！！" << endl;
        if (matrix)
        {
            free(matrix);
            matrix = nullptr;
        }
        return;
    }

    else
    {
        callbackCounts();
        float max = matrix[0], min = matrix[0], avg = 0, sum = 0;
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

        tee << getTime() << "  "
            << "maxTemp:" << fixed << setprecision(2) << max << "  "
            << "minTemp:" << fixed << setprecision(2) << min << "  "
            << "avgTemp:" << fixed << setprecision(2) << sum / (640 * 512) << endl;
    }

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
    scanf("%s", server);*/
   /* int n;
    tee << endl;
    tee << "Please enter the testing time:";
    cin >> n;*/
    const char* server = "192.168.21.4";
    const char* username = "root";
    const char* password = "guide123";
    int port = 80;
    int ret1 = SGP_Login(handle, server, username, password, port);

    if (ret1 == SGP_OK)
    {
        cout << "登陆成功！" << endl;

        thread myThread(threadFunction);
        myThread.join();
       
        //while (true)
        //{
        //    int x = 120;
        //    int y = 120;
        //    float output = 0.0f;
        //    int ret = SGP_GetPointTemp(handle, x, y, &output);
        //    if (ret == SGP_OK)
        //    {
        //        tee <<  output << endl;
        //    }
        //    else
        //    {
        //        cout << "获取单点温度失败\n" << "ret的返回值为：" << ret << endl;
        //    }
        //    //Sleep(20);
        //}

        /*int j = 1;
        while (j++)
        {
            SGP_IMAGE_TYPE type = SGP_IR_IMAGE;
            string screencap = "D:/Testpicture/screencap" + std::to_string(j) + ".jpg";
   
            int ret = SGP_GetScreenCapture(handle, type, screencap.c_str());
            if (ret == SGP_OK)
            {
                cout << "获取屏幕截图成功" << j-1<<"张" << endl;
            }
            else
            {
                cout << "获取屏幕截图失败\n" << "ret的返回值为：" << ret << endl;
                break;
            }

            Sleep(3000);

            
        }*/

        /*int j = 1;
        int errCount = 0;
        while (j<=360*n)
        {
            tee << "第" << j << "轮" << endl;                  
            Sleep(2000);
            SGP_IMAGE_TYPE type = SGP_IR_IMAGE;
            char path[] = "./screencap.jpg";
            int retc = SGP_GetScreenCapture(handle, type, path);
            if (retc == SGP_OK)
            {
                tee << "获取屏幕截图成功" << endl;
            }
            else
            {
                tee << "获取屏幕截图失败\n" << "ret的返回值为：" << retc << endl;
                errCount += 1;
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
                errCount += 1;
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
                errCount += 1;
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
                errCount += 1;
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
                    else
                    {
                        tee << "获取温度矩阵失败" <<"rett="<<rett<< endl;
                        errCount += 1;
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

            tee << endl;
            tee << "接口调用失败次数：" << errCount << endl;
            tee << endl; tee << endl;
            
            j++;
        }     */
        
        /*thread myTest(
            [&pause]() {
                while (true)
                {
                    if (!pause)
                    {
                        Test();                                 
                    }                 
                }
            });

        while (true) 
        {
            if (cin.get() == '\n') 
            {
                pause = !pause; 
            }
        }
        myTest.join();*/
        
        /*int j = 1;
        while (j++)
        {
            tee << "第" << j -1<< "次打快门！" << endl;
            SGP_SHUTTER_ENUM type = SGP_SHUTTER;
            int ret = SGP_DoShutter(handle, type);
            if (ret == SGP_OK)
            {
                tee << "返回成功" << endl;
            }
            else
            {
                tee << "返回失败\n" << "ret的返回值为：" << ret << endl;
            }
            Sleep(3000);
            tee << endl;
        }*/
        
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

    Sleep(1600);
    int retq = SGP_SetFocus(handle, type, value2);
    cout << "ret is:" << retq << endl;
    Sleep(1600);
    
    /*cout << "第" << j-1 << "次打快门" << endl;
    SGP_FOCUS_TYPE type = SGP_FOCUS_AUTO;
    int value1 = 340;
    int ret = SGP_SetFocus(handle, type, value1);
    cout << "ret is:" << ret << endl;
    Sleep(3000);*/
}





