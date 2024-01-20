#include"common.h"

class GetTempMatrixMaxMinT : public testing::Test
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

// 01��ȡ�¶Ⱦ�������������DLT
TEST_F(GetTempMatrixMaxMinT, 01_GetMaxMinTemp_DLT)
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
	getTempMatrixMaxMinTemp(&dltMatrixInfo);

	float maxT = 0.0;
	float minT = 0.0;
	result = ITA_GetTempMatrixMaxMinT(instance, &dltMatrixInfo, &maxT, &minT);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixMaxMinT fail" << endl;
	printf(" maxT:%f    minT:%f \n", maxT, minT);
}

// 02��ȡ�¶Ⱦ�������������FIR
TEST_F(GetTempMatrixMaxMinT, 01_GetMaxMinTemp_FIR)
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
	getTempMatrixMaxMinTemp(&dltMatrixInfo);

	float maxT = 0.0;
	float minT = 0.0;
	result = ITA_GetTempMatrixMaxMinT(instance, &dltMatrixInfo, &maxT, &minT);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixMaxMinT fail" << endl;
	printf(" maxT:%f    minT:%f \n", maxT, minT);
}

// 03 handle�����ָ��
TEST_F(GetTempMatrixMaxMinT, 03_handle_NULL)
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

	float maxT = 0.0;
	float minT = 0.0;
	result = ITA_GetTempMatrixMaxMinT(NULL, &dltMatrixInfo, &maxT, &minT);
	ASSERT_EQ(result, ITA_NULL_PTR_ERR) << "03_handle_NULL fail" << endl;
}

// 04 �¶Ⱦ������ָ��
TEST_F(GetTempMatrixMaxMinT, 04_NULL)
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

	float maxT = 0.0;
	float minT = 0.0;
	result = ITA_GetTempMatrixMaxMinT(instance, NULL, &maxT, &minT);
	ASSERT_EQ(result, ITA_NULL_PTR_ERR) << "04_NULL fail" << endl;
}

// 05 ����´����ָ��
TEST_F(GetTempMatrixMaxMinT, 05_NULL)
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

	float maxT = 0.0;
	float minT = 0.0;
	result = ITA_GetTempMatrixMaxMinT(instance, &dltMatrixInfo, NULL, &minT);
	ASSERT_EQ(result, ITA_NULL_PTR_ERR) << "05_NULL fail" << endl;
}

// 06 ����´����ָ��
TEST_F(GetTempMatrixMaxMinT, 06_NULL)
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

	float maxT = 0.0;
	float minT = 0.0;
	result = ITA_GetTempMatrixMaxMinT(instance, &dltMatrixInfo, &maxT, NULL);
	ASSERT_EQ(result, ITA_NULL_PTR_ERR) << "06_NULL fail" << endl;
}




