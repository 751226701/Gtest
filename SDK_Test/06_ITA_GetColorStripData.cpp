#include"common.h"

class GetColorStripData : public ::testing::TestWithParam<pair<ITA_PALETTE_TYPE, string>>
{
public:
    HANDLE_T instance;

    void SetUp() override
    {
        instance = ITA_HeatmapInit();
    }

    void TearDown() override
    {
        ITA_HeatmapUninit(instance);
    }
};
class GetColorStripDataNoParam : public testing::Test
{
public:
    HANDLE_T instance;

    void SetUp() override
    {
        instance = ITA_HeatmapInit();
    }

    void TearDown() override
    {
        ITA_HeatmapUninit(instance);
    }
};

INSTANTIATE_TEST_CASE_P(Colordata, GetColorStripData,
    ::testing::ValuesIn(GenerateColorData()));

//��ȡ26��ɫ����ɫ��������
TEST_P(GetColorStripData, ColorString)
{
    ITA_RESULT result;
    ITA_PALETTE_TYPE Index = GetParam().first;
    string colorname = GetParam().second;
    string filename = colorname + "Color.raw";
    const int len = 1024;
    unsigned char* colorStripData = new unsigned char[len];
    result = ITA_GetColorStripData(instance, Index, colorStripData, len);
    ASSERT_EQ(result, ITA_OK) << "GetColorStripData faild" << filename << endl;
    cout << "��ȡɫ�������ݳɹ���" << endl;
    saveColorStripData(filename.c_str(), colorStripData, len);
}

//��֤handle=NULL
TEST_F(GetColorStripDataNoParam, handle_NULL)
{
    ITA_RESULT result;
    ITA_PALETTE_TYPE Index = ITA_WHITE_HEAT;
    string filename = "����.raw";
    const int len = 1024;
    unsigned char* colorStripData = new unsigned char[len];
    result = ITA_GetColorStripData(instance, Index, colorStripData, len);
    ASSERT_EQ(result, ITA_OK) << "GetColorStripData faild" << filename << endl;
}







