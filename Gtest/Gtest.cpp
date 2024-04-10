#include "COMMON.h"

//抓取热图和高压热图
void getHeatMap(SGP_HANDLE handle) {
    const char* path = "./testPicture/screenpic.jpg";
    int ret = SGP_GetHeatMap(handle, path);
    if (ret == SGP_OK)
    {
        cout << "获取热图成功" << endl;
    }
    else
    {
        cout << "获取热图失败\n" << "ret的返回值为：" << ret << endl;
    }

    const char* path1 = "./testPicture/screenpic.fir";
    int ret1 = SGP_GetFirHeatMap(handle, path1);
    if (ret1 == SGP_OK)
    {
        cout << "获取高压热图成功" << endl;
    }
    else
    {
        cout << "获取高压热图失败\n" << "ret的返回值为：" << ret << endl;
    }
}
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
                matrixToVideoEx(matrix, output);
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
                Sleep(150);
            }
            free(output);
            output = NULL;
        }
        free(output);
        output = NULL;
    }
}
//读取文件
void* readFile(const char* filename, size_t* numElements, size_t elementSize) {
    FILE* file = fopen(filename, "rb");

    if (file == NULL) {
        fprintf(stderr, "无法打开文件 %s\n", filename);
        return NULL;
    }

    // 获取文件的大小
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 计算包含的元素个数
    *numElements = fileSize / elementSize;

    // 分配内存以存储数据
    void* dataArray = malloc(fileSize);
    if (dataArray == NULL) {
        fprintf(stderr, "内存分配失败\n");
        fclose(file);
        return NULL;
    }

    // 从文件中读取数据到 dataArray
    size_t elementsRead = fread(dataArray, elementSize, *numElements, file);
    if (elementsRead != *numElements) {
        fprintf(stderr, "读取文件时出现错误\n");
        fclose(file);
        free(dataArray);
        return NULL;
    }

    // 关闭文件并返回 dataArray
    fclose(file);
    return dataArray;
}
//读取单帧温度矩阵转为图像
void readMatrixToImage(const char* filename) {
    size_t numElements;
    float* matrixData = (float*)readFile(filename, &numElements, sizeof(float));
    if (matrixData != NULL) {
        printf("成功读取了 %zu 个 float 类型元素\n", numElements);
    }
    
    matrixToVideo(matrixData);
    free(matrixData);
    matrixData = nullptr;
}
//读取单帧Y16矩阵转为图像
void readY16ToImage(const char* filename) {
    size_t numElements;
    short* Y16Data = (short*)readFile(filename, &numElements, sizeof(short));
    if (Y16Data != NULL) {
        printf("成功读取了 %zu 个 short 类型元素\n", numElements);
    }

    y16ToVideo(Y16Data);
    free(Y16Data);
    Y16Data = nullptr;
}
//保存温度矩阵
void saveMatrix(char filename[], int length, float* matrix) {
    FILE* file = fopen(filename, "wb");
    if (file != NULL)
    {
        fwrite(matrix, sizeof(float), length, file);
        fclose(file);
        printf("温度矩阵信息已保存到文件：%s\n", filename);
    }
    else
    {
        printf("无法打开文件进行写入操作。\n");
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
    const char* server = "192.168.1.14";
    const char* username = "root";
    const char* password = "guide123";
    int port = 80;
    int ret1 = SGP_Login(handle, server, username, password, port);
    if (ret1 == SGP_OK)
    {
        cout << "登录成功" << endl;
        GetVersionInfo(handle);
        

        /*const char* filename = "D:\\APP\\VS2022\\project\\Gtest\\Gtest\\temp_matrix.raw";
        readMatrixToImage(filename);*/
        matrixToImage(handle);
        //getHeatMap(handle);
       
        
        

   







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



