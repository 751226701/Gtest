#include <iostream>     
#include <fstream> 
#include <strstream>
#include <string>
#include <iomanip>
#include <vector>
#include <ctime>
#include <chrono>
#include <sstream>
#include <map>
#include <algorithm>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <thread>
#include "SgpApi.h"
#include "SgpParam.h"
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

using namespace std;

class TemperatureAnalyzer {
public:
	static void getTemp(const std::string& temp) {
		std::vector<short> short_temp;
		std::string decoded_temp = base64_decode(temp);
		const char* decode_byte_temp = decoded_temp.c_str();
		size_t count = decoded_temp.length() / 2;
		
		for (size_t i = 0; i < count; ++i) {
			short value = (static_cast<uint8_t>(decode_byte_temp[i * 2 + 1]) << 8) | static_cast<uint8_t>(decode_byte_temp[i * 2]);
			short_temp.push_back(value);
		}
		
		short maxtemp = short_temp[0];
		short mintemp = short_temp[0];
		
		for (size_t i = 0; i < std::min(short_temp.size(), static_cast<size_t>(IMAGE_WIDTH * IMAGE_HEIGHT)); ++i)
		{
			if (maxtemp <= short_temp[i]) {
				maxtemp = short_temp[i];
			}
			if (mintemp >= short_temp[i]) {
				mintemp = short_temp[i];
			}
		}
		
		std::time_t now = std::time(nullptr);
		std::tm* time_info = std::localtime(&now);
		char time_str[100];
		std::strftime(time_str, sizeof(time_str), "[%Y-%m-%d %H:%M:%S]", time_info);

		std::cout << time_str << " maxTemp: " << static_cast<double>(maxtemp) / 100.0 << std::endl;
		std::cout << time_str << " minTemp: " << static_cast<double>(mintemp) / 100.0 << std::endl;
		std::cout << std::endl;
	}

private:
	static const int IMAGE_WIDTH = 640;
	static const int IMAGE_HEIGHT = 512;

	static std::string base64_decode(const std::string& encoded_data) {
		BIO* bio = BIO_new(BIO_f_base64());
		BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
		BIO* mem = BIO_new_mem_buf(encoded_data.c_str(), encoded_data.length());
		bio = BIO_push(bio, mem);

		const size_t decode_length = encoded_data.length() * 3 / 4;
		char* buffer = new char[decode_length + 1];
		memset(buffer, 0, decode_length + 1);

		BIO_read(bio, buffer, encoded_data.length());
		std::string decoded_data(buffer);
		delete[] buffer;

		BIO_free_all(bio);
		return decoded_data;
	}
};

struct IptPictureFrame
{
	char* IRImage;//������Ƶ��ͼ�����ļ�
	unsigned char     FileVersion[2];//�ļ��汾
	unsigned short    Width;//�¶ȵ�����
	unsigned short    Height;//�¶ȵ���߶�
	unsigned char     DateTime[14];//����ʱ��
	float* IRData;//�����¶�ֵ��������
	float     Emiss;//������
	float     AmbientTemperature;//�����¶�
	unsigned char     Len;//��ͷ����
	unsigned int      Distance;//�������
	unsigned char     RelativeHumidity;//���ʪ��
	float     ReflectiveTemperature;//�����¶�
	unsigned char     Productor[32];//��������
	unsigned char     Type[32];//��Ʒ�ͺ�
	unsigned char     SerialNO[32];//��Ʒ���к�
	double    Longitude;//����
	double    Latitude;//γ��
	int       Altitude;//����
	unsigned int      DescriptionLength;//��ע��Ϣ����
	unsigned char* DescriptionData;//��ע��Ϣ,�����������Ϣ
	unsigned int      IRDataOffset;//�������ݵ���ʼƫ�Ƶ�ַ
	unsigned char     FileEndType[16];//�ļ�ĩβ��ʶ
public:
	IptPictureFrame()
	{
		memset(this, 0, sizeof(IptPictureFrame));
	}
};

struct FirFrame
{
	unsigned char     FileFlag[4];//�ļ����
	float             OptiTrans; //��ѧ͸����
	float             Emiss;//������
	float             Distance;//�������
	float      AmbientTemperature;//�����¶�
	float    RelativeHumidity;//���ʪ��
	unsigned short    Width;//�¶ȵ�����
	unsigned short    Height;//�¶ȵ���߶�
	unsigned char     Precision[1];//����
	short* IRData;//�����¶�ֵ��������
public:
	FirFrame()
	{
		memset(this, 0, sizeof(FirFrame));
	}

};

std::string byteArrayToString(void* pData, int nDataLen)
{
	std::string s1;

	char cBuf[50] = { 0 };

	for (int i = 0; i < nDataLen; i++)
	{
		if (i > 0)
		{
			s1 += ",";
		}

		unsigned char ch = *((unsigned char*)pData + i);
		sprintf(cBuf, "%d", ch);
		s1 += cBuf;
	}

	return s1;
}

void convertUnCharToStr(char* str, unsigned char* UnChar, int ucLen)
{
	int i = 0;
	for (i = 0; i < ucLen; i++)
	{
		//��ʽ����str,ÿunsigned char ת���ַ�ռ��λ��%xд��%Xд��  
		sprintf(str + i * 2, "%02x", UnChar[i]);
	}
}

//std::string ConvertFloattoStr(float number)
//{
//	std::ostringstream buff;
//	buff << number;
//	return buff.str();
//}


//imgPathֵ����E://20210506//20210506152031609temp.jpg
static int GetGWTempEx(std::string imgPath, float& maxTemp, float& minTemp, float& avgTemp)
{
	IptPictureFrame pictureFrame;         
	int readByes = 0;   
	unsigned char expectedFileEndType[16] = { 0x37, 0x66 ,0x07, 0x1a, 0x12 ,0x3a ,0x4c ,0x9f, 0xa9, 0x5d ,0x21 ,0xd2 ,0xda, 0x7d ,0x26, 0xbc };
	ifstream inFile(imgPath.c_str(), ios::in | ios::binary);
	if (!inFile) {
		cout << "error��file open failed��" << endl;
		return 0;
	}
	inFile.seekg(0, ios::end);  
	char singleChar;
	int picLen = inFile.tellg();
	while (!inFile.eof())
	{
		inFile.read((char*)&singleChar, sizeof(char));
		picLen++;
		cout << "��û�е��ļ�β" << "��ǰ��ȡ���ַ���" << singleChar << endl;
	}

	if (inFile.eof())
		cout << "���ļ�β��" << endl;
	picLen = picLen - 1;
	cout << "Picture length is " << picLen << endl;

	inFile.clear();
	inFile.seekg(picLen - 16, ios::beg);
	inFile.read((char*)&pictureFrame.FileEndType, sizeof(pictureFrame.FileEndType));
	readByes = inFile.gcount();
	cout << "��ȡ���ֽ���" << readByes << endl;
	//��ӡ�ļ���β��־
	int wrongFileEndNum = 0;
	for (int i = 0; i < 16; i++)
	{
		cout << hex << (int)pictureFrame.FileEndType[i] << endl;
		if (pictureFrame.FileEndType[i] != expectedFileEndType[i])
			wrongFileEndNum++;
	}
	if (wrongFileEndNum == 0)
	{
		printf("�ļ���β�ַ�������ȷ\n");
	}
	else
	{
		printf("�ļ���β�ַ��������\n");
	}
	//��ȡ�������ݵ���ʼƫ�Ƶ�ַ
	inFile.clear();
	inFile.seekg(picLen - 20, ios::beg);
	inFile.read((char*)&pictureFrame.IRDataOffset, sizeof(pictureFrame.IRDataOffset));
	cout << "��ȡ�������ݵ���ʼƫ�Ƶ�ַ�ǣ�" << pictureFrame.IRDataOffset << endl;

	//��ȡ�ļ��汾
	inFile.clear();
	inFile.seekg(pictureFrame.IRDataOffset, ios::beg);
	inFile.read((char*)&pictureFrame.FileVersion, sizeof(pictureFrame.FileVersion));
	for (int i = 0; i < 2; i++)
	{
		cout << hex << (int)pictureFrame.FileVersion[i] << endl;
	}
	char cFileVersion[2];
	convertUnCharToStr(cFileVersion, pictureFrame.FileVersion, 2);
	printf("�ļ��汾��%s\n", cFileVersion);
	//��ȡͼ���ļ���
	inFile.read((char*)&pictureFrame.Width, sizeof(pictureFrame.Width));
	cout << dec << "��ȡ�����ļ��Ŀ��ǣ�" << pictureFrame.Width << endl;
	//��ȡͼ���ļ���
	inFile.read((char*)&pictureFrame.Height, sizeof(pictureFrame.Height));
	cout << dec << "��ȡ�����ļ��ĸ��ǣ�" << pictureFrame.Height << endl;
	//��ȡͼƬ����ʱ��
	inFile.read((char*)&pictureFrame.DateTime, sizeof(pictureFrame.DateTime));
	/*for (int i = 0; i < 14; i++)
	{
	cout << dec << (char)pictureFrame.DateTime[i] << endl;
	}*/
	printf("ͼƬ����ʱ���ǣ�%s\n", pictureFrame.DateTime);
	//��ȡͼƬ�¶Ⱦ�����Ϣ
	float max = 0, min = 0, sum = 0, avg = 0;
	printf("�¶Ⱦ������%d,����%d\n", pictureFrame.Width, pictureFrame.Height);
	pictureFrame.IRData = (float*)calloc(pictureFrame.Width * pictureFrame.Height, sizeof(float));
	inFile.read((char*)&pictureFrame.IRData[0], sizeof(float));

	max = pictureFrame.IRData[0], min = pictureFrame.IRData[0];
	for (int i = 1; i < pictureFrame.Width * pictureFrame.Height; i++)
	{
		inFile.read((char*)&pictureFrame.IRData[i], sizeof(float));
		//printf("��%d������¶���%f\n", i, matrix[i]);
		if (pictureFrame.IRData[i] >= max)
		{
			max = pictureFrame.IRData[i];
		}

		if (min >= pictureFrame.IRData[i])
		{
			min = pictureFrame.IRData[i];
		}
		sum = sum + pictureFrame.IRData[i];
	}
	maxTemp = max;
	minTemp = min;
	avg = sum / (pictureFrame.Width * pictureFrame.Height);
	avgTemp = avg;

	printf("�������%f,�������%f,ƽ����%f\n", max, min, avg);


	//��ȡ������
	inFile.read((char*)&pictureFrame.Emiss, sizeof(pictureFrame.Emiss));
	printf("��ȡ�ķ�������%f\n", pictureFrame.Emiss);

	//��ȡ�����¶�
	inFile.read((char*)&pictureFrame.AmbientTemperature, sizeof(pictureFrame.AmbientTemperature));
	printf("��ȡ�Ļ����¶���%f\n", pictureFrame.AmbientTemperature);

	//��ȡ��ͷ����
	inFile.read((char*)&pictureFrame.Len, sizeof(pictureFrame.Len));
	printf("��ȡ�ľ�ͷ������%s\n", pictureFrame.Len);

	//��ȡ�������
	inFile.read((char*)&pictureFrame.Distance, sizeof(pictureFrame.Distance));
	printf("��ȡ�����������%u\n", pictureFrame.Distance);

	//��ȡ���ʪ��
	inFile.read((char*)&pictureFrame.RelativeHumidity, sizeof(pictureFrame.RelativeHumidity));
	printf("��ȡ�����ʪ����%d\n", (int)pictureFrame.RelativeHumidity);

	//��ȡ�����¶�
	inFile.read((char*)&pictureFrame.ReflectiveTemperature, sizeof(pictureFrame.ReflectiveTemperature));
	printf("��ȡ�ķ����¶���%f\n", pictureFrame.ReflectiveTemperature);

	//��ȡ��������
	inFile.read((char*)&pictureFrame.Productor, sizeof(pictureFrame.Productor));
	printf("��ȡ������������%s\n", pictureFrame.Productor);

	//��ȡ��Ʒ�ͺ�
	inFile.read((char*)&pictureFrame.Type, sizeof(pictureFrame.Type));
	printf("��ȡ�Ĳ�Ʒ�ͺ���%s\n", pictureFrame.Type);

	//��ȡ��Ʒ���к�
	inFile.read((char*)&pictureFrame.SerialNO, sizeof(pictureFrame.SerialNO));
	printf("��ȡ�Ĳ�Ʒ���к���%s\n", pictureFrame.SerialNO);

	//��ȡ����
	inFile.read((char*)&pictureFrame.Longitude, sizeof(pictureFrame.Longitude));
	printf("��ȡ�ľ�����%f\n", pictureFrame.Longitude);

	//��ȡγ��
	inFile.read((char*)&pictureFrame.Latitude, sizeof(pictureFrame.Latitude));
	printf("��ȡ��γ����%f\n", pictureFrame.Latitude);

	//��ȡ����
	inFile.read((char*)&pictureFrame.Altitude, sizeof(pictureFrame.Altitude));
	printf("��ȡ�ĺ�����%d\n", pictureFrame.Altitude);

	//��ȡ��ע��Ϣ����
	inFile.read((char*)&pictureFrame.DescriptionLength, sizeof(pictureFrame.DescriptionLength));
	printf("��ȡ�ı�ע��Ϣ������%u\n", pictureFrame.DescriptionLength);

	//��ע��Ϣ����
	/*if (pictureFrame.DescriptionLength > 0) 
	{
		pictureFrame.DescriptionData = new unsigned char[pictureFrame.DescriptionLength];
		inFile.read((char*)pictureFrame.DescriptionData, pictureFrame.DescriptionLength);

		printf("��ע��Ϣ�ǣ�");
		for (unsigned int i = 0; i < pictureFrame.DescriptionLength; i++) 
		{
			printf("%c", pictureFrame.DescriptionData[i]);
		}
		printf("\n");
	}*/

	std::string y16;
	if (pictureFrame.DescriptionLength > 0) {
		pictureFrame.DescriptionData = new unsigned char[pictureFrame.DescriptionLength];
		inFile.read((char*)pictureFrame.DescriptionData, pictureFrame.DescriptionLength);

		std::string description(reinterpret_cast<const char*>(pictureFrame.DescriptionData), pictureFrame.DescriptionLength);

		size_t y16Pos = description.find("y16Data");
		if (y16Pos != std::string::npos) {
			size_t fieldValueStart = y16Pos + strlen("y16Data") + 1;  // �����ֶ�����ð��
			size_t fieldValueEnd = description.find(",", fieldValueStart);
			if (fieldValueEnd == std::string::npos) {
				fieldValueEnd = description.length();  // ���û�ж��ţ�˵�������һ���ֶ�
			}

			y16 = description.substr(fieldValueStart, fieldValueEnd - fieldValueStart);
		}
		//printf("��ע��Ϣ�ǣ�%s\n", description.c_str());
	}
	printf("�ֶ� y16Data �������ǣ�%s\n", y16);
	
	
	if (pictureFrame.DescriptionData) 
	{
		delete[] pictureFrame.DescriptionData;
		pictureFrame.DescriptionData = nullptr;
	}

	//���¶Ⱦ����ڴ�
	if (pictureFrame.IRData)
	{
		free(pictureFrame.IRData);
		pictureFrame.IRData = NULL;
	}

	//�ر��ļ�
	inFile.close();

	//�Ƚ��¶�
	float leftRange = 1, rightRange = 60;
	//�Ƚ������
	if (max > avg && fabs(max - avg) > 1e-6 && max < rightRange && fabs(max - rightRange)>1e-6 && max > leftRange && fabs(max - leftRange) > 1e-6)
		cout << "Success ! �����" << max << "��" << leftRange << "��" << rightRange << "֮��" << endl;
	else
		cout << "Fail ! �����" << max << "����" << leftRange << "��" << rightRange << endl;
	//�Ƚ������
	if (min > leftRange && fabs(min - leftRange) > 1e-6 && min < rightRange && fabs(min - rightRange)>1e-6 && min < avg && fabs(min - avg)>1e-6)
		//if ((int)lowTemp > leftRange && (int)lowTemp < rightRange )
		cout << "Success ! �����" << min << "��" << leftRange << "��" << rightRange << "֮��" << endl;
	else
		cout << "Fail ! �����" << min << "����" << leftRange << "��" << rightRange << "֮��" << endl;
	//�Ƚ�ƽ����
	if (avg > leftRange && fabs(avg - leftRange) > 1e-6 && avgTemp < max && fabs(avgTemp - max)>1e-6 && avg > min && fabs(avg - min) > 1e-6)
		cout << "Success ! ƽ����" << avg << "��" << leftRange << "��" << rightRange << "֮��" << endl;
	else
		cout << "Fail ! ƽ����" << avg << "����" << leftRange << "��" << rightRange << "֮��" << endl;

	return 0;
}



//imgPathֵ����E://20210506//20210506152031609temp.jpg
static int GetFirFile(std::string imgPath, float& maxTemp, float& minTemp, float& avgTemp)
{
	FirFrame pictureFrame;
	int readByes = 0;
	ifstream inFile(imgPath.c_str(), ios::in | ios::binary);
	if (!inFile)
	{
		cout << "error" << endl;
		return 0;
	}
	inFile.seekg(0, ios::beg);
	inFile.read((char*)&pictureFrame.FileFlag, sizeof(pictureFrame.FileFlag));
	printf("�ļ������%s\n", &pictureFrame.FileFlag);
	//��ȡ��ѧ͸����
	inFile.read((char*)&pictureFrame.OptiTrans, sizeof(pictureFrame.OptiTrans));
	cout << dec << "��ȡ�Ĺ�ѧ͸�����ǣ�" << pictureFrame.OptiTrans << endl;

	//��ȡ������
	inFile.read((char*)&pictureFrame.Emiss, sizeof(pictureFrame.Emiss));
	cout << dec << "��ȡ�ķ������ǣ�" << pictureFrame.Emiss << endl;

	//��ȡ�������
	inFile.read((char*)&pictureFrame.Distance, sizeof(pictureFrame.Distance));
	printf("��������ǣ�%f\n", pictureFrame.Distance);

	//��ȡ�����¶�
	inFile.read((char*)&pictureFrame.AmbientTemperature, sizeof(pictureFrame.AmbientTemperature));
	printf("��ȡ�Ļ����¶���%f\n", pictureFrame.AmbientTemperature);


	//��ȡ���ʪ��
	inFile.read((char*)&pictureFrame.RelativeHumidity, sizeof(pictureFrame.RelativeHumidity));
	printf("��ȡ�����ʪ����%f\n", pictureFrame.RelativeHumidity);

	//��ȡͼ���ļ���
	inFile.read((char*)&pictureFrame.Height, sizeof(pictureFrame.Height));
	cout << dec << "��ȡ�ļ��ĸ��ǣ�" << pictureFrame.Height << endl;

	//��ȡͼ���ļ���
	inFile.read((char*)&pictureFrame.Width, sizeof(pictureFrame.Width));
	cout << dec << "��ȡ�ļ��Ŀ��ǣ�" << pictureFrame.Width << endl;


	//��ȡ����
	inFile.read((char*)&pictureFrame.Precision, sizeof(pictureFrame.Precision));
	std::string preciStr = byteArrayToString(pictureFrame.Precision, 1);
	printf("��ȡ�ľ�����%s\n", preciStr.c_str());

	inFile.seekg(64, ios::beg);
	//��ȡͼƬ�¶Ⱦ�����Ϣ
	short max = 0, min = 0,avg=0;
	int sum = 0;
	printf("�¶Ⱦ������%d,����%d\n", pictureFrame.Width, pictureFrame.Height);
	pictureFrame.IRData = (short*)calloc(pictureFrame.Width * pictureFrame.Height, sizeof(short));
	inFile.read((char*)&pictureFrame.IRData[0], sizeof(short));


	max = pictureFrame.IRData[0], min = pictureFrame.IRData[0];
	for (int i = 1; i < pictureFrame.Width * pictureFrame.Height; i++)
	{
		inFile.read((char*)&pictureFrame.IRData[i], sizeof(short));
		//printf("��%d������¶���%d\n", i, &pictureFrame.IRData[i]);
		if (pictureFrame.IRData[i] >= max)
		{
			max = pictureFrame.IRData[i];
		}

		if (min >= pictureFrame.IRData[i])
		{
			min = pictureFrame.IRData[i];
		}
		sum = sum + pictureFrame.IRData[i];
	}
	cout << sum << endl;
	maxTemp = (float)max / 10;
	minTemp = (float)min / 10;
	avg = sum / (pictureFrame.Width * pictureFrame.Height);
	avgTemp = (float)avg/10;

	//printf("�������%f,�������%f\n", (float)max/10, (float)min/10);
	cout << "������ǣ�" << setprecision(3) << (float)max / 10 << endl;
	cout << "������ǣ�" << setprecision(3) << (float)min / 10 << endl;
	cout << "ƽ�����ǣ�" << setprecision(3) << (float)avg / 10 << endl;

	//���¶Ⱦ����ڴ�
	if (pictureFrame.IRData)
	{
		free(pictureFrame.IRData);
		pictureFrame.IRData = NULL;
	}

	//�ر��ļ�
	inFile.close();

	return 0;
}


int main()
{
	float max;
	float min;
	float avg;
	int a = 0;
	int b = 0;

	string heatmap, firmap;

	int nums;
	cout << "Enter picture nums:" << endl;
	cin >> nums;

	for (int i = 1; i <= nums; i++)   //��ͼ����
	{
		cout << "��" << i << "�εķ������Ϊ" << endl;
		//heatmap = "D:/Testpicture/heatmap_" + std::to_string(i) + ".jpg";
		heatmap = "C:\\Users\\gd09186\\Desktop\\IR_Common_20240529_103404680(1).jpg";
		GetGWTempEx(heatmap, max, min, avg);
		if (max < 100 && min >0)
		{
			a += 1;
			cout << "��" << a << "��������Ƭ" << endl;
		}
		else
		{
			b += 1;
			cout << "�쳣��Ƭ" << endl;
			cout << "��" << b << "���쳣��Ƭ" << endl;

		}
		cout << endl;
		cout << endl;
	}
	
	cout << "����ͼƬ������" << a << endl;
	cout << "�쳣ͼƬ������" << b << endl;
	cout << "ͼƬ�쳣�ʣ�" << b / (a + b) << endl;

}
	//----------------------------------------------------------------------------------------------------------------------


//	for (int i = 1; i <= 134; i++)    //��ѹ��ͼ����	
//	{
//		cout << "��" << i << "�εķ������Ϊ" << endl;
//		firmap = "D:/Test/ZU08D_firmap/firmap/Ubuntu22.04_ASIC11.6_ARMAPP1.3.21/firmap_" + std::to_string(i)+".fir" ;
//		//firmap = "D:/Test/ZU08D_firmap/firmap/202211241435110682784.fir";
//		GetFirFile(firmap,max,min,avg);	
//		if (max<100 && min >-100)
//		{
//			a += 1;
//			cout << "��" << a << "��������Ƭ" << endl;
//		}
//		else
//		{
//			b += 1;
//			cout << "�쳣��Ƭ" << endl;
//			cout << "��" << b << "���쳣��Ƭ" << endl;
//
//		}
//		cout << endl;
//		cout << endl;
//		cout << endl;
//		cout << endl;
//	}
//	cout << "����ͼƬ������" << a << endl;
//	cout << "�쳣ͼƬ������" << b << endl;
//	cout << "ͼƬ�쳣�ʣ�" << b / (a + b) << endl;
//
//
//	return 0;
//}
