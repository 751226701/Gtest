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
string getTime()
{
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    return tmp;
}
static void GetIrRtsp(unsigned char* outdata, int w, int h, void* pUser)
{
    //printf("outdata is %s\n", outdata);
    //printf("w is %d, h is %d\n", w, h);
   // Sleep(2000);
}
void getTempMatrix(short* y16)
{
    if (!y16)
    {
        return;
    }

    float* matrix = (float*)malloc(640 * 512 * sizeof(float));
    int ret = SGP_GetTempMatrixEx(handle, matrix, y16, 640, 512);

    if (ret == 1)
    {
        if (matrix)
        {
            free(matrix);
            matrix = nullptr;
        }
        return;
    }

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
static void GetY16Data(short* y16, int length, void* ptr)
{
    callbackCount++;
    getTempMatrix(y16);
    auto now = chrono::system_clock::now();
    auto currentSecond = chrono::duration_cast<chrono::seconds>(now.time_since_epoch()).count();
    auto lastSecondCount = chrono::duration_cast<chrono::seconds>(lastSecond.time_since_epoch()).count();
    if (currentSecond != lastSecondCount)
    {
        cout << getTime() << "  " << "CallbacksPerSecond: " << callbackCount << endl;
        callbackCount = 0;
        lastSecond = now;
    }
}


static int callbackCount2 = 0;
static auto lastSecond2 = chrono::system_clock::now();
SGP_HANDLE handle2 = 0;
static void GetIrRtsp2(unsigned char* outdata, int w, int h, void* pUser)
{
    //printf("outdata is %s\n", outdata);
    //printf("w is %d, h is %d\n", w, h);
   // Sleep(2000);
}
void getTempMatrix2(short* y16)
{
    if (!y16)
    {
        return;
    }
    
    float* matrix = (float*)malloc(640 * 512 * sizeof(float));
    int ret = SGP_GetTempMatrixEx(handle2, matrix, y16, 640, 512);
    if (ret == 1)
    {
        if (matrix)
        {
            free(matrix);
            matrix = nullptr;
        }
        return;
    }

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
static void GetY16Data2(short* y16, int length, void* ptr)
{
    callbackCount2++;
    getTempMatrix2(y16);
    auto now = chrono::system_clock::now();
    auto currentSecond = chrono::duration_cast<chrono::seconds>(now.time_since_epoch()).count();
    auto lastSecondCount = chrono::duration_cast<chrono::seconds>(lastSecond2.time_since_epoch()).count();
    if (currentSecond != lastSecondCount)
    {
        cout << getTime() << "  " << "CallbacksPerSecond2: " << callbackCount2 << endl;
        callbackCount2 = 0;
        lastSecond2 = now;
    }
}

void thread01()
{
    cout << "线程1已启动" << endl;
    handle = SGP_InitDevice();
    
    const char* server = "192.168.21.153";
    const char* username = "root";
    const char* password = "guide123";
    int port = 80;
    int ret1 = SGP_Login(handle, server, username, password, port);

    SGP_OpenIrVideo(handle, GetIrRtsp, 0);
    SGP_GetY16(handle, GetY16Data, 0);
    Sleep(99999999999);

}

void thread02()
{
    cout << "线程2已启动" << endl;
    handle2 = SGP_InitDevice();

    const char* server = "192.168.21.153";
    const char* username = "root";
    const char* password = "guide123";
    int port = 80;
    int ret1 = SGP_Login(handle2, server, username, password, port);

    SGP_OpenIrVideo(handle2, GetIrRtsp2, 0);
    SGP_GetY16(handle2, GetY16Data2, 0);
    Sleep(99999999999);
}


int main()
{
	thread THREAD01(thread01);
	THREAD01.detach();
	thread THREAD02(thread02);
	THREAD02.detach();

    Sleep(99999999999);

	system("pause");
	return 0;
}