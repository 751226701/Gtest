/*
一、连接设备

修改密码
        const char* username = "admin";
        const char* oldpassword = "admin123";
        const char* newpassword = "admin567";
        int ret1 = SGP_ChangePassword(handle, username, oldpassword, newpassword);
        if (ret1 == SGP_OK)
        {
            cout << "密码修改成功" << endl;
        }
        else
        {
            cout << "密码修改失败！" << endl;
            cout << "ret的返回值为：" << ret1 << endl;
        }


重置密码
        const char* usernames = "admin";
        int ret = SGP_ResetPassword(handle, usernames);
        if (ret == SGP_OK)
        {
            cout << "重置密码成功" << endl;
        }
        else
        {
            cout << "重置密码失败！" << endl;
            cout << "ret的返回值为：" << ret << endl;
        }


获取用户信息
        SGP_GENERAL_INFO info;
        memset(&info, 0, sizeof(info));
        int rets = SGP_GetGeneralInfo(handle, &info);
        cout << "获取的通用信息为：" << endl;
        cout << "系统时间为：" << info.datetime << endl;
        cout << "红外模组的宽为：" << info.ir_model_w << endl;
        cout << "红外模组的高为：" << info.ir_model_h << endl;
        cout << "红外通道输出宽为：" << info.ir_output_w << endl;
        cout << "红外通道输出高为：" << info.ir_output_h << endl;  
        cout << "红外主码流地址为：" << info.ir_rtsp_url << endl;
        cout << "测温范围数量为：" << info.range_num << endl;



二、测温
获取单点温度
        int x = 120;
        int y = 120;
        float output = 0.0f;
        int ret = SGP_GetPointTemp(handle, x, y, &output);
        if (ret == SGP_OK)
        {
            cout << "获取单点温度成功\n" << "获取的温度为：" << output << endl;
        }
        else
        {
            cout << "获取单点温度失败\n" << "ret的返回值为：" << ret << endl;
        }


 获取分析对象温度
        SGP_ANALYTIC_TEMPS array;
        memset(&array, 0x00, sizeof(array));
        int ret = SGP_GetAnalyticObjectsTemp(handle,&array);
        if (ret == SGP_OK)
        {
            for (int i = 0; i < array.analytic_num; i++)
            {
                cout << "获取分析对象温度成功,获取分析对象信息如下：" << endl;
                cout << "分析对象个数为：" << array.analytic_num << endl;             
                cout << "分析对象的规则ID为：" << array.analytic[i].rule_id << endl;
                cout << "分析对象的规则名称为：" << array.analytic[i].rule_name << endl;
                cout << "分析对象的类型为：" << array.analytic[i].type << endl;
                cout << "分析对象的最高温度为：" << array.analytic[i].max_temp << endl;
                cout << "分析对象的平均温度为：" << array.analytic[i].avg_temp << endl;
                cout << "分析对象的最低温度为：" << array.analytic[i].min_temp << endl;
                cout << endl;
            }
           
        }
        else
        {
            cout << "获取分析对象温度失败\n" << "ret的返回值为：" << ret << endl;
        }


获取温度矩阵
         //抓图作为对比
        SGP_IMAGE_TYPE types = SGP_IR_IMAGE;
        char path[] = "./testPicture/screencap.jpg";
        int ret11 = SGP_GetScreenCapture(handle, types, path);

        //获取温度矩阵并分析温度
        SGP_GENERAL_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetGeneralInfo(handle, &info);
        if (ret == SGP_OK)
        {
            int height = info.ir_model_h;
            int width = info.ir_model_w;
            int length = height * width;
            int type = 1;
            float* output = (float*)calloc(length, sizeof(float));
            if (output != NULL)
            {
                ret = SGP_GetImageTemps(handle, output, length * 4, type);
                if(ret == SGP_OK)
                {
                    cout << "返回成功" << endl;
                }
                
                float max=0, min=100,sum=0;
                for (int i = 0; i < length; i++)
                {
                    if (max < output[i])
                    {
                        max = output[i];
                    }
                    if (min > output[i])
                    {
                        min = output[i];
                    }
                    sum += output[i];
                }

                cout << "获取的最高温为：" <<setprecision(3) << max << endl;
                cout << "获取的最低温为：" <<setprecision(3) << min << endl;
                cout << "获取的平均温为：" <<setprecision(3) << sum/length << endl;
            }
            free(output);
            output = NULL;          
        }


        //获取温度矩阵并分析温度（医疗机芯）
        SGP_GENERAL_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetTempMatrix(handle, TempCall,NULL);
        if (ret == SGP_OK)
        {
            int height = info.ir_model_h;
            int width = info.ir_model_w;
            int length = height * width;
            int type = 1;
            float* output = (float*)calloc(length, sizeof(float));
            if (output != NULL)
            {
                ret = SGP_GetImageTemps(handle, output, length * 4, type);
                if(ret == SGP_OK)
                {
                    cout << "返回成功" << endl;
                }

                float max=0, min=100,sum=0;
                for (int i = 0; i < length; i++)
                {
                    if (max < output[i])
                    {
                        max = output[i];
                    }
                    if (min > output[i])
                    {
                        min = output[i];
                    }
                    sum += output[i];
                }

                cout << "获取的最高温为：" <<setprecision(3) << max << endl;
                cout << "获取的最低温为：" <<setprecision(3) << min << endl;
                cout << "获取的平均温为：" <<setprecision(3) << sum/length << endl;
            }
            free(output);
            output = NULL;
        }

//温度矩阵旋转
        SGP_GENERAL_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetGeneralInfo(handle, &info);
        if (ret == SGP_OK)
        {
            int height = info.ir_model_h;
            int width = info.ir_model_w;
            int length = height * width;
            int type = 1;
            float* output = (float*)calloc(length, sizeof(float));
            float* rotateOutput = (float*)calloc(length, sizeof(float));
            if (output != NULL)
            {
                ret = SGP_GetImageTemps(handle, output, length * 4, type);
                if (ret == SGP_OK)
                {
                    cout << "返回成功" << endl;
                }
                ret = SGP_GetTempMatriRotationEx(handle, rotateOutput, output, 640, 512, 2);
                if (ret != SGP_OK) {
                    return -1;
                }
                matrixToVideo(rotateOutput);  //旋转后注意修改成像的宽高
            }
            free(output);
            free(rotateOutput);
            output = NULL;
            rotateOutput = NULL;
        }


三、拍照
获取屏幕截图
        SGP_IMAGE_TYPE type = SGP_IR_IMAGE;
        char path[] = "./testPicture/screencap.jpg";
        int ret = SGP_GetScreenCapture(handle,type, path);
        if (ret == SGP_OK)
        {
            cout << "获取屏幕截图成功" << endl;
        }
        else
        {
            cout << "获取屏幕截图失败\n" << "ret的返回值为：" << ret << endl;
        }


获取热图
        const char* path = "./testPicture/screenpic.jpg";
        int ret = SGP_GetHeatMap(handle, path);
        if (ret == SGP_OK)
        {
            cout << "返回成功" << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }



        for (int i = 1; i <= 50; i++)
        {
            Slepp(3000);
            string screepic = "heatmap_";
            string name;

            cout << name;
            name = screepic + std::to_string(i) + ".jpg";

            const char path[] = "./screenpic.jpg";
            int ret = SGP_GetHeatMap(handle, name.c_str());
            if (ret == SGP_OK)
            {
                cout << "获取热图成功" << endl;
            }
            else
            {
                cout << "获取热图失败" << endl;
            }

        }


获取高压热图
        const char* path = "./testPicture/screenpic.fir";
        int ret = SGP_GetFirHeatMap(handle, path);
        if (ret == SGP_OK)
        {
            cout << "返回成功" << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }


获取屏幕截图缓存
        int input_length = 1024 * 1024 * 10;
        int output_length = 0;
        SGP_IMAGE_TYPE type = SGP_IR_IMAGE;
        char* input = (char*)calloc(input_length, sizeof(char));
        if (input != NULL)
        {
            int ret = SGP_GetScreenCaptureCache(handle, type, input, input_length,&output_length);
            if (ret == SGP_OK)
            {
                cout << "获取屏幕截图缓存成功" << endl;
                cout << output_length << endl;

                ofstream outputFile("screenshot.bin", std::ios::binary);
                if (outputFile.is_open()) {
                    outputFile.write(input, output_length);
                    outputFile.close();
                    cout << "获取屏幕截缓存图成功，并保存为 screenshot.bin" << endl;
                }
                else {
                    cout << "无法打开文件以保存截图数据" << endl;
                }
            }
            else
            {
                cout << "获取屏幕截图缓存失败" << endl;
            }
        }
        free(input);
        input = NULL; 

获取热图缓存
        int input_length = 1024 * 1024 * 10;
        int output_length = 0;
        char* input = (char*)calloc(input_length, sizeof(char));
        if (input != NULL)
        {
            int ret = SGP_GetHeatMapCache(handle, input, input_length, &output_length);
            if (ret == SGP_OK)
            {
                cout << "获取热图缓存成功" << endl;
                cout << output_length << endl;
                ofstream outputFile("heatMapCache.bin", std::ios::binary);
                if (outputFile.is_open()) {
                    outputFile.write(input, output_length);
                    outputFile.close();
                    cout << "获取热图缓存成功，并保存为 heatMapCache.bin" << endl;
                }
                else {
                    cout << "无法打开文件以保存热图数据" << endl;
                }
            }
            else
            {
                cout << "获取热图缓存失败" << endl;
            }
        }
        free(input);
        input = NULL;


获取高压热图缓存
        int input_length = 1024 * 1024 * 10;
        int output_length = 0;
        char* input = (char*)calloc(input_length, sizeof(char));
        if (input != NULL)
        {
            int ret = SGP_GetFirHeatMapCache(handle, input, input_length, &output_length);
            if (ret == SGP_OK)
            {
                cout << "获取高压热图缓存成功" << endl;
                cout << output_length << endl;
                ofstream outputFile("firMapCache.bin", std::ios::binary);
                if (outputFile.is_open()) {
                    outputFile.write(input, output_length);
                    outputFile.close();
                    cout << "获取高压热图缓存成功，并保存为 firMapCache.bin" << endl;
                }
                else {
                    cout << "无法打开文件以保存高压热图数据" << endl;
                }
            }
            else
            {
                cout << "获取高压热图缓存失败" << endl;
            }
        }
        free(input);
        input = NULL;


四、成像
开启红外视频

回调函数定义：
static void GetIrRtsp(unsigned char* outdata, int w, int h, void* pUser)
{
    printf("outdata is %s\n", outdata);
    printf("w is %d, h is %d\n", w, h);
    Sleep(2000);
}
static void GetRecordStatus(int state, void* pUser)
{
    //printf("Current record status is %d\n", state);
    //Sleep(2000);
}

            接口：
            for (int i = 1; i <= 1; i++)
            {
            int result = SGP_OpenIrVideo(handle, GetIrRtsp, 0);
            printf("第%d次SGP_OpenIrVideo接口返回值是%d\n", i, result);
            Sleep(5000);
            std::string IRFile = "D:/photo/1234.mp4";
            int startResult = SGP_StartRecord(handle, SGP_IR_VIDEO,IRFile.c_str(), GetRecordStatus,0);
            printf("SGP_StartRecord接口红外返回值是%d\n", startResult);
            Sleep(60000);
            SGP_StopRecord(handle, SGP_IR_VIDEO);
            //关闭视频流
            SGP_CloseIrVideo(handle);
            }

开始录制（控制设备端）
        int record = 1;
        int record_stream = 2;
        int ret = SGP_Record(handle, record, record_stream);
        if (ret == SGP_OK)
        {
            cout << "开始录制" << endl;
        }
        else
        {
            cout << "录制失败" << endl;
        }



五、操控设备

设置全局温度参数
        SGP_THERMOMETRY_PARAM info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetThermometryParam(handle, &info);
        if (ret == SGP_OK)
        {
            info.color_bar = 12;  //色带
            info.color_show = 1;  //色带显示
            info.flag = 1;        //测温开关
            info.mod_temp = 0;    //温度修正
            info.ambient = 22;    //环境温度
            info.atmo_trans = 0.2;//大气透过率
            info.dist = 10;      //距离
            info.emiss = 0.5;     //发射率
            info.emiss_mode = 1;  //发射率类型
            info.gear = 0;        //测温范围
            info.humi = 66;       //温度范围
            info.ref_temp = 23;   //反射温度
            strcpy(info.show_desc, "123456"); //显示字符串
            info.show_mode = 7;   //温度显示类型
            info.show_string = 5; //字符串显示位置
            info.opti_trans = 0.2;//光学透过率
            info.isot_flag = 1;   //等温线开关
            info.isot_high = 20;  //等温线高温阈值
            info.isot_low = 20;   //等温线低温阈值
            info.isot_type = 2;   //等温线类型
            strcpy(info.isot_high_color, "#00ff00");   //等温线高温颜色
            strcpy(info.isot_low_color, "#00ff00");    //等温线低温颜色
            ret = SGP_SetThermometryParam(handle, info);
            if (ret == SGP_OK)
            {
                cout << "设置全局温度参数成功,请检查结果" << endl;
            }
            else
            {
                cout << "设置全局温度参数失败\n" << "ret的返回值为：" << ret << endl;
            }
        }


获取全局温度参数
        SGP_THERMOMETRY_PARAM info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetThermometryParam(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "返回成功,全局测温参数信息如下：" << endl;
            cout << "环境温度为：  " << info.ambient << endl;
            cout << "大气透过率为：" << info.atmo_trans << endl;
            cout << "色带号为：    " << info.color_bar << endl;
            cout << "距离为：      " << info.dist << endl;
            cout << "发射率为：    " << info.emiss << endl;
            cout << "发射率类型为：" << info.emiss_mode << endl;
            cout << "湿度为：      " << info.humi << endl;
            cout << "光学透过率为：" << info.opti_trans << endl;
            cout << "字符串显示为：" << info.show_desc << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }


设置全局测温开关
        int flag = 1;
        int ret = SGP_SetThermometryFlag(handle, flag);
        if (ret == SGP_OK)
        {
            cout << "设置全局测温开关成功,请核对设置是否成功" << endl;
        }
        else
        {
            cout << "设置全局测温开关失败\n" << "ret的返回值为：" << ret << endl;
        }



设置色带号
        int colorbar = 24;
        int ret = SGP_SetColorBar(handle, colorbar);
        if (ret == SGP_OK)
        {
            cout << "设置色带号成功,请核对设置是否成功" << endl;
        }
        else
        {
            cout << "设置色带号失败\n" << "ret的返回值为：" << ret << endl;
        }


设置色带显示
        int showcolorbar = 0;
        int ret = SGP_SetColorBarShow(handle, showcolorbar);
        if (ret == SGP_OK)
        {
            cout << "设置色带显示成功，请核对设置是否成功" << endl;
        }
        else
        {
            cout << "设置色带显示失败\n" << "ret的返回值为：" << ret << endl;
        }


设置温度显示类型
        int showtype = 7;
        int ret = SGP_SetTempShowMode(handle, showtype);
        if (ret == SGP_OK)
        {
            cout << "设置温度显示类型成功，请核对设置是否成功" << endl;
        }
        else
        {
            cout << "设置温度显示类型失败\n" << "ret的返回值为：" << ret << endl;
        }


设置字符串叠加
        int type = 2;
        const char* dateshow = "123";
        int ret = SGP_SetStringShow(handle, type, dateshow);
        if (ret == SGP_OK)
        {
            cout << "设置字符串叠加成功，请核对设置是否成功" << endl;
        }
        else
        {
            cout << "设置字符串叠加失败\n" << "ret的返回值为：" << ret << endl;
        }


设置分析对象温度显示类型
        int showtype = 1;
        int ret = SGP_SetThermometryRuleShowMode(handle, showtype);
        if (ret == SGP_OK)
        {
            cout << "设置分析对象温度显示类型成功，请核对设置是否成功" << endl;
        }
        else
        {
            cout << "设置分析对象温度显示类型失败\n" << "ret的返回值为：" << ret << endl;
        }




添加分析对象
        SGP_RULE rulePoint;
        memset(&rulePoint, 0x00, sizeof(SGP_RULE));
        rulePoint.alarm_condition = 1;
        rulePoint.alarm_flag = 1;
        rulePoint.alarm_time = 10;
        rulePoint.alarm_type = 1;
        rulePoint.alarm_interal = 30;
        rulePoint.avg_temp = 30;
        rulePoint.flag = 1;
        rulePoint.high_temp = 35;
        rulePoint.low_temp = 28;
        rulePoint.show_type = 1;
        rulePoint.points_num = 1; //点个数是1
        rulePoint.points[0].x = 200;
        rulePoint.points[0].y = 200;
        strcpy(rulePoint.rule_name, "点1");
        rulePoint.show_location = 1;
        rulePoint.temp_mod = 1;
        rulePoint.type = 1;  //类型是1
        rulePoint.atmo_trans = 0.9;
        rulePoint.dist = 2;
        rulePoint.emiss = 0.8;
        rulePoint.emiss_mode = 1;
        rulePoint.humi = 80;
        rulePoint.opti_trans = 1;
        rulePoint.ref_temp = 25;
        int ret = SGP_AddThermometryRule(handle, rulePoint);
        if (ret == SGP_OK)
        {
            cout << "添加分析对象成功，请核对设置是否成功" << endl;
        }
        else
        {
            cout << "添加分析对象失败\n" << "ret的返回值为：" << ret << endl;
        }
       
        //SGP_DeleteAllThermometryRule(handle);

更新分析对象
        SGP_RULE_ARRAY array;
        memset(&array, 0x00, sizeof(array));
        int ret = SGP_GetThermometryRule(handle, &array);
        if (ret == SGP_OK)
        {
            if (array.rule_num > 0)
            {
                SGP_RULE rule;
                memset(&rule, 0, sizeof(rule));
                memcpy(&rule, &array.rule[0], sizeof(rule));
                rule.alarm_condition = 1;
                rule.alarm_type = 1;
                rule.alarm_flag = 1;
                rule.alarm_time = 3;
                rule.high_temp = 20;
                rule.low_temp = 22;
                rule.avg_temp = 33;
                rule.alarm_interal = 3600;
                rule.show_type = 1;
                int ret = SGP_UpdateThermometryRule(handle, rule);
                if (ret == SGP_OK)
                {
                    cout << "更新分析对象成功，请核对设置是否成功" << endl;
                }
                else
                {
                    cout << "更新分析对象失败\n" << "ret的返回值为：" << ret << endl;
                }
               
            }
        }


删除分析对象
       SGP_RULE_ARRAY array;
        memset(&array, 0x00, sizeof(array));
        int ret = SGP_GetThermometryRule(handle, &array);
        if (ret == SGP_OK)
        {
            if (array.rule_num > 0)
            {
                int ret = SGP_DeleteThermometryRule(handle, array.rule[0].id);
                if (ret == SGP_OK)
                {
                    cout << "删除分析对象成功，请核对设置是否成功" << endl;
                }
                else
                {
                    cout << "删除分析对象失败\n" << "ret的返回值为：" << ret << endl;
                }
               
            }
        }

       

删除全部分析对象
        int ret = SGP_DeleteAllThermometryRule(handle);
        if (ret == SGP_OK)
        {
            cout << "删除全部分析对象成功，请核对设置是否成功" << endl;
        }
        else
        {
            cout << "删除全部分析对象失败\n" << "ret的返回值为：" << ret << endl;
        }



获取分析对象
        SGP_RULE_ARRAY array;
        memset(&array, 0x00, sizeof(array));
        int ret = SGP_GetThermometryRule(handle, &array);
        if (ret == SGP_OK)
        {
            cout << "分析对象个数为：" << array.rule_num << endl;
            for (int i = 0; i < array.rule_num; i++)
            {
                cout << "第" << i + 1 << "个分析对象信息：" << endl;
                cout << "大气透过率为：" << array.rule[i].atmo_trans << endl;
                cout << "距离为：" << array.rule[i].dist << endl;
                cout << "ID为：" << array.rule[i].id << endl;
                cout << "报警条件为：" << array.rule[i].alarm_condition << endl;
                cout << "是否需要报警：" << array.rule[i].alarm_flag << endl;
                cout << "报警类型：" << array.rule[i].alarm_type << endl;
                cout << "平均温：" << array.rule[i].avg_temp << endl;
                cout << "是否启用：" << array.rule[i].flag << endl;
                cout << "报警高温阈值：" << array.rule[i].high_temp << endl;
                cout << "报警低温阈值：" << array.rule[i].low_temp << endl;
                cout << "规则名称：" << array.rule[i].rule_name << endl;
                cout << "显示位置：" << array.rule[i].show_location << endl;
                cout << "温度误差：" << array.rule[i].temp_mod << endl;
                cout << "大气透过率：" << array.rule[i].atmo_trans << endl;
                cout << "发射率：" << array.rule[i].emiss << endl;
                cout << "发射率类型：" << array.rule[i].emiss_mode << endl;
                cout << "湿度：" << array.rule[i].humi << endl;
                cout << "光学透过率：" << array.rule[i].opti_trans << endl;
                cout << "反射温度：" << array.rule[i].ref_temp << endl;
                cout << endl;
            }
            
            cout << "获取分析对象成功，请核对设置是否成功" << endl;
        }
        else
        {
            cout << "获取分析对象失败\n" << "ret的返回值为：" << ret << endl;
        }



设置红外图像效果参数
        SGP_IR_IMAGE_EFFECT_ENUM type = SGP_IR_SHARPNESS;
        int value = 50;
        int ret = SGP_SetIrImageEffectParam(handle, type, value);
        if (ret == SGP_OK)
        {
            cout << "设置红外图像效果参数成功，请核对设置是否成功" << endl;
        }
        else
        {
            cout << "设置红外图像效果参数失败\n" << "ret的返回值为：" << ret << endl;
        }


获取红外图像效果参数
        SGP_IAMGE_EFFECT_PARAM_IR_CONFIG info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetIrImageEffectParam(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "获取红外图像效果参数成功，获取的信息如下：" << endl;
            cout << "获取的快门补偿时间为：" << info.auto_shutter << endl;
            cout << "获取的亮度为：        " << info.brightness << endl;
            cout << "获取的对比度为：      " << info.contrast << endl;
            cout << "获取的细节增强值为：  " << info.iee_value  << endl;
            cout << "获取的锐度值为：      " << info.sharpness << endl;                     
        }
        else
        {
            cout << "获取红外图像效果参数失败\n" << "ret的返回值为：" << ret << endl;
        }


设置网络信息
        SGP_NET_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetNetInfo(handle, &info);
        if (ret == SGP_OK)
        {
            info.card = 0;
            strcpy(info.dns1, "192.168.1.168");
            strcpy(info.dns2, "192.168.1.167");
            strcpy(info.gateway, "192.168.21.1");
            strcpy(info.host_name, "qwe123");
            //strcpy(info.ipaddr, "192.168.21.152");
            strcpy(info.netmask, "255.255.252.0");
            info.mode = 0;
            ret = SGP_SetNetInfo(handle, info);
            if (ret == SGP_OK)
            {
                cout << "设置网络信息成功，请核对设置是否成功" << endl;
            }
            else
            {
                cout << "设置网络信息失败\n" << "ret的返回值为：" << ret << endl;
            }
        }
               

获取网络信息      
       SGP_NET_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetNetInfo(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "获取网络信息成功，获取信息如下：" << endl;
            cout << "获取的主机名为："<<info.host_name << endl;
            cout << "获取ip地址为："  <<info.ipaddr << endl;
        }
        else
        {
            cout << "获取网络信息失败\n" << "ret的返回值为：" << ret << endl;
        }


设置端口信息
        SGP_PORT_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetPortInfo(handle, &info);
        if (ret == SGP_OK)
        {
            info.max_connectios = 10;
            info.http_port = 80;
            info.rtsp_port = 1111;
            info.onvif_check = 0;
            //info.tcp_port = 100;
            ret = SGP_SetPortInfo(handle, info);
            if (ret == SGP_OK)
            {
                cout << "返回成功，请核对设置是否成功" << endl;
            }
            else
            {
                cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
            }
        }

获取端口信息
        SGP_PORT_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetPortInfo(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "返回成功，获取的端口信息如下：" << endl;
            cout << "http端口号为：\t" << info.http_port << endl;
            cout << "最大连接设备数为:" << info.max_connectios << endl;
            cout << "onvif开关：\t" << info.onvif_check << endl;
            cout << "rtsp端口号为：\t" << info.rtsp_port << endl;
            cout << "tcp端口号为：\t" << info.tcp_port << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }



设置录制信息
        SGP_RECORD_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetRecordInfo(handle, &info);
        if (ret == SGP_OK)
        {
            info.record_interval = 10;
            info.record_max_size = 888;
            info.record_time = 10;
            ret = SGP_SetRecordInfo(handle, info);
            if (ret == SGP_OK)
            {
                cout << "返回成功，请核对设置是否成功" << endl;
            }
            else
            {
                cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
            }

        }


获取录制信息
        SGP_RECORD_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetRecordInfo(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "返回成功，获取的端口信息如下：" << endl;
            cout << "录像延时时间：\t" << info.record_interval << endl;
            cout << "最大录像文件大小：" << info.record_max_size << endl;
            cout << "录像时长： \t" << info.record_time << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }




获取屏蔽区域
        SGP_SHIELD_AREA_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetShieldArea(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "返回成功，获取屏蔽区域信息如下：" << endl;
            cout << "屏蔽区域个数为：" << info.rect_num << endl;
            cout << "屏蔽区域坐标为：" << endl;
            for (int i = 0; i < info.rect_num; i++)
            {
                printf("第%d个屏蔽区域的坐标为：\n", i+1);
                cout << "x=" << info.rect[i].x << endl;
                cout << "y=" << info.rect[i].y << endl;
                cout << "w=" << info.rect[i].w << endl;
                cout << "h=" << info.rect[i].h << endl;
                cout << endl;
            }
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }



设置屏蔽区域
        SGP_SHIELD_AREA_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetShieldArea(handle, &info);
        if (ret == SGP_OK)
        {
            info.rect_num = 1;
            info.rect[0].x = 250;
            info.rect[0].y = 250;
            info.rect[0].w = 150;
            info.rect[0].h = 150;
            info.rect[1].x = 50;
            info.rect[1].y = 50;
            info.rect[1].w = 150;
            info.rect[1].h = 150;           
            ret = SGP_SetShieldArea(handle, info);
            if (ret == SGP_OK)
            {
                cout << "返回成功，请核对设置是否成功" << endl;
            }
            else
            {
                cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
            }
        }


获取全局温度告警
        SGP_COLD_HOT_TRACE_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetColdHotTrace(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "返回成功，获取全局温度告警信息如下：" << endl;
            cout << "capture_flag:" << info.capture_flag << endl;
            cout << "capture_stream:" << info.capture_stream << endl;
            cout << "high_flag:" << info.high_flag << endl;
            cout << "high_temp:" << info.high_temp << endl;
            cout << "low_flag:" << info.low_flag << endl;
            cout << "low_temp:" << info.low_temp << endl;
            cout << "sendmail:" << info.sendmail << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }

设置全局温度告警
        SGP_COLD_HOT_TRACE_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetColdHotTrace(handle, &info);
        if (ret == SGP_OK)
        {
            info.alarm_interal = 300;
            info.high_flag = 1;
            info.high_temp =33;
            info.low_flag = 1;
            info.low_temp = 22;
            info.capture_flag = 1;
            info.capture_stream = 2;
            info.output_flag = 1;
            info.output_hold = 300;
            info.record_flag = 1;
            info.record_stream = 2;
            info.sendmail = 1;
            info.record_delay = 300;
            info.alarm_shake = 10;
            info.trace_flag = 1;
            strcpy(info.high_color, "#0000ff");
            strcpy(info.low_color, "#ff0000");
            for (int i = 0; i < 7; i++)
            {
                info.effect_day[i].day = i + 1;
                info.effect_day[i].period_num = 7;
                strcpy(info.effect_day[i].period->start, "12:00:00");
                strcpy(info.effect_day[i].period->end, "22:59:59");
            }

            ret = SGP_SetColdHotTrace(handle, info);
            if (ret == SGP_OK)
            {
                cout << "返回成功，请核对设置是否成功" << endl;
            }
            else
            {
                cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
            }
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }


获取分析对象告警
        SGP_TEMP_ALARM_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetTempAlarm(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "返回成功，获取分析对象告警信息如下：" << endl;
            cout << "alarm_flag:" << info.alarm_flag << endl;
            cout << "capture_flag:" << info.capture_flag << endl;
            cout << "capture_stream:" << info.capture_stream << endl;
            cout << "output_flag:" << info.output_flag << endl;
            cout << "output_hold:" << info.output_hold << endl;
            cout << "sendmail:" << info.sendmail << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }


设置分析对象告警
        SGP_TEMP_ALARM_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetTempAlarm(handle, &info);
        if (ret == SGP_OK)
        {
            info.alarm_flag = 1;//是否开启报警 1:开启; 0:不开启
            info.capture_flag = 1;//是否截图 0:否; 1:是
            info.capture_stream = 2;//截图类型 0:不截图; 1:只截图可见光; 2:只截图红外; 3:截图红外和可见光
            info.record_flag = 1;//是否录制 0:不录制; 1:录制
            info.record_stream = 2;//录制类型 0:不录制; 1:只录制可见光; 2:只录制红外; 3:录制红外和可见光
            info.record_delay = 150;//录制时间 10-300s
            info.output_flag = 1;//是否外部输出 0:不输出 1:输出
            info.output_hold = 20;
            info.alarm_shake = 8;
            info.sendmail = 1;
            ret = SGP_SetTempAlarm(handle, info);
            if (ret == SGP_OK)
            {
                cout << "返回成功，请核对设置是否成功" << endl;
            }
            else
            {
                cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
            }
        }


获取视频参数
        SGP_VIDEO_PARAM_ENUM type = SGP_IR;
        SGP_VIDEO_PARAM param;
        memset(&param, 0x00, sizeof(param));
        int ret = SGP_GetVideoParam(handle, type, &param);
        if (ret == SGP_OK)
        {
            cout << "返回成功，获取的视频参数如下：" << endl;
            cout << "param.bit_size=" << param.bit_size << endl;
            cout << "param.fps=" << param.fps << endl;
            cout << "param.gop_size=" << param.gop_size << endl;
            cout << "param.level=" << param.level << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }


设置视频参数
        SGP_GENERAL_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetGeneralInfo(handle, &info);
        if (ret == SGP_OK)
        {
            SGP_VIDEO_PARAM_ENUM type = SGP_IR;
            SGP_VIDEO_PARAM param;
            memset(&param, 0x00, sizeof(param));
            ret = SGP_GetVideoParam(handle, type, &param);
            param.fps = 25;
            param.gop_size = param.fps * 2;
            param.bit_size= info.ir_model_w * info.ir_model_h * param.fps * 8 * 3 / 2 / 1024 / 18;
            param.level = 1;

            ret = SGP_SetVideoParam(handle, type, param);
            if (ret == SGP_OK)
            {
                cout << "返回成功，请核对设置是否成功" << endl;
            }
            else
            {
                cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
            }
        }


获取网络异常
        SGP_NET_EXCEPTION_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetNetException(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "返回成功，获取网络异常信息如下：" << endl;
            cout << "flag=" << info.flag << endl;
            cout << "output_flag=" << info.output_flag << endl;
            cout << "output_hold=" << info.output_hold << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }

设置网络异常
        SGP_NET_EXCEPTION_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetNetException(handle, &info);
        if (ret == SGP_OK)
        {
            info.flag = 1;
            info.output_flag = 1;
            info.output_hold = 20;
            info.interval_time = 30;
            ret = SGP_SetNetException(handle, info);
            if (ret == SGP_OK)
            {
                cout << "返回成功，请核对设置是否成功" << endl;
            }
            else
            {
                cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
            }

        }

获取非法访问
        SGP_ACCESS_VIOLATION_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetAccessViolation(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "返回成功，获取的非法访问信息如下：" << endl;
            cout << "allow_count=" << info.allow_count << endl;
            cout << "flag=" << info.flag << endl;
            cout << "output_flag=" << info.output_flag << endl;
            cout << "output_hold=" << info.output_hold << endl;
            cout << "sendmail=" << info.sendmail << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }

设置非法访问
        SGP_ACCESS_VIOLATION_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetAccessViolation(handle, &info);
        if (ret == SGP_OK)
        {
            info.allow_count = 10;
            info.flag = 1;
            info.output_flag = 1;
            info.output_hold = 12;
            info.sendmail = 1;
            info.lock_time = 30;
            ret = SGP_SetAccessViolation(handle, info);
            if (ret == SGP_OK)
            {
                cout << "返回成功，请核对设置是否成功" << endl;
            }
            else
            {
                cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
            }
        }

获取邮件信息
        SGP_EMAIL_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetEmilInfo(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "返回成功，获取的邮件信息如下：" << endl;
            cout << "alarm=" << info.alarm << endl;
            cout << "alarm_value=" << info.alarm_value << endl;
            cout << "enclosure=" << info.enclosure << endl;
            cout << "encry_type=" << info.encry_type << endl;
            cout << "health=" << info.health << endl;
            cout << "health_value=" << info.health_value << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }

设置邮件信息
        SGP_EMAIL_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetEmilInfo(handle, &info);
        if (ret == SGP_OK)
        {
            info.alarm = 1;
            info.alarm_value = 3600;
            info.enclosure = 1;
            info.encry_type = 2;
            info.health = 1;
            info.health_value = 1;
            info.is_anon = 1;
            info.mailto_num = 5;
            info.smtp_port = 26;
            strcpy(info.smtp_server, "192.168.21.111");
            strcpy(info.username, "123456789");
            strcpy(info.password, "123456");
            strcpy(info.from, "123qq.com");
            strcpy(info.subject, "TEST");
            strcpy(info.mailto[1], "123qq.com");
            ret = SGP_SetEmilInfo(handle, info);
            if (ret == SGP_OK)
            {
                cout << "返回成功，请核对设置是否成功" << endl;
            }
            else
            {
                cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
            }
        }

切换测温范围
        SGP_GENERAL_INFO info;
        memset(&info, 0x00, sizeof(SGP_GENERAL_INFO));
        int ret = SGP_GetGeneralInfo(handle, &info);
        if (ret == SGP_OK)
        {
            int range = info.range_num;
            ret = SGP_SetRange(handle, range - 1);
            if (ret == SGP_OK)
            {
                cout << "返回成功，请核对设置是否成功" << endl;
            }
            else
            {
                cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
            }
        }

        
获取系统版本信息
        SGP_VERSION_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetVersionInfo(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "返回成功，获取的系统信息为：" << endl;
            cout << "设备型号：" << info.model << endl;
            cout << "系统版本：" << info.version << endl;
            cout << "序列号：  " << info.serial << endl;
            cout << "FPGA版本：" << info.fpga_version << endl;
            cout << "测温版本：" << info.measure_version << endl;
            cout << "SDK版本： " << info.sdk_version << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }


同步系统时间
        const char* datetime = "2022-12-11 11:11:11";
        int ret = SGP_SynchroTime(handle, datetime);
        if (ret == SGP_OK)
        {
            cout << "返回成功" << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }


系统重启
        int ret = SGP_RebootSystem(handle);
        if (ret == SGP_OK)
        {
            cout << "系统重启成功" << endl;
        }
        else
        {
            cout << "系统重启失败" << endl;
        }

数据清理
        int ret = SGP_ClearData(handle);
        if (ret == SGP_OK)
        {
            cout << "返回成功" << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }

快门操作
        SGP_SHUTTER_ENUM type = SGP_SHUTTER;
        int ret = SGP_DoShutter(handle,type);
        if (ret == SGP_OK)
        {
            cout << "返回成功" << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }


调焦
        SGP_FOCUS_TYPE type = SGP_FOCUS_PLACE;
        int value = 750;
        int ret = SGP_SetFocus(handle, type, value);
        if (ret == SGP_OK)
        {
            cout << "返回成功，请核对设置是否成功" << endl;
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }

获取电机位置
        int value = 0;
        int ret = SGP_GetMotorPosition(handle, &value);
        if (ret == SGP_OK)
        {
            cout << "返回成功，获取的电机位置为："<<value << endl;
            
        }
        else
        {
            cout << "返回失败\n" << "ret的返回值为：" << ret << endl;
        }

设置电子变倍
        int magnification = 3;
        SGP_VIDEO_PARAM_ENUM type = SGP_IR;
        int ret = SGP_SetElectronicMagnification(handle, type, magnification);
        if (ret == SGP_OK)
        {
            cout << "设置放大"<<magnification<<"倍" << endl;
        }
        else
        {
            cout << "设置电子变倍失败" << endl;
        }

设置报警输入
        SGP_ALARM_INPUT_INFO  info;
        memset(&info, 0x00, sizeof(SGP_ALARM_INPUT_INFO));
        int ret = SGP_GetAlarmInput(handle, &info);
        if (ret == SGP_OK)
        {
            info.flag = 1;
            ret = SGP_SetAlarmInput(handle, info);
            if (ret == SGP_OK)
            {
                cout << "设置报警输入成功" << endl;
            }
            else
            {
                cout << "设置报警输入失败" << endl;
            }

        }

        else
        {
            cout << "获取失败" << endl;
        }

获取报警输入
        SGP_ALARM_INPUT_INFO  info;
        memset(&info, 0x00, sizeof(SGP_ALARM_INPUT_INFO));
        int ret = SGP_GetAlarmInput(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "获取报警输入成功" << endl;
        }
        else
        {
            cout << "获取报警输入失败" << endl;
        }
        

恢复出厂设置
        int ret = SGP_FactoryReset(handle);
        cout << ret << endl;
        if (ret == SGP_OK)
        {
            cout << "恢复出厂设置成功" << endl;
        }
        else
        {
            cout << "恢复出厂设置失败" << endl;
        }


设置测温点索引数组
        const int pointNum = 100;
        int* index = (int*)malloc(pointNum * sizeof(int));
        for (int i = 0; i < pointNum; i++)
        {
            index[i] = i * 100;
        }
        int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
        if (ret == SGP_OK)
        {
            cout << "设置成功！" << endl;
        }
        else
        {
             cout << "设置失败！ret is:" << ret << endl;
        }
        free(index);
        index = NULL;

        


获取测温点数组
        const int pointNum = 100;
        int* index = (int*)malloc(pointNum * sizeof(int));
        for (int i = 0; i < pointNum; i++)
        {
            index[i] = i * 100;
        }
        int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
        if (ret == SGP_OK)
        {
            cout << "设置索引成功！" << endl;
            float* temp = (float*)malloc(pointNum * sizeof(float));
            memset(temp, 0, pointNum * sizeof(float));
            if (temp != NULL)
            {
                int ret = SGP_GetTempPoints(handle, temp, pointNum, 1);
                if (ret == SGP_OK)
                {
                    cout << "获取温度成功！" << endl;
                    for (int i = 0; i < pointNum; i++)
                    {
                        cout << temp[i] << endl;
                    }
                }
                else
                {
                    cout << "获取温度失败！ret is:" << ret << endl;
                }
            }
            free(temp);
            temp = NULL;
        }
        else
        {
            cout << "设置索引失败！ret is:" << ret << endl;
        }
        free(index);
        index = NULL;

获取指定矩形区域温度矩阵
        float* output = new float[640*512];
        SGP_RECT rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = 5;
        rect.h = 5;
        const int  length = rect.w * rect.h;
        int ret = SGP_GetMatrixTempPoints(handle, output, length, rect);
        if (ret == SGP_OK)
        {
            cout << "获取成功" << endl;
            for (int i = 0; i < length; i++)
            {
                cout << output[i] << endl;
            }
        }
        else
        {
            cout << "获取失败！ ret is:" << ret << endl;
        }
        delete[] output;
        output = nullptr;

获取分析对象实时温度
        SGP_ANALYTIC_TEMPS array;
        memset(&array, 0x00, sizeof(array));
        int ret = SGP_GetAnalyticObjectsTemp(handle, &array);
        if (ret == SGP_OK)
        {
            cout << "获取成功！" << endl;
            cout << "全局最高温:" << array.global_max_temp << endl;
            cout << "全局最低温:" << array.global_min_temp << endl;
            cout << "全局平均温:" << array.global_avg_temp << endl;
            cout << "分析对象个数:" << array.analytic_num << endl;
            cout << endl;
            if (array.analytic_num > 0)
            {
                for (int i = 0; i < array.analytic_num; i++)
                {
                    cout << "第" << i + 1 << "个分析对象：" << endl;
                    cout << "分析对象ID：" << array.analytic[i].rule_id << endl;
                    cout << "分析对象名称：" << array.analytic[i].rule_name << endl;
                    cout << "分析对象类型：" << array.analytic[i].type << endl;
                    cout << "最高温:" << array.analytic[i].max_temp << endl;
                    cout << "最低温:" << array.analytic[i].min_temp << endl;
                    cout << "平均温:" << array.analytic[i].avg_temp << endl;
                    cout << endl;
                }
            }
            else { cout << "无分析对象" << endl; }
        }
        else
        {
            cout << "获取失败！ret is:"<< ret << endl;
        }

获取校温信息
        SGP_MEASURE_TEMP_INFO output;
        int ret = SGP_GetMeasureTempInfo(handle, output);
        if (ret == SGP_OK)
        {
            cout << "获取成功！" << endl;
            cout << "实时快门温：" << output.realshuttertemp << endl;
            cout << "上次快门温：" << output.lastshuttertemp << endl;
            cout << "实时镜筒温：" << output.realmirrortemp << endl;
        }
        else
        {
            cout << "获取失败！ret is:" << ret << endl;
        }








































































*/