#include "SDK_TEST.h"
using namespace std;

#define WIDTH 640
#define HEIGHT 512

#define DLT_PICTUERE_PATH "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpg"
#define FIR_PICTUERE_PATH "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.fir"

//�����¶Ⱦ���
void saveTempMatrix(ITATempMatrixInfo* tempMatrixInfo)
{
	char filePath[] = "temp_matrix.txt";

	FILE* file = fopen(filePath, "w");
	if (file != NULL)
	{
		for (int i = 0; i < 640 * 512; ++i)
		{
			fprintf(file, "%.2f ", tempMatrixInfo->tempMatrix[i]);
		}

		fclose(file);
		printf("�¶Ⱦ�����Ϣ�ѱ��浽�ļ���%s\n", filePath);
	}
	else
	{
		printf("�޷����ļ�����д�������\n");
	}
}
//��ȡ�¶Ⱦ�������¡�����¡�ƽ����
void getTempMatrixMaxMinTemp(ITATempMatrixInfo* tempMatrixInfo)
{
	float max = tempMatrixInfo->tempMatrix[0], min = tempMatrixInfo->tempMatrix[0], avg = 0, sum = 0;
	for (int i = 0; i < 640 * 512; i++)
	{
		if (tempMatrixInfo->tempMatrix[i] >= max)
		{
			max = tempMatrixInfo->tempMatrix[i];
		}

		if (min >= tempMatrixInfo->tempMatrix[i])
		{
			min = tempMatrixInfo->tempMatrix[i];
		}
		sum += tempMatrixInfo->tempMatrix[i];
	}
	avg = sum / (640 * 512);
	cout << "MaxTemp: " << fixed << setprecision(1) << max << endl;
	cout << "MinTemp: " << fixed << setprecision(1) << min << endl;
	cout << "AvgTemp: " << fixed << setprecision(1) << avg << endl;
}
//����Y16����
void saveY16Matrix(ITAY16MatrixInfo* y16Info)
{
	char filePath[] = "y16_matrix.txt";

	FILE* file = fopen(filePath, "w");
	if (file != NULL)
	{
		for (int i = 0; i < 640 * 512; ++i)
		{
			fprintf(file, "%hd ", y16Info->y16Matrix[i]);
		}

		fclose(file);
		printf("Y16������Ϣ�ѱ��浽�ļ���%s\n", filePath);
	}
	else
	{
		printf("�޷����ļ�����д�������\n");
	}
}
//����RGB����
void saveRGBasRaw(const char* filename, unsigned char* rgbData, int dataSize)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);

	if (file.is_open())
	{
		file.write(reinterpret_cast<char*>(rgbData), dataSize);
		file.close();
		std::cout << "RGB���ݱ���ɹ�: " << filename << std::endl;
	}
	else {
		std::cerr << "�ļ�����ʧ��!" << std::endl;
	}
}
//����ɫ��������
void saveColorStripData(const char* filename, unsigned char* colorStripData, int len)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);

	if (file.is_open())
	{
		file.write(reinterpret_cast<char*>(colorStripData), len);
		file.close();
		std::cout << "ɫ�������ݱ���ɹ�: " << filename << std::endl;
	}
	else {
		std::cerr << "�ļ�����ʧ��!" << std::endl;
	}
}
//����JPG��Ƭ
void saveJpgPicture(const char* filename, unsigned char* jpgBuf, int jpgBufLen)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);

	if (file.is_open())
	{
		file.write(reinterpret_cast<char*>(jpgBuf), jpgBufLen);
		file.close();
		std::cout << "��ͼ����ɹ�: " << filename << std::endl;
	}
	else {
		std::cerr << "�ļ�����ʧ��!" << std::endl;
	}
}
// �� short �������ݸ��Ƶ� unsigned char ���͵��ڴ���
void ConvertShortToUnsignedChar2(const short* srcData, unsigned char* dstData, int height, int width)
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			int offset = (i * width + j) * sizeof(short);
			dstData[offset] = static_cast<unsigned char>(srcData[i * width + j] & 0xFF); // ȡ short ���ݵĵͰ�λ
			dstData[offset + 1] = static_cast<unsigned char>((srcData[i * width + j] >> 8) & 0xFF); // ȡ short ���ݵĸ߰�λ
		}
	}
}
void ConvertShortToUnsignedChar1(const short* srcData, unsigned char* dstData, int length)
{
	for (int i = 0; i < length; ++i) {
		int offset = i * sizeof(short);
		dstData[offset] = static_cast<unsigned char>(srcData[i] & 0xFF); // ȡ short ���ݵĵͰ�λ
		dstData[offset + 1] = static_cast<unsigned char>((srcData[i] >> 8) & 0xFF); // ȡ short ���ݵĸ߰�λ
	}
}

char file[] = FIR_PICTUERE_PATH;
class TestEnvironment : public ::testing::Environment {
public:
	HANDLE_T instance;
	void SetUp() override 
	{
		//instance = ITA_HeatmapInit();
	}

	
	void TearDown() override 
	{
		//ITA_HeatmapUninit(instance);
	}
};
class ItaTest : public testing::Test
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
TEST_F(ItaTest, 01_ITA_GetTempMatrixInfo_DLT)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	
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
TEST_F(ItaTest, 02_ITA_GetTempMatrixInfo_FIR)
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
//TEST_F(ItaTest, 03_ITA_GetTempMatrixInfo_TYPE_ERR1)
//{
//	int width = WIDTH;
//	int height = HEIGHT;
//	ITA_RESULT result;
//	char file[] = DLT_PICTUERE_PATH;
//	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
//	ITA_TEMPMATRIX_INFO MatrixInfo;
//	MatrixInfo.tempMatrix = new float[width * height];
//
//	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &MatrixInfo);
//	EXPECT_EQ(result, ITA_ARG_OUT_OF_RANGE) << "�����ļ�����ͼ���Ͳ�ƥ��1ʧ�ܣ�" << endl;
//}

//04.�����ļ�����ͼ���Ͳ�ƥ��2
TEST_F(ItaTest, 04_ITA_GetTempMatrixInfo_TYPE_ERR2)
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
TEST_F(ItaTest, 05_ITA_GetTempMatrixInfo_PATHE_NONE)
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
TEST_F(ItaTest, 06_ITA_GetTempMatrixInfo_HANDLE_NULL)
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
TEST_F(ItaTest, 07_ITA_GetTempMatrixInfo_OUTPUT_NULL)
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

//08.��ITA_DLT��ͼ��ȡY16����
TEST_F(ItaTest, 08_ITA_GetY16MatrixInfo)
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

//09.�����ļ�����ͼ���Ͳ�ƥ��
TEST_F(ItaTest, 09_ITA_GetY16MatrixInfo_TYPE_ERR)
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

//10.��ȡDLT��ͼY16����ʱ�����ļ�·������
TEST_F(ItaTest, 10_ITA_GetY16MatrixInfo_PATH_ERR)
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

//11.��ȡDLT��ͼY16����ʱhandle�����ָ��
TEST_F(ItaTest, 11_ITA_GetY16MatrixInfo_HANDLE_NULL)
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

// 12.��ȡDLT��ͼY16����ʱ������������ָ��
TEST_F(ItaTest, 12_ITA_GetY16MatrixInfo_OUTPUT_NULL)
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

// 13.��DLT��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת90��,����
TEST_F(ItaTest, 13_ITA_TempMatrixRotation_DLT_90)
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
	ASSERT_EQ(result, ITA_OK) << "13_ITA_TempMatrixRotation_DLT_90 fial!" << endl;
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

// 14.��DLT��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת180��,����
TEST_F(ItaTest, 14_ITA_TempMatrixRotation_DLT_180)
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
	ASSERT_EQ(result, ITA_OK) << "14_ITA_TempMatrixRotation_DLT_180 fial!" << endl;
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

// 15.��DLT��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת270��,����
TEST_F(ItaTest, 15_ITA_TempMatrixRotation_270)
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
	ASSERT_EQ(result, ITA_OK) << "15_ITA_TempMatrixRotation_270 fial!" << endl;
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

// 16.��DLT��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת,����
TEST_F(ItaTest, 16_ITA_TempMatrixRotation_NONE)
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
	ASSERT_EQ(result, ITA_OK) << "16_ITA_TempMatrixRotation_NONE fial!" << endl;
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

// 17.��FIR��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת90��,����
TEST_F(ItaTest, 17_ITA_TempMatrixRotation_FIR_90)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO firMatrixInfo;
	firMatrixInfo.tempMatrix = new float[width * height];

	cout << file << endl;


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
	ASSERT_EQ(result, ITA_OK) << "17_ITA_TempMatrixRotation_FIR_90 fial!" << endl;
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

// 18.��FIR��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת180��,����
TEST_F(ItaTest, 18_ITA_TempMatrixRotation_FIR_180)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char firfile[] = FIR_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO firMatrixInfo;
	firMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, firfile, heatMapType, &firMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fial!" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	ITA_ROTATE_TYPE rotateType = ITA_ROTATE_180;
	ITA_TEMPMATRIX_INFO dstInfo;
	dstInfo.tempMatrix = new float[width * height];
	dstInfo.w = 0;
	dstInfo.h = 0;
	result = ITA_TempMatrixRotation(instance, &firMatrixInfo, rotateType, dstInfo.tempMatrix, &(dstInfo.w), &(dstInfo.h));
	ASSERT_EQ(result, ITA_OK) << "18_ITA_TempMatrixRotation_FIR_180 fial!" << endl;
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

// 19.��FIR��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת270��,����
TEST_F(ItaTest, 19_ITA_TempMatrixRotation_FIR_270)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char firfile[] = FIR_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO firMatrixInfo;
	firMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, firfile, heatMapType, &firMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fial!" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	ITA_ROTATE_TYPE rotateType = ITA_ROTATE_270;
	ITA_TEMPMATRIX_INFO dstInfo;
	dstInfo.tempMatrix = new float[width * height];
	dstInfo.w = 0;
	dstInfo.h = 0;
	result = ITA_TempMatrixRotation(instance, &firMatrixInfo, rotateType, dstInfo.tempMatrix, &(dstInfo.w), &(dstInfo.h));
	ASSERT_EQ(result, ITA_OK) << "19_ITA_TempMatrixRotation_FIR_270 fial!" << endl;
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

// 20.��FIR��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת,����
TEST_F(ItaTest, 20_ITA_TempMatrixRotation_FIR_NONE)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char firfile[] = FIR_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO firMatrixInfo;
	firMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, firfile, heatMapType, &firMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fial!" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	ITA_ROTATE_TYPE rotateType = ITA_ROTATE_NONE;
	ITA_TEMPMATRIX_INFO dstInfo;
	dstInfo.tempMatrix = new float[width * height];
	dstInfo.w = 0;
	dstInfo.h = 0;
	result = ITA_TempMatrixRotation(instance, &firMatrixInfo, rotateType, dstInfo.tempMatrix, &(dstInfo.w), &(dstInfo.h));
	ASSERT_EQ(result, ITA_OK) << "20_ITA_TempMatrixRotation_FIR_NONE fial!" << endl;
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

// 21.handle�����ָ��
TEST_F(ItaTest, 21_ITA_TempMatrixRotation_handle_NULL)
{
	int width = WIDTH;
	int height = HEIGHT;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char firfile[] = FIR_PICTUERE_PATH;
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO firMatrixInfo;
	firMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, firfile, heatMapType, &firMatrixInfo);
	ASSERT_EQ(result, ITA_OK) << "ITA_GetTempMatrixInfo fial!" << endl;
	cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

	ITA_ROTATE_TYPE rotateType = ITA_ROTATE_NONE;
	ITA_TEMPMATRIX_INFO dstInfo;
	dstInfo.tempMatrix = new float[width * height];
	dstInfo.w = 0;
	dstInfo.h = 0;
	result = ITA_TempMatrixRotation(NULL, &firMatrixInfo, rotateType, dstInfo.tempMatrix, &(dstInfo.w), &(dstInfo.h));
	ASSERT_EQ(result, ITA_NULL_PTR_ERR) << "21_ITA_TempMatrixRotation_handle_NULL fial!" << endl;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
	//::testing::GTEST_FLAG(filter) = "ItaTest.20_ITA_TempMatrixRotation_FIR_NONE";
    return RUN_ALL_TESTS();
}