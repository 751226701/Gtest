/*
01 ��ITA_DLT��ͼ��ȡ�¶Ⱦ���
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_TEMPMATRIX_INFO dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];

	result =ITA_GetTempMatrixInfo(instance, file, heatMapType, &dltMatrixInfo);
	if (result == ITA_OK)
	{
		cout << "��ȡ�ɹ���" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}


02 ��ITA_FIR��ͼ��ȡ�¶Ⱦ���
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.fir";
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITATempMatrixInfo dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];

	result =ITA_GetTempMatrixInfo(instance, file, heatMapType, &dltMatrixInfo);
	if (result == ITA_OK)
	{
		cout << "��ȡ�ɹ���" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}

03 �����ļ�����ͼ���Ͳ�ƥ��1
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITATempMatrixInfo dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];
	
	result =ITA_GetTempMatrixInfo(instance, file, heatMapType, &dltMatrixInfo);
	if (result == ITA_OK)    //result=-2
	{
		cout << "��ȡ�ɹ���" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}

04 �����ļ�����ͼ���Ͳ�ƥ��2
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.fir";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITATempMatrixInfo dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];

	result =ITA_GetTempMatrixInfo(instance, file, heatMapType, &dltMatrixInfo);
	if (result == ITA_OK)   //result=-2
	{
		cout << "��ȡ�ɹ���" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}

05 ��ȡDLT��ͼ�¶Ⱦ���ʱ�����ļ�·������
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpgsss";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITATempMatrixInfo dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];
	
	result =ITA_GetTempMatrixInfo(instance, file, heatMapType, &dltMatrixInfo);
	if (result == ITA_OK)  //result = -3
	{
		cout << "��ȡ�ɹ���" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}

06 ��ȡDLT��ͼ�¶Ⱦ���ʱ�����ļ�·��������
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicturess/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITATempMatrixInfo dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];

	result =ITA_GetTempMatrixInfo(instance, file, heatMapType, &dltMatrixInfo);
	if (result == ITA_OK)   //result = -3
	{
		cout << "��ȡ�ɹ���" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}

07 ��ȡFIR��ͼ�¶Ⱦ���ʱ�����ļ�·������
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.firs";
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITATempMatrixInfo dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];
	
	result =ITA_GetTempMatrixInfo(instance, file, heatMapType, &dltMatrixInfo);
	if (result == ITA_OK)    //result = -3
	{
		cout << "��ȡ�ɹ���" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}

08 ��ȡFIR��ͼ�¶Ⱦ���ʱ�����ļ�·��������
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPictures/test.fir";
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITATempMatrixInfo dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];
	
	result =ITA_GetTempMatrixInfo(instance, file, heatMapType, &dltMatrixInfo);
	if (result == ITA_OK)  //result = -3
	{
		cout << "��ȡ�ɹ���" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}

09 ��ȡDLT��ͼ�¶Ⱦ���ʱhandle�����ָ��
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITATempMatrixInfo dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];
	
	result =ITA_GetTempMatrixInfo(NULL, file, heatMapType, &dltMatrixInfo);
	if (result == ITA_OK)  //result = -1001
	{
		cout << "��ȡ�ɹ���" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}

10 ��ȡDLT��ͼ�¶Ⱦ���ʱ������������ָ��
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITATempMatrixInfo dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];
	
	result =ITA_GetTempMatrixInfo(instance, file, heatMapType, NULL);
	if (result == ITA_OK)  //result = -1001
	{
		cout << "��ȡ�ɹ���" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}

11 ��ȡFIR��ͼ�¶Ⱦ���ʱhandle�����ָ��
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.fir";
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITATempMatrixInfo dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];
	
	result =ITA_GetTempMatrixInfo(NULL, file, heatMapType, &dltMatrixInfo);
	if (result == ITA_OK)  //result = -1001
	{
		cout << "��ȡ�ɹ���" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}

12 ��ȡFIR��ͼ�¶Ⱦ���ʱ������������ָ��
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.fir";
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITATempMatrixInfo dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];
	
	result =ITA_GetTempMatrixInfo(instance, file, heatMapType, NULL);
	if (result == ITA_OK)  //result = -1001
	{
		cout << "��ȡ�ɹ���" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}

13 ��ITA_DLT��ͼ��ȡY16����
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[width * height];
	
	result = ITA_GetY16MatrixInfo(instance, file, heatMapType, &y16MaxtrixInfo);
	if (result == ITA_OK)
	{
		cout << "��ȡ�ɹ���" << endl;
		saveY16Matrix(&y16MaxtrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}

14 �����ļ�����ͼ���Ͳ�ƥ��1
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[width * height];
	
	result = ITA_GetY16MatrixInfo(instance, file, heatMapType, &y16MaxtrixInfo);
	if (result == ITA_OK)   //result = -2
	{
		cout << "��ȡ�ɹ���" << endl;
		saveY16Matrix(&y16MaxtrixInfo);
		getY16TempMatrixMaxMinTemp(&y16MaxtrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}

15 ��ȡDLT��ͼY16����ʱ�����ļ�·������
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpgs";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[width * height];
	
	result = ITA_GetY16MatrixInfo(instance, file, heatMapType, &y16MaxtrixInfo);
	if (result == ITA_OK)   //result = -3
	{
		cout << "��ȡ�ɹ���" << endl;
		saveY16Matrix(&y16MaxtrixInfo);
		getY16TempMatrixMaxMinTemp(&y16MaxtrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}

16 ��ȡDLT��ͼY16����ʱ�����ļ�·��������
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPictures/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[width * height];
	
	result = ITA_GetY16MatrixInfo(instance, file, heatMapType, &y16MaxtrixInfo);
	if (result == ITA_OK)   //result = -3
	{
		cout << "��ȡ�ɹ���" << endl;
		saveY16Matrix(&y16MaxtrixInfo);
		getY16TempMatrixMaxMinTemp(&y16MaxtrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}

17 ��ȡDLT��ͼY16����ʱhandle�����ָ��
int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[width * height];

	result = ITA_GetY16MatrixInfo(NULL, file, heatMapType, &y16MaxtrixInfo);
	if (result == ITA_OK)   //result = -1001
	{
		cout << "��ȡ�ɹ���" << endl;
		saveY16Matrix(&y16MaxtrixInfo);
		getY16TempMatrixMaxMinTemp(&y16MaxtrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}
	
18 ��ȡDLT��ͼY16����ʱ������������ָ��
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[width * height];
	
	result = ITA_GetY16MatrixInfo(instance, file, heatMapType, NULL);
	if (result == ITA_OK)
	{
		cout << "��ȡ�ɹ���" << endl;
		saveY16Matrix(&y16MaxtrixInfo);
		getY16TempMatrixMaxMinTemp(&y16MaxtrixInfo);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}

19 ��DLT��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת90��
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_TEMPMATRIX_INFO dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &dltMatrixInfo);
	if (result == ITA_OK)
	{
		cout << "��ȡ�¶Ⱦ���ɹ���" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);

		ITA_ROTATE_TYPE rotateType = ITA_ROTATE_90;
		ITA_TEMPMATRIX_INFO dstInfo;
		dstInfo.tempMatrix = new float[width * height];
		dstInfo.w = 0;
		dstInfo.h = 0;
		result = ITA_TempMatrixRotation(instance, &dltMatrixInfo, rotateType, dstInfo.tempMatrix, &(dstInfo.w), &(dstInfo.h));
		if (result == ITA_OK)
		{
			printf("��תǰ�Ŀ�Ϊ��%d   ��תǰ�ĸ�Ϊ��%d \n", dltMatrixInfo.w, dltMatrixInfo.h);
			printf("�¶Ⱦ�����ת�ɹ�����ת��Ŀ�Ϊ��%d   ��ת��ĸ�Ϊ��%d \n", dstInfo.w, dstInfo.h);
			int w = dstInfo.w;
			int h = dstInfo.h;
			int dltmatrix_len = w * h * 3;
			ITA_PALETTE_TYPE palette_index = ITA_IRON_RED;
			unsigned char* rgbData = new unsigned char[dltmatrix_len];
			result = ITA_TempMatrix2Rgb(instance, &dstInfo, palette_index, rgbData, dltmatrix_len);
			if (result == ITA_OK)
			{
				cout << "תRGB���ݳɹ�" << endl;
				saveRGBasRaw("rgb.raw", rgbData, dltmatrix_len);
			}
			else
			{
				cout << "תRGB����ʧ��,result is:" <<result<< endl;
			}	
			delete[] rgbData;
		}
		else
		{
			printf("�¶Ⱦ�����תʧ�ܣ�result is��%d", result);
		}
		delete[] dstInfo.tempMatrix;
	}
	else
	{
		cout << "��ȡ�¶Ⱦ���ʧ��,result is:" << result << endl;
	}

	delete[] dltMatrixInfo.tempMatrix; 

20 ��DLT��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת180��

21 ��DLT��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת270��

22 ��DLT��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת

   ��FIR��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת90��
   int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.fir";
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO firMatrixInfo;
	firMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &firMatrixInfo);
	if (result == ITA_OK)
	{
		cout << "��ȡ�¶Ⱦ���ɹ���" << endl;
		saveTempMatrix(&firMatrixInfo);
		getTempMatrixMaxMinTemp(&firMatrixInfo);

		ITA_ROTATE_TYPE rotateType = ITA_ROTATE_NONE;
		ITA_TEMPMATRIX_INFO dstInfo;
		dstInfo.tempMatrix = new float[width * height];
		dstInfo.w = 0;
		dstInfo.h = 0;
		result = ITA_TempMatrixRotation(instance, &firMatrixInfo, rotateType, dstInfo.tempMatrix, &(dstInfo.w), &(dstInfo.h));
		if (result == ITA_OK)
		{
			printf("��תǰ�Ŀ�Ϊ��%d   ��תǰ�ĸ�Ϊ��%d \n", firMatrixInfo.w, firMatrixInfo.h);
			printf("�¶Ⱦ�����ת�ɹ�����ת��Ŀ�Ϊ��%d   ��ת��ĸ�Ϊ��%d \n", dstInfo.w, dstInfo.h);
			int w = dstInfo.w;
			int h = dstInfo.h;
			int dltmatrix_len = w * h * 3;
			ITA_PALETTE_TYPE palette_index = ITA_IRON_RED;
			unsigned char* rgbData = new unsigned char[dltmatrix_len];
			result = ITA_TempMatrix2Rgb(instance, &dstInfo, palette_index, rgbData, dltmatrix_len);
			if (result == ITA_OK)
			{
				cout << "תRGB���ݳɹ�" << endl;
				saveRGBasRaw("rgb.raw", rgbData, dltmatrix_len);
			}
			else
			{
				cout << "תRGB����ʧ��,result is:" <<result<< endl;
			}
			delete[] rgbData;
		}
		else
		{
			printf("�¶Ⱦ�����תʧ�ܣ�result is��%d", result);
		}
		delete[] dstInfo.tempMatrix;
	}
	else
	{
		cout << "��ȡ�¶Ⱦ���ʧ��,result is:" << result << endl;
	}

	delete[] firMatrixInfo.tempMatrix;

   ��FIR��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת180��
   ��FIR��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת270��
   ��DLT��ͼ��ȡ�¶Ⱦ��������¶Ⱦ�����ת

23 handle�����ָ��

24 �����¶Ⱦ������ָ��

25 ����¶Ⱦ������ָ��

26 ��������ָ��

27 ����ߴ����ָ��

28 ���¶Ⱦ���תΪ����RGB����
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.fir";
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &dltMatrixInfo);
	if (result == ITA_OK)
	{
		cout << "��ȡ�¶Ⱦ���ɹ���" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);

		int w = dltMatrixInfo.w;
		int h = dltMatrixInfo.h;
		int dltmatrix_len = w * h*3;
		ITA_PALETTE_TYPE palette_index = ITA_WHITE_HEAT;
		unsigned char* rgbData = new unsigned char[dltmatrix_len];
		result = ITA_TempMatrix2Rgb(instance, &dltMatrixInfo, palette_index, rgbData, dltmatrix_len);
		if (result == ITA_OK)
		{
			cout << "תRGB���ݳɹ�" << endl;
			saveRGBasRaw("rgb.raw", rgbData, dltmatrix_len);
		}
		else
		{
			cout << "תRGB����ʧ��,result is:" << result << endl;
		}
		delete[] rgbData;
	}
	else
	{
		cout << "��ȡ�¶Ⱦ���ʧ��,result is:" << result << endl;
	}

	delete[] dltMatrixInfo.tempMatrix;

29 ���¶Ⱦ���תΪ����RGB����

30 ���¶Ⱦ���תΪ����RGB����

31 ���¶Ⱦ���תΪ����RGB����

32 ���¶Ⱦ���תΪҽ��RGB����

33 ���¶Ⱦ���תΪ����RGB����

34 ���¶Ⱦ���תΪ�ʺ�RGB����

35 ���¶Ⱦ���תΪ�ʺ�2RGB����

36 ���¶Ⱦ���תΪ����RGB����

37 ���¶Ⱦ���תΪ����ɸ��RGB����

38 ���¶Ⱦ���תΪ���RGB����

39 ���¶Ⱦ���תΪ����RGB����

40 ���¶Ⱦ���תΪ����RGB����

41 ���¶Ⱦ���תΪҽ��1RGB����

42 ���¶Ⱦ���תΪҽ��2RGB����

43 ���¶Ⱦ���תΪҽ��3RGB����

44 ���¶Ⱦ���תΪ�ʺ�3RGB����

45 ���¶Ⱦ���תΪ���2RGB����

46 ���¶Ⱦ���תΪ���3RGB����

47 ���¶Ⱦ���תΪ����RGB����

48 ���¶Ⱦ���תΪ������RGB����

49 ���¶Ⱦ���תΪ�ֲ�RGB����

50 ���¶Ⱦ���תΪ���RGB����

51 ���¶Ⱦ���תΪ����RGB����

52 ���¶Ⱦ���תΪ����RGB����

53 ���¶Ⱦ���תΪ����RGB����

54 RGB���ݵ��ڴ泤������ƫС

55 handle�����ָ��

56 �����¶Ⱦ������ָ��

57 ���RGB���ݴ����ָ��

58 ��ȡ�¶Ⱦ�������������
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.fir";
	ITA_HEATMAP_TYPE heatMapType = ITA_FIR;
	ITA_TEMPMATRIX_INFO dltMatrixInfo;
	dltMatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &dltMatrixInfo);
	if (result == ITA_OK)
	{
		cout << "��ȡ�¶Ⱦ���ɹ���" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);

		float maxT = 0.0;
		float minT = 0.0;
		result =ITA_GetTempMatrixMaxMinT(instance, &dltMatrixInfo, &maxT, &minT);
		if (result == ITA_OK)
		{
			printf(" maxT:%f    minT:%f \n", maxT, minT);
		}
		else
		{
			printf("��ȡ�ȶ���������������ʧ�ܣ� result is ��%d", result);
		}
	}
	else
	{
		cout << "��ȡ�¶Ⱦ���ʧ��,result is:" << result << endl;
	}

	delete[] dltMatrixInfo.tempMatrix;

59 handle�����ָ��

60 �¶Ⱦ������ָ��

61 ����´����ָ��

62 ����´����ָ��

63 ��ȡ����ɫ����ɫ��������
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	
	ITA_PALETTE_TYPE Index = ITA_BLUE_HOT;
	const int len = 1024;
	unsigned char* colorStripData = new unsigned char[len];
	result = ITA_GetColorStripData(instance, Index, colorStripData, len);
	if (result == ITA_OK)
	{
		cout << "��ȡɫ�������ݳɹ���" << endl;
		saveColorStripData("����.raw", colorStripData, len);
	}
	else
	{
		cout << "��ȡɫ��������ʧ�ܣ�result is��" << result << endl;
	}

64 ��ȡ����ɫ����ɫ��������

65 ��ȡ����ɫ����ɫ��������

66 ��ȡ����ɫ����ɫ��������

67 ��ȡҽ��ɫ����ɫ��������

68 ��ȡ����ɫ����ɫ��������

69 ��ȡ�ʺ�ɫ����ɫ��������

70 ��ȡ�ʺ�2ɫ����ɫ��������

71 ��ȡ����ɫ����ɫ��������

72 ��ȡ����ɸ��ɫ����ɫ��������

73 ��ȡ���ɫ����ɫ��������

74 ��ȡ����ɫ����ɫ��������

75 ��ȡ����ɫ����ɫ��������

76 ��ȡҽ��1ɫ����ɫ��������

77 ��ȡҽ��2ɫ����ɫ��������

78 ��ȡҽ��3ɫ����ɫ��������

79 ��ȡ�ʺ�3ɫ����ɫ��������

80 ��ȡ���2ɫ����ɫ��������

81 ��ȡ���3ɫ����ɫ��������

82 ��ȡ����ɫ����ɫ��������

83 ��ȡ������ɫ����ɫ��������

84 ��ȡ�ֲ�ɫ����ɫ��������

85 ��ȡ���ɫ����ɫ��������

86 ��ȡ����ɫ����ɫ��������

87 ��ȡ����ɫ����ɫ��������

88 ��ȡ����ɫ����ɫ��������

89 ����handleΪ��ָ��

90 �����len���ȹ�С

91 ��DLT��ͼ��ȡ�¶Ⱦ����ʹ�ð���RBG����������ͼ
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	ITAHeatMapInputInfo inputinfo;
	inputinfo.w = width;
	inputinfo.h = height;
	inputinfo.tempMatrix = new float[width * height];
	inputinfo.tempMatrixLen = width * height * sizeof(float);
	inputinfo.rgb = new unsigned char[width * height * 3];
	inputinfo.rgbLen = width * height * 3;

	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_TEMPMATRIX_INFO MatrixInfo;
	MatrixInfo.tempMatrix = new float[width * height];

	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &MatrixInfo);
	if (result == ITA_OK)
	{
		cout << "��ȡ�¶Ⱦ���ɹ���" << endl;

		int w = MatrixInfo.w;
		int h = MatrixInfo.h;
		int matrix_len = w * h * 3;
		ITA_PALETTE_TYPE palette_index = ITA_WINTER;
		unsigned char* rgbData = new unsigned char[matrix_len];
		result = ITA_TempMatrix2Rgb(instance, &MatrixInfo, palette_index, rgbData, matrix_len);
		if (result == ITA_OK)
		{
			cout << "תRGB���ݳɹ�" << endl;
			inputinfo.tempMatrix = MatrixInfo.tempMatrix;
			inputinfo.rgb = rgbData;
			ITAHeatMapOutput outPutInfo;
			result = ITA_GenerateHeapMapJpg(instance, &inputinfo, &outPutInfo);
			if (result == ITA_OK)
			{
				saveJpgPicture("����.jpg", outPutInfo.jpgBuf, outPutInfo.jpgBufLen);
			}
			else
			{
				cout << "��Ƭ����ʧ�ܣ� result is��" << result << endl;
			}
			delete[] inputinfo.tempMatrix;
			delete[] inputinfo.rgb;
		}
		else
		{
			cout << "תRGB����ʧ��,result is:" << result << endl;
		}
		delete[] rgbData;
	}
	else
	{
		cout << "��ȡ�¶Ⱦ���ʧ��,result is:" << result << endl;
	}
	delete[] MatrixInfo.tempMatrix;

	ITA_HeatmapUninit(instance);
   
92 ........����26��α��...........................................

93 DLT��ͼY16����תRGB������
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	ITAHeatMapInputInfo inputinfo;
	inputinfo.w = width;
	inputinfo.h = height;
	inputinfo.tempMatrix = new float[width * height];
	inputinfo.tempMatrixLen = width * height * sizeof(float);
	inputinfo.rgb = new unsigned char[width * height * 3];
	inputinfo.rgbLen = width * height * 3;
	
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_TEMPMATRIX_INFO MatrixInfo;
	MatrixInfo.tempMatrix = new float[width * height];
	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &MatrixInfo);
	if (result == ITA_OK)
	{
		cout << "��ȡ�¶Ⱦ���ɹ���" << endl;
	}
	else
	{
		cout << "��ȡ�¶Ⱦ���ʧ��,result is:" << result << endl;
	}

	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[inputinfo.w * inputinfo.h];
	result = ITA_GetY16MatrixInfo(instance, file, heatMapType, &y16MaxtrixInfo);
	if (result == ITA_OK)
	{
		cout << "��ȡY16����ɹ���" << endl;
		saveY16Matrix(&y16MaxtrixInfo);

		ITA_MODE mode = ITA_Y16;
		ITA_RANGE range = ITA_INDUSTRY_LOW;
		int cameraID = 1;
		HANDLE_T handle = ITA_Init(mode, range, width, height, cameraID);

		ITAISPResult resultinfo;
		int srcSize = width * height * sizeof(short);
		unsigned char* srcData = new unsigned char[srcSize];
		ConvertShortToUnsignedChar(y16MaxtrixInfo.y16Matrix, srcData, height, width);
		result = ITA_ISP(handle, srcData, srcSize, &resultinfo);
		if (result == ITA_OK)
		{
			cout << "ͼ����ɹ���" << endl;

			ITAHeatMapOutput outputinfo;
			inputinfo.tempMatrix = MatrixInfo.tempMatrix;
			inputinfo.rgb = resultinfo.imgDst;
			result=ITA_GenerateHeapMapJpg(instance, &inputinfo, &outputinfo);
			if (result == ITA_OK) { saveJpgPicture("Y16����.jpg", outputinfo.jpgBuf, outputinfo.jpgBufLen); }
			else { cout << "��ͼ����ʧ��" << endl; }
		}
		else
		{
			cout << "ͼ����ʧ�ܣ�" << endl;
		}
		ITA_Uninit(handle);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}
	
	delete[] inputinfo.tempMatrix;
	delete[] inputinfo.rgb;
	delete[] y16MaxtrixInfo.y16Matrix;
	delete[] MatrixInfo.tempMatrix;
	ITA_HeatmapUninit(instance);

94 ��DLT��ͼY16�����ֶ����⡢�����¿�����¡�����£�
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	ITAHeatMapInputInfo inputinfo;
	inputinfo.w = width;
	inputinfo.h = height;
	inputinfo.tempMatrix = new float[width * height];
	inputinfo.tempMatrixLen = width * height * sizeof(float);
	inputinfo.rgb = new unsigned char[width * height * 3];
	inputinfo.rgbLen = width * height * 3;
	
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_TEMPMATRIX_INFO MatrixInfo;
	MatrixInfo.tempMatrix = new float[width * height];
	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &MatrixInfo);
	if (result == ITA_OK)
	{
		cout << "��ȡ�¶Ⱦ���ɹ���" << endl;
	}
	else
	{
		cout << "��ȡ�¶Ⱦ���ʧ��,result is:" << result << endl;
	}

	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[inputinfo.w * inputinfo.h];
	result = ITA_GetY16MatrixInfo(instance, file, heatMapType, &y16MaxtrixInfo);
	if (result == ITA_OK)
	{
		cout << "��ȡY16����ɹ���" << endl;
		saveY16Matrix(&y16MaxtrixInfo);

		ITA_MODE mode = ITA_Y16;
		ITA_RANGE range = ITA_INDUSTRY_LOW;
		int cameraID = 1;
		HANDLE_T handle = ITA_Init(mode, range, width, height, cameraID);

		ITA_DRT_TYPE type = ITA_DRT_MANUAL;
		ITADRTParam Param;
		Param.manltone_minY16 = 2000;
		Param.manltone_maxY16 = 5000;
		result = ITA_DimmingType(handle, type, &Param);
		if (result == ITA_OK) { cout << "�����¿�ɹ���" << endl; }
		else { cout << "�����¿�ʧ�ܣ�result is��"<<result << endl; }

		ITAISPResult resultinfo;
		int srcSize = width * height * sizeof(short);
		unsigned char* srcData = new unsigned char[srcSize];
		ConvertShortToUnsignedChar(y16MaxtrixInfo.y16Matrix, srcData, height, width);
		result = ITA_ISP(handle, srcData, srcSize, &resultinfo);
		if (result == ITA_OK)
		{
			cout << "ͼ����ɹ���" << endl;

			ITAHeatMapOutput outputinfo;
			inputinfo.tempMatrix = MatrixInfo.tempMatrix;
			inputinfo.rgb = resultinfo.imgDst;
			result=ITA_GenerateHeapMapJpg(instance, &inputinfo, &outputinfo);
			if (result == ITA_OK) { saveJpgPicture("Y16�ֶ�����.jpg", outputinfo.jpgBuf, outputinfo.jpgBufLen); }
			else { cout << "��ͼ����ʧ��" << endl; }
		}
		else
		{
			cout << "ͼ����ʧ�ܣ�" << endl;
		}
		ITA_Uninit(handle);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}
	
	delete[] inputinfo.tempMatrix;
	delete[] inputinfo.rgb;
	delete[] y16MaxtrixInfo.y16Matrix;
	delete[] MatrixInfo.tempMatrix;
	ITA_HeatmapUninit(instance);

95 ��DLT��ͼY16�����������ȡ��Աȶȡ���ȡ�ϸ����ǿ
	int width = 640;
	int height = 512;
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	ITAHeatMapInputInfo inputinfo;
	inputinfo.w = width;
	inputinfo.h = height;
	inputinfo.tempMatrix = new float[width * height];
	inputinfo.tempMatrixLen = width * height * sizeof(float);
	inputinfo.rgb = new unsigned char[width * height * 3];
	inputinfo.rgbLen = width * height * 3;
	
	char file[] = "D:/APP/VS2022/project/Gtest/Gtest/testPicture/test.jpg";
	ITA_HEATMAP_TYPE heatMapType = ITA_DLT;
	ITA_TEMPMATRIX_INFO MatrixInfo;
	MatrixInfo.tempMatrix = new float[width * height];
	result = ITA_GetTempMatrixInfo(instance, file, heatMapType, &MatrixInfo);
	if (result == ITA_OK)
	{
		cout << "��ȡ�¶Ⱦ���ɹ���" << endl;
	}
	else
	{
		cout << "��ȡ�¶Ⱦ���ʧ��,result is:" << result << endl;
	}

	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[inputinfo.w * inputinfo.h];
	result = ITA_GetY16MatrixInfo(instance, file, heatMapType, &y16MaxtrixInfo);
	if (result == ITA_OK)
	{
		cout << "��ȡY16����ɹ���" << endl;
		saveY16Matrix(&y16MaxtrixInfo);

		ITA_MODE mode = ITA_Y16;
		ITA_RANGE range = ITA_INDUSTRY_LOW;
		int cameraID = 1;
		HANDLE_T handle = ITA_Init(mode, range, width, height, cameraID);

		int bright = 125;
		int contrast = 255;
		bool sharpening = false;
		bool enhance = false;
		ITA_ImageControl(handle, ITA_SET_BRIGHTNESS, &bright); //��������
		ITA_ImageControl(handle, ITA_SET_CONTRAST, &contrast); //���öԱȶ�
		ITA_ImageControl(handle, ITA_SHARPENING, &sharpening); //�������
		ITA_ImageControl(handle, ITA_DETAIL_ENHANCE, &enhance); //����ϸ����ǿ

		ITAISPResult resultinfo;
		int srcSize = width * height * sizeof(short);
		unsigned char* srcData = new unsigned char[srcSize];
		ConvertShortToUnsignedChar(y16MaxtrixInfo.y16Matrix, srcData, height, width);
		result = ITA_ISP(handle, srcData, srcSize, &resultinfo);
		if (result == ITA_OK)
		{
			cout << "ͼ����ɹ���" << endl;

			ITAHeatMapOutput outputinfo;
			inputinfo.tempMatrix = MatrixInfo.tempMatrix;
			inputinfo.rgb = resultinfo.imgDst;
			result=ITA_GenerateHeapMapJpg(instance, &inputinfo, &outputinfo);
			if (result == ITA_OK) { saveJpgPicture("Y16�ֶ�����ϸ����ǿ��.jpg", outputinfo.jpgBuf, outputinfo.jpgBufLen); }
			else { cout << "��ͼ����ʧ��" << endl; }
		}
		else
		{
			cout << "ͼ����ʧ�ܣ�" << endl;
		}
		ITA_Uninit(handle);
	}
	else
	{
		cout << "��ȡʧ��,result is:" << result << endl;
	}
	
	delete[] inputinfo.tempMatrix;
	delete[] inputinfo.rgb;
	delete[] y16MaxtrixInfo.y16Matrix;
	delete[] MatrixInfo.tempMatrix;
	ITA_HeatmapUninit(instance);
96 
97 
98 
99 











































*/
