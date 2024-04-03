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
#include <opencv2/opencv.hpp>
#include "SgpApi.h"
#include "SgpParam.h"
#include "stdio.h"
using namespace std;
using namespace cv;

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
        cout << "�ļ���ʧ��" << endl;
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

    // ����ģ�����أ����ڴ��� manipulators���� std::endl��
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
        tee << "�ص�ȱʧ��" << currentSecond - lastSecondCount - 1 << "��" << endl;
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
//�������ȶԱȶ�
void adjustBrightnessContrast(Mat& image, double brightness, int contrast) {
    image.convertTo(image, -1, brightness, contrast);
}
//�¶Ⱦ������
void matrixToVideo(float* matrix) {
    
    //���¶Ⱦ���ת��ΪCV_32F�������ʹ洢
    Mat temperatureImage(512, 640, CV_32F, matrix);
    //���ݹ�һ�����¶�ӳ�䵽0-1��Χ��,תΪ�Ҷ�ͼ
    normalize(temperatureImage, temperatureImage, 0, 1, NORM_MINMAX);
    //��CV_32F����ת��Ϊ8λͼ������
    Mat normalized8U;
    temperatureImage.convertTo(normalized8U, CV_8U, 255.0);

    try {
        //���Ҷ�ͼӳ�䵽��Ӧ��α�ʷ�����
        Mat coloredImage;
        applyColorMap(normalized8U, coloredImage, COLORMAP_PARULA);

        double brightness = 1;  //���ȷ�Χ0-3
        int contrast = 50;  //�Աȶȷ�Χ-100-100
        adjustBrightnessContrast(coloredImage, brightness, contrast);

        //��ʾͼ��
        imshow("matrix_Video", coloredImage);
        waitKey(1);
    }
    catch (Exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }
}
//Y16�������
void y16ToVideo(short* y16) {
    Mat temperatureImage(512, 640, CV_16S, y16);
    normalize(temperatureImage, temperatureImage, 0, 255, NORM_MINMAX);
    Mat temperature8U;
    temperatureImage.convertTo(temperature8U, CV_8U);

    try {
        Mat coloredImage;
        applyColorMap(temperature8U, coloredImage, COLORMAP_WINTER);

        double brightness = 1;  // ���ȷ�Χ0-3
        int contrast = 50;      // �Աȶȷ�Χ-100-100
        adjustBrightnessContrast(coloredImage, brightness, contrast);

        imshow("Temperature Image", coloredImage);
        waitKey(1);
    }
    catch (Exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }
}
//��ȡ�¶Ⱦ�������������
void getMaxMinTemp(float* matrix) {
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
void getTempMatrix(short* y16) {
    if (!y16) {
        return;
    }

    float* matrix = (float*)malloc(640 * 512 * sizeof(float));
    int ret = SGP_GetTempMatrixEx(handle, matrix, y16, 640, 512);

    if (ret != 0) {
        cout << "ת�¶Ⱦ����쳣��������" << endl;
        if (matrix) {
            free(matrix);
            matrix = nullptr;
        }
        return;
    }

    y16ToVideo(y16);
    //matrixToVideo(matrix);
    //callbackCounts();
    //getMaxMinTemp(matrix);

    free(matrix);
    matrix = nullptr;
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
        cout << "��ʼ���ɹ�" << endl;
    }
    else
    {
        cout << "��ʼ��ʧ��" << endl;
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
        cout << "��½�ɹ���" << endl;

        thread myThread(threadFunction);
        myThread.join();
       
        
       
        
        int retl = SGP_Logout(handle);
        if (retl == SGP_OK)
        {
            cout << "�û��ǳ��ɹ���" << endl;
        }
        else
        {
            cout << "�û��ǳ�ʧ�ܣ�" << endl;
        }
        
        SGP_UnInitDevice(handle);     
        logFile.close();
    }

    else
    {
        printf("��½ʧ��");
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
    
    /*cout << "��" << j-1 << "�δ����" << endl;
    SGP_FOCUS_TYPE type = SGP_FOCUS_AUTO;
    int value1 = 340;
    int ret = SGP_SetFocus(handle, type, value1);
    cout << "ret is:" << ret << endl;
    Sleep(3000);*/
}





