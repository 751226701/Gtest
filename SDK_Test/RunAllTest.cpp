#include "SDK_TEST.h"
using namespace std;


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
        const char* server = "192.168.21.4";
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

//class SgpTest : public testing::Test
//{
//public:
//    static SGP_HANDLE handle;
//
//    static void SetUpTestCase()
//    {
//        handle = SGP_InitDevice();
//        ASSERT_NE(handle, 0) << "SGP_InitDevice failed!" << endl;
//
//        const char* server = "192.168.21.152";
//        const char* username = "root";
//        const char* password = "guide123";
//        int port = 80;
//        int retl = SGP_Login(handle, server, username, password, port);
//        ASSERT_EQ(retl, SGP_OK) << "SGP_Login failed" << endl;
//    }
//
//    static void TearDownTestCase()
//    {
//        int retq = SGP_Logout(handle);
//        EXPECT_EQ(retq, SGP_OK) << "SGP_Logout failed" << endl;
//
//        SGP_UnInitDevice(handle);
//    }
//
//    void SetUp() override
//    {
//        
//    }
//
//    void TearDown() override
//    {
//        
//    }
//};
//SGP_HANDLE SgpTest::handle;



//01.�޸�����
TEST_F(SgpTest, 001_ChangePassword)
{
    const char* username = "admin";
    const char* oldpassword = "admin123";
    const char* newpassword = "admin567";
    int ret = SGP_ChangePassword(handle, username, oldpassword, newpassword);
    EXPECT_EQ(ret, SGP_OK) << "SGP_ChangePassword failed" << endl;
}

//02.��������
TEST_F(SgpTest, 002_ResetPassword)
{
    const char* usernames = "admin";
    int ret = SGP_ResetPassword(handle, usernames);
    EXPECT_EQ(ret, SGP_OK) << "SGP_ResetPassword failed" << endl;
}

//03.��ȡ�û���Ϣ
TEST_F(SgpTest, 003_GetGeneralInfo)
{
    SGP_GENERAL_INFO info;
    memset(&info, 0, sizeof(info));
    int ret = SGP_GetGeneralInfo(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetGeneralInfo failed" << endl;
    cout << "��ȡ��ͨ����ϢΪ��" << endl;
    cout << "ϵͳʱ��Ϊ��" << info.datetime << endl;
    cout << "����ģ��Ŀ�Ϊ��" << info.ir_model_w << endl;
    cout << "����ģ��ĸ�Ϊ��" << info.ir_model_h << endl;
    cout << "����ͨ�������Ϊ��" << info.ir_output_w << endl;
    cout << "����ͨ�������Ϊ��" << info.ir_output_h << endl;
    cout << "������������ַΪ��" << info.ir_rtsp_url << endl;
    cout << "���·�Χ����Ϊ��" << info.range_num << endl;
}

//04.��ȡ�����¶�
TEST_F(SgpTest, 004_GetPointTemp)
{
    int x = 1;
    int y = 1;
    float output = 0.0f;
    int ret = SGP_GetPointTemp(handle, x, y, &output);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetPointTemp failed xy" << endl;
    cout <<  "��ȡ�ĵ�һ�����¶�Ϊ��" << output << endl;

    int x1 = 640;
    int y1 = 512;
    float output1 = 0.0f;
    int ret1 = SGP_GetPointTemp(handle, x1, y1, &output);
    ASSERT_EQ(ret1, SGP_OK) << "SGP_GetPointTemp failed x1y1" << endl << endl;
    cout << "��ȡ�����һ�����¶�Ϊ��" << output << endl;
}

//05.��ȡ���������¶�
TEST_F(SgpTest, 005_GetAnalyticObjectsTemp)
{
    SGP_ANALYTIC_TEMPS array;
    memset(&array, 0x00, sizeof(array));
    int ret = SGP_GetAnalyticObjectsTemp(handle, &array);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetAnalyticObjectsTemp failed" << endl;
    if (array.analytic_num > 0)
    {
        for (int i = 0; i < array.analytic_num; i++)
        {
            cout << "��ȡ���������¶ȳɹ�,��ȡ����������Ϣ���£�" << endl;
            cout << "�����������Ϊ��" << array.analytic_num << endl;
            cout << "��������Ĺ���IDΪ��" << array.analytic[i].rule_id << endl;
            cout << "��������Ĺ�������Ϊ��" << array.analytic[i].rule_name << endl;
            cout << "�������������Ϊ��" << array.analytic[i].type << endl;
            cout << "�������������¶�Ϊ��" << array.analytic[i].max_temp << endl;
            cout << "���������ƽ���¶�Ϊ��" << array.analytic[i].avg_temp << endl;
            cout << "�������������¶�Ϊ��" << array.analytic[i].min_temp << endl;
            cout << endl;
        }
    }
    else { cout << "�����������Ϊ��0" << endl; };
}

//06.��ȡ�¶Ⱦ���
TEST_F(SgpTest, 006_GetImageTemps)
{
    SGP_GENERAL_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetGeneralInfo(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetGeneralInfo failed" << endl;
    
    int height = info.ir_model_h;
    int width = info.ir_model_w;
    int length = height * width;
    int type = 1;
    float* output = (float*)calloc(length, sizeof(float));
    if (output != NULL)
    {
        ret = SGP_GetImageTemps(handle, output, length * 4, type);
    }
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetImageTemps failed" << endl;
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

    cout << "��ȡ�������Ϊ��" <<  max << endl;
    cout << "��ȡ�������Ϊ��" <<  min << endl;
    cout << "��ȡ��ƽ����Ϊ��" <<  sum / length << endl;
    free(output);
    output = NULL;
}

//07.��ȡ��Ļ��ͼ
TEST_F(SgpTest, 007_GetScreenCapture)
{
    SGP_IMAGE_TYPE type = SGP_IR_IMAGE;
    char path[] = "./screencap.jpg";
    int ret = SGP_GetScreenCapture(handle, type, path);
    EXPECT_EQ(ret, SGP_OK) << "SGP_GetScreenCapture failed" << endl;
}

//08.��ȡ��ͼ
TEST_F(SgpTest, 008_GetHeatMap)
{
    const char* path = "./screenpic.jpg";
    int ret = SGP_GetHeatMap(handle, path);
    EXPECT_EQ(ret, SGP_OK) << "SGP_GetHeatMap failed" << endl;
}

//09.��ȡ��ѹ��ͼ
TEST_F(SgpTest, 009_GetFirHeatMap)
{
    const char* path = "./screenpic.fir";
    int ret = SGP_GetFirHeatMap(handle, path);
    EXPECT_EQ(ret, SGP_OK) << "SGP_GetFirHeatMap failed" << endl;
}

//10.��ȡ��Ļ��ͼ����
TEST_F(SgpTest, 010_GetScreenCaptureCache)
{
    int input_length = 1024 * 1024 * 10;
    int output_length = 0;
    SGP_IMAGE_TYPE type = SGP_IR_IMAGE;
    char* input = (char*)calloc(input_length, sizeof(char));
    if (input != NULL)
    {
        int ret = SGP_GetScreenCaptureCache(handle, type, input, input_length,&output_length);
        ASSERT_EQ(ret, SGP_OK) << "SGP_GetScreenCaptureCache failed" << endl;
        ofstream outputFile("screenPicCache.bin", std::ios::binary);
        if (outputFile.is_open()) 
        {
            outputFile.write(input, output_length);
            outputFile.close();
            cout << "��ȡ��Ļ�ػ���ͼ�ɹ���������Ϊ screenshot.bin" << endl;
        }
        else {cout << "�޷����ļ��Ա����ͼ����" << endl;}
    }
    free(input);
    input = NULL;
}

//11.��ȡ��ͼ����
TEST_F(SgpTest, 011_GetHeatMapCache)
{
    int input_length = 1024 * 1024 * 10;
    int output_length = 0;
    char* input = (char*)calloc(input_length, sizeof(char));
    if (input != NULL)
    {
        int ret = SGP_GetHeatMapCache(handle, input, input_length, &output_length);
        ASSERT_EQ(ret, SGP_OK) << "SGP_GetHeatMapCache failed" << endl;
        ofstream outputFile("heatMapCache.bin", std::ios::binary);
        if (outputFile.is_open()) 
        {
            outputFile.write(input, output_length);
            outputFile.close();
            cout << "��ȡ��ͼ����ɹ���������Ϊ heatMapCache.bin" << endl;
        }
        else {cout << "�޷����ļ��Ա�����ͼ����" << endl;}
    }
    free(input);
    input = NULL;
}

//12.��ȡ��ѹ��ͼ����
TEST_F(SgpTest, 012_GetFirHeatMapCache)
{
    int input_length = 1024 * 1024 * 10;
    int output_length = 0;
    char* input = (char*)calloc(input_length, sizeof(char));
    if (input != NULL)
    {
        int ret = SGP_GetFirHeatMapCache(handle, input, input_length, &output_length);
        ASSERT_EQ(ret, SGP_OK) << "SGP_GetFirHeatMapCache failed" << endl;
        ofstream outputFile("firHeatMapCache.bin", std::ios::binary);
        if (outputFile.is_open()) 
        {
            outputFile.write(input, output_length);
            outputFile.close();
            cout << "��ȡ��ѹ��ͼ����ɹ���������Ϊ firHeatMapCache.bin" << endl;
        }
        else {cout << "�޷����ļ��Ա����ѹ��ͼ����" << endl;}
    }
    free(input);
    input = NULL;
}

//13.��ʼ¼��
TEST_F(SgpTest, 013_Record)
{
    int record = 1;
    int record_stream = 2;
    int ret = SGP_Record(handle, record, record_stream);
    EXPECT_EQ(ret, SGP_OK) << "SGP_Record failed" << endl;
}

//14.ֹͣ¼��
TEST_F(SgpTest, 014_StopRecord)
{
    int record = 2;
    int record_stream = 2;
    int ret = SGP_Record(handle, record, record_stream);
    EXPECT_EQ(ret, SGP_OK) << "SGP_StopRecord failed" << endl;
}

//15.����ȫ���¶Ȳ���
TEST_F(SgpTest, 015_SetThermometryParam)
{
    SGP_THERMOMETRY_PARAM info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetThermometryParam(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetThermometryParam failed" << endl;
    
    info.color_bar = 12;  //ɫ��
    info.color_show = 1;  //ɫ����ʾ
    info.flag = 1;        //���¿���
    info.mod_temp = 1;    //�¶�����
    info.ambient = 22;    //�����¶�
    info.atmo_trans = 0.2;//����͸����
    info.dist = 10;      //����
    info.emiss = 0.5;     //������
    info.emiss_mode = 2;  //����������
    info.gear = 0;        //���·�Χ
    info.humi = 66;       //�¶ȷ�Χ
    info.ref_temp = 23;   //�����¶�
    strcpy(info.show_desc, "123456"); //��ʾ�ַ���
    info.show_mode = 7;   //�¶���ʾ����
    info.show_string = 5; //�ַ�����ʾλ��
    info.opti_trans = 0.2;//��ѧ͸����
    ret = SGP_SetThermometryParam(handle, info);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetThermometryParam failed" << endl;
}

//16.��ȡȫ���¶Ȳ���
TEST_F(SgpTest, 016_GetThermometryParam)
{
    SGP_THERMOMETRY_PARAM info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetThermometryParam(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetThermometryParam failed" << endl;
    cout << "���سɹ�,ȫ�ֲ��²�����Ϣ���£�" << endl;
    cout << "�����¶�Ϊ��  " << info.ambient << endl;
    cout << "����͸����Ϊ��" << info.atmo_trans << endl;
    cout << "ɫ����Ϊ��    " << info.color_bar << endl;
    cout << "����Ϊ��      " << info.dist << endl;
    cout << "������Ϊ��    " << info.emiss << endl;
    cout << "����������Ϊ��" << info.emiss_mode << endl;
    cout << "ʪ��Ϊ��      " << info.humi << endl;
    cout << "��ѧ͸����Ϊ��" << info.opti_trans << endl;
    cout << "�ַ�����ʾΪ��" << info.show_desc << endl;
}

//17.����ȫ�ֲ��¿���-��
TEST_F(SgpTest, 017_SetThermometryFlag_OFF)
{
    int flag = 0;
    int ret = SGP_SetThermometryFlag(handle, flag);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetThermometryFlag failed" << endl;
}

//18.����ȫ�ֲ��¿���-��
TEST_F(SgpTest, 018_SetThermometryFlag_ON)
{
    int flag = 1;
    int ret = SGP_SetThermometryFlag(handle, flag);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetThermometryFlag failed" << endl;
}

//19.����ɫ����1
TEST_F(SgpTest, 019_SetColorBar_1)
{
    int colorbar = 1;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar1 failed" << endl;
}

//20.����ɫ����2
TEST_F(SgpTest, 020_SetColorBar_2)
{
    int colorbar = 2;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar2 failed" << endl;
}

//21.����ɫ����3
TEST_F(SgpTest, 021_SetColorBar_3)
{
    int colorbar = 3;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar3 failed" << endl;
}

//22.����ɫ����4
TEST_F(SgpTest, 022_SetColorBar_4)
{
    int colorbar = 4;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar4 failed" << endl;
}

//23.����ɫ����5
TEST_F(SgpTest, 023_SetColorBar_5)
{
    int colorbar = 5;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar5 failed" << endl;
}

//24.����ɫ����6
TEST_F(SgpTest, 024_SetColorBar_6)
{
    int colorbar = 6;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar6 failed" << endl;
}

//25.����ɫ����7
TEST_F(SgpTest, 025_SetColorBar_7)
{
    int colorbar = 7;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar7 failed" << endl;
}

//26.����ɫ����8
TEST_F(SgpTest, 026_SetColorBar_8)
{
    int colorbar = 8;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar8 failed" << endl;
}

//27.����ɫ����9
TEST_F(SgpTest, 027_SetColorBar_9)
{
    int colorbar = 9;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar9 failed" << endl;
}

//28.����ɫ����10
TEST_F(SgpTest, 028_SetColorBar_10)
{
    int colorbar = 10;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar10 failed" << endl;
}

//29.����ɫ����11
TEST_F(SgpTest, 029_SetColorBar_11)
{
    int colorbar = 11;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar11 failed" << endl;
}

//30.����ɫ����12
TEST_F(SgpTest, 030_SetColorBar_12)
{
    int colorbar = 12;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar12 failed" << endl;
}

//31.����ɫ����13
TEST_F(SgpTest, 031_SetColorBar_13)
{
    int colorbar = 13;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar13 failed" << endl;
}

//32.����ɫ����14
TEST_F(SgpTest, 032_SetColorBar_14)
{
    int colorbar = 14;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar14 failed" << endl;
}

//33.����ɫ����15
TEST_F(SgpTest, 033_SetColorBar_15)
{
    int colorbar = 15;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar15 failed" << endl;
}

//34.����ɫ����16
TEST_F(SgpTest, 034_SetColorBar_16)
{
    int colorbar = 16;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar16 failed" << endl;
}

//35.����ɫ����17
TEST_F(SgpTest, 035_SetColorBar_17)
{
    int colorbar = 17;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar17 failed" << endl;
}

//36.����ɫ����18
TEST_F(SgpTest, 036_SetColorBar_18)
{
    int colorbar = 18;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar18 failed" << endl;
}

//37.����ɫ����19
TEST_F(SgpTest, 037_SetColorBar_19)
{
    int colorbar = 19;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar19 failed" << endl;
}

//38.����ɫ����20
TEST_F(SgpTest, 038_SetColorBar_20)
{
    int colorbar = 20;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar20 failed" << endl;
}

//39.����ɫ����21
TEST_F(SgpTest, 039_SetColorBar_21)
{
    int colorbar = 21;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar21 failed" << endl;
}

//40.����ɫ����22
TEST_F(SgpTest, 040_SetColorBar_22)
{
    int colorbar = 22;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar22 failed" << endl;
}

//41.����ɫ����23
TEST_F(SgpTest, 041_SetColorBar_23)
{
    int colorbar = 23;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar23 failed" << endl;
}

//42.����ɫ����24
TEST_F(SgpTest, 042_SetColorBar_24)
{
    int colorbar = 24;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar24 failed" << endl;
}

//43.����ɫ����25
TEST_F(SgpTest, 043_SetColorBar_25)
{
    int colorbar = 25;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar25 failed" << endl;
}

//44.����ɫ����26
TEST_F(SgpTest, 044_SetColorBar_26)
{
    int colorbar = 26;
    int ret = SGP_SetColorBar(handle, colorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBar26 failed" << endl;
}

//45.����ɫ����ʾ-��
TEST_F(SgpTest, 045_SetColorBarShow_OFF)
{
    int showcolorbar = 0;
    int ret = SGP_SetColorBarShow(handle, showcolorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBarShowON failed" << endl;
}

//46.����ɫ����ʾ-��
TEST_F(SgpTest, 046_SetColorBarShow_ON)
{
    int showcolorbar = 1;
    int ret = SGP_SetColorBarShow(handle, showcolorbar);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColorBarShowOFF failed" << endl;
}

//47.�����¶���ʾ����1
TEST_F(SgpTest, 047_SetTempShowMode_1)
{
    int showtype = 1;
    int ret = SGP_SetTempShowMode(handle, showtype);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetTempShowMode_1 failed" << endl;
}

//48.�����¶���ʾ����2
TEST_F(SgpTest, 048_SetTempShowMode_2)
{
    int showtype = 2;
    int ret = SGP_SetTempShowMode(handle, showtype);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetTempShowMode_2 failed" << endl;
}

//49.�����¶���ʾ����3
TEST_F(SgpTest, 049_SetTempShowMode_3)
{
    int showtype = 3;
    int ret = SGP_SetTempShowMode(handle, showtype);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetTempShowMode_3 failed" << endl;
}

//50.�����¶���ʾ����4
TEST_F(SgpTest, 050_SetTempShowMode_4)
{
    int showtype = 4;
    int ret = SGP_SetTempShowMode(handle, showtype);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetTempShowMode_4 failed" << endl;
}

//51.�����¶���ʾ����5
TEST_F(SgpTest, 051_SetTempShowMode_5)
{
    int showtype = 5;
    int ret = SGP_SetTempShowMode(handle, showtype);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetTempShowMode_5 failed" << endl;
}

//52.�����¶���ʾ����6
TEST_F(SgpTest, 052_SetTempShowMode_6)
{
    int showtype = 6;
    int ret = SGP_SetTempShowMode(handle, showtype);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetTempShowMode_6 failed" << endl;
}

//53.�����¶���ʾ����7
TEST_F(SgpTest, 053_SetTempShowMode_7)
{
    int showtype = 7;
    int ret = SGP_SetTempShowMode(handle, showtype);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetTempShowMode_7 failed" << endl;
}

//54.�����ַ�������
TEST_F(SgpTest, 054_SetStringShow)
{
    int type = 5;
    const char* dateshow = "123";
    int ret = SGP_SetStringShow(handle, type, dateshow);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetStringShow failed" << endl;
}

//55.���÷��������¶���ʾ����1
TEST_F(SgpTest, 055_SetThermometryRuleShowMode_1)
{
    int showtype = 1;
    int ret = SGP_SetThermometryRuleShowMode(handle, showtype);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetThermometryRuleShowMode_1 failed" << endl;
}

//56.���÷��������¶���ʾ����2
TEST_F(SgpTest, 056_SetThermometryRuleShowMode_2)
{
    int showtype = 2;
    int ret = SGP_SetThermometryRuleShowMode(handle, showtype);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetThermometryRuleShowMode_2 failed" << endl;
}

//57.���÷��������¶���ʾ����3
TEST_F(SgpTest, 057_SetThermometryRuleShowMode_3)
{
    int showtype = 3;
    int ret = SGP_SetThermometryRuleShowMode(handle, showtype);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetThermometryRuleShowMode_3 failed" << endl;
}

//58.���÷��������¶���ʾ����4
TEST_F(SgpTest, 058_SetThermometryRuleShowMode_4)
{
    int showtype = 4;
    int ret = SGP_SetThermometryRuleShowMode(handle, showtype);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetThermometryRuleShowMode_4 failed" << endl;
}

//59.���÷��������¶���ʾ����5
TEST_F(SgpTest, 059_SetThermometryRuleShowMode_5)
{
    int showtype = 5;
    int ret = SGP_SetThermometryRuleShowMode(handle, showtype);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetThermometryRuleShowMode_5 failed" << endl;
}

//60.���÷��������¶���ʾ����6
TEST_F(SgpTest, 060_SetThermometryRuleShowMode_6)
{
    int showtype = 6;
    int ret = SGP_SetThermometryRuleShowMode(handle, showtype);
    EXPECT_EQ(ret, SGP_ERR) << "SGP_SetThermometryRuleShowMode_6 failed" << endl;
}

//61.���÷��������¶���ʾ����7
TEST_F(SgpTest, 061_SetThermometryRuleShowMode_7)
{
    int showtype = 7;
    int ret = SGP_SetThermometryRuleShowMode(handle, showtype);
    EXPECT_EQ(ret, SGP_ERR) << "SGP_SetThermometryRuleShowMode_7 failed" << endl;
}

//62.��ӷ�������-��
TEST_F(SgpTest, 062_AddThermometryRule_Point)
{
    SGP_RULE rulePoint;
    memset(&rulePoint, 0x00, sizeof(SGP_RULE));
    rulePoint.alarm_condition = 1;
    rulePoint.alarm_flag = 1;
    rulePoint.alarm_time = 30;
    rulePoint.alarm_type = 1;
    rulePoint.alarm_interal = 30;
    rulePoint.avg_temp = 30;
    rulePoint.flag = 1;
    rulePoint.high_temp = 35;
    rulePoint.low_temp = 28;
    rulePoint.show_type = 1;
    rulePoint.points_num = 1; //�������1
    rulePoint.points[0].x = 200;
    rulePoint.points[0].y = 200;
    strcpy(rulePoint.rule_name, "Point");
    rulePoint.show_location = 1;
    rulePoint.temp_mod = 1;
    rulePoint.type = 1;  //������1
    rulePoint.atmo_trans = 0.9;
    rulePoint.dist = 2;
    rulePoint.emiss = 0.8;
    rulePoint.emiss_mode = 1;
    rulePoint.humi = 80;
    rulePoint.opti_trans = 1;
    rulePoint.ref_temp = 25;
    int ret = SGP_AddThermometryRule(handle, rulePoint);
    EXPECT_EQ(ret, SGP_OK) << "SGP_AddThermometryRule_Point failed" << endl;
}

//63.��ӷ�������-��
TEST_F(SgpTest, 063_AddThermometryRule_Line)
{
    SGP_RULE rulePoint;
    memset(&rulePoint, 0x00, sizeof(SGP_RULE));
    rulePoint.alarm_condition = 1;
    rulePoint.alarm_flag = 1;
    rulePoint.alarm_time = 30;
    rulePoint.alarm_type = 1;
    rulePoint.alarm_interal = 30;
    rulePoint.avg_temp = 30;
    rulePoint.flag = 1;
    rulePoint.high_temp = 35;
    rulePoint.low_temp = 28;
    rulePoint.show_type = 1;
    rulePoint.points_num = 2; //�������1
    rulePoint.points[0].x = 250;
    rulePoint.points[0].y = 250;
    rulePoint.points[1].x = 300;
    rulePoint.points[1].y = 300;
    strcpy(rulePoint.rule_name, "Line");
    rulePoint.show_location = 1;
    rulePoint.temp_mod = 1;
    rulePoint.type = 2;  //������2
    rulePoint.atmo_trans = 0.9;
    rulePoint.dist = 2;
    rulePoint.emiss = 0.8;
    rulePoint.emiss_mode = 1;
    rulePoint.humi = 80;
    rulePoint.opti_trans = 1;
    rulePoint.ref_temp = 25;
    int ret = SGP_AddThermometryRule(handle, rulePoint);
    EXPECT_EQ(ret, SGP_OK) << "SGP_AddThermometryRule_Line failed" << endl;
}

//64.��ӷ�������-����
TEST_F(SgpTest, 064_AddThermometryRule_Rectangle)
{
    SGP_RULE rulePoint;
    memset(&rulePoint, 0x00, sizeof(SGP_RULE));
    rulePoint.alarm_condition = 1;
    rulePoint.alarm_flag = 1;
    rulePoint.alarm_time = 30;
    rulePoint.alarm_type = 1;
    rulePoint.alarm_interal = 30;
    rulePoint.avg_temp = 30;
    rulePoint.flag = 1;
    rulePoint.high_temp = 35;
    rulePoint.low_temp = 28;
    rulePoint.show_type = 1;
    rulePoint.points_num = 4; //�������1
    rulePoint.points[0].x = 362;
    rulePoint.points[0].y = 90;
    rulePoint.points[1].x = 497;
    rulePoint.points[1].y = 90;
    rulePoint.points[2].x = 497;
    rulePoint.points[2].y = 175;
    rulePoint.points[3].x = 362;
    rulePoint.points[3].y = 175;
    strcpy(rulePoint.rule_name, "Rectangle");
    rulePoint.show_location = 1;
    rulePoint.temp_mod = 1;
    rulePoint.type = 3;  //������3
    rulePoint.atmo_trans = 0.9;
    rulePoint.dist = 2;
    rulePoint.emiss = 0.8;
    rulePoint.emiss_mode = 1;
    rulePoint.humi = 80;
    rulePoint.opti_trans = 1;
    rulePoint.ref_temp = 25;
    int ret = SGP_AddThermometryRule(handle, rulePoint);
    EXPECT_EQ(ret, SGP_OK) << "SGP_AddThermometryRule_Rectangle failed" << endl;
}

//65.��ӷ�������-Բ
TEST_F(SgpTest, 065_AddThermometryRule_Circle)
{
    SGP_RULE rulePoint;
    memset(&rulePoint, 0x00, sizeof(SGP_RULE));
    rulePoint.alarm_condition = 1;
    rulePoint.alarm_flag = 1;
    rulePoint.alarm_time = 30;
    rulePoint.alarm_type = 1;
    rulePoint.alarm_interal = 30;
    rulePoint.avg_temp = 30;
    rulePoint.flag = 1;
    rulePoint.high_temp = 35;
    rulePoint.low_temp = 28;
    rulePoint.show_type = 1;
    rulePoint.points_num = 4; //�������1
    rulePoint.points[0].x = 428;
    rulePoint.points[0].y = 308;
    rulePoint.points[1].x = 478;
    rulePoint.points[1].y = 254;
    rulePoint.points[2].x = 529;
    rulePoint.points[2].y = 308;
    rulePoint.points[3].x = 478;
    rulePoint.points[3].y = 362;
    strcpy(rulePoint.rule_name, "Circle");
    rulePoint.show_location = 1;
    rulePoint.temp_mod = 1;
    rulePoint.type = 5;  //������5
    rulePoint.atmo_trans = 0.9;
    rulePoint.dist = 2;
    rulePoint.emiss = 0.8;
    rulePoint.emiss_mode = 1;
    rulePoint.humi = 80;
    rulePoint.opti_trans = 1;
    rulePoint.ref_temp = 25;
    int ret = SGP_AddThermometryRule(handle, rulePoint);
    EXPECT_EQ(ret, SGP_OK) << "SGP_AddThermometryRule_Rectangle_Circle failed" << endl;
}

//66.��ӷ�������-�����
TEST_F(SgpTest, 066_AddThermometryRule_Polygon)
{
    SGP_RULE rulePoint;
    memset(&rulePoint, 0x00, sizeof(SGP_RULE));
    rulePoint.alarm_condition = 1;
    rulePoint.alarm_flag = 1;
    rulePoint.alarm_time = 30;
    rulePoint.alarm_type = 1;
    rulePoint.alarm_interal = 30;
    rulePoint.avg_temp = 30;
    rulePoint.flag = 1;
    rulePoint.high_temp = 35;
    rulePoint.low_temp = 28;
    rulePoint.show_type = 1;
    rulePoint.points_num = 6; //�������1
    rulePoint.points[0].x = 107;
    rulePoint.points[0].y = 330;
    rulePoint.points[1].x = 186;
    rulePoint.points[1].y = 329;
    rulePoint.points[2].x = 190;
    rulePoint.points[2].y = 378;
    rulePoint.points[3].x = 194;
    rulePoint.points[3].y = 429;
    rulePoint.points[4].x = 131;
    rulePoint.points[4].y = 433;
    rulePoint.points[5].x = 62;
    rulePoint.points[5].y = 428;
    rulePoint.points[6].x = 127;
    rulePoint.points[6].y = 382;
    strcpy(rulePoint.rule_name, "Polygon");
    rulePoint.show_location = 1;
    rulePoint.temp_mod = 1;
    rulePoint.type = 4;  //������1
    rulePoint.atmo_trans = 0.9;
    rulePoint.dist = 2;
    rulePoint.emiss = 0.8;
    rulePoint.emiss_mode = 1;
    rulePoint.humi = 80;
    rulePoint.opti_trans = 1;
    rulePoint.ref_temp = 25;
    int ret = SGP_AddThermometryRule(handle, rulePoint);
    EXPECT_EQ(ret, SGP_OK) << "SGP_AddThermometryRule_Rectangle_Polygon failed" << endl;
}

//67.��ȡ��������
TEST_F(SgpTest, 067_GetThermometryRule)
{
    SGP_RULE_ARRAY array;
    memset(&array, 0x00, sizeof(array));
    int ret = SGP_GetThermometryRule(handle, &array);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetThermometryRule failed" << endl;
    cout << "�����������Ϊ��" << array.rule_num << endl;
    for (int i = 0; i < array.rule_num; i++)
    {
        cout << "��" << i + 1 << "������������Ϣ��" << endl;
        cout << "����͸����Ϊ��" << array.rule[i].atmo_trans << endl;
        cout << "����Ϊ��" << array.rule[i].dist << endl;
        cout << "IDΪ��" << array.rule[i].id << endl;
        cout << "��������Ϊ��" << array.rule[i].alarm_condition << endl;
        cout << "�Ƿ���Ҫ������" << array.rule[i].alarm_flag << endl;
        cout << "�������ͣ�" << array.rule[i].alarm_type << endl;
        cout << "ƽ���£�" << array.rule[i].avg_temp << endl;
        cout << "�Ƿ����ã�" << array.rule[i].flag << endl;
        cout << "����������ֵ��" << array.rule[i].high_temp << endl;
        cout << "����������ֵ��" << array.rule[i].low_temp << endl;
        cout << "�������ƣ�" << array.rule[i].rule_name << endl;
        cout << "��ʾλ�ã�" << array.rule[i].show_location << endl;
        cout << "�¶���" << array.rule[i].temp_mod << endl;
        cout << "����͸���ʣ�" << array.rule[i].atmo_trans << endl;
        cout << "�����ʣ�" << array.rule[i].emiss << endl;
        cout << "���������ͣ�" << array.rule[i].emiss_mode << endl;
        cout << "ʪ�ȣ�" << array.rule[i].humi << endl;
        cout << "��ѧ͸���ʣ�" << array.rule[i].opti_trans << endl;
        cout << "�����¶ȣ�" << array.rule[i].ref_temp << endl;
        cout << endl;
    }
}

//68.���·�������
TEST_F(SgpTest, 068_UpdateThermometryRule)
{
    SGP_RULE_ARRAY array;
    memset(&array, 0x00, sizeof(array));
    int ret = SGP_GetThermometryRule(handle, &array);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetThermometryRule failed" << endl;

    SGP_RULE rule;
    memset(&rule, 0, sizeof(rule));
    memcpy(&rule, &array.rule[0], sizeof(rule));
    rule.alarm_condition = 1;
    rule.alarm_type = 1;
    rule.alarm_flag = 1;
    rule.alarm_time = 3;
    rule.high_temp = 20;
    rule.low_temp = 22;
    rule.show_type = 1;
    ret = SGP_UpdateThermometryRule(handle, rule);
    EXPECT_EQ(ret, SGP_OK) << "SGP_UpdateThermometryRule failed" << endl;
}


//69.ɾ����������
TEST_F(SgpTest, 069_DeleteThermometryRule)
{
    SGP_RULE_ARRAY array;
    memset(&array, 0x00, sizeof(array));
    int ret = SGP_GetThermometryRule(handle, &array);
    EXPECT_EQ(ret, SGP_OK) << "SGP_GetThermometryRule failed" << endl;
    if (array.rule_num > 0)
    {
        int ret = SGP_DeleteThermometryRule(handle, array.rule[0].id);
        EXPECT_EQ(ret, SGP_OK) << "SGP_DeleteThermometryRule failed" << endl;
    }
}

//70.ɾ��ȫ����������
TEST_F(SgpTest, 070_DeleteAllThermometryRule)
{
    int ret = SGP_DeleteAllThermometryRule(handle);
    EXPECT_EQ(ret, SGP_OK) << "SGP_DeleteAllThermometryRule failed" << endl;
}

//71.���ú���ͼ��Ч������-���ż��ʱ��3min
TEST_F(SgpTest, 071_SetIrImageEffectParam_AUTO_SHUTTER_3)
{
    SGP_IR_IMAGE_EFFECT_ENUM type = SGP_IR_AUTO_SHUTTER;
    int value = 3;
    int ret = SGP_SetIrImageEffectParam(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SetIrImageEffectParam_AUTO_SHUTTER_3 failed" << endl;
}

//72.���ú���ͼ��Ч������-����1
TEST_F(SgpTest, 072_SetIrImageEffectParam_BRIGHTNESS_1)
{
    SGP_IR_IMAGE_EFFECT_ENUM type = SGP_IR_BRIGHTNESS;
    int value = 1;
    int ret = SGP_SetIrImageEffectParam(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SetIrImageEffectParam_BRIGHTNESS_1 failed" << endl;
}

//73.���ú���ͼ��Ч������-����100
TEST_F(SgpTest, 073_SetIrImageEffectParam_BRIGHTNESS_100)
{
    SGP_IR_IMAGE_EFFECT_ENUM type = SGP_IR_BRIGHTNESS;
    int value = 100;
    int ret = SGP_SetIrImageEffectParam(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SetIrImageEffectParam_BRIGHTNESS_100 failed" << endl;
}

//74.���ú���ͼ��Ч������-�Աȶ�1
TEST_F(SgpTest, 074_SetIrImageEffectParam_CONTRAST_1)
{
    SGP_IR_IMAGE_EFFECT_ENUM type = SGP_IR_CONTRAST;
    int value = 1;
    int ret = SGP_SetIrImageEffectParam(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SetIrImageEffectParam_CONTRAST_1 failed" << endl;
}

//75.���ú���ͼ��Ч������-�Աȶ�100
TEST_F(SgpTest, 075_SetIrImageEffectParam_CONTRAST_100)
{
    SGP_IR_IMAGE_EFFECT_ENUM type = SGP_IR_CONTRAST;
    int value = 100;
    int ret = SGP_SetIrImageEffectParam(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SetIrImageEffectParam_CONTRAST_100 failed" << endl;
}

//76.���ú���ͼ��Ч������-��ת��
TEST_F(SgpTest, 076_SetIrImageEffectParam_REVERSE_ON)
{
    SGP_IR_IMAGE_EFFECT_ENUM type = SGP_IR_REVERSE;
    int value = 1;
    int ret = SGP_SetIrImageEffectParam(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SetIrImageEffectParam_REVERSE_ON failed" << endl;
}

//77.���ú���ͼ��Ч������-��ת��
TEST_F(SgpTest, 077_SetIrImageEffectParam_REVERSE_OFF)
{
    SGP_IR_IMAGE_EFFECT_ENUM type = SGP_IR_REVERSE;
    int value = 0;
    int ret = SGP_SetIrImageEffectParam(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SetIrImageEffectParam_REVERSE_ON failed" << endl;
}

//78.���ú���ͼ��Ч������-���1
TEST_F(SgpTest, 078_SetIrImageEffectParam_SHARPNESS_1)
{
    SGP_IR_IMAGE_EFFECT_ENUM type = SGP_IR_SHARPNESS;
    int value = 1;
    int ret = SGP_SetIrImageEffectParam(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SetIrImageEffectParam_SHARPNESS_1 failed" << endl;
}

//79.���ú���ͼ��Ч������-���1
TEST_F(SgpTest, 079_SetIrImageEffectParam_SHARPNESS_100)
{
    SGP_IR_IMAGE_EFFECT_ENUM type = SGP_IR_SHARPNESS;
    int value = 100;
    int ret = SGP_SetIrImageEffectParam(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SetIrImageEffectParam_SHARPNESS_100 failed" << endl;
}

//80.���ú���ͼ��Ч������-ϸ����ǿ��
TEST_F(SgpTest, 080_SetIrImageEffectParam_IEE_FLAG_ON)
{
    SGP_IR_IMAGE_EFFECT_ENUM type = SGP_IR_IEE_FLAG;
    int value = 1;
    int ret = SGP_SetIrImageEffectParam(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SetIrImageEffectParam_IEE_FLAG_ON failed" << endl;
}

//81.���ú���ͼ��Ч������-ϸ����ǿ��
TEST_F(SgpTest, 081_SetIrImageEffectParam_IEE_FLAG_OFF)
{
    SGP_IR_IMAGE_EFFECT_ENUM type = SGP_IR_IEE_FLAG;
    int value = 0;
    int ret = SGP_SetIrImageEffectParam(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SetIrImageEffectParam_IEE_FLAG_OFF failed" << endl;
}

//82.���ú���ͼ��Ч������-ϸ����ǿֵ1
TEST_F(SgpTest, 082_SetIrImageEffectParam_IEE_VALUE_1)
{
    SGP_IR_IMAGE_EFFECT_ENUM type = SGP_IR_IEE_VALUE;
    int value = 1;
    int ret = SGP_SetIrImageEffectParam(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SetIrImageEffectParam_IEE_FLAG_OFF failed" << endl;
}

//83.���ú���ͼ��Ч������-ϸ����ǿֵ100
TEST_F(SgpTest, 083_SetIrImageEffectParam_IEE_VALUE_100)
{
    SGP_IR_IMAGE_EFFECT_ENUM type = SGP_IR_IEE_VALUE;
    int value = 100;
    int ret = SGP_SetIrImageEffectParam(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SetIrImageEffectParam_IEE_FLAG_OFF failed" << endl;
}

//84.��ȡ����ͼ��Ч������
TEST_F(SgpTest, 084_GetIrImageEffectParam)
{
    SGP_IAMGE_EFFECT_PARAM_IR_CONFIG info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetIrImageEffectParam(handle, &info);
    EXPECT_EQ(ret, SGP_OK) << "SGP_GetIrImageEffectParam failed" << endl;
}

//85.����������Ϣ
TEST_F(SgpTest, 085_SetNetInfo)
{
    SGP_NET_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetNetInfo(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_SetNetInfo failed" << endl;
    if (ret == SGP_OK)
    {
        info.card = 0;
        strcpy(info.dns1, "192.168.1.168");
        strcpy(info.dns2, "192.168.1.167");
        strcpy(info.gateway, "192.168.21.1");
        strcpy(info.host_name, "qwe123");
        //strcpy(info.ipaddr, "192.168.21.152");
        strcpy(info.netmask, "255.255.252.0");
        info.mode = 0;
        ret = SGP_SetNetInfo(handle, info);
        EXPECT_EQ(ret, SGP_OK) << "SGP_SetNetInfo failed" << endl;
    }
}

//86.��ȡ������Ϣ
TEST_F(SgpTest, 086_GetNetInfo)
{
    SGP_NET_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetNetInfo(handle, &info);
    EXPECT_EQ(ret, SGP_OK) << "SGP_GetNetInfo failed" << endl;
    cout << "��ȡ������Ϣ�ɹ�����ȡ��Ϣ���£�" << endl;
    cout << "��ȡ��������Ϊ��" << info.host_name << endl;
    cout << "��ȡip��ַΪ��" << info.ipaddr << endl;
}

//87.���ö˿���Ϣ
TEST_F(SgpTest, 087_SetPortInfo)
{
    SGP_PORT_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetPortInfo(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetPortInfo failed" << endl;
    info.max_connectios = 20;
    info.http_port = 80;
    info.rtsp_port = 8888;
    info.onvif_check = 0;
    //info.tcp_port = 100;
    ret = SGP_SetPortInfo(handle, info);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetPortInfo failed" << endl;
}

//88.��ȡ�˿���Ϣ
TEST_F(SgpTest, 088_GetPortInfo)
{
    SGP_PORT_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetPortInfo(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetPortInfo failed" << endl;
    cout << "���سɹ�����ȡ�Ķ˿���Ϣ���£�" << endl;
    cout << "http�˿ں�Ϊ��\t" << info.http_port << endl;
    cout << "��������豸��Ϊ:" << info.max_connectios << endl;
    cout << "onvif���أ�\t" << info.onvif_check << endl;
    cout << "rtsp�˿ں�Ϊ��\t" << info.rtsp_port << endl;
    cout << "tcp�˿ں�Ϊ��\t" << info.tcp_port << endl;
}

//89.����¼����Ϣ
TEST_F(SgpTest, 089_SetRecordInfo)
{
    SGP_RECORD_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetRecordInfo(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetRecordInfo failed" << endl;
    info.record_interval = 10;
    info.record_max_size = 999;
    info.record_time = 10;
    ret = SGP_SetRecordInfo(handle, info);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetRecordInfo failed" << endl;
}

//90.��ȡ¼����Ϣ
TEST_F(SgpTest, 090_GetRecordInfo)
{
    SGP_RECORD_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetRecordInfo(handle, &info);
    EXPECT_EQ(ret, SGP_OK) << "SGP_GetRecordInfo failed" << endl;
    cout << "���سɹ�����ȡ�Ķ˿���Ϣ���£�" << endl;
    cout << "¼����ʱʱ�䣺\t" << info.record_interval << endl;
    cout << "���¼���ļ���С��" << info.record_max_size << endl;
    cout << "¼��ʱ���� \t" << info.record_time << endl;
}

//91.������������
TEST_F(SgpTest, 091_SetShieldArea)
{
    SGP_SHIELD_AREA_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetShieldArea(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetShieldArea failed" << endl;
    info.rect_num = 2;
    info.rect[0].x = 250;
    info.rect[0].y = 250;
    info.rect[0].w = 150;
    info.rect[0].h = 150;
    info.rect[1].x = 50;
    info.rect[1].y = 50;
    info.rect[1].w = 150;
    info.rect[1].h = 150;
    ret = SGP_SetShieldArea(handle, info);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetShieldArea failed" << endl;
}

//92.��ȡ��������
TEST_F(SgpTest, 092_GetShieldAre)
{
    SGP_SHIELD_AREA_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetShieldArea(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetShieldArea failed" << endl;
    cout << "���سɹ�����ȡ����������Ϣ���£�" << endl;
    cout << "�����������Ϊ��" << info.rect_num << endl;
    cout << "������������Ϊ��" << endl;
    for (int i = 0; i < info.rect_num; i++)
    {
        printf("��%d���������������Ϊ��\n", i + 1);
        cout << "x=" << info.rect[i].x << endl;
        cout << "y=" << info.rect[i].y << endl;
        cout << "w=" << info.rect[i].w << endl;
        cout << "h=" << info.rect[i].h << endl;
        cout << endl;
    }
}

//93.����ȫ���¶ȸ澯
TEST_F(SgpTest, 093_SetColdHotTrace)
{
    SGP_COLD_HOT_TRACE_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetColdHotTrace(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetColdHotTrace failed" << endl;
    info.high_flag = 1;
    info.high_temp = 22;
    info.low_flag = 1;
    info.low_temp = 33;
    info.capture_flag = 1;
    info.capture_stream = 2;
    info.output_flag = 1;
    info.output_hold = 15;
    info.record_flag = 1;
    info.record_stream = 2;
    info.sendmail = 1;
    info.record_delay = 200;
    info.alarm_shake = 3;
    ret = SGP_SetColdHotTrace(handle, info);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetColdHotTrace failed" << endl;
}

//94.��ȡȫ���¶ȸ澯
TEST_F(SgpTest, 094_GetColdHotTrace)
{
    SGP_COLD_HOT_TRACE_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetColdHotTrace(handle, &info);
    EXPECT_EQ(ret, SGP_OK) << "SGP_GetColdHotTrace failed" << endl;
    cout << "���سɹ�����ȡȫ���¶ȸ澯��Ϣ���£�" << endl;
    cout << "capture_flag:" << info.capture_flag << endl;
    cout << "capture_stream:" << info.capture_stream << endl;
    cout << "high_flag:" << info.high_flag << endl;
    cout << "high_temp:" << info.high_temp << endl;
    cout << "low_flag:" << info.low_flag << endl;
    cout << "low_temp:" << info.low_temp << endl;
    cout << "sendmail:" << info.sendmail << endl;
}

//95.���÷�������澯
TEST_F(SgpTest, 095_SetTempAlarm)
{
    SGP_TEMP_ALARM_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetTempAlarm(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetTempAlarm failed" << endl;
    info.alarm_flag = 1;//�Ƿ������� 1:����; 0:������
    info.capture_flag = 1;//�Ƿ��ͼ 0:��; 1:��
    info.capture_stream = 2;//��ͼ���� 0:����ͼ; 1:ֻ��ͼ�ɼ���; 2:ֻ��ͼ����; 3:��ͼ����Ϳɼ���
    info.record_flag = 1;//�Ƿ�¼�� 0:��¼��; 1:¼��
    info.record_stream = 2;//¼������ 0:��¼��; 1:ֻ¼�ƿɼ���; 2:ֻ¼�ƺ���; 3:¼�ƺ���Ϳɼ���
    info.record_delay = 150;//¼��ʱ�� 10-300s
    info.output_flag = 1;//�Ƿ��ⲿ��� 0:����� 1:���
    info.output_hold = 20;
    info.alarm_shake = 8;
    info.sendmail = 1;
    ret = SGP_SetTempAlarm(handle, info);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetTempAlarm failed" << endl;
}

//96.��ȡ��������澯
TEST_F(SgpTest, 096_GetTempAlarm)
{
    SGP_TEMP_ALARM_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetTempAlarm(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetTempAlarm failed" << endl;
    cout << "���سɹ�����ȡ��������澯��Ϣ���£�" << endl;
    cout << "alarm_flag:" << info.alarm_flag << endl;
    cout << "capture_flag:" << info.capture_flag << endl;
    cout << "capture_stream:" << info.capture_stream << endl;
    cout << "output_flag:" << info.output_flag << endl;
    cout << "output_hold:" << info.output_hold << endl;
    cout << "sendmail:" << info.sendmail << endl;
}

//97.������Ƶ����
TEST_F(SgpTest, 097_SetVideoParam)
{
    SGP_GENERAL_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetGeneralInfo(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetGeneralInfo failed" << endl;
    SGP_VIDEO_PARAM_ENUM type = SGP_IR;
    SGP_VIDEO_PARAM param;
    memset(&param, 0x00, sizeof(param));
    ret = SGP_GetVideoParam(handle, type, &param);
    param.fps = 25;
    param.gop_size = param.fps * 2;
    param.bit_size = info.ir_model_w * info.ir_model_h * param.fps * 8 * 3 / 2 / 1024 / 18;
    param.level = 1;

    ret = SGP_SetVideoParam(handle, type, param);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetVideoParam failed" << endl;
}

//98.��ȡ��Ƶ����
TEST_F(SgpTest, 098_GetVideoParam)
{
    SGP_VIDEO_PARAM_ENUM type = SGP_IR;
    SGP_VIDEO_PARAM param;
    memset(&param, 0x00, sizeof(param));
    int ret = SGP_GetVideoParam(handle, type, &param);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetVideoParam failed" << endl;
    cout << "���سɹ�����ȡ����Ƶ�������£�" << endl;
    cout << "param.bit_size=" << param.bit_size << endl;
    cout << "param.fps=" << param.fps << endl;
    cout << "param.gop_size=" << param.gop_size << endl;
    cout << "param.level=" << param.level << endl;
}

//99.���������쳣
TEST_F(SgpTest, 099_SetNetException)
{
    SGP_NET_EXCEPTION_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetNetException(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetNetException failed" << endl;

    info.flag = 1;
    info.output_flag = 1;
    info.output_hold = 20;
    ret = SGP_SetNetException(handle, info);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetNetException failed" << endl;
}

//100.��ȡ�����쳣
TEST_F(SgpTest, 100_GetNetException)
{
    SGP_NET_EXCEPTION_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetNetException(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetNetException failed" << endl;
    cout << "���سɹ�����ȡ�����쳣��Ϣ���£�" << endl;
    cout << "flag=" << info.flag << endl;
    cout << "output_flag=" << info.output_flag << endl;
    cout << "output_hold=" << info.output_hold << endl;
}

//101.���÷Ƿ�����
TEST_F(SgpTest, 101_SetAccessViolation)
{
    SGP_ACCESS_VIOLATION_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetAccessViolation(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetAccessViolation failed" << endl;

    info.allow_count = 10;
    info.flag = 1;
    info.output_flag = 1;
    info.output_hold = 12;
    info.sendmail = 1;
    ret = SGP_SetAccessViolation(handle, info);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetAccessViolation failed" << endl;
}

//102.��ȡ�Ƿ�����
TEST_F(SgpTest, 102_GetAccessViolation)
{
    SGP_ACCESS_VIOLATION_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetAccessViolation(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetAccessViolation failed" << endl;
    cout << "���سɹ�����ȡ�ķǷ�������Ϣ���£�" << endl;
    cout << "allow_count=" << info.allow_count << endl;
    cout << "flag=" << info.flag << endl;
    cout << "output_flag=" << info.output_flag << endl;
    cout << "output_hold=" << info.output_hold << endl;
    cout << "sendmail=" << info.sendmail << endl;
}

//103.�����ʼ���Ϣ
TEST_F(SgpTest, 103_SetEmilInfo)
{
    SGP_EMAIL_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetEmilInfo(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetEmilInfo failed" << endl;

    info.alarm = 1;
    info.alarm_value = 12;
    info.enclosure = 1;
    info.encry_type = 2;
    info.health = 1;
    info.health_value = 12;
    info.is_anon = 1;
    info.mailto_num = 1;
    info.smtp_port = 25;
    ret = SGP_SetEmilInfo(handle, info);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetEmilInfo failed" << endl;
}

//104.��ȡ�ʼ���Ϣ
TEST_F(SgpTest, 104_GetEmilInfo)
{
    SGP_EMAIL_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetEmilInfo(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetEmilInfo failed" << endl;

    cout << "���سɹ�����ȡ���ʼ���Ϣ���£�" << endl;
    cout << "alarm=" << info.alarm << endl;
    cout << "alarm_value=" << info.alarm_value << endl;
    cout << "enclosure=" << info.enclosure << endl;
    cout << "encry_type=" << info.encry_type << endl;
    cout << "health=" << info.health << endl;
    cout << "health_value=" << info.health_value << endl;
}

//105.�л����·�Χ
TEST_F(SgpTest, 105_SetRange)
{
    SGP_GENERAL_INFO info;
    memset(&info, 0x00, sizeof(SGP_GENERAL_INFO));
    int ret = SGP_GetGeneralInfo(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetGeneralInfo failed" << endl;

    int range = info.range_num;
    ret = SGP_SetRange(handle, range - 1);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetRange failed" << endl;
}

//106.��ȡϵͳ�汾��Ϣ
TEST_F(SgpTest, 106_GetVersionInfo)
{
    SGP_VERSION_INFO info;
    memset(&info, 0x00, sizeof(info));
    int ret = SGP_GetVersionInfo(handle, &info);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetVersionInfo failed" << endl;

    cout << "���سɹ�����ȡ��ϵͳ��ϢΪ��" << endl;
    cout << "�豸�ͺţ�" << info.model << endl;
    cout << "ϵͳ�汾��" << info.version << endl;
    cout << "���кţ�  " << info.serial << endl;
    cout << "FPGA�汾��" << info.fpga_version << endl;
    cout << "���°汾��" << info.measure_version << endl;
    cout << "SDK�汾�� " << info.sdk_version << endl;
}

//107.ͬ��ϵͳʱ��
//TEST_F(SgpTest, 107_SynchroTime)
//{
//    const char* datetime = "2022-12-11 11:11:11";
//    int ret = SGP_SynchroTime(handle, datetime);
//    EXPECT_EQ(ret, SGP_OK) << "SGP_SynchroTime failed" << endl;
//}

//108.��������
TEST_F(SgpTest, 108_ClearData)
{
    int ret = SGP_ClearData(handle);
    EXPECT_EQ(ret, SGP_OK) << "SGP_ClearData failed" << endl;
}

//109.���Ų���-�����
TEST_F(SgpTest, 109_DoShutter)
{
    SGP_SHUTTER_ENUM type = SGP_SHUTTER;
    int ret = SGP_DoShutter(handle, type);
    EXPECT_EQ(ret, SGP_OK) << "SGP_DoShutter failed" << endl;
}

//110.���Ų���-���ų���
TEST_F(SgpTest, 110_DoShutter_SGP_SHUTTER_CLOSE)
{
    SGP_SHUTTER_ENUM type = SGP_SHUTTER_CLOSE;
    int ret = SGP_DoShutter(handle, type);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SHUTTER_CLOSE failed" << endl;
}

//111.���Ų���-���ų���
TEST_F(SgpTest, 111_DoShutter_SGP_SHUTTER_OPEN)
{
    SGP_SHUTTER_ENUM type = SGP_SHUTTER_OPEN;
    int ret = SGP_DoShutter(handle, type);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SHUTTER_OPEN failed" << endl;
}

//112.���Ų���-�Զ�����
TEST_F(SgpTest, 112_DoShutter_SGP_SHUTTER_AUTO)
{
    SGP_SHUTTER_ENUM type = SGP_SHUTTER_AUTO;
    int ret = SGP_DoShutter(handle, type);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SHUTTER_AUTO failed" << endl;
}

//113.�Զ�����
TEST_F(SgpTest, 113_SetFocus_SGP_FOCUS_AUTO)
{
    SGP_FOCUS_TYPE type = SGP_FOCUS_AUTO;
    int value = 750;
    int ret = SGP_SetFocus(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SGP_FOCUS_AUTO failed" << endl;
}

//114.Զ��΢��
TEST_F(SgpTest, 114_SetFocus_SGP_FOCUS_FAR_FINE)
{
    SGP_FOCUS_TYPE type = SGP_FOCUS_FAR_FINE;
    int value = 750;
    int ret = SGP_SetFocus(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SGP_FOCUS_FAR_FINE failed" << endl;
}

//115.����΢��
TEST_F(SgpTest, 115_SetFocus_SGP_FOCUS_NEAR_FINE)
{
    SGP_FOCUS_TYPE type = SGP_FOCUS_NEAR_FINE;
    int value = 750;
    int ret = SGP_SetFocus(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SGP_FOCUS_NEAR_FINE failed" << endl;
}

//116.Զ��
TEST_F(SgpTest, 116_SetFocus_SGP_FOCUS_FAR)
{
    SGP_FOCUS_TYPE type = SGP_FOCUS_FAR;
    int value = 750;
    int ret = SGP_SetFocus(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SGP_FOCUS_FAR failed" << endl;
}

//117.����
TEST_F(SgpTest, 118_SetFocus_SGP_FOCUS_NEAR)
{
    SGP_FOCUS_TYPE type = SGP_FOCUS_NEAR;
    int value = 750;
    int ret = SGP_SetFocus(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SGP_FOCUS_NEAR failed" << endl;
}

//118.���õ��λ��0
TEST_F(SgpTest, 118_SetFocus_SGP_FOCUS_PLACE_0)
{
    SGP_FOCUS_TYPE type = SGP_FOCUS_PLACE;
    int value = 0;
    int ret = SGP_SetFocus(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SGP_FOCUS_PLACE_0 failed" << endl;
}

//119.���õ��λ��750
TEST_F(SgpTest, 119_SetFocus_SGP_FOCUS_PLACE_750)
{
    SGP_FOCUS_TYPE type = SGP_FOCUS_PLACE;
    int value = 750;
    int ret = SGP_SetFocus(handle, type, value);
    EXPECT_EQ(ret, SGP_OK) << "SGP_FOCUS_PLACE_750 failed" << endl;
}

//120.��ȡ���λ��
TEST_F(SgpTest, 120_GetMotorPosition)
{
    int value = 0;
    int ret = SGP_GetMotorPosition(handle, &value);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetMotorPosition failed" << endl;
    cout << "��ȡ�ĵ��λ��Ϊ��" << value << endl;
}

//121.���õ��ӱ䱶3��
TEST_F(SgpTest, 121_SGP_SetElectronicMagnification_3)
{
    int magnification = 3;
    SGP_VIDEO_PARAM_ENUM type = SGP_IR;
    int ret = SGP_SetElectronicMagnification(handle, type, magnification);
    ASSERT_EQ(ret, SGP_OK) << "SGP_SetElectronicMagnification_3 failed" << endl;
}

//122.���õ��ӱ䱶2��
TEST_F(SgpTest, 122_SGP_SetElectronicMagnification_2)
{
    int magnification = 2;
    SGP_VIDEO_PARAM_ENUM type = SGP_IR;
    int ret = SGP_SetElectronicMagnification(handle, type, magnification);
    ASSERT_EQ(ret, SGP_OK) << "SGP_SetElectronicMagnification_2 failed" << endl;
}

//123.���õ��ӱ䱶1��
TEST_F(SgpTest, 123_SGP_SetElectronicMagnification_1)
{
    int magnification = 1;
    SGP_VIDEO_PARAM_ENUM type = SGP_IR;
    int ret = SGP_SetElectronicMagnification(handle, type, magnification);
    ASSERT_EQ(ret, SGP_OK) << "SGP_SetElectronicMagnification_1 failed" << endl;
}

//124.���ò��µ���������
TEST_F(SgpTest, 124_SGP_SetTempPoints)
{
    const int pointNum = 100;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i * 100;
    }
    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    EXPECT_EQ(ret, SGP_OK) << "SGP_SetTempPoints failed" << endl;
    free(index);
    index = NULL;
}

//125.��ȡ���µ�����
TEST_F(SgpTest, 125_SGP_GetTempPoints)
{
    const int pointNum = 100;
    int* index = (int*)malloc(pointNum * sizeof(int));
    for (int i = 0; i < pointNum; i++)
    {
        index[i] = i * 100;
    }

    int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
    ASSERT_EQ(ret, SGP_OK) << "SGP_GetTempPoints failed" << endl;
    float* temp = (float*)malloc(pointNum * sizeof(float));
    memset(temp, 0, 10 * sizeof(float));
    if (temp != NULL)
    {
        int ret = SGP_GetTempPoints(handle, temp, pointNum, 1);
        EXPECT_EQ(ret, SGP_OK) << "SGP_GetTempPoints failed" << endl;
    }
    free(temp);
    temp = NULL;
    free(index);
    index = nullptr;
}

//126.ϵͳ����
TEST_F(SgpTest, 126_RebootSystem)
{
    int ret = SGP_RebootSystem(handle);
    EXPECT_EQ(ret, SGP_OK) << "SGP_RebootSystem failed" << endl;
}

//127.�ָ���������
//TEST_F(SgpTest, FactoryReset)
//{
//    int ret = SGP_FactoryReset(handle);
//    EXPECT_EQ(ret, SGP_OK) << "SGP_FactoryReset failed";
//}






int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    //::testing::GTEST_FLAG(filter) = "SgpTest.105_SetRange";
    return RUN_ALL_TESTS();
}








