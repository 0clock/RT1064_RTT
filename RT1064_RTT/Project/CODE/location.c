//
// Created by ThinkPad on 2022/6/28.
//
#include <math.h>
#include "location.h"
#include "motor.h"
#include "attitude_solution.h"
#include <stdlib.h>
#include <string.h>
#include "buzzer.h"
#include "imgproc.h"
#include "SEEKFREE_MT9V03X_CSI.h"
#include "flash_param.h"

//**Ѱ�ұ߽�**//

#define COLUMN_SCOPE 70 //��ɨ�跶Χ ���� & ���� ɨ��
#define ROW_SCOPE 50    //��ɨ�跶Χ ���� & ���� ɨ��

#define COLUMN_OFFSET 50 //��ƫִ ���� & ���� ɨ��ʱ������ֱ� ���� & ���� �ж�������
#define ROW_OFFSET 50    //��ƫִ ���� & ���� ɨ��ʱ������ֱ� ���� & ���� �ж�������

#define COLUMN_TAR 60 //���ж���ֵ
#define ROW_TAR 55    //���ж���ֵ

uint8_t img_line_data[MT9V03X_CSI_H][MT9V03X_CSI_W];
uint8_t img_thres_data[MT9V03X_CSI_H][MT9V03X_CSI_W];
image_t img_raw = DEF_IMAGE(NULL, MT9V03X_CSI_W, MT9V03X_CSI_H);
image_t img_thres = DEF_IMAGE((uint8_t *) img_thres_data, MT9V03X_CSI_W, MT9V03X_CSI_H);
image_t img_line = DEF_IMAGE((uint8_t *) img_line_data, MT9V03X_CSI_W, MT9V03X_CSI_H);

int tempTest;

location_goal Car={0}; //С��״̬��λ�ã�Ŀ�꣩�洢�ṹ��

bool initHashMapFlag = false; //�Ƿ��ʼ����ϣ��

const float PI = 3.1415926f;

//��Ե������ Xt �ϱ�ԵX���� Xb �±�ԵX���� Yl ���ԵY���� Yr �ұ�ԵY����
uint8 Xt = 10, Xb = 35, Yl = 10, Yr = 45;


//-------------------�ṹ��-----------------------//

struct Route_Point {//����ṹ��
	int num;//���
	float dist;//����
	bool isPointed;//�Ƿ��Ѿ����������
} HashMap[locate_sz];

//---------------------����-----------------------//

float originMap[locate_sz][2] = {//����ԭʼ����
		1, 1,
		10, 10,
		20, 20,
		5, 5,
		15, 15,
		17,17,
		3,3,
		2,2,
		8,8,
		25,10,
		10,1,
		25,20
};

/*
 ***************************************************************
*	�� �� ��: Locate_Route
*   ����˵��: ·���滮
*	��    ��: ��
*	�� �� ֵ: num:·�������
 ***************************************************************
 *  ���
 *  int t;//t�����ĸ�����ֻ��ʼ��ǰt���ṹ��
	scanf("%d",&t);
	initHashMap(t);
	if (initHashMapFlag != 1) {
		printf("��ʼ��HashMap����\n");
	}
	else printf("��ʼ��HashMap�ɹ�\n");
	for (int i = 0; i < t; ++i) {
		int n=locate_route();//n��ʾoriginMap�ĵ�N���
		printf("%f %f\n",originMap[n][0],originMap[n][1]);
	}
 */
void initHashMap(int true_sz) {//��ʼ��HashMap
	for (int i = 0; i < locate_sz; ++i) {
		HashMap[i].num = i;
		HashMap[i].dist = 0;
		if (i < true_sz)HashMap[i].isPointed = false;
		else HashMap[i].isPointed = true;
	}
	initHashMapFlag = 1;
}

int locate_route() {
    int road_best = 1;           //�ֲ����ŵ�
	for (int j = 0; j < locate_sz; ++j) {
		if (HashMap[j].isPointed) continue;
		HashMap[j].dist = sqrtf((powf((Car.x - originMap[j][0]), 2) +
		                         powf((Car.y - originMap[j][1]), 2))); //�������
	}
	for(int j=0;j<locate_sz;++j){
		if(HashMap[j].isPointed)continue;
		if(HashMap[j].dist<HashMap[road_best].dist&&j!=road_best)road_best = j;
	}

    tempTest=road_best;

    HashMap[road_best].isPointed = true;
	return HashMap[road_best].num;
}



void Find_Edge_1(void)
{
    uint8_t mt9v03x_thres_image[MT9V03X_CSI_W][MT9V03X_CSI_H];
    memset(&mt9v03x_thres_image,*img_thres.data,sizeof(img_thres.data));//
    uint8 aspect = 255;   //����3 ��|�� ѹ������ֵ
    uint8 black_nums = 0; //��¼��ǰɨ���кڵ���ֵ
    //�ϰ����� ���м��������� ����
    for (uint8 i = 60; i > 60 - ROW_SCOPE; --i)
    {
        black_nums = 0;
        //�������� ÿ�ΰ����������������µ�������ں�
        for (uint8 j = 94 - COLUMN_OFFSET; j < 94 + COLUMN_OFFSET; ++j)
        {
            aspect = mt9v03x_thres_image [i - 1][j] &
                    mt9v03x_thres_image [i][j] & mt9v03x_thres_image[i + 1][j];
            if (aspect == 0)
                black_nums++;
        }
        if (black_nums > COLUMN_TAR)
        {
            Xt = i;
            break;
        }
    }

    //�Ұ����� ���м��������� ����
    for (uint8 j = 94; j < 94 + COLUMN_SCOPE; ++j)
    {
        black_nums = 0;
        //�������� ÿ�ΰ����������������µ�������ں�
        for (uint8 i = 60 - ROW_OFFSET; i < 60 + ROW_OFFSET; ++i)
        {
            aspect = mt9v03x_thres_image[i][j - 1] &
                     mt9v03x_thres_image[i][j] & mt9v03x_thres_image[i][j + 1];
            if (aspect == 0)
                black_nums++;
        }
        if (black_nums > ROW_TAR)
        {
            Yr = j;
            break;
        }
    }

    //�°����� ���м��������� ����
    for (uint8 i = 60; i < 60 + ROW_SCOPE; ++i)
    {
        black_nums = 0;
        //�������� ÿ�ΰ����������������µ�������ں�
        for (uint8 j = 94 - COLUMN_OFFSET; j < 94 + COLUMN_OFFSET; ++j)
        {
            aspect = mt9v03x_thres_image[i - 1][j] &
                     mt9v03x_thres_image[i][j] & mt9v03x_thres_image[i + 1][j];
            if (aspect == 0)
                black_nums++;
        }
        if (black_nums > COLUMN_TAR)
        {
            Xb = i;
            break;
        }
    }

    //������� ���м��������� ����
    for (uint8 j = 94; j > 94 - COLUMN_SCOPE; --j)
    {
        black_nums = 0;
        //�������� ÿ�ΰ����������������µ�������ں�
        for (uint8 i = 60 - ROW_OFFSET; i < 60 + ROW_OFFSET; ++i)
        {
            aspect = mt9v03x_thres_image[i][j - 1] &
                     mt9v03x_thres_image[i][j] & mt9v03x_thres_image[i][j + 1];
            if (aspect == 0)
                black_nums++;
        }
        if (black_nums > ROW_TAR)
        {
            Yl = j;
            break;
        }
    }
}

void carlocation_init(){
    initHashMap(12);
    Car.x=0;
    Car.y=0;
	int tmp=locate_route();
    Car.x1=originMap[tmp][0];
    Car.y1=originMap[tmp][1];
}

void location_entry(){
    while(1){

        }
}

void location_thres_init(void)
{
    rt_thread_t tid;
    //��ʼ��
    //����Ѱ�������߳� ���ȼ�����Ϊ8
    tid = rt_thread_create("location", location_entry, RT_NULL, 2048, 31, 100);
    //���ȼ������̸߳ߣ��տ�ʼ��ִ�����俨���ڴ��̣߳��ҵ��������߳�return����

    //����Ѱ�������߳�
    if (RT_NULL != tid)
    {
        rt_thread_startup(tid);
    }
}

/*
//ת������
void map_change(int input[][2], int output[][2], int pts_nums, int *pts_label, int yr, int xb) {
    for (int i = 0; i <= pts_nums; ++i) {
        output[i][0] = input[pts_label[i]][0];
        output[i][1] = input[pts_label[i]][1];
    }//��������

    for (int i = 0; i <= pts_nums; ++i) {
        output[i][0] = abs(output[i][0] - yr);
        output[i][1] 

= abs(output[i][1] - xb);
    }//����ӳ������ϵ

    return ;
}

//ת������ֵ
void map_calculate(int input[][2], double *angle, double *gap, const int pts_nums, double x_length, double y_length) {

//    x_length = (double)(Yr - Yl) / 100.0f;
//    y_length = (double)(Xb - Xt) / 100.0f;

    for (int i = 0; i <= pts_nums; ++i) {
        angle[i] = atan2(input[i+1][1] - input[i][1],
                         input[i+1][0] - input[i][0]) * 180.0f / PI;
        if(angle[i] < 0)
            angle[i] = 360.0f + angle[i];

//        for (int j = 1; j <= pts_nums; ++j) {
//          input[j][0] = input[j][0] - (x_length * 10.0f);
//          input[j][1] = input[j][1] + (y_length * 8.0f);
//        }

        gap[i] = sqrt(pow((((double) input[i][0] / x_length * 7.0f) -
                       ((double) input[i + 1][0] / x_length * 7.0f)), 2)
                       + pow((((double) input[i][1] / y_length * 5.0f) -
                       ((double) input[i + 1][1] / y_length * 5.0f)), 2));
    }
}

*/