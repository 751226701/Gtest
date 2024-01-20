#include"common.h"

//1 ��ȡ�¶Ⱦ���
int GetTempMatrixInfo()
{
	::testing::GTEST_FLAG(filter) = "GetTempMatrixInfo.*";
	return RUN_ALL_TESTS();
}
//2 ��ȡY16����
int GetY16MatrixInfo()
{
    ::testing::GTEST_FLAG(filter) = "GetY16MatrixInfo.*";
    return RUN_ALL_TESTS();
}
//3 �¶Ⱦ�����ת
int TempMatrixRotation()
{
    ::testing::GTEST_FLAG(filter) = "TempMatrixRotation.*";
    return RUN_ALL_TESTS();
}
//4 �¶Ⱦ���תRGB
int TempMatrix2Rgb()
{
    ::testing::GTEST_FLAG(filter) = "TempMatrix2Rgb.*:*TempMatrix2RgbParam.*";
    return RUN_ALL_TESTS();
}
//5 ��ȡ�¶Ⱦ�������¡������
int GetTempMatrixMaxMinT()
{
    ::testing::GTEST_FLAG(filter) = "GetTempMatrixMaxMinT.*";
    return RUN_ALL_TESTS();
}
//6 ��ȡɫ��������
int GetColorStripData()
{
    ::testing::GTEST_FLAG(filter) = "*GetColorStripData.*:GetColorStripDataNoParam.*";
    return RUN_ALL_TESTS();
}
//7 ������ͼ
int GenerateHeapMapJpg()
{
    ::testing::GTEST_FLAG(filter) = "GenerateHeapMapJpg.*:*GenerateHeapMapJpgParam.*";
    return RUN_ALL_TESTS();
}
//8 Y16תRGB������
int Y16Set()
{
    ::testing::GTEST_FLAG(filter) = "Y16Set.*";
    return RUN_ALL_TESTS();
}
//9 ִ�����в���
int RunAllTest()
{
    return RUN_ALL_TESTS();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int choice;
    int ret = 0;
    do {
        cout << endl; cout << endl;
        cout << "******************ITA_SDK_TEST*********************" << endl;
        cout << "Choose a test suite to run:" << endl;
        cout << "1.��ȡ�¶Ⱦ���(GetTempMatrixInfo)" << endl;
        cout << "2.��ȡY16����(GetY16MatrixInfo)" << endl;
        cout << "3.�¶Ⱦ�����ת(TempMatrixRotation)" << endl;
        cout << "4.�¶Ⱦ���תRGB(TempMatrix2Rgb)" << endl;
        cout << "5.��ȡ�¶Ⱦ�������¡������(GetTempMatrixMaxMinT)" << endl;
        cout << "6.��ȡɫ��������(GetColorStripData)" << endl;
        cout << "7.������ͼ(GenerateHeapMapJpg)" << endl;
        cout << "8.Y16תRGB������(Y16Set)" << endl;
        cout << "9.RunAllTest" << endl;
        cout << "0.Exit" << endl;
        cout << "***************************************************" << endl;
        cout << "Enter your choice: " << endl;
        cin >> choice;
        cout << endl;

        switch (choice) 
        {
        case 1:
            ret = GetTempMatrixInfo();
            break;
        case 2:
            ret = GetY16MatrixInfo();
            break;
        case 3:
            ret = TempMatrixRotation();
            break;
        case 4:
            ret = TempMatrix2Rgb();
            break;
        case 5:
            ret = GetTempMatrixMaxMinT();
            break;
        case 6:
            ret = GetColorStripData();
            break;
        case 7:
            ret = GenerateHeapMapJpg();
            break;
        case 8:
            ret = Y16Set();
            break;
        case 9:
            ret = RunAllTest();
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }

    } while (choice != 0);

    return ret;
}