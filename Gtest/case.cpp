/*
һ�������豸

�޸�����
        const char* username = "admin";
        const char* oldpassword = "admin123";
        const char* newpassword = "admin567";
        int ret1 = SGP_ChangePassword(handle, username, oldpassword, newpassword);
        if (ret1 == SGP_OK)
        {
            cout << "�����޸ĳɹ�" << endl;
        }
        else
        {
            cout << "�����޸�ʧ�ܣ�" << endl;
            cout << "ret�ķ���ֵΪ��" << ret1 << endl;
        }


��������
        const char* usernames = "admin";
        int ret = SGP_ResetPassword(handle, usernames);
        if (ret == SGP_OK)
        {
            cout << "��������ɹ�" << endl;
        }
        else
        {
            cout << "��������ʧ�ܣ�" << endl;
            cout << "ret�ķ���ֵΪ��" << ret << endl;
        }


��ȡ�û���Ϣ
        SGP_GENERAL_INFO info;
        memset(&info, 0, sizeof(info));
        int rets = SGP_GetGeneralInfo(handle, &info);
        cout << "��ȡ��ͨ����ϢΪ��" << endl;
        cout << "ϵͳʱ��Ϊ��" << info.datetime << endl;
        cout << "����ģ��Ŀ�Ϊ��" << info.ir_model_w << endl;
        cout << "����ģ��ĸ�Ϊ��" << info.ir_model_h << endl;
        cout << "����ͨ�������Ϊ��" << info.ir_output_w << endl;
        cout << "����ͨ�������Ϊ��" << info.ir_output_h << endl;  
        cout << "������������ַΪ��" << info.ir_rtsp_url << endl;
        cout << "���·�Χ����Ϊ��" << info.range_num << endl;



��������
��ȡ�����¶�
        int x = 120;
        int y = 120;
        float output = 0.0f;
        int ret = SGP_GetPointTemp(handle, x, y, &output);
        if (ret == SGP_OK)
        {
            cout << "��ȡ�����¶ȳɹ�\n" << "��ȡ���¶�Ϊ��" << output << endl;
        }
        else
        {
            cout << "��ȡ�����¶�ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


 ��ȡ���������¶�
        SGP_ANALYTIC_TEMPS array;
        memset(&array, 0x00, sizeof(array));
        int ret = SGP_GetAnalyticObjectsTemp(handle,&array);
        if (ret == SGP_OK)
        {
            for (int i = 0; i < array.analytic_num; i++)
            {
                cout << "��ȡ���������¶ȳɹ�,��ȡ����������Ϣ���£�" << endl;
                cout << "�����������Ϊ��" << array.analytic_num << endl;             
                cout << "��������Ĺ���IDΪ��" << array.analytic[i].rule_id << endl;
                cout << "��������Ĺ�������Ϊ��" << array.analytic[i].rule_name << endl;
                cout << "�������������Ϊ��" << array.analytic[i].type << endl;
                cout << "�������������¶�Ϊ��" << array.analytic[i].max_temp << endl;
                cout << "���������ƽ���¶�Ϊ��" << array.analytic[i].avg_temp << endl;
                cout << "�������������¶�Ϊ��" << array.analytic[i].min_temp << endl;
                cout << endl;
            }
           
        }
        else
        {
            cout << "��ȡ���������¶�ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


��ȡ�¶Ⱦ���
         //ץͼ��Ϊ�Ա�
        SGP_IMAGE_TYPE types = SGP_IR_IMAGE;
        char path[] = "./testPicture/screencap.jpg";
        int ret11 = SGP_GetScreenCapture(handle, types, path);

        //��ȡ�¶Ⱦ��󲢷����¶�
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
                    cout << "���سɹ�" << endl;
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

                cout << "��ȡ�������Ϊ��" <<setprecision(3) << max << endl;
                cout << "��ȡ�������Ϊ��" <<setprecision(3) << min << endl;
                cout << "��ȡ��ƽ����Ϊ��" <<setprecision(3) << sum/length << endl;
            }
            free(output);
            output = NULL;          
        }


        //��ȡ�¶Ⱦ��󲢷����¶ȣ�ҽ�ƻ�о��
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
                    cout << "���سɹ�" << endl;
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

                cout << "��ȡ�������Ϊ��" <<setprecision(3) << max << endl;
                cout << "��ȡ�������Ϊ��" <<setprecision(3) << min << endl;
                cout << "��ȡ��ƽ����Ϊ��" <<setprecision(3) << sum/length << endl;
            }
            free(output);
            output = NULL;
        }

//�¶Ⱦ�����ת
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
                    cout << "���سɹ�" << endl;
                }
                ret = SGP_GetTempMatriRotationEx(handle, rotateOutput, output, 640, 512, 2);
                if (ret != SGP_OK) {
                    return -1;
                }
                matrixToVideo(rotateOutput);  //��ת��ע���޸ĳ���Ŀ��
            }
            free(output);
            free(rotateOutput);
            output = NULL;
            rotateOutput = NULL;
        }


��������
��ȡ��Ļ��ͼ
        SGP_IMAGE_TYPE type = SGP_IR_IMAGE;
        char path[] = "./testPicture/screencap.jpg";
        int ret = SGP_GetScreenCapture(handle,type, path);
        if (ret == SGP_OK)
        {
            cout << "��ȡ��Ļ��ͼ�ɹ�" << endl;
        }
        else
        {
            cout << "��ȡ��Ļ��ͼʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


��ȡ��ͼ
        const char* path = "./testPicture/screenpic.jpg";
        int ret = SGP_GetHeatMap(handle, path);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�" << endl;
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
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
                cout << "��ȡ��ͼ�ɹ�" << endl;
            }
            else
            {
                cout << "��ȡ��ͼʧ��" << endl;
            }

        }


��ȡ��ѹ��ͼ
        const char* path = "./testPicture/screenpic.fir";
        int ret = SGP_GetFirHeatMap(handle, path);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�" << endl;
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


��ȡ��Ļ��ͼ����
        int input_length = 1024 * 1024 * 10;
        int output_length = 0;
        SGP_IMAGE_TYPE type = SGP_IR_IMAGE;
        char* input = (char*)calloc(input_length, sizeof(char));
        if (input != NULL)
        {
            int ret = SGP_GetScreenCaptureCache(handle, type, input, input_length,&output_length);
            if (ret == SGP_OK)
            {
                cout << "��ȡ��Ļ��ͼ����ɹ�" << endl;
                cout << output_length << endl;

                ofstream outputFile("screenshot.bin", std::ios::binary);
                if (outputFile.is_open()) {
                    outputFile.write(input, output_length);
                    outputFile.close();
                    cout << "��ȡ��Ļ�ػ���ͼ�ɹ���������Ϊ screenshot.bin" << endl;
                }
                else {
                    cout << "�޷����ļ��Ա����ͼ����" << endl;
                }
            }
            else
            {
                cout << "��ȡ��Ļ��ͼ����ʧ��" << endl;
            }
        }
        free(input);
        input = NULL; 

��ȡ��ͼ����
        int input_length = 1024 * 1024 * 10;
        int output_length = 0;
        char* input = (char*)calloc(input_length, sizeof(char));
        if (input != NULL)
        {
            int ret = SGP_GetHeatMapCache(handle, input, input_length, &output_length);
            if (ret == SGP_OK)
            {
                cout << "��ȡ��ͼ����ɹ�" << endl;
                cout << output_length << endl;
                ofstream outputFile("heatMapCache.bin", std::ios::binary);
                if (outputFile.is_open()) {
                    outputFile.write(input, output_length);
                    outputFile.close();
                    cout << "��ȡ��ͼ����ɹ���������Ϊ heatMapCache.bin" << endl;
                }
                else {
                    cout << "�޷����ļ��Ա�����ͼ����" << endl;
                }
            }
            else
            {
                cout << "��ȡ��ͼ����ʧ��" << endl;
            }
        }
        free(input);
        input = NULL;


��ȡ��ѹ��ͼ����
        int input_length = 1024 * 1024 * 10;
        int output_length = 0;
        char* input = (char*)calloc(input_length, sizeof(char));
        if (input != NULL)
        {
            int ret = SGP_GetFirHeatMapCache(handle, input, input_length, &output_length);
            if (ret == SGP_OK)
            {
                cout << "��ȡ��ѹ��ͼ����ɹ�" << endl;
                cout << output_length << endl;
                ofstream outputFile("firMapCache.bin", std::ios::binary);
                if (outputFile.is_open()) {
                    outputFile.write(input, output_length);
                    outputFile.close();
                    cout << "��ȡ��ѹ��ͼ����ɹ���������Ϊ firMapCache.bin" << endl;
                }
                else {
                    cout << "�޷����ļ��Ա����ѹ��ͼ����" << endl;
                }
            }
            else
            {
                cout << "��ȡ��ѹ��ͼ����ʧ��" << endl;
            }
        }
        free(input);
        input = NULL;


�ġ�����
����������Ƶ

�ص��������壺
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

            �ӿڣ�
            for (int i = 1; i <= 1; i++)
            {
            int result = SGP_OpenIrVideo(handle, GetIrRtsp, 0);
            printf("��%d��SGP_OpenIrVideo�ӿڷ���ֵ��%d\n", i, result);
            Sleep(5000);
            std::string IRFile = "D:/photo/1234.mp4";
            int startResult = SGP_StartRecord(handle, SGP_IR_VIDEO,IRFile.c_str(), GetRecordStatus,0);
            printf("SGP_StartRecord�ӿں��ⷵ��ֵ��%d\n", startResult);
            Sleep(60000);
            SGP_StopRecord(handle, SGP_IR_VIDEO);
            //�ر���Ƶ��
            SGP_CloseIrVideo(handle);
            }

��ʼ¼�ƣ������豸�ˣ�
        int record = 1;
        int record_stream = 2;
        int ret = SGP_Record(handle, record, record_stream);
        if (ret == SGP_OK)
        {
            cout << "��ʼ¼��" << endl;
        }
        else
        {
            cout << "¼��ʧ��" << endl;
        }



�塢�ٿ��豸

����ȫ���¶Ȳ���
        SGP_THERMOMETRY_PARAM info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetThermometryParam(handle, &info);
        if (ret == SGP_OK)
        {
            info.color_bar = 12;  //ɫ��
            info.color_show = 1;  //ɫ����ʾ
            info.flag = 1;        //���¿���
            info.mod_temp = 0;    //�¶�����
            info.ambient = 22;    //�����¶�
            info.atmo_trans = 0.2;//����͸����
            info.dist = 10;      //����
            info.emiss = 0.5;     //������
            info.emiss_mode = 1;  //����������
            info.gear = 0;        //���·�Χ
            info.humi = 66;       //�¶ȷ�Χ
            info.ref_temp = 23;   //�����¶�
            strcpy(info.show_desc, "123456"); //��ʾ�ַ���
            info.show_mode = 7;   //�¶���ʾ����
            info.show_string = 5; //�ַ�����ʾλ��
            info.opti_trans = 0.2;//��ѧ͸����
            info.isot_flag = 1;   //�����߿���
            info.isot_high = 20;  //�����߸�����ֵ
            info.isot_low = 20;   //�����ߵ�����ֵ
            info.isot_type = 2;   //����������
            strcpy(info.isot_high_color, "#00ff00");   //�����߸�����ɫ
            strcpy(info.isot_low_color, "#00ff00");    //�����ߵ�����ɫ
            ret = SGP_SetThermometryParam(handle, info);
            if (ret == SGP_OK)
            {
                cout << "����ȫ���¶Ȳ����ɹ�,������" << endl;
            }
            else
            {
                cout << "����ȫ���¶Ȳ���ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
            }
        }


��ȡȫ���¶Ȳ���
        SGP_THERMOMETRY_PARAM info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetThermometryParam(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�,ȫ�ֲ��²�����Ϣ���£�" << endl;
            cout << "�����¶�Ϊ��  " << info.ambient << endl;
            cout << "����͸����Ϊ��" << info.atmo_trans << endl;
            cout << "ɫ����Ϊ��    " << info.color_bar << endl;
            cout << "����Ϊ��      " << info.dist << endl;
            cout << "������Ϊ��    " << info.emiss << endl;
            cout << "����������Ϊ��" << info.emiss_mode << endl;
            cout << "ʪ��Ϊ��      " << info.humi << endl;
            cout << "��ѧ͸����Ϊ��" << info.opti_trans << endl;
            cout << "�ַ�����ʾΪ��" << info.show_desc << endl;
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


����ȫ�ֲ��¿���
        int flag = 1;
        int ret = SGP_SetThermometryFlag(handle, flag);
        if (ret == SGP_OK)
        {
            cout << "����ȫ�ֲ��¿��سɹ�,��˶������Ƿ�ɹ�" << endl;
        }
        else
        {
            cout << "����ȫ�ֲ��¿���ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }



����ɫ����
        int colorbar = 24;
        int ret = SGP_SetColorBar(handle, colorbar);
        if (ret == SGP_OK)
        {
            cout << "����ɫ���ųɹ�,��˶������Ƿ�ɹ�" << endl;
        }
        else
        {
            cout << "����ɫ����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


����ɫ����ʾ
        int showcolorbar = 0;
        int ret = SGP_SetColorBarShow(handle, showcolorbar);
        if (ret == SGP_OK)
        {
            cout << "����ɫ����ʾ�ɹ�����˶������Ƿ�ɹ�" << endl;
        }
        else
        {
            cout << "����ɫ����ʾʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


�����¶���ʾ����
        int showtype = 7;
        int ret = SGP_SetTempShowMode(handle, showtype);
        if (ret == SGP_OK)
        {
            cout << "�����¶���ʾ���ͳɹ�����˶������Ƿ�ɹ�" << endl;
        }
        else
        {
            cout << "�����¶���ʾ����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


�����ַ�������
        int type = 2;
        const char* dateshow = "123";
        int ret = SGP_SetStringShow(handle, type, dateshow);
        if (ret == SGP_OK)
        {
            cout << "�����ַ������ӳɹ�����˶������Ƿ�ɹ�" << endl;
        }
        else
        {
            cout << "�����ַ�������ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


���÷��������¶���ʾ����
        int showtype = 1;
        int ret = SGP_SetThermometryRuleShowMode(handle, showtype);
        if (ret == SGP_OK)
        {
            cout << "���÷��������¶���ʾ���ͳɹ�����˶������Ƿ�ɹ�" << endl;
        }
        else
        {
            cout << "���÷��������¶���ʾ����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }




��ӷ�������
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
        rulePoint.points_num = 1; //�������1
        rulePoint.points[0].x = 200;
        rulePoint.points[0].y = 200;
        strcpy(rulePoint.rule_name, "��1");
        rulePoint.show_location = 1;
        rulePoint.temp_mod = 1;
        rulePoint.type = 1;  //������1
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
            cout << "��ӷ�������ɹ�����˶������Ƿ�ɹ�" << endl;
        }
        else
        {
            cout << "��ӷ�������ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }
       
        //SGP_DeleteAllThermometryRule(handle);

���·�������
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
                    cout << "���·�������ɹ�����˶������Ƿ�ɹ�" << endl;
                }
                else
                {
                    cout << "���·�������ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
                }
               
            }
        }


ɾ����������
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
                    cout << "ɾ����������ɹ�����˶������Ƿ�ɹ�" << endl;
                }
                else
                {
                    cout << "ɾ����������ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
                }
               
            }
        }

       

ɾ��ȫ����������
        int ret = SGP_DeleteAllThermometryRule(handle);
        if (ret == SGP_OK)
        {
            cout << "ɾ��ȫ����������ɹ�����˶������Ƿ�ɹ�" << endl;
        }
        else
        {
            cout << "ɾ��ȫ����������ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }



��ȡ��������
        SGP_RULE_ARRAY array;
        memset(&array, 0x00, sizeof(array));
        int ret = SGP_GetThermometryRule(handle, &array);
        if (ret == SGP_OK)
        {
            cout << "�����������Ϊ��" << array.rule_num << endl;
            for (int i = 0; i < array.rule_num; i++)
            {
                cout << "��" << i + 1 << "������������Ϣ��" << endl;
                cout << "����͸����Ϊ��" << array.rule[i].atmo_trans << endl;
                cout << "����Ϊ��" << array.rule[i].dist << endl;
                cout << "IDΪ��" << array.rule[i].id << endl;
                cout << "��������Ϊ��" << array.rule[i].alarm_condition << endl;
                cout << "�Ƿ���Ҫ������" << array.rule[i].alarm_flag << endl;
                cout << "�������ͣ�" << array.rule[i].alarm_type << endl;
                cout << "ƽ���£�" << array.rule[i].avg_temp << endl;
                cout << "�Ƿ����ã�" << array.rule[i].flag << endl;
                cout << "����������ֵ��" << array.rule[i].high_temp << endl;
                cout << "����������ֵ��" << array.rule[i].low_temp << endl;
                cout << "�������ƣ�" << array.rule[i].rule_name << endl;
                cout << "��ʾλ�ã�" << array.rule[i].show_location << endl;
                cout << "�¶���" << array.rule[i].temp_mod << endl;
                cout << "����͸���ʣ�" << array.rule[i].atmo_trans << endl;
                cout << "�����ʣ�" << array.rule[i].emiss << endl;
                cout << "���������ͣ�" << array.rule[i].emiss_mode << endl;
                cout << "ʪ�ȣ�" << array.rule[i].humi << endl;
                cout << "��ѧ͸���ʣ�" << array.rule[i].opti_trans << endl;
                cout << "�����¶ȣ�" << array.rule[i].ref_temp << endl;
                cout << endl;
            }
            
            cout << "��ȡ��������ɹ�����˶������Ƿ�ɹ�" << endl;
        }
        else
        {
            cout << "��ȡ��������ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }



���ú���ͼ��Ч������
        SGP_IR_IMAGE_EFFECT_ENUM type = SGP_IR_SHARPNESS;
        int value = 50;
        int ret = SGP_SetIrImageEffectParam(handle, type, value);
        if (ret == SGP_OK)
        {
            cout << "���ú���ͼ��Ч�������ɹ�����˶������Ƿ�ɹ�" << endl;
        }
        else
        {
            cout << "���ú���ͼ��Ч������ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


��ȡ����ͼ��Ч������
        SGP_IAMGE_EFFECT_PARAM_IR_CONFIG info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetIrImageEffectParam(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "��ȡ����ͼ��Ч�������ɹ�����ȡ����Ϣ���£�" << endl;
            cout << "��ȡ�Ŀ��Ų���ʱ��Ϊ��" << info.auto_shutter << endl;
            cout << "��ȡ������Ϊ��        " << info.brightness << endl;
            cout << "��ȡ�ĶԱȶ�Ϊ��      " << info.contrast << endl;
            cout << "��ȡ��ϸ����ǿֵΪ��  " << info.iee_value  << endl;
            cout << "��ȡ�����ֵΪ��      " << info.sharpness << endl;                     
        }
        else
        {
            cout << "��ȡ����ͼ��Ч������ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


����������Ϣ
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
                cout << "����������Ϣ�ɹ�����˶������Ƿ�ɹ�" << endl;
            }
            else
            {
                cout << "����������Ϣʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
            }
        }
               

��ȡ������Ϣ      
       SGP_NET_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetNetInfo(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "��ȡ������Ϣ�ɹ�����ȡ��Ϣ���£�" << endl;
            cout << "��ȡ��������Ϊ��"<<info.host_name << endl;
            cout << "��ȡip��ַΪ��"  <<info.ipaddr << endl;
        }
        else
        {
            cout << "��ȡ������Ϣʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


���ö˿���Ϣ
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
                cout << "���سɹ�����˶������Ƿ�ɹ�" << endl;
            }
            else
            {
                cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
            }
        }

��ȡ�˿���Ϣ
        SGP_PORT_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetPortInfo(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�����ȡ�Ķ˿���Ϣ���£�" << endl;
            cout << "http�˿ں�Ϊ��\t" << info.http_port << endl;
            cout << "��������豸��Ϊ:" << info.max_connectios << endl;
            cout << "onvif���أ�\t" << info.onvif_check << endl;
            cout << "rtsp�˿ں�Ϊ��\t" << info.rtsp_port << endl;
            cout << "tcp�˿ں�Ϊ��\t" << info.tcp_port << endl;
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }



����¼����Ϣ
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
                cout << "���سɹ�����˶������Ƿ�ɹ�" << endl;
            }
            else
            {
                cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
            }

        }


��ȡ¼����Ϣ
        SGP_RECORD_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetRecordInfo(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�����ȡ�Ķ˿���Ϣ���£�" << endl;
            cout << "¼����ʱʱ�䣺\t" << info.record_interval << endl;
            cout << "���¼���ļ���С��" << info.record_max_size << endl;
            cout << "¼��ʱ���� \t" << info.record_time << endl;
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }




��ȡ��������
        SGP_SHIELD_AREA_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetShieldArea(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�����ȡ����������Ϣ���£�" << endl;
            cout << "�����������Ϊ��" << info.rect_num << endl;
            cout << "������������Ϊ��" << endl;
            for (int i = 0; i < info.rect_num; i++)
            {
                printf("��%d���������������Ϊ��\n", i+1);
                cout << "x=" << info.rect[i].x << endl;
                cout << "y=" << info.rect[i].y << endl;
                cout << "w=" << info.rect[i].w << endl;
                cout << "h=" << info.rect[i].h << endl;
                cout << endl;
            }
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }



������������
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
                cout << "���سɹ�����˶������Ƿ�ɹ�" << endl;
            }
            else
            {
                cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
            }
        }


��ȡȫ���¶ȸ澯
        SGP_COLD_HOT_TRACE_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetColdHotTrace(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�����ȡȫ���¶ȸ澯��Ϣ���£�" << endl;
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
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }

����ȫ���¶ȸ澯
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
                cout << "���سɹ�����˶������Ƿ�ɹ�" << endl;
            }
            else
            {
                cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
            }
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


��ȡ��������澯
        SGP_TEMP_ALARM_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetTempAlarm(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�����ȡ��������澯��Ϣ���£�" << endl;
            cout << "alarm_flag:" << info.alarm_flag << endl;
            cout << "capture_flag:" << info.capture_flag << endl;
            cout << "capture_stream:" << info.capture_stream << endl;
            cout << "output_flag:" << info.output_flag << endl;
            cout << "output_hold:" << info.output_hold << endl;
            cout << "sendmail:" << info.sendmail << endl;
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


���÷�������澯
        SGP_TEMP_ALARM_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetTempAlarm(handle, &info);
        if (ret == SGP_OK)
        {
            info.alarm_flag = 1;//�Ƿ������� 1:����; 0:������
            info.capture_flag = 1;//�Ƿ��ͼ 0:��; 1:��
            info.capture_stream = 2;//��ͼ���� 0:����ͼ; 1:ֻ��ͼ�ɼ���; 2:ֻ��ͼ����; 3:��ͼ����Ϳɼ���
            info.record_flag = 1;//�Ƿ�¼�� 0:��¼��; 1:¼��
            info.record_stream = 2;//¼������ 0:��¼��; 1:ֻ¼�ƿɼ���; 2:ֻ¼�ƺ���; 3:¼�ƺ���Ϳɼ���
            info.record_delay = 150;//¼��ʱ�� 10-300s
            info.output_flag = 1;//�Ƿ��ⲿ��� 0:����� 1:���
            info.output_hold = 20;
            info.alarm_shake = 8;
            info.sendmail = 1;
            ret = SGP_SetTempAlarm(handle, info);
            if (ret == SGP_OK)
            {
                cout << "���سɹ�����˶������Ƿ�ɹ�" << endl;
            }
            else
            {
                cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
            }
        }


��ȡ��Ƶ����
        SGP_VIDEO_PARAM_ENUM type = SGP_IR;
        SGP_VIDEO_PARAM param;
        memset(&param, 0x00, sizeof(param));
        int ret = SGP_GetVideoParam(handle, type, &param);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�����ȡ����Ƶ�������£�" << endl;
            cout << "param.bit_size=" << param.bit_size << endl;
            cout << "param.fps=" << param.fps << endl;
            cout << "param.gop_size=" << param.gop_size << endl;
            cout << "param.level=" << param.level << endl;
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


������Ƶ����
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
                cout << "���سɹ�����˶������Ƿ�ɹ�" << endl;
            }
            else
            {
                cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
            }
        }


��ȡ�����쳣
        SGP_NET_EXCEPTION_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetNetException(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�����ȡ�����쳣��Ϣ���£�" << endl;
            cout << "flag=" << info.flag << endl;
            cout << "output_flag=" << info.output_flag << endl;
            cout << "output_hold=" << info.output_hold << endl;
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }

���������쳣
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
                cout << "���سɹ�����˶������Ƿ�ɹ�" << endl;
            }
            else
            {
                cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
            }

        }

��ȡ�Ƿ�����
        SGP_ACCESS_VIOLATION_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetAccessViolation(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�����ȡ�ķǷ�������Ϣ���£�" << endl;
            cout << "allow_count=" << info.allow_count << endl;
            cout << "flag=" << info.flag << endl;
            cout << "output_flag=" << info.output_flag << endl;
            cout << "output_hold=" << info.output_hold << endl;
            cout << "sendmail=" << info.sendmail << endl;
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }

���÷Ƿ�����
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
                cout << "���سɹ�����˶������Ƿ�ɹ�" << endl;
            }
            else
            {
                cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
            }
        }

��ȡ�ʼ���Ϣ
        SGP_EMAIL_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetEmilInfo(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�����ȡ���ʼ���Ϣ���£�" << endl;
            cout << "alarm=" << info.alarm << endl;
            cout << "alarm_value=" << info.alarm_value << endl;
            cout << "enclosure=" << info.enclosure << endl;
            cout << "encry_type=" << info.encry_type << endl;
            cout << "health=" << info.health << endl;
            cout << "health_value=" << info.health_value << endl;
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }

�����ʼ���Ϣ
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
                cout << "���سɹ�����˶������Ƿ�ɹ�" << endl;
            }
            else
            {
                cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
            }
        }

�л����·�Χ
        SGP_GENERAL_INFO info;
        memset(&info, 0x00, sizeof(SGP_GENERAL_INFO));
        int ret = SGP_GetGeneralInfo(handle, &info);
        if (ret == SGP_OK)
        {
            int range = info.range_num;
            ret = SGP_SetRange(handle, range - 1);
            if (ret == SGP_OK)
            {
                cout << "���سɹ�����˶������Ƿ�ɹ�" << endl;
            }
            else
            {
                cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
            }
        }

        
��ȡϵͳ�汾��Ϣ
        SGP_VERSION_INFO info;
        memset(&info, 0x00, sizeof(info));
        int ret = SGP_GetVersionInfo(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�����ȡ��ϵͳ��ϢΪ��" << endl;
            cout << "�豸�ͺţ�" << info.model << endl;
            cout << "ϵͳ�汾��" << info.version << endl;
            cout << "���кţ�  " << info.serial << endl;
            cout << "FPGA�汾��" << info.fpga_version << endl;
            cout << "���°汾��" << info.measure_version << endl;
            cout << "SDK�汾�� " << info.sdk_version << endl;
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


ͬ��ϵͳʱ��
        const char* datetime = "2022-12-11 11:11:11";
        int ret = SGP_SynchroTime(handle, datetime);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�" << endl;
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


ϵͳ����
        int ret = SGP_RebootSystem(handle);
        if (ret == SGP_OK)
        {
            cout << "ϵͳ�����ɹ�" << endl;
        }
        else
        {
            cout << "ϵͳ����ʧ��" << endl;
        }

��������
        int ret = SGP_ClearData(handle);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�" << endl;
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }

���Ų���
        SGP_SHUTTER_ENUM type = SGP_SHUTTER;
        int ret = SGP_DoShutter(handle,type);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�" << endl;
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }


����
        SGP_FOCUS_TYPE type = SGP_FOCUS_PLACE;
        int value = 750;
        int ret = SGP_SetFocus(handle, type, value);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�����˶������Ƿ�ɹ�" << endl;
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }

��ȡ���λ��
        int value = 0;
        int ret = SGP_GetMotorPosition(handle, &value);
        if (ret == SGP_OK)
        {
            cout << "���سɹ�����ȡ�ĵ��λ��Ϊ��"<<value << endl;
            
        }
        else
        {
            cout << "����ʧ��\n" << "ret�ķ���ֵΪ��" << ret << endl;
        }

���õ��ӱ䱶
        int magnification = 3;
        SGP_VIDEO_PARAM_ENUM type = SGP_IR;
        int ret = SGP_SetElectronicMagnification(handle, type, magnification);
        if (ret == SGP_OK)
        {
            cout << "���÷Ŵ�"<<magnification<<"��" << endl;
        }
        else
        {
            cout << "���õ��ӱ䱶ʧ��" << endl;
        }

���ñ�������
        SGP_ALARM_INPUT_INFO  info;
        memset(&info, 0x00, sizeof(SGP_ALARM_INPUT_INFO));
        int ret = SGP_GetAlarmInput(handle, &info);
        if (ret == SGP_OK)
        {
            info.flag = 1;
            ret = SGP_SetAlarmInput(handle, info);
            if (ret == SGP_OK)
            {
                cout << "���ñ�������ɹ�" << endl;
            }
            else
            {
                cout << "���ñ�������ʧ��" << endl;
            }

        }

        else
        {
            cout << "��ȡʧ��" << endl;
        }

��ȡ��������
        SGP_ALARM_INPUT_INFO  info;
        memset(&info, 0x00, sizeof(SGP_ALARM_INPUT_INFO));
        int ret = SGP_GetAlarmInput(handle, &info);
        if (ret == SGP_OK)
        {
            cout << "��ȡ��������ɹ�" << endl;
        }
        else
        {
            cout << "��ȡ��������ʧ��" << endl;
        }
        

�ָ���������
        int ret = SGP_FactoryReset(handle);
        cout << ret << endl;
        if (ret == SGP_OK)
        {
            cout << "�ָ��������óɹ�" << endl;
        }
        else
        {
            cout << "�ָ���������ʧ��" << endl;
        }


���ò��µ���������
        const int pointNum = 100;
        int* index = (int*)malloc(pointNum * sizeof(int));
        for (int i = 0; i < pointNum; i++)
        {
            index[i] = i * 100;
        }
        int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
        if (ret == SGP_OK)
        {
            cout << "���óɹ���" << endl;
        }
        else
        {
             cout << "����ʧ�ܣ�ret is:" << ret << endl;
        }
        free(index);
        index = NULL;

        


��ȡ���µ�����
        const int pointNum = 100;
        int* index = (int*)malloc(pointNum * sizeof(int));
        for (int i = 0; i < pointNum; i++)
        {
            index[i] = i * 100;
        }
        int ret = SGP_SetTempPoints(handle, index, pointNum, 1);
        if (ret == SGP_OK)
        {
            cout << "���������ɹ���" << endl;
            float* temp = (float*)malloc(pointNum * sizeof(float));
            memset(temp, 0, pointNum * sizeof(float));
            if (temp != NULL)
            {
                int ret = SGP_GetTempPoints(handle, temp, pointNum, 1);
                if (ret == SGP_OK)
                {
                    cout << "��ȡ�¶ȳɹ���" << endl;
                    for (int i = 0; i < pointNum; i++)
                    {
                        cout << temp[i] << endl;
                    }
                }
                else
                {
                    cout << "��ȡ�¶�ʧ�ܣ�ret is:" << ret << endl;
                }
            }
            free(temp);
            temp = NULL;
        }
        else
        {
            cout << "��������ʧ�ܣ�ret is:" << ret << endl;
        }
        free(index);
        index = NULL;

��ȡָ�����������¶Ⱦ���
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
            cout << "��ȡ�ɹ�" << endl;
            for (int i = 0; i < length; i++)
            {
                cout << output[i] << endl;
            }
        }
        else
        {
            cout << "��ȡʧ�ܣ� ret is:" << ret << endl;
        }
        delete[] output;
        output = nullptr;

��ȡ��������ʵʱ�¶�
        SGP_ANALYTIC_TEMPS array;
        memset(&array, 0x00, sizeof(array));
        int ret = SGP_GetAnalyticObjectsTemp(handle, &array);
        if (ret == SGP_OK)
        {
            cout << "��ȡ�ɹ���" << endl;
            cout << "ȫ�������:" << array.global_max_temp << endl;
            cout << "ȫ�������:" << array.global_min_temp << endl;
            cout << "ȫ��ƽ����:" << array.global_avg_temp << endl;
            cout << "�����������:" << array.analytic_num << endl;
            cout << endl;
            if (array.analytic_num > 0)
            {
                for (int i = 0; i < array.analytic_num; i++)
                {
                    cout << "��" << i + 1 << "����������" << endl;
                    cout << "��������ID��" << array.analytic[i].rule_id << endl;
                    cout << "�����������ƣ�" << array.analytic[i].rule_name << endl;
                    cout << "�����������ͣ�" << array.analytic[i].type << endl;
                    cout << "�����:" << array.analytic[i].max_temp << endl;
                    cout << "�����:" << array.analytic[i].min_temp << endl;
                    cout << "ƽ����:" << array.analytic[i].avg_temp << endl;
                    cout << endl;
                }
            }
            else { cout << "�޷�������" << endl; }
        }
        else
        {
            cout << "��ȡʧ�ܣ�ret is:"<< ret << endl;
        }

��ȡУ����Ϣ
        SGP_MEASURE_TEMP_INFO output;
        int ret = SGP_GetMeasureTempInfo(handle, output);
        if (ret == SGP_OK)
        {
            cout << "��ȡ�ɹ���" << endl;
            cout << "ʵʱ�����£�" << output.realshuttertemp << endl;
            cout << "�ϴο����£�" << output.lastshuttertemp << endl;
            cout << "ʵʱ��Ͳ�£�" << output.realmirrortemp << endl;
        }
        else
        {
            cout << "��ȡʧ�ܣ�ret is:" << ret << endl;
        }








































































*/