#include"common.h"

class TempMatrix2Rgb : public testing::Test
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
class TempMatrix2RgbParam : public ::testing::TestWithParam<pair<ITA_PALETTE_TYPE, string>>
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

INSTANTIATE_TEST_CASE_P(Colordata, TempMatrix2RgbParam,
	::testing::ValuesIn(GenerateColorData()));

// ��DLT��ͼ�е��¶Ⱦ���תΪ26��α��RGB����
TEST_P(TempMatrix2RgbParam, DLTMaxtrixToRGB)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = DLT_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_TEMPMATRIX_INFO dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &dltMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fail" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	int w = dltMatrixInfo.w;
	int h = dltMatrixInfo.h;
	int dltmatrix_len = w * h * 3;
	ITA_PALETTE_TYPE palette_index = GetParam().first;
	string colorname = GetParam().second;
	string filename = "DLT"+colorname + ".raw";
	unsigned char* rgbData = new unsigned char[dltmatrix_len];
	result = ITA_TempMatrix2Rgb(instance, &dltMatrixInfo, palette_index, rgbData, dltmatrix_len);
	ASSERT_EQ(result, ITA_OK) << "MaxtrixToRGB fail" << filename << endl;
	cout << "תRGB���ݳɹ�" << endl;
	saveRGBasRaw(filename.c_str(), rgbData, dltmatrix_len);
}

// ��FIR��ͼ�е��¶Ⱦ���תΪ26��α��RGB����
TEST_P(TempMatrix2RgbParam, FIRMaxtrixToRGB)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = FIR_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &dltMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fail" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	int w = dltMatrixInfo.w;
	int h = dltMatrixInfo.h;
	int dltmatrix_len = w * h * 3;
	ITA_PALETTE_TYPE palette_index = GetParam().first;
	string colorname = GetParam().second;
	string filename = "FIR" + colorname + ".raw";
	unsigned char* rgbData = new unsigned char[dltmatrix_len];
	result = ITA_TempMatrix2Rgb(instance, &dltMatrixInfo, palette_index, rgbData, dltmatrix_len);
	ASSERT_EQ(result, ITA_OK) << "MaxtrixToRGB fail" << filename << endl;
	cout << "תRGB���ݳɹ�" << endl;
	saveRGBasRaw(filename.c_str(), rgbData, dltmatrix_len);
}

// handle�����ָ��
TEST_F(TempMatrix2Rgb, NULL1)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = FIR_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &dltMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fail" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	int w = dltMatrixInfo.w;
	int h = dltMatrixInfo.h;
	int dltmatrix_len = w * h * 3;
	ITA_PALETTE_TYPE palette_index = ITA_AMBER;
	unsigned char* rgbData = new unsigned char[dltmatrix_len];
	result = ITA_TempMatrix2Rgb(NULL, &dltMatrixInfo, palette_index, rgbData, dltmatrix_len);
	ASSERT_EQ(result, ITA_NULL_PTR_ERR) << "NULL1 fail" << endl;
}

// �����¶Ⱦ������ָ��
TEST_F(TempMatrix2Rgb, NULL2)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = FIR_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &dltMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fail" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	int w = dltMatrixInfo.w;
	int h = dltMatrixInfo.h;
	int dltmatrix_len = w * h * 3;
	ITA_PALETTE_TYPE palette_index = ITA_AMBER;
	unsigned char* rgbData = new unsigned char[dltmatrix_len];
	result = ITA_TempMatrix2Rgb(instance, NULL, palette_index, rgbData, dltmatrix_len);
	ASSERT_EQ(result, ITA_NULL_PTR_ERR) << "NULL2 fail" << endl;
}

// ���RGB���ݴ����ָ��
TEST_F(TempMatrix2Rgb, NULL3)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = FIR_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &dltMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fail" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	int w = dltMatrixInfo.w;
	int h = dltMatrixInfo.h;
	int dltmatrix_len = w * h * 3;
	ITA_PALETTE_TYPE palette_index = ITA_AMBER;
	unsigned char* rgbData = new unsigned char[dltmatrix_len];
	result = ITA_TempMatrix2Rgb(instance, &dltMatrixInfo, palette_index, NULL, dltmatrix_len);
	ASSERT_EQ(result, ITA_NULL_PTR_ERR) << "NULL3 fail" << endl;
}