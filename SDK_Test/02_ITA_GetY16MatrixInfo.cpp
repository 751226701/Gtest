#include"common.h"

class GetY16MatrixInfo : public testing::Test
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

//01.��ITA_DLT��ͼ��ȡY16����
TEST_F(GetY16MatrixInfo, 01_DLT)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	char file[] = DLT_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[width * height];

	result = ITA_GetY16MatrixInfo(instance, file, heatMapType, &y16MaxtrixInfo);
	ASSERT_EQ(result, ITA_OK) << "��ITA_DLT��ͼ��ȡY16����ʧ�ܣ�" << endl;
	cout << "��ITA_DLT��ͼ��ȡY16����ɹ���" << endl;
	saveY16Matrix(&y16MaxtrixInfo);
	EXPECT_EQ(y16MaxtrixInfo.w, WIDTH) << "��ȡ�Ŀ����" << endl;
	EXPECT_EQ(y16MaxtrixInfo.h, HEIGHT) << "��ȡ�ĸߴ���" << endl;
}

//02.�����ļ�����ͼ���Ͳ�ƥ��
TEST_F(GetY16MatrixInfo, 02_TYPE_ERR)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	char file[] = DLT_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[width * height];

	result = ITA_GetY16MatrixInfo(instance, file, heatMapType, &y16MaxtrixInfo);
	EXPECT_EQ(result, ITA_ERROR) << "�����ļ�����ͼ���Ͳ�ƥ��ʧ�ܣ�" << endl;
}

//03.��ȡDLT��ͼY16����ʱ�����ļ�·������
TEST_F(GetY16MatrixInfo, 03_PATH_ERR)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPictures/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[width * height];

	result = ITA_GetY16MatrixInfo(instance, file, heatMapType, &y16MaxtrixInfo);
	EXPECT_EQ(result, ITA_ERROR) << "��ȡDLT��ͼY16����ʱ�����ļ�·������ʧ�ܣ�" << endl;
}

//04.��ȡDLT��ͼY16����ʱhandle�����ָ��
TEST_F(GetY16MatrixInfo, 04_HANDLE_NULL)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	char file[] = DLT_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[width * height];

	result = ITA_GetY16MatrixInfo(NULL, file, heatMapType, &y16MaxtrixInfo);
	EXPECT_EQ(result, ITA_NULL_PTR_ERR) << "��ȡDLT��ͼY16����ʱhandle�����ָ��ʧ�ܣ�" << endl;
}

// 05.��ȡDLT��ͼY16����ʱ������������ָ��
TEST_F(GetY16MatrixInfo, 05_OUTPUT_NULL)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	char file[] = DLT_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[width * height];

	result = ITA_GetY16MatrixInfo(instance, file, heatMapType, NULL);
	EXPECT_EQ(result, ITA_NULL_PTR_ERR) << "��ȡDLT��ͼY16����ʱ������������ָ��ʧ�ܣ�" << endl;
}
