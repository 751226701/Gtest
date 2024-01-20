#include"common.h"

class GetTempMatrixInfo : public testing::Test
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

//01.��ITA_DLT��ͼ��ȡ�¶Ⱦ���
TEST_F(GetTempMatrixInfo, 01_DLT)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	char file[] = DLT_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_TEMPMATRIX_INFO MatrixInfo;
	MatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &MatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "��DLT��ͼ��ȡ�¶Ⱦ���ʧ�ܣ�" << endl;
	cout << "��DLT��ͼ��ȡ�¶Ⱦ���" << endl;
	saveTempMatrix(&MatrixInfo);
	getTempMatrixMaxMinTemp(&MatrixInfo);
	EXPECT_EQ(MatrixInfo.w, WIDTH) << "��ȡ�Ŀ����" << endl;
	EXPECT_EQ(MatrixInfo.h, HEIGHT) << "��ȡ�ĸߴ���" << endl;
}

//02.��ITA_FIR��ͼ��ȡ�¶Ⱦ���
TEST_F(GetTempMatrixInfo, 02_FIR)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	char file[] = FIR_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO MatrixInfo;
	MatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &MatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "��FIR��ͼ��ȡ�¶Ⱦ���ʧ�ܣ�" << endl;
	cout << "��FIR��ͼ��ȡ�¶Ⱦ���ɹ���" << endl;
	saveTempMatrix(&MatrixInfo);
	getTempMatrixMaxMinTemp(&MatrixInfo);
	EXPECT_EQ(MatrixInfo.w, WIDTH) << "��ȡ�Ŀ����" << endl;
	EXPECT_EQ(MatrixInfo.h, HEIGHT) << "��ȡ�ĸߴ���" << endl;
}

//03.�����ļ�����ͼ���Ͳ�ƥ��1
TEST_F(GetTempMatrixInfo, 03_TYPE_ERR1)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	char file[] = DLT_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO MatrixInfo;
	MatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &MatrixInfo);
	EXPECT_EQ(result, ITA_ARG_OUT_OF_RANGE) << "�����ļ�����ͼ���Ͳ�ƥ��1ʧ�ܣ�" << endl;
}

//04.�����ļ�����ͼ���Ͳ�ƥ��2
TEST_F(GetTempMatrixInfo, 04_TYPE_ERR2)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	char file[] = FIR_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_TEMPMATRIX_INFO MatrixInfo;
	MatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &MatrixInfo);
	EXPECT_EQ(result, ITA_ARG_OUT_OF_RANGE) << "�����ļ�����ͼ���Ͳ�ƥ��2ʧ�ܣ�" << endl;
}

//05.��ȡDLT��ͼ�¶Ⱦ���ʱ�����ļ�·������
TEST_F(GetTempMatrixInfo, 05_PATHE_NONE)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPictures/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_TEMPMATRIX_INFO MatrixInfo;
	MatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &MatrixInfo);
	EXPECT_EQ(result, ITA_FILE_NOT_EXIST) << "��ȡDLT��ͼ�¶Ⱦ���ʱ�����ļ�·������ʧ�ܣ�" << endl;
}

//06.��ȡDLT��ͼ�¶Ⱦ���ʱhandle�����ָ��
TEST_F(GetTempMatrixInfo, 06_HANDLE_NULL)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	char file[] = DLT_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_TEMPMATRIX_INFO MatrixInfo;
	MatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(NULL, file, heatMapType, &MatrixInfo);
	EXPECT_EQ(result, ITA_NULL_PTR_ERR) << "��ȡDLT��ͼ�¶Ⱦ���ʱhandle�����ָ��ʧ�ܣ�" << endl;
}

//07.��ȡDLT��ͼ�¶Ⱦ���ʱ������������ָ��
TEST_F(GetTempMatrixInfo, 07_OUTPUT_NULL)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	char file[] = DLT_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_TEMPMATRIX_INFO MatrixInfo;
	MatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, NULL);
	EXPECT_EQ(result, ITA_NULL_PTR_ERR) << "��ȡDLT��ͼ�¶Ⱦ���ʱ������������ָ��ʧ�ܣ�" << endl;
}


