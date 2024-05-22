#include "SDK_TEST.h"
using namespace std;

#define WIDTH 640;
#define HEIGHT 512

class SgpTest : public testing::Test
{
public:
    SGP_HANDLE handle;

    static void SetUpTestCase()
    {
        cout << "Start Test" << endl;
    }
    static void TearDownTestCase()
    {
        cout << "Test over" << endl;
    }

    void SetUp() override
    {
        handle = SGP_InitDevice();
        ASSERT_NE(handle, 0) << "SGP_InitDevice failed!" << endl;
        const char* server = "192.168.21.31";
        const char* username = "root";
        const char* password = "guide123";
        int port = 80;
        int retl = SGP_Login(handle, server, username, password, port);
        ASSERT_EQ(retl, SGP_OK) << "SGP_Login failed" << endl;
    }

    void TearDown() override
    {
        int retq = SGP_Logout(handle);
        EXPECT_EQ(retq, SGP_OK) << "SGP_Logout failed" << endl;

        SGP_UnInitDevice(handle);
    }
};


//һ��SGP_SetTempPoints
//01 ����������type=0  
TEST_F(SgpTest, 01_type_0)
{
    const int pointNum = 100;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i * 100;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 0);
    EXPECT_EQ(ret, SGP_OK) << "01_type_0 fail" << endl;
    free(index);
    index = NULL;
}

//02 ����������type=1
TEST_F(SgpTest, 02_type_1)
{
    const int pointNum = 100;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i * 100;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    EXPECT_EQ(ret, SGP_OK) << "02_type_1 fail" << endl;
    free(index);
    index = NULL;
}

//03 ���õ�һ������
TEST_F(SgpTest, 03_first_line)
{
    const int pointNum = 640;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    EXPECT_EQ(ret, SGP_OK) << "03_first_line fail" << endl;
    free(index);
    index = NULL;
}

//04 �������һ������
TEST_F(SgpTest, 04_last_line)
{
    const int pointNum = 640;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i + 327039;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    EXPECT_EQ(ret, SGP_OK) << "04_last_line fail" << endl;
    free(index);
    index = NULL;
}

// 05 ���õ�һ������
TEST_F(SgpTest, 05_first_column)
{
    const int pointNum = 512;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i * 640;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    EXPECT_EQ(ret, SGP_OK) << "05_first_column fail" << endl;
    free(index);
    index = NULL;
}

//06 �������һ������
TEST_F(SgpTest, 06_last_column)
{
    const int pointNum = 512;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = 639 + i * 640;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    EXPECT_EQ(ret, SGP_OK) << "06_last_column fail" << endl;
    free(index);
    index = NULL;
}

//07 �������е�����
TEST_F(SgpTest, 07_all_point)
{
    const int pointNum = 75000;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    EXPECT_EQ(ret, SGP_OK) << "07_all_point fail" << endl;
    free(index);
    index = NULL;
}

//08 ���õ�����������(��)
//TEST_F(SgpTest, 08_err_index)
//{
//    const int pointNum = 1;
//    int* index = (int*)malloc(pointNum * sizeof(int));
//    for (int i = 0; i < pointNum; i++)
//    {
//        index[i] = -1;
//    }
//    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
//    EXPECT_EQ(ret, SGP_ERR) << "08 ���õ�����������ʧ��" << endl;
//    free(index);
//    index = NULL;
//}

//09 ���������������ʵ�ʲ�һ��(��)
//TEST_F(SgpTest, 09���������������ʵ�ʲ�һ��)
//{
//    const int pointNum = 20;
//    int* index = (int*)malloc(pointNum * sizeof(int));
//    for (int i = 0; i < 21; i++)
//    {
//        index[i] = i;
//    }
//    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
//    EXPECT_EQ(ret, SGP_ERR) << "09 ���������������ʵ�ʲ�һ��ʧ��" << endl;
//    free(index);
//    index = NULL;
//}

//10 ���ò����ڵ�type=3(��)
//TEST_F(SgpTest, 10���ò����ڵ�type_3)
//{
//    const int pointNum = 20;
//    int* index = (int*)malloc(pointNum * sizeof(int));
//    for (int i = 0; i < pointNum; i++)
//    {
//        index[i] = i;
//    }
//    int ret = SGP_SetTempPoints(handle, index, pointNum, 3);
//    EXPECT_EQ(ret, SGP_ERR) << "10 ���ò����ڵ�type=3ʧ��" << endl;
//    free(index);
//    index = NULL;
//}

//11 ������Χ�����ָ�루����
TEST_F(SgpTest, 11_index_NULL)
{
    const int pointNum = 20;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i;
    }
    int ret = SGP_SetTempPoints(handle, NULL, pointNum, 1);
    EXPECT_EQ(ret, SGP_ERR) << "11_index_NULL fail" << endl;
    free(index);
    index = NULL;
}

//12 ��������handle(��)
TEST_F(SgpTest, 12_handle_NULL)
{
    const int pointNum = 20;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i;
    }
    int ret = SGP_SetTempPoints(NULL, index, pointNum, 1);
    EXPECT_EQ(ret, SGP_ERR) << "12_handle_NULL fail" << endl;
    free(index);
    index = NULL;
}

//����SGP_GetTempPoints
//13 ����������type=0����ȡ����λ���¶�  
TEST_F(SgpTest, 13_type_0_get_temp)
{
    const int pointNum = 100;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i * 100;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 0);
    ASSERT_EQ(ret, SGP_OK) << "13_type_0 fail" << endl;

    float* temp = (float*)malloc(pointNum * sizeof(float));
    memset(temp, 0, pointNum * sizeof(float));
    if (temp != NULL)
    {
        int ret = SGP_GetTempPoints(handle, temp, pointNum, 0);
        ASSERT_EQ(ret, SGP_OK) << "13_type_0_get_temp fail" << endl;
        cout << "��ȡ�¶ȳɹ���" << endl;
        for (int i = 0; i < pointNum; i++)
        {
            cout << temp[i] << endl;
        }
    }
    free(temp);
    temp = NULL;
    free(index);
    index = NULL;
}

//14 ����������type=1����ȡ����λ���¶�
TEST_F(SgpTest, 14_type_1_get_temp)
{
    const int pointNum = 100;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i * 100;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    ASSERT_EQ(ret, SGP_OK) << "14_type_1 fail" << endl;

    float* temp = (float*)malloc(pointNum * sizeof(float));
    memset(temp, 0x00, pointNum * sizeof(float));
    if (temp != NULL)
    {
        int ret = SGP_GetTempPoints(handle, temp, pointNum, 1);
        ASSERT_EQ(ret, SGP_OK) << "14_type_1_get_temp fail" << endl;
        /*cout << "��ȡ�¶ȳɹ���" << endl;
        for (int i = 0; i < pointNum; i++)
        {
            cout << temp[i] << endl;
        }*/
    }
    free(temp);
    temp = NULL;
    free(index);
    index = NULL;
}

//15 ���õ�һ����������ȡ����λ���¶�
TEST_F(SgpTest, 15_first_line_getTemp)
{
    const int pointNum = 640;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    ASSERT_EQ(ret, SGP_OK) << "15_first_line fail" << endl;

    float* temp = (float*)malloc(pointNum * sizeof(float));
    memset(temp, 0x00, pointNum * sizeof(float));
    if (temp != NULL)
    {
        int ret = SGP_GetTempPoints(handle, temp, pointNum, 1);
        ASSERT_EQ(ret, SGP_OK) << "15_first_line_getTemp fail" << endl;
        /*cout << "��ȡ�¶ȳɹ���" << endl;
        for (int i = 0; i < pointNum; i++)
        {
            cout << temp[i] << endl;
        }*/
    }
    free(temp);
    temp = NULL;
    free(index);
    index = NULL;
}

//16 �������һ����������ȡ����λ���¶�
TEST_F(SgpTest, 16_last_line_getTemp)
{
    const int pointNum = 640;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i + 327039;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    ASSERT_EQ(ret, SGP_OK) << "16_last_line fail" << endl;

    float* temp = (float*)malloc(pointNum * sizeof(float));
    memset(temp, 0x00, pointNum * sizeof(float));
    if (temp != NULL)
    {
        int ret = SGP_GetTempPoints(handle, temp, pointNum, 1);
        ASSERT_EQ(ret, SGP_OK) << "16_last_line_getTemp fail" << endl;
        /*cout << "��ȡ�¶ȳɹ���" << endl;
        for (int i = 0; i < pointNum; i++)
        {
            cout << temp[i] << endl;
        }*/
    }
    free(temp);
    temp = NULL;
    free(index);
    index = NULL;
}

// 17 ���õ�һ����������ȡ������λ�ö�
TEST_F(SgpTest, 17_first_column_getTemp)
{
    const int pointNum = 512;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i * 640;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    ASSERT_EQ(ret, SGP_OK) << "17_first_column fail" << endl;

    float* temp = (float*)malloc(pointNum * sizeof(float));
    memset(temp, 0x00, pointNum * sizeof(float));
    if (temp != NULL)
    {
        int ret = SGP_GetTempPoints(handle, temp, pointNum, 1);
        ASSERT_EQ(ret, SGP_OK) << "17_first_column_getTemp fail" << endl;
        /*cout << "��ȡ�¶ȳɹ���" << endl;
        for (int i = 0; i < pointNum; i++)
        {
            cout << temp[i] << endl;
        }*/
    }
    free(temp);
    temp = NULL;
    free(index);
    index = NULL;
}

//18 �������һ����������ȡ����λ���¶�
TEST_F(SgpTest, 18_last_column_getTemp)
{
    const int pointNum = 512;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = 639 + i * 640;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    ASSERT_EQ(ret, SGP_OK) << "18_last_column fail" << endl;

    float* temp = (float*)malloc(pointNum * sizeof(float));
    memset(temp, 0x00, pointNum * sizeof(float));
    if (temp != NULL)
    {
        int ret = SGP_GetTempPoints(handle, temp, pointNum, 1);
        ASSERT_EQ(ret, SGP_OK) << "18_last_column_getTemp fail" << endl;
        /*cout << "��ȡ�¶ȳɹ���" << endl;
        for (int i = 0; i < pointNum; i++)
        {
            cout << temp[i] << endl;
        }*/
    }
    free(temp);
    temp = NULL;
    free(index);
    index = NULL;
}

//19 �������е���������ȡ�¶�
TEST_F(SgpTest, 19_all_points_getTemp)
{
    const int pointNum = 75000;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    ASSERT_EQ(ret, SGP_OK) << "19_all_points fail" << endl;

    float* temp = (float*)malloc(pointNum * sizeof(float));
    memset(temp, 0x00, pointNum * sizeof(float));
    if (temp != NULL)
    {
        int ret = SGP_GetTempPoints(handle, temp, pointNum, 1);
        ASSERT_EQ(ret, SGP_OK) << "19_all_points_getTemp fail" << endl;
        /*cout << "��ȡ�¶ȳɹ���" << endl;
        for (int i = 0; i < pointNum; i++)
        {
            cout << temp[i] << endl;
        }*/
    }
    free(temp);
    temp = NULL;
    free(index);
    index = NULL;
}

//20 �����������Ϊ��ָ��output=NULL(��)
TEST_F(SgpTest, 20_output_NULL)
{
    const int pointNum = 100;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i * 100;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    ASSERT_EQ(ret, SGP_OK) << "20_type_1 fail" << endl;

    float* temp = (float*)malloc(pointNum * sizeof(float));
    memset(temp, 0x00, pointNum * sizeof(float));
    if (temp != NULL)
    {
        int ret = SGP_GetTempPoints(handle, NULL, pointNum, 1);
        ASSERT_EQ(ret, SGP_ERR) << "20_output_NULL fail" << endl;
    }
    free(temp);
    temp = NULL;
    free(index);
    index = NULL;
}

//21 �������������Ĳ�һ��
//TEST_F(SgpTest, 21)
//{
//    const int pointNum = 100;
//    int* index = (int*)malloc(pointNum * sizeof(int));
//    for (int i = 0; i < pointNum; i++)
//    {
//        index[i] = i * 100;
//    }
//    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
//    ASSERT_EQ(ret, SGP_OK) << "21 ����������type=1ʧ��" << endl;
//
//    float* temp = (float*)malloc(pointNum * sizeof(float));
//    memset(temp, 0, pointNum * sizeof(float));
//    if (temp != NULL)
//    {
//        int ret = SGP_GetTempPoints(handle, temp, 101, 1);
//        ASSERT_EQ(ret, SGP_ERR) << "21 �������������Ĳ�һ��ʧ��" << endl;
//    }
//    free(temp);
//    temp = NULL;
//    free(index);
//    index = NULL;
//}

//22 �¶Ⱦ�����������䲻һ��
//TEST_F(SgpTest, 22�¶Ⱦ�����������䲻һ��)
//{
//    const int pointNum = 100;
//    int* index = (int*)malloc(pointNum * sizeof(int));
//    for (int i = 0; i < pointNum; i++)
//    {
//        index[i] = i * 100;
//    }
//    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
//    ASSERT_EQ(ret, SGP_OK) << "22 ����������type=1ʧ��" << endl;
//
//    float* temp = (float*)malloc(pointNum * sizeof(float));
//    memset(temp, 0, pointNum * sizeof(float));
//    if (temp != NULL)
//    {
//        int ret = SGP_GetTempPoints(handle, temp, pointNum, 0);
//        ASSERT_EQ(ret, SGP_ERR) << "22 �¶Ⱦ�����������䲻һ��" << endl;
//    }
//    free(temp);
//    temp = NULL;
//    free(index);
//    index = NULL;
//}

//23 ��������handle
TEST_F(SgpTest, 23_handle_NULL)
{
    const int pointNum = 100;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i * 100;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    ASSERT_EQ(ret, SGP_OK) << "23_type_1 fail" << endl;

    float* temp = (float*)malloc(pointNum * sizeof(float));
    memset(temp, 0, pointNum * sizeof(float));
    if (temp != NULL)
    {
        int ret = SGP_GetTempPoints(NULL, temp, pointNum, 1);
        ASSERT_EQ(ret, SGP_ERR) << "23_handle_NULL fail" << endl;
    }
    free(temp);
    temp = NULL;
    free(index);
    index = NULL;
}

//����SGP_GetMatrixTempPoints
//24 ��ȡȫͼ��Χ���¶Ⱦ���
TEST_F(SgpTest, 24_getMaxtrix_all)
{
    float* output = new float[640 * 512];
    memset(output, 0x00, 640 * 512 * sizeof(float));
    SGP_RECT rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 640;
    rect.h = 512;
    const int  length = rect.w * rect.h;
    int ret = SGP_GetMatrixTempPoints(handle, output, length, rect);
    EXPECT_EQ(ret, SGP_OK) << "24_getMaxtrix_all fail" << endl;
    /*cout << "��ȡ�ɹ�" << endl;
    for (int i = 0; i < length; i++)
    {
        cout << output[i] << endl;
    }*/
    delete[] output;
    output = nullptr;
}

//25 ��ȡָ����Χ���¶Ⱦ���
TEST_F(SgpTest, 25_getMaxtrix_all_region)
{
    float* output = new float[10000];
    memset(output, 0x00, 10000 * sizeof(float));
    SGP_RECT rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 100;
    rect.h = 100;
    const int  length = rect.w * rect.h;
    int ret = SGP_GetMatrixTempPoints(handle, output, length, rect);
    EXPECT_EQ(ret, SGP_OK) << "25_getMaxtrix_all_region fail" << endl;
    /*cout << "��ȡ�ɹ�" << endl;
    for (int i = 0; i < length; i++)
    {
        cout << output[i] << endl;
    }*/
    delete[] output;
    output = nullptr;
}

//26 ��������handle
//TEST_F(SgpTest, 26��������handle)
//{
//    float* output = new float[640 * 512];
//    SGP_RECT rect;
//    rect.x = 0;
//    rect.y = 0;
//    rect.w = 100;
//    rect.h = 100;
//    const int  length = rect.w * rect.h;
//    int ret = SGP_GetMatrixTempPoints(123, output, length, rect);
//    EXPECT_EQ(ret, SGP_OK) << "26 ��������handleʧ��" << endl;
//    /*cout << "��ȡ�ɹ�" << endl;
//    for (int i = 0; i < length; i++)
//    {
//        cout << output[i] << endl;
//    }*/
//    delete[] output;
//    output = nullptr;
//}

//27 handle����NULL
TEST_F(SgpTest, 27_handle_NULL)
{
    float* output = new float[10000];
    memset(output, 0x00, 10000 * sizeof(float));
    SGP_RECT rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 100;
    rect.h = 100;
    const int  length = rect.w * rect.h;
    int ret = SGP_GetMatrixTempPoints(NULL, output, length, rect);
    EXPECT_EQ(ret, SGP_ERR) << "27_handle_NULL fail" << endl;
    /*cout << "��ȡ�ɹ�" << endl;
    for (int i = 0; i < length; i++)
    {
        cout << output[i] << endl;
    }*/
    delete[] output;
    output = nullptr;
}

//28 �������output=NULL
TEST_F(SgpTest, 28_output_NULL)
{
    float* output = new float[10000];
    memset(output, 0x00, 10000 * sizeof(float));
    SGP_RECT rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 100;
    rect.h = 100;
    const int  length = rect.w * rect.h;
    int ret = SGP_GetMatrixTempPoints(handle, NULL, length, rect);
    EXPECT_EQ(ret, SGP_ERR) << "28_output_NULL fail" << endl;
    /*cout << "��ȡ�ɹ�" << endl;
    for (int i = 0; i < length; i++)
    {
        cout << output[i] << endl;
    }*/
    delete[] output;
    output = nullptr;
}

//29 X+W����Χ
TEST_F(SgpTest, 29_XW_overRange)
{
    float* output = new float[10000];
    memset(output, 0x00, 10000 * sizeof(float));
    SGP_RECT rect;
    rect.x = 541;
    rect.y = 0;
    rect.w = 100;
    rect.h = 100;
    const int  length = rect.w * rect.h;
    int ret = SGP_GetMatrixTempPoints(handle, output, length, rect);
    EXPECT_EQ(ret, SGP_ERR_10002) << "29_XW_overRange fail" << endl;
    /*cout << "��ȡ�ɹ�" << endl;
    for (int i = 0; i < length; i++)
    {
        cout << output[i] << endl;
    }*/
    delete[] output;
    output = nullptr;
}

//30 Y+H����Χ
TEST_F(SgpTest, 30_YH_overRange)
{
    float* output = new float[10000];
    memset(output, 0x00, 10000 * sizeof(float));
    SGP_RECT rect;
    rect.x = 0;
    rect.y = 413;
    rect.w = 100;
    rect.h = 100;
    const int  length = rect.w * rect.h;
    int ret = SGP_GetMatrixTempPoints(handle, output, length, rect);
    EXPECT_EQ(ret, SGP_ERR_10002) << "30_YH_overRange fail" << endl;
    /*cout << "��ȡ�ɹ�" << endl;
    for (int i = 0; i < length; i++)
    {
        cout << output[i] << endl;
    }*/
    delete[] output;
    output = nullptr;
}

//31 ��ȡȫ�֡���������ʵʱ�¶�
TEST_F(SgpTest, 31_getAllTemp)
{
    SGP_ANALYTIC_TEMPS array;
    memset(&array, 0x00, sizeof(array));
    int ret = SGP_GetAnalyticObjectsTemp(handle, &array);
    ASSERT_EQ(ret, SGP_OK) << "31_getAllTemp fail" << endl;
    cout << "��ȡ�ɹ���" << endl;
    cout << "ȫ�������:" << array.global_max_temp << endl;
    cout << "ȫ�������:" << array.global_min_temp << endl;
    cout << "ȫ��ƽ����:" << array.global_avg_temp << endl;
    cout << "�����������:" << array.analytic_num << endl;
    cout << endl;
    if (array.analytic_num > 0)
    {
        for (int i = 0; i < array.analytic_num; i++)
        {
            cout << "��" << i + 1 << "����������" << endl;
            cout << "��������ID��" << array.analytic[i].rule_id << endl;
            cout << "�����������ƣ�" << array.analytic[i].rule_name << endl;
            cout << "�����������ͣ�" << array.analytic[i].type << endl;
            cout << "�����:" << array.analytic[i].max_temp << endl;
            cout << "�����:" << array.analytic[i].min_temp << endl;
            cout << "ƽ����:" << array.analytic[i].avg_temp << endl;
            cout << endl;
        }
    }
    else { cout << "�޷�������" << endl; }
}

//32 ��ȡУ����Ϣ
TEST_F(SgpTest, 32_getMeasureTemp)
{
    SGP_MEASURE_TEMP_INFO output;
    int ret = SGP_GetMeasureTempInfo(handle, output);
    ASSERT_EQ(ret, SGP_OK) << "32_getMeasureTemp fail" << endl;
    cout << "��ȡ�ɹ���" << endl;
    cout << "ʵʱ�����£�" << output.realshuttertemp << endl;
    cout << "�ϴο����£�" << output.lastshuttertemp << endl;
    cout << "ʵʱ�����£�" << output.realmirrortemp << endl;
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    //::testing::GTEST_FLAG(filter) = "SgpTest.19_all_points_getTemp";
    return RUN_ALL_TESTS();
}