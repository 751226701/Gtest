/*
01 从ITA_DLT热图获取温度矩阵
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
		cout << "获取成功！" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}


02 从ITA_FIR热图获取温度矩阵
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
		cout << "获取成功！" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}

03 传入文件与热图类型不匹配1
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
		cout << "获取成功！" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}

04 传入文件与热图类型不匹配2
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
		cout << "获取成功！" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}

05 获取DLT热图温度矩阵时传入文件路径错误
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
		cout << "获取成功！" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}

06 获取DLT热图温度矩阵时传入文件路径不存在
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
		cout << "获取成功！" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}

07 获取FIR热图温度矩阵时传入文件路径错误
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
		cout << "获取成功！" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}

08 获取FIR热图温度矩阵时传入文件路径不存在
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
		cout << "获取成功！" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}

09 获取DLT热图温度矩阵时handle传入空指针
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
		cout << "获取成功！" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}

10 获取DLT热图温度矩阵时输出参数传入空指针
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
		cout << "获取成功！" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}

11 获取FIR热图温度矩阵时handle传入空指针
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
		cout << "获取成功！" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}

12 获取FIR热图温度矩阵时输出参数传入空指针
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
		cout << "获取成功！" << endl;
		saveTempMatrix(&dltMatrixInfo);
		getTempMatrixMaxMinTemp(&dltMatrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}

13 从ITA_DLT热图获取Y16矩阵
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
		cout << "获取成功！" << endl;
		saveY16Matrix(&y16MaxtrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}

14 传入文件与热图类型不匹配1
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
		cout << "获取成功！" << endl;
		saveY16Matrix(&y16MaxtrixInfo);
		getY16TempMatrixMaxMinTemp(&y16MaxtrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}

15 获取DLT热图Y16矩阵时传入文件路径错误
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
		cout << "获取成功！" << endl;
		saveY16Matrix(&y16MaxtrixInfo);
		getY16TempMatrixMaxMinTemp(&y16MaxtrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}

16 获取DLT热图Y16矩阵时传入文件路径不存在
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
		cout << "获取成功！" << endl;
		saveY16Matrix(&y16MaxtrixInfo);
		getY16TempMatrixMaxMinTemp(&y16MaxtrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}

17 获取DLT热图Y16矩阵时handle传入空指针
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
		cout << "获取成功！" << endl;
		saveY16Matrix(&y16MaxtrixInfo);
		getY16TempMatrixMaxMinTemp(&y16MaxtrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}
	
18 获取DLT热图Y16矩阵时输出参数传入空指针
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
		cout << "获取成功！" << endl;
		saveY16Matrix(&y16MaxtrixInfo);
		getY16TempMatrixMaxMinTemp(&y16MaxtrixInfo);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}

19 从DLT热图获取温度矩阵设置温度矩阵旋转90°
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
		cout << "获取温度矩阵成功！" << endl;
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
			printf("旋转前的宽为：%d   旋转前的高为：%d \n", dltMatrixInfo.w, dltMatrixInfo.h);
			printf("温度矩阵旋转成功，旋转后的宽为：%d   旋转后的高为：%d \n", dstInfo.w, dstInfo.h);
			int w = dstInfo.w;
			int h = dstInfo.h;
			int dltmatrix_len = w * h * 3;
			ITA_PALETTE_TYPE palette_index = ITA_IRON_RED;
			unsigned char* rgbData = new unsigned char[dltmatrix_len];
			result = ITA_TempMatrix2Rgb(instance, &dstInfo, palette_index, rgbData, dltmatrix_len);
			if (result == ITA_OK)
			{
				cout << "转RGB数据成功" << endl;
				saveRGBasRaw("rgb.raw", rgbData, dltmatrix_len);
			}
			else
			{
				cout << "转RGB数据失败,result is:" <<result<< endl;
			}	
			delete[] rgbData;
		}
		else
		{
			printf("温度矩阵旋转失败，result is：%d", result);
		}
		delete[] dstInfo.tempMatrix;
	}
	else
	{
		cout << "获取温度矩阵失败,result is:" << result << endl;
	}

	delete[] dltMatrixInfo.tempMatrix; 

20 从DLT热图获取温度矩阵设置温度矩阵旋转180°

21 从DLT热图获取温度矩阵设置温度矩阵旋转270°

22 从DLT热图获取温度矩阵设置温度矩阵不旋转

   从FIR热图获取温度矩阵设置温度矩阵旋转90°
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
		cout << "获取温度矩阵成功！" << endl;
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
			printf("旋转前的宽为：%d   旋转前的高为：%d \n", firMatrixInfo.w, firMatrixInfo.h);
			printf("温度矩阵旋转成功，旋转后的宽为：%d   旋转后的高为：%d \n", dstInfo.w, dstInfo.h);
			int w = dstInfo.w;
			int h = dstInfo.h;
			int dltmatrix_len = w * h * 3;
			ITA_PALETTE_TYPE palette_index = ITA_IRON_RED;
			unsigned char* rgbData = new unsigned char[dltmatrix_len];
			result = ITA_TempMatrix2Rgb(instance, &dstInfo, palette_index, rgbData, dltmatrix_len);
			if (result == ITA_OK)
			{
				cout << "转RGB数据成功" << endl;
				saveRGBasRaw("rgb.raw", rgbData, dltmatrix_len);
			}
			else
			{
				cout << "转RGB数据失败,result is:" <<result<< endl;
			}
			delete[] rgbData;
		}
		else
		{
			printf("温度矩阵旋转失败，result is：%d", result);
		}
		delete[] dstInfo.tempMatrix;
	}
	else
	{
		cout << "获取温度矩阵失败,result is:" << result << endl;
	}

	delete[] firMatrixInfo.tempMatrix;

   从FIR热图获取温度矩阵设置温度矩阵旋转180°
   从FIR热图获取温度矩阵设置温度矩阵旋转270°
   从DLT热图获取温度矩阵设置温度矩阵不旋转

23 handle传入空指针

24 输入温度矩阵传入空指针

25 输出温度矩阵传入空指针

26 输出宽传入空指针

27 输出高传入空指针

28 蒋温度矩阵转为白热RGB数据
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
		cout << "获取温度矩阵成功！" << endl;
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
			cout << "转RGB数据成功" << endl;
			saveRGBasRaw("rgb.raw", rgbData, dltmatrix_len);
		}
		else
		{
			cout << "转RGB数据失败,result is:" << result << endl;
		}
		delete[] rgbData;
	}
	else
	{
		cout << "获取温度矩阵失败,result is:" << result << endl;
	}

	delete[] dltMatrixInfo.tempMatrix;

29 蒋温度矩阵转为熔岩RGB数据

30 蒋温度矩阵转为铁红RGB数据

31 蒋温度矩阵转为热铁RGB数据

32 蒋温度矩阵转为医疗RGB数据

33 蒋温度矩阵转为北极RGB数据

34 蒋温度矩阵转为彩虹RGB数据

35 蒋温度矩阵转为彩虹2RGB数据

36 蒋温度矩阵转为黑热RGB数据

37 蒋温度矩阵转为人体筛查RGB数据

38 蒋温度矩阵转为描红RGB数据

39 蒋温度矩阵转为蓝热RGB数据

40 蒋温度矩阵转为绿热RGB数据

41 蒋温度矩阵转为医疗1RGB数据

42 蒋温度矩阵转为医疗2RGB数据

43 蒋温度矩阵转为医疗3RGB数据

44 蒋温度矩阵转为彩虹3RGB数据

45 蒋温度矩阵转为描红2RGB数据

46 蒋温度矩阵转为描红3RGB数据

47 蒋温度矩阵转为冰火RGB数据

48 蒋温度矩阵转为反冰火RGB数据

49 蒋温度矩阵转为分层RGB数据

50 蒋温度矩阵转为深褐RGB数据

51 蒋温度矩阵转为冬季RGB数据

52 蒋温度矩阵转为高亮RGB数据

53 蒋温度矩阵转为琥珀RGB数据

54 RGB数据的内存长度申请偏小

55 handle传入空指针

56 输入温度矩阵传入空指针

57 输出RGB数据传入空指针

58 获取温度矩阵最高温最低温
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
		cout << "获取温度矩阵成功！" << endl;
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
			printf("获取稳定矩阵最高温最低温失败！ result is ：%d", result);
		}
	}
	else
	{
		cout << "获取温度矩阵失败,result is:" << result << endl;
	}

	delete[] dltMatrixInfo.tempMatrix;

59 handle传入空指针

60 温度矩阵传入空指针

61 最高温传入空指针

62 最低温传入空指针

63 获取白热色带的色带条数据
	ITA_RESULT result;
	HANDLE_T instance = ITA_HeatmapInit();
	
	ITA_PALETTE_TYPE Index = ITA_BLUE_HOT;
	const int len = 1024;
	unsigned char* colorStripData = new unsigned char[len];
	result = ITA_GetColorStripData(instance, Index, colorStripData, len);
	if (result == ITA_OK)
	{
		cout << "获取色带条数据成功！" << endl;
		saveColorStripData("蓝热.raw", colorStripData, len);
	}
	else
	{
		cout << "获取色带条数据失败！result is：" << result << endl;
	}

64 获取熔岩色带的色带条数据

65 获取铁红色带的色带条数据

66 获取热铁色带的色带条数据

67 获取医疗色带的色带条数据

68 获取北极色带的色带条数据

69 获取彩虹色带的色带条数据

70 获取彩虹2色带的色带条数据

71 获取黑热色带的色带条数据

72 获取人体筛查色带的色带条数据

73 获取描红色带的色带条数据

74 获取蓝热色带的色带条数据

75 获取绿热色带的色带条数据

76 获取医疗1色带的色带条数据

77 获取医疗2色带的色带条数据

78 获取医疗3色带的色带条数据

79 获取彩虹3色带的色带条数据

80 获取描红2色带的色带条数据

81 获取描红3色带的色带条数据

82 获取冰火色带的色带条数据

83 获取反冰火色带的色带条数据

84 获取分层色带的色带条数据

85 获取深褐色带的色带条数据

86 获取冬季色带的色带条数据

87 获取高亮色带的色带条数据

88 获取琥珀色带的色带条数据

89 传入handle为空指针

90 申请的len长度过小

91 从DLT热图获取温度矩阵后，使用白热RBG数据生成热图
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
		cout << "获取温度矩阵成功！" << endl;

		int w = MatrixInfo.w;
		int h = MatrixInfo.h;
		int matrix_len = w * h * 3;
		ITA_PALETTE_TYPE palette_index = ITA_WINTER;
		unsigned char* rgbData = new unsigned char[matrix_len];
		result = ITA_TempMatrix2Rgb(instance, &MatrixInfo, palette_index, rgbData, matrix_len);
		if (result == ITA_OK)
		{
			cout << "转RGB数据成功" << endl;
			inputinfo.tempMatrix = MatrixInfo.tempMatrix;
			inputinfo.rgb = rgbData;
			ITAHeatMapOutput outPutInfo;
			result = ITA_GenerateHeapMapJpg(instance, &inputinfo, &outPutInfo);
			if (result == ITA_OK)
			{
				saveJpgPicture("琥珀.jpg", outPutInfo.jpgBuf, outPutInfo.jpgBufLen);
			}
			else
			{
				cout << "照片生成失败！ result is：" << result << endl;
			}
			delete[] inputinfo.tempMatrix;
			delete[] inputinfo.rgb;
		}
		else
		{
			cout << "转RGB数据失败,result is:" << result << endl;
		}
		delete[] rgbData;
	}
	else
	{
		cout << "获取温度矩阵失败,result is:" << result << endl;
	}
	delete[] MatrixInfo.tempMatrix;

	ITA_HeatmapUninit(instance);
   
92 ........覆盖26种伪彩...........................................

93 DLT热图Y16数据转RGB，成像
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
		cout << "获取温度矩阵成功！" << endl;
	}
	else
	{
		cout << "获取温度矩阵失败,result is:" << result << endl;
	}

	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[inputinfo.w * inputinfo.h];
	result = ITA_GetY16MatrixInfo(instance, file, heatMapType, &y16MaxtrixInfo);
	if (result == ITA_OK)
	{
		cout << "获取Y16矩阵成功！" << endl;
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
			cout << "图像处理成功！" << endl;

			ITAHeatMapOutput outputinfo;
			inputinfo.tempMatrix = MatrixInfo.tempMatrix;
			inputinfo.rgb = resultinfo.imgDst;
			result=ITA_GenerateHeapMapJpg(instance, &inputinfo, &outputinfo);
			if (result == ITA_OK) { saveJpgPicture("Y16调光.jpg", outputinfo.jpgBuf, outputinfo.jpgBufLen); }
			else { cout << "热图生成失败" << endl; }
		}
		else
		{
			cout << "图像处理失败！" << endl;
		}
		ITA_Uninit(handle);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}
	
	delete[] inputinfo.tempMatrix;
	delete[] inputinfo.rgb;
	delete[] y16MaxtrixInfo.y16Matrix;
	delete[] MatrixInfo.tempMatrix;
	ITA_HeatmapUninit(instance);

94 对DLT热图Y16成像、手动调光、设置温宽（最高温、最低温）
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
		cout << "获取温度矩阵成功！" << endl;
	}
	else
	{
		cout << "获取温度矩阵失败,result is:" << result << endl;
	}

	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[inputinfo.w * inputinfo.h];
	result = ITA_GetY16MatrixInfo(instance, file, heatMapType, &y16MaxtrixInfo);
	if (result == ITA_OK)
	{
		cout << "获取Y16矩阵成功！" << endl;
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
		if (result == ITA_OK) { cout << "设置温宽成功！" << endl; }
		else { cout << "设置温宽失败！result is："<<result << endl; }

		ITAISPResult resultinfo;
		int srcSize = width * height * sizeof(short);
		unsigned char* srcData = new unsigned char[srcSize];
		ConvertShortToUnsignedChar(y16MaxtrixInfo.y16Matrix, srcData, height, width);
		result = ITA_ISP(handle, srcData, srcSize, &resultinfo);
		if (result == ITA_OK)
		{
			cout << "图像处理成功！" << endl;

			ITAHeatMapOutput outputinfo;
			inputinfo.tempMatrix = MatrixInfo.tempMatrix;
			inputinfo.rgb = resultinfo.imgDst;
			result=ITA_GenerateHeapMapJpg(instance, &inputinfo, &outputinfo);
			if (result == ITA_OK) { saveJpgPicture("Y16手动调光.jpg", outputinfo.jpgBuf, outputinfo.jpgBufLen); }
			else { cout << "热图生成失败" << endl; }
		}
		else
		{
			cout << "图像处理失败！" << endl;
		}
		ITA_Uninit(handle);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
	}
	
	delete[] inputinfo.tempMatrix;
	delete[] inputinfo.rgb;
	delete[] y16MaxtrixInfo.y16Matrix;
	delete[] MatrixInfo.tempMatrix;
	ITA_HeatmapUninit(instance);

95 对DLT热图Y16成像，设置亮度、对比度、锐度、细节增强
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
		cout << "获取温度矩阵成功！" << endl;
	}
	else
	{
		cout << "获取温度矩阵失败,result is:" << result << endl;
	}

	ITA_Y16MATRIX_INFO y16MaxtrixInfo;
	y16MaxtrixInfo.y16Matrix = new short[inputinfo.w * inputinfo.h];
	result = ITA_GetY16MatrixInfo(instance, file, heatMapType, &y16MaxtrixInfo);
	if (result == ITA_OK)
	{
		cout << "获取Y16矩阵成功！" << endl;
		saveY16Matrix(&y16MaxtrixInfo);

		ITA_MODE mode = ITA_Y16;
		ITA_RANGE range = ITA_INDUSTRY_LOW;
		int cameraID = 1;
		HANDLE_T handle = ITA_Init(mode, range, width, height, cameraID);

		int bright = 125;
		int contrast = 255;
		bool sharpening = false;
		bool enhance = false;
		ITA_ImageControl(handle, ITA_SET_BRIGHTNESS, &bright); //设置亮度
		ITA_ImageControl(handle, ITA_SET_CONTRAST, &contrast); //设置对比度
		ITA_ImageControl(handle, ITA_SHARPENING, &sharpening); //设置锐度
		ITA_ImageControl(handle, ITA_DETAIL_ENHANCE, &enhance); //设置细节增强

		ITAISPResult resultinfo;
		int srcSize = width * height * sizeof(short);
		unsigned char* srcData = new unsigned char[srcSize];
		ConvertShortToUnsignedChar(y16MaxtrixInfo.y16Matrix, srcData, height, width);
		result = ITA_ISP(handle, srcData, srcSize, &resultinfo);
		if (result == ITA_OK)
		{
			cout << "图像处理成功！" << endl;

			ITAHeatMapOutput outputinfo;
			inputinfo.tempMatrix = MatrixInfo.tempMatrix;
			inputinfo.rgb = resultinfo.imgDst;
			result=ITA_GenerateHeapMapJpg(instance, &inputinfo, &outputinfo);
			if (result == ITA_OK) { saveJpgPicture("Y16手动调光细节增强关.jpg", outputinfo.jpgBuf, outputinfo.jpgBufLen); }
			else { cout << "热图生成失败" << endl; }
		}
		else
		{
			cout << "图像处理失败！" << endl;
		}
		ITA_Uninit(handle);
	}
	else
	{
		cout << "获取失败,result is:" << result << endl;
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
