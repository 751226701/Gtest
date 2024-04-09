#pragma once
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
#include <string>
#include <sstream>
#include <mutex>
#include <opencv2/opencv.hpp>
#include "SgpApi.h"
#include "SgpParam.h"
#include "ITAHeatmap.h"
#include "ERROR.h"
#include "ITA.h"
using namespace std;
using namespace cv;

string getTime()
{
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    return tmp;
}
std::string getTimeEx()
{
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(epoch);
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_c);

    std::ostringstream oss;
    oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");
    oss << '.' << std::setfill('0') << std::setw(3) << epoch.count() % 1000;

    return oss.str();
}
std::string getTimeInterval(const std::chrono::steady_clock::time_point& start, const std::chrono::steady_clock::time_point& end)
{
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return std::to_string(elapsed.count()) + "����";
}
static void TempCall(short* temp, int w, int h, void* pUser)
{
    cout << *temp << endl;
    cout << w << endl;
    cout << h << endl;
}
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
std::ofstream logFile("C:\\Users\\gd09186\\Desktop\\test.log", std::ios::app);  // ���ļ�ʱʹ��׷��ģʽ
CoutTeeBuffer teeBuffer(std::cout.rdbuf(), logFile.rdbuf());
std::ostream tee(&teeBuffer);

class Logger {
public:
    // ���캯����������־�ļ�·��
    explicit Logger(const std::string& path)
        : file_path_(path), stream_(nullptr) {
        openFile();
    }

    // �����������ر���־�ļ�
    ~Logger() {
        if (stream_ != nullptr) {
            stream_->close();
            delete stream_;
        }
    }

    // �����־��Ϣ��֧�����������̨���ļ��������ʱ���
    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);

        // ��ȡ��ǰʱ��
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_c);

        // ������־��
        std::ostringstream log_line;
        log_line << std::put_time(&now_tm, "[%Y-%m-%d %X]") << "  " << message;

        // ���������̨
        std::cout << log_line.str() << std::endl;

        // д���ļ�
        if (stream_ != nullptr) {
            *stream_ << log_line.str() << std::endl;
        }
    }

    // �򿪻����´���־�ļ�
    void openFile() {
        if (stream_ != nullptr) {
            stream_->close();
            delete stream_;
            stream_ = nullptr;
        }

        // ��׷��ģʽ����־�ļ�
        stream_ = new std::ofstream(file_path_, std::ios::app);
        if (!stream_->is_open()) {
            std::cerr << "Failed to open log file: " << file_path_ << std::endl;
        }
    }

private:
    std::string file_path_;
    std::ofstream* stream_;
    std::mutex mutex_;
};


//������־��¼��
std::ostream& initTee(const std::string& logFilePath) {
    static std::ofstream logFile(logFilePath, std::ios::app); 
    static CoutTeeBuffer teeBuffer(std::cout.rdbuf(), logFile.rdbuf());
    static std::ostream tee(&teeBuffer);
    return tee;
}
//���ò��µ������
int setPoint(int x, int y) {
    return x + y * 640 - 1;
}
//����ָ������¶�
void testPointTemp(SGP_HANDLE handle)
{
    float standTemp = 250;      //��׼�¶�
    float tempE = 20;           //��Χ  
    int counts = 0;             //�쳣�¶ȴ���
    int rounds = 1;             //�����ִ�

    while (1) {
        tee << "��" << rounds << "�ֲ���" << endl;
        SGP_SHUTTER_ENUM type = SGP_SHUTTER;
        int ret = SGP_DoShutter(handle, type);
        if (ret == SGP_OK)
        {
            tee << "����ţ�8S��ʼ���£�" << endl;
        }
        else
        {
            tee << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }

        Sleep(8000);

        for (int i = 0; i < 3; i++)
        {
            const int pointNum = 10;
            int* index = (int*)malloc(pointNum * sizeof(int));
            index[0] = 151371;
            index[1] = 136658;
            index[2] = 140416;
            index[3] = 189050;
            index[4] = 102659;
            index[5] = 210872;
            index[6] = 182810;
            index[7] = 217981;
            index[8] = 231370;
            index[9] = 215302;


            int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
            if (ret == SGP_OK)
            {
                float* temp = (float*)malloc(pointNum * sizeof(float));
                memset(temp, 0x00, pointNum * sizeof(float));
                if (temp != NULL)
                {
                    int ret = SGP_GetTempPoints(handle, temp, pointNum, 1);
                    if (ret == SGP_OK)
                    {
                        for (int i = 0; i < pointNum; i++)
                        {
                            float dif = std::abs(temp[i] - standTemp);
                            if (dif > tempE)
                            {
                                counts++;
                            }
                            tee << fixed << setprecision(1) << "��" << i + 1 << "����ʵʱ�¶ȣ�" << temp[i] << "   �Ƚϱ�׼��" << standTemp
                                << "   ��ֵ��" << dif << "   ��Χ��" << tempE << "   �쳣�¶ȴ���" << counts << endl;
                        }
                    }
                    else
                    {
                        tee << "��ȡ�¶�ʧ�ܣ�ret is:" << ret << endl;
                    }
                }
                free(temp);
                temp = NULL;
            }
            else
            {
                tee << "��������ʧ�ܣ�ret is:" << ret << endl;
            }
            free(index);
            index = NULL;
            Sleep(500);
        }
        rounds++;
        tee << endl;
    }
}
//��ȡ�豸�汾��Ϣ
void GetVersionInfo(SGP_HANDLE handle) {
    SGP_VERSION_INFO info1;
    memset(&info1, 0x00, sizeof(info1));
    SGP_GetVersionInfo(handle, &info1);
    cout << "��ȡ��ϵͳ��ϢΪ��" << endl;
    cout << "�豸�ͺţ�" << info1.model << endl;
    cout << "ϵͳ�汾��" << info1.version << endl;
    cout << "���кţ�  " << info1.serial << endl;
    cout << "FPGA�汾��" << info1.fpga_version << endl;
    cout << "���°汾��" << info1.measure_version << endl;
    cout << "SDK�汾�� " << info1.sdk_version << endl;
    cout << "****************************************" << endl;
    cout << endl;
}
//��������
void StressTest(int n, SGP_HANDLE handle) {
    int j = 1;
    int errCount = 0;
    while (j <= 360 * n)
    {
        tee << "��" << j << "��" << endl;
        Sleep(2000);
        SGP_IMAGE_TYPE type = SGP_IR_IMAGE;
        char path[] = "./screencap.jpg";
        int retc = SGP_GetScreenCapture(handle, type, path);
        if (retc == SGP_OK)
        {
            tee << "��ȡ��Ļ��ͼ�ɹ�" << endl;
        }
        else
        {
            tee << "��ȡ��Ļ��ͼʧ��\n" << "ret�ķ���ֵΪ��" << retc << endl;
            errCount += 1;
        }
        tee << endl;

        Sleep(1000);
        const char* paths = "screenpic.jpg";
        int retg = SGP_GetHeatMap(handle, paths);
        if (retg == SGP_OK)
        {
            tee << "��ȡ��ͼ�ɹ�" << endl;
        }
        else
        {
            tee << "��ȡ��ͼʧ��\n" << "ret�ķ���ֵΪ��" << retg << endl;
            errCount += 1;
        }
        tee << endl;

        Sleep(2000);
        SGP_FOCUS_TYPE types = SGP_FOCUS_AUTO;
        int value = 750;
        int retj = SGP_SetFocus(handle, types, value);
        if (retj == SGP_OK)
        {
            tee << "�۽��ɹ�" << endl;
        }
        else
        {
            tee << "�۽�ʧ��\n" << "ret�ķ���ֵΪ��" << retj << endl;
            errCount += 1;
        }
        tee << endl;

        Sleep(3000);
        SGP_SHUTTER_ENUM typek = SGP_SHUTTER;
        int retk = SGP_DoShutter(handle, typek);
        if (retk == SGP_OK)
        {
            tee << "����ųɹ���" << endl;
        }
        else
        {
            tee << "�����ʧ��\n" << "ret�ķ���ֵΪ��" << retk << endl;
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
                    tee << "��ȡ�¶Ⱦ���ɹ�" << endl;
                }
                else
                {
                    tee << "��ȡ�¶Ⱦ���ʧ��" << "rett=" << rett << endl;
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

                tee << "��ȡ�������Ϊ��" << setprecision(3) << max << endl;
                tee << "��ȡ�������Ϊ��" << setprecision(3) << min << endl;
                tee << "��ȡ��ƽ����Ϊ��" << setprecision(3) << sum / length << endl;
            }
            free(output);
            output = NULL;
        }

        tee << endl;
        tee << "�ӿڵ���ʧ�ܴ�����" << errCount << endl;
        tee << endl; tee << endl;

        j++;
    }
}


int gloableX = 1;
int gloableY = 1;
#define PRECISION 1
#define WIDTH 640
#define HEIGHT 512
//���ص�
static void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_MOUSEMOVE) {
        Mat* temperatureImage = (Mat*)userdata;
        float temperature = temperatureImage->at<float>(y, x);
        gloableX = x;
        gloableY = y;
        //cout << "mouse position (" << x << ", " << y << ")"<< endl;
    }
}
//�������ȶԱȶ�
void adjustBrightnessContrast(Mat& image, double brightness, int contrast) {
    image.convertTo(image, -1, brightness, contrast);
}
//�¶Ⱦ������1
void matrixToVideo(float* matrix) {
    cout << "position: (" << gloableX << "," << gloableY << ")  temp:"
        << fixed << setprecision(PRECISION) << matrix[gloableY * WIDTH + gloableX - 1] << endl;

    //���¶Ⱦ���ת��ΪCV_32F�������ʹ洢
    Mat temperatureImage(HEIGHT, WIDTH, CV_32F, matrix);
    //���ݹ�һ�����¶�ӳ�䵽0-1��Χ��,תΪ�Ҷ�ͼ
    normalize(temperatureImage, temperatureImage, 0, 1, NORM_MINMAX);
    //��CV_32F����ת��Ϊ8λͼ������
    Mat normalized8U;
    temperatureImage.convertTo(normalized8U, CV_8U, 255.0);

    try {
        //���Ҷ�ͼӳ�䵽��Ӧ��α�ʷ�����
        Mat coloredImage;
        applyColorMap(normalized8U, coloredImage, COLORMAP_JET);

        double brightness = 1;  //���ȷ�Χ0-3
        int contrast = 50;  //�Աȶȷ�Χ-100-100
        adjustBrightnessContrast(coloredImage, brightness, contrast);

        //��ʾͼ��
        imshow("matrix_Video", coloredImage);
        setMouseCallback("matrix_Video", onMouse, (void*)&temperatureImage);
        waitKey(1);

        imwrite("matrix_image.jpg", coloredImage);
    }
    catch (Exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }
}
//�¶Ⱦ������2
void matrixToVideoEx(float* matrix, float* output) {
    cout << "position: (" << gloableX << "," << gloableY << ")  temp:"
        << fixed << setprecision(PRECISION) << output[gloableY * WIDTH + gloableX - 1] << endl;

    //���¶Ⱦ���ת��ΪCV_32F�������ʹ洢
    Mat temperatureImage(HEIGHT, WIDTH, CV_32F, matrix);
    //���ݹ�һ�����¶�ӳ�䵽0-1��Χ��,תΪ�Ҷ�ͼ
    normalize(temperatureImage, temperatureImage, 0, 1, NORM_MINMAX);
    //��CV_32F����ת��Ϊ8λͼ������
    Mat normalized8U;
    temperatureImage.convertTo(normalized8U, CV_8U, 255.0);

    try {
        //���Ҷ�ͼӳ�䵽��Ӧ��α�ʷ�����
        Mat coloredImage;
        applyColorMap(normalized8U, coloredImage, COLORMAP_JET);

        double brightness = 1;  //���ȷ�Χ0-3
        int contrast = 50;  //�Աȶȷ�Χ-100-100
        adjustBrightnessContrast(coloredImage, brightness, contrast);

        //����ʮ�ֹ��
        coloredImage.row(gloableY).setTo(Scalar(255, 0, 0));  // ˮƽ��
        coloredImage.col(gloableX).setTo(Scalar(255, 0, 0));  // ��ֱ��

        //��ʾͼ��
        imshow("matrix_Video", coloredImage);
        setMouseCallback("matrix_Video", onMouse, (void*)&temperatureImage);
        waitKey(1);
    }
    catch (Exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }
}
//Y16�������
void y16ToVideo(short* y16) {
    cout << "position: (" << gloableX << "," << gloableY << ")  Y16:" << y16[gloableY * WIDTH + gloableX - 1] << endl;
    Mat temperatureImage(HEIGHT, WIDTH, CV_16S, y16);
    normalize(temperatureImage, temperatureImage, 0, 255, NORM_MINMAX);
    Mat temperature8U;
    temperatureImage.convertTo(temperature8U, CV_8U);

    try {
        Mat coloredImage;
        applyColorMap(temperature8U, coloredImage, COLORMAP_JET);

        double brightness = 1;  // ���ȷ�Χ0-3
        int contrast = 50;      // �Աȶȷ�Χ-100-100
        adjustBrightnessContrast(coloredImage, brightness, contrast);

        imshow("Y16_Video", coloredImage);
        setMouseCallback("Y16_Video", onMouse, (void*)&temperatureImage);
        waitKey(1);
        imwrite("y16_image.jpg", coloredImage);
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

