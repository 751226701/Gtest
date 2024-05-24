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
//连续获取指定点温间隔时间
void getPointTempIntervalTime(SGP_HANDLE handle,int n) {
    const int pointNum = 165;
    int index[165] = { 24840,25470,25620,25620,25400,24990,24510,24500,24100,24110,24290,24270,24060,23950,23950,26290,23960,24010,23940,23960,23990,23860,23890,23790,23860,23990,26970,24020,24020,23950,24210,23950,24120,26970,23830,24010,23870,23830,23790,23550,26579,23790,23830,23860,23830,24120,23720,24120,23720,23840,24210,23860,24210,23830,23730,24410,23670,23760,24410,23790,24010,24640,24140,24630,24630,24870,24920,25060,24920,24810,25620,24710,25200,24770,25700,24770,27100,26629,24600,25700,24820,27110,25690,25420,24820,24510,26740,25250,24900,24540,25150,25160,25200,25200,25080,24900,25979,25900,25470,25320,24660,24360,24270,26090,24230,24980,24860,26140,24220,25000,26140,24210,24210,24860,25900,25170,25080,26060,24170,24630,26240,24170,24080,24470,25350,25610,26240,24080,24500,26370,25520,25740,24040,24670,26370,24040,24920,25520,25829,26429,24050,25580,25380,26400,25570,25650,25700,24050,26040,25700,25640,25380,24220,25800,26400,24890,25800,25640,25220,26550,25470 };

    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    if (ret != SGP_OK)
    {
        tee << "设置索引失败！ret is:" << ret << endl;
        return;
    }

    while (true)
    {
        float* temp = (float*)malloc(pointNum * sizeof(float));
        memset(temp, 0x00, pointNum * sizeof(float));
        if (temp != NULL)
        {
            auto start_time = std::chrono::steady_clock::now();
            int ret = SGP_GetTempPoints(handle, temp, pointNum, 1);
            auto end_time = std::chrono::steady_clock::now();
            if (ret == SGP_OK)
            {
                //cout << getTime() << " 获取点温成功" << std::endl;
                //cout << "距离上一次成功获取点温的时间间隔为：" << getTimeInterval(start_time, end_time) << std::endl;
                tee << getTimeInterval(start_time, end_time) << endl;
            }
            else
            {
                cout << "获取温度失败！ret is:" << ret << endl;
            }
        }
        free(temp);
        temp = NULL;
        Sleep(n);
    }
    free(index);
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
void saveMatrix2(float *output, char filename[]) {
    std::ofstream outfile(filename, std::ios::binary);
    if (outfile.is_open()) {
        outfile.write(reinterpret_cast<char*>(output), sizeof(float) * 640 * 512);
        outfile.close();
        std::cout << "温度矩阵已成功写入文件" << std::endl;
    }
    else {
        std::cerr << "无法打开文件" << std::endl;
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
    const char* server = "192.168.21.244";
    const char* username = "root";
    const char* password = "guide123";
    int port = 80;
    int ret1 = SGP_Login(handle, server, username, password, port);
    if (ret1 == SGP_OK)
    {
        cout << "登录成功" << endl;
        GetVersionInfo(handle);
        
        /*const char* filename = "C:\\Users\\gd09186\\Desktop\\matrix.raw";
        readMatrixToImage(filename);*/
        //matrixToImage(handle);
        //getHeatMap(handle);
        

        //StressTest(handle, 24);

        int i = 1;
        int errCount = 0;
        while (true)
        {
            cout << "第" << i << "次" << endl;
            
            SGP_IMAGE_TYPE type = SGP_IR_IMAGE;
            char path[] = "./testPicture/screencap.jpg";
            int ret = SGP_GetScreenCapture(handle, type, path);
            if (ret == SGP_OK)
            {
                cout << "获取屏幕截图成功" << endl;
            }
            else
            {
                cout << "获取屏幕截图失败\n" << "ret的返回值为：" << ret << endl;
                errCount++;
            }

            i++;
            cout << "失败次数：" << errCount << endl;
            Sleep(3000); cout << endl;
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

//int main()
//{
//    for (int i = 1; i < 201; i++)
//    {
//        cout << "第" << i << "轮" << endl;
//        SGP_HANDLE handle = 0;
//        handle = SGP_InitDevice();
//        const char* server = "192.168.21.31";
//        const char* username = "root";
//        const char* password = "guide123";
//        int port = 80;
//        int ret1 = SGP_Login(handle, server, username, password, port);
//        if (ret1 != SGP_OK)
//        {
//            cout << "登录失败！ ret is:" << ret1 << endl;;
//            SGP_UnInitDevice(handle);
//            return -1;
//        }
//
//        cout << "登录成功" << endl;
//        Sleep(2000);
//        int retqq = SGP_Logout(handle);
//        if (retqq == SGP_OK)
//        {
//            cout << "用户登出成功！" << endl;
//        }
//        else
//        {
//            cout << "用户登出失败！ ret is:" << retqq << endl;
//        }
//        SGP_UnInitDevice(handle);
//        cout << endl;
//    }
//}

