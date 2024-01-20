#include"common.h"
class TempMatrixRotation : public testing::Test
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

// 01.��DLT��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת90��,����
TEST_F(TempMatrixRotation, 01_DLT_90)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = DLT_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_TEMPMATRIX_INFO firMatrixInfo;
	firMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &firMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fial!" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	ITA_ROTATE_TYPE rotateType = ITA_ROTATE_90;
	ITA_TEMPMATRIX_INFO dstInfo;
	dstInfo.tempMatrix = new float[width * height];
	dstInfo.w = 0;
	dstInfo.h = 0;
	result = ITA_TempMatrixRotation(instance, &firMatrixInfo, rotateType, dstInfo.tempMatrix, &(dstInfo.w), &(dstInfo.h));
	printf("��תǰ�Ŀ�Ϊ��%d   ��תǰ�ĸ�Ϊ��%d \n", firMatrixInfo.w, firMatrixInfo.h);
	printf("�¶Ⱦ�����ת�ɹ�����ת��Ŀ�Ϊ��%d   ��ת��ĸ�Ϊ��%d \n", dstInfo.w, dstInfo.h);
	ASSERT_EQ(result, ITA_OK) << "01_DLT_90 fial!" << endl;
	EXPECT_EQ(dstInfo.w, firMatrixInfo.h);
	EXPECT_EQ(dstInfo.h, firMatrixInfo.w);

	int w = dstInfo.w;
	int h = dstInfo.h;
	int dltmatrix_len = w * h * 3;
	ITA_PALETTE_TYPE palette_index = ITA_IRON_RED;
	unsigned char* rgbData = new unsigned char[dltmatrix_len];
	result = ITA_TempMatrix2Rgb(instance, &dstInfo, palette_index, rgbData, dltmatrix_len);
	ASSERT_EQ(result, ITA_OK) << "ITA_TempMatrix2Rgb fial!" << endl;
	cout << "תRGB���ݳɹ�" << endl;
	saveRGBasRaw("DLT_RGB_90.raw", rgbData, dltmatrix_len);
}

// 02.��DLT��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת180��,����
TEST_F(TempMatrixRotation, 02_DLT_180)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = DLT_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_TEMPMATRIX_INFO firMatrixInfo;
	firMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &firMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fial!" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	ITA_ROTATE_TYPE rotateType = ITA_ROTATE_180;
	ITA_TEMPMATRIX_INFO dstInfo;
	dstInfo.tempMatrix = new float[width * height];
	dstInfo.w = 0;
	dstInfo.h = 0;
	result = ITA_TempMatrixRotation(instance, &firMatrixInfo, rotateType, dstInfo.tempMatrix, &(dstInfo.w), &(dstInfo.h));
	ASSERT_EQ(result, ITA_OK) << "02_DLT_180 fial!" << endl;
	printf("��תǰ�Ŀ�Ϊ��%d   ��תǰ�ĸ�Ϊ��%d \n", firMatrixInfo.w, firMatrixInfo.h);
	printf("�¶Ⱦ�����ת�ɹ�����ת��Ŀ�Ϊ��%d   ��ת��ĸ�Ϊ��%d \n", dstInfo.w, dstInfo.h);
	EXPECT_EQ(dstInfo.w, firMatrixInfo.w);
	EXPECT_EQ(dstInfo.h, firMatrixInfo.h);

	int w = dstInfo.w;
	int h = dstInfo.h;
	int dltmatrix_len = w * h * 3;
	ITA_PALETTE_TYPE palette_index = ITA_IRON_RED;
	unsigned char* rgbData = new unsigned char[dltmatrix_len];
	result = ITA_TempMatrix2Rgb(instance, &dstInfo, palette_index, rgbData, dltmatrix_len);
	ASSERT_EQ(result, ITA_OK) << "ITA_TempMatrix2Rgb fial!" << endl;
	cout << "תRGB���ݳɹ�" << endl;
	saveRGBasRaw("DLT_RGB_180.raw", rgbData, dltmatrix_len);
}

// 03.��DLT��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת270��,����
TEST_F(TempMatrixRotation, 03_DLT_270)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = DLT_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_TEMPMATRIX_INFO firMatrixInfo;
	firMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &firMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fial!" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	ITA_ROTATE_TYPE rotateType = ITA_ROTATE_270;
	ITA_TEMPMATRIX_INFO dstInfo;
	dstInfo.tempMatrix = new float[width * height];
	dstInfo.w = 0;
	dstInfo.h = 0;
	result = ITA_TempMatrixRotation(instance, &firMatrixInfo, rotateType, dstInfo.tempMatrix, &(dstInfo.w), &(dstInfo.h));
	ASSERT_EQ(result, ITA_OK) << "03_DLT_270 fial!" << endl;
	printf("��תǰ�Ŀ�Ϊ��%d   ��תǰ�ĸ�Ϊ��%d \n", firMatrixInfo.w, firMatrixInfo.h);
	printf("�¶Ⱦ�����ת�ɹ�����ת��Ŀ�Ϊ��%d   ��ת��ĸ�Ϊ��%d \n", dstInfo.w, dstInfo.h);
	EXPECT_EQ(dstInfo.w, firMatrixInfo.h);
	EXPECT_EQ(dstInfo.h, firMatrixInfo.w);

	int w = dstInfo.w;
	int h = dstInfo.h;
	int dltmatrix_len = w * h * 3;
	ITA_PALETTE_TYPE palette_index = ITA_IRON_RED;
	unsigned char* rgbData = new unsigned char[dltmatrix_len];
	result = ITA_TempMatrix2Rgb(instance, &dstInfo, palette_index, rgbData, dltmatrix_len);
	ASSERT_EQ(result, ITA_OK) << "ITA_TempMatrix2Rgb fial!" << endl;
	cout << "תRGB���ݳɹ�" << endl;
	saveRGBasRaw("DLT_RGB_270.raw", rgbData, dltmatrix_len);
}

// 04.��DLT��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת,����
TEST_F(TempMatrixRotation, 04_DLT_NONE)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = DLT_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_TEMPMATRIX_INFO firMatrixInfo;
	firMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &firMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fial!" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	ITA_ROTATE_TYPE rotateType = ITA_ROTATE_NONE;
	ITA_TEMPMATRIX_INFO dstInfo;
	dstInfo.tempMatrix = new float[width * height];
	dstInfo.w = 0;
	dstInfo.h = 0;
	result = ITA_TempMatrixRotation(instance, &firMatrixInfo, rotateType, dstInfo.tempMatrix, &(dstInfo.w), &(dstInfo.h));
	ASSERT_EQ(result, ITA_OK) << "04_DLT_NONE fial!" << endl;
	printf("��תǰ�Ŀ�Ϊ��%d   ��תǰ�ĸ�Ϊ��%d \n", firMatrixInfo.w, firMatrixInfo.h);
	printf("�¶Ⱦ�����ת�ɹ�����ת��Ŀ�Ϊ��%d   ��ת��ĸ�Ϊ��%d \n", dstInfo.w, dstInfo.h);

	int w = dstInfo.w;
	int h = dstInfo.h;
	int dltmatrix_len = w * h * 3;
	ITA_PALETTE_TYPE palette_index = ITA_IRON_RED;
	unsigned char* rgbData = new unsigned char[dltmatrix_len];
	result = ITA_TempMatrix2Rgb(instance, &dstInfo, palette_index, rgbData, dltmatrix_len);
	ASSERT_EQ(result, ITA_OK) << "ITA_TempMatrix2Rgb fial!" << endl;
	cout << "תRGB���ݳɹ�" << endl;
	saveRGBasRaw("DLT_RGB_NONE.raw", rgbData, dltmatrix_len);
}

// 05.��FIR��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת90��,����
TEST_F(TempMatrixRotation, 05_FIR_90)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = FIR_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO firMatrixInfo;
	firMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &firMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fial!" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	ITA_ROTATE_TYPE rotateType = ITA_ROTATE_90;
	ITA_TEMPMATRIX_INFO dstInfo;
	dstInfo.tempMatrix = new float[width * height];
	dstInfo.w = 0;
	dstInfo.h = 0;
	result = ITA_TempMatrixRotation(instance, &firMatrixInfo, rotateType, dstInfo.tempMatrix, &(dstInfo.w), &(dstInfo.h));
	printf("��תǰ�Ŀ�Ϊ��%d   ��תǰ�ĸ�Ϊ��%d \n", firMatrixInfo.w, firMatrixInfo.h);
	printf("�¶Ⱦ�����ת�ɹ�����ת��Ŀ�Ϊ��%d   ��ת��ĸ�Ϊ��%d \n", dstInfo.w, dstInfo.h);
	ASSERT_EQ(result, ITA_OK) << "05_FIR_90 fial!" << endl;
	EXPECT_EQ(dstInfo.w, firMatrixInfo.h);
	EXPECT_EQ(dstInfo.h, firMatrixInfo.w);

	int w = dstInfo.w;
	int h = dstInfo.h;
	int dltmatrix_len = w * h * 3;
	ITA_PALETTE_TYPE palette_index = ITA_IRON_RED;
	unsigned char* rgbData = new unsigned char[dltmatrix_len];
	result = ITA_TempMatrix2Rgb(instance, &dstInfo, palette_index, rgbData, dltmatrix_len);
	ASSERT_EQ(result, ITA_OK) << "ITA_TempMatrix2Rgb fial!" << endl;
	cout << "תRGB���ݳɹ�" << endl;
	saveRGBasRaw("FIR_RGB_90.raw", rgbData, dltmatrix_len);
}

// 06.��FIR��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת180��,����
TEST_F(TempMatrixRotation, 06_FIR_180)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = FIR_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO firMatrixInfo;
	firMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &firMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fial!" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	ITA_ROTATE_TYPE rotateType = ITA_ROTATE_180;
	ITA_TEMPMATRIX_INFO dstInfo;
	dstInfo.tempMatrix = new float[width * height];
	dstInfo.w = 0;
	dstInfo.h = 0;
	result = ITA_TempMatrixRotation(instance, &firMatrixInfo, rotateType, dstInfo.tempMatrix, &(dstInfo.w), &(dstInfo.h));
	ASSERT_EQ(result, ITA_OK) << "06_FIR_180 fial!" << endl;
	printf("��תǰ�Ŀ�Ϊ��%d   ��תǰ�ĸ�Ϊ��%d \n", firMatrixInfo.w, firMatrixInfo.h);
	printf("�¶Ⱦ�����ת�ɹ�����ת��Ŀ�Ϊ��%d   ��ת��ĸ�Ϊ��%d \n", dstInfo.w, dstInfo.h);
	EXPECT_EQ(dstInfo.w, firMatrixInfo.w);
	EXPECT_EQ(dstInfo.h, firMatrixInfo.h);

	int w = dstInfo.w;
	int h = dstInfo.h;
	int dltmatrix_len = w * h * 3;
	ITA_PALETTE_TYPE palette_index = ITA_IRON_RED;
	unsigned char* rgbData = new unsigned char[dltmatrix_len];
	result = ITA_TempMatrix2Rgb(instance, &dstInfo, palette_index, rgbData, dltmatrix_len);
	ASSERT_EQ(result, ITA_OK) << "ITA_TempMatrix2Rgb fial!" << endl;
	cout << "תRGB���ݳɹ�" << endl;
	saveRGBasRaw("FIR_RGB_180.raw", rgbData, dltmatrix_len);
}

// 07.��FIR��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת270��,����
TEST_F(TempMatrixRotation, 07_FIR_270)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = FIR_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO firMatrixInfo;
	firMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &firMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fial!" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	ITA_ROTATE_TYPE rotateType = ITA_ROTATE_270;
	ITA_TEMPMATRIX_INFO dstInfo;
	dstInfo.tempMatrix = new float[width * height];
	dstInfo.w = 0;
	dstInfo.h = 0;
	result = ITA_TempMatrixRotation(instance, &firMatrixInfo, rotateType, dstInfo.tempMatrix, &(dstInfo.w), &(dstInfo.h));
	ASSERT_EQ(result, ITA_OK) << "07_FIR_270 fial!" << endl;
	printf("��תǰ�Ŀ�Ϊ��%d   ��תǰ�ĸ�Ϊ��%d \n", firMatrixInfo.w, firMatrixInfo.h);
	printf("�¶Ⱦ�����ת�ɹ�����ת��Ŀ�Ϊ��%d   ��ת��ĸ�Ϊ��%d \n", dstInfo.w, dstInfo.h);
	EXPECT_EQ(dstInfo.w, firMatrixInfo.h);
	EXPECT_EQ(dstInfo.h, firMatrixInfo.w);

	int w = dstInfo.w;
	int h = dstInfo.h;
	int dltmatrix_len = w * h * 3;
	ITA_PALETTE_TYPE palette_index = ITA_IRON_RED;
	unsigned char* rgbData = new unsigned char[dltmatrix_len];
	result = ITA_TempMatrix2Rgb(instance, &dstInfo, palette_index, rgbData, dltmatrix_len);
	ASSERT_EQ(result, ITA_OK) << "ITA_TempMatrix2Rgb fial!" << endl;
	cout << "תRGB���ݳɹ�" << endl;
	saveRGBasRaw("FIR_RGB_270.raw", rgbData, dltmatrix_len);
}

// 08.��FIR��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת,����
TEST_F(TempMatrixRotation, 08_FIR_NONE)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = FIR_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO firMatrixInfo;
	firMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &firMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fial!" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	ITA_ROTATE_TYPE rotateType = ITA_ROTATE_NONE;
	ITA_TEMPMATRIX_INFO dstInfo;
	dstInfo.tempMatrix = new float[width * height];
	dstInfo.w = 0;
	dstInfo.h = 0;
	result = ITA_TempMatrixRotation(instance, &firMatrixInfo, rotateType, dstInfo.tempMatrix, &(dstInfo.w), &(dstInfo.h));
	ASSERT_EQ(result, ITA_OK) << "08_FIR_NONE fial!" << endl;
	printf("��תǰ�Ŀ�Ϊ��%d   ��תǰ�ĸ�Ϊ��%d \n", firMatrixInfo.w, firMatrixInfo.h);
	printf("�¶Ⱦ�����ת�ɹ�����ת��Ŀ�Ϊ��%d   ��ת��ĸ�Ϊ��%d \n", dstInfo.w, dstInfo.h);

	int w = dstInfo.w;
	int h = dstInfo.h;
	int dltmatrix_len = w * h * 3;
	ITA_PALETTE_TYPE palette_index = ITA_IRON_RED;
	unsigned char* rgbData = new unsigned char[dltmatrix_len];
	result = ITA_TempMatrix2Rgb(instance, &dstInfo, palette_index, rgbData, dltmatrix_len);
	ASSERT_EQ(result, ITA_OK) << "ITA_TempMatrix2Rgb fial!" << endl;
	cout << "תRGB���ݳɹ�" << endl;
	saveRGBasRaw("FIR_RGB_NONE.raw", rgbData, dltmatrix_len);
}

// 09.handle�����ָ��
TEST_F(TempMatrixRotation, 09_handle_NULL)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = FIR_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO firMatrixInfo;
	firMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &firMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fial!" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	ITA_ROTATE_TYPE rotateType = ITA_ROTATE_NONE;
	ITA_TEMPMATRIX_INFO dstInfo;
	dstInfo.tempMatrix = new float[width * height];
	dstInfo.w = 0;
	dstInfo.h = 0;
	result = ITA_TempMatrixRotation(NULL, &firMatrixInfo, rotateType, dstInfo.tempMatrix, &(dstInfo.w), &(dstInfo.h));
	ASSERT_EQ(result, ITA_NULL_PTR_ERR) << "09_handle_NULL fial!" << endl;
}
