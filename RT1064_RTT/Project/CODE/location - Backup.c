//
// Created by ThinkPad on 2022/6/28.
//
#include <math.h>
#include "location.h"
#include "motor.h"
#include "attitude_solution.h"

#include <stdlib.h>
#include "buzzer.h"

#define locate_sz 7             //������������,���ܻ���Ҫ���ģ�Ŀ�������ȷ����(5-20���п���)


location_goal Car={0}; //С��״̬��λ�ã�Ŀ�꣩�洢�ṹ��

//-------------------�ṹ��-----------------------//

struct Route_Dist{//����ṹ��
    int num;//���
    double dist;//����
} Route_D[5];

//---------------------����-----------------------//
float Car_Location[locate_sz][2]={//����ԭʼ����
        10,15,
        1,1,
        9,8,
        2,3,
        13,20,
        3,6,
        10,10
};

float Car_Location_Route[locate_sz][2]={0,0};//��ž���·���滮�㷨֮�����������

/*
 ***************************************************************
*	�� �� ��: Location_Route
*   ����˵��: ·���滮
*	��    ��: ��
*	�� �� ֵ: ��
 ***************************************************************
 */

double dis(int aNum){
    double tmpDis;
    tmpDis= sqrt(pow(Car_Location[aNum][0],2)+ pow(Car_Location[aNum][1],2));
    return tmpDis;
}
int cmpFunc(const void *aa, const void *bb){//�жϺ����������Ǵ�С����
    return (*(struct Route_Dist*)aa).dist>(*(struct Route_Dist*)bb).dist;
}
void location_route(){

    for(int location_count=0;location_count<locate_sz;location_count++){
        Route_D[location_count].dist = dis(location_count);
        Route_D[location_count].num=location_count;
    }

    qsort(Route_D,locate_sz, sizeof(Route_D),cmpFunc);//���� z


    for(int location_count=0;location_count<locate_sz;++location_count) {
        Car_Location_Route[location_count][0] = Car_Location[Route_D[location_count].num][0];
        Car_Location_Route[location_count][1] = Car_Location[Route_D[location_count].num][1];
    }
}


/*
***************************************************************
*	�� �� ��: Charge_Locate
* ����˵��: �����жϵõ���ǰ������,���н�ģʽ��ѭ�����У�
*	��    ��: ��
*	�� �� ֵ: ��������
***************************************************************
*/

void charge_locate(void)
{
    //��ȡ��ǰ����
    if (Car.Position_Pointer == 0){ //λ�����
        Car.x=0;
        Car.y=0;
    }else if(Car.Position_Pointer < locate_sz){
        Car.x=Car_Location_Route[Car.Position_Pointer-1][0];
        Car.y=Car_Location_Route[Car.Position_Pointer-1][1];
    } else if (Car.Position_Pointer==locate_sz){
        Car.x=Car_Location_Route[locate_sz-1][0];
        Car.y=Car_Location_Route[locate_sz-1][1];
    }

/*    Car.x+=Car.MileageX/20;
    Car.y+=Car.MileageY/20;*/
    //�����������Է��������
}

/*
***************************************************************
*	�� �� ��: Get_Target
* ����˵��: ����ṹ����һ������Ԫ�ص�����,ÿ���н�ģʽ֮ǰʹ��
*	��    ��: ����
*	�� �� ֵ: ��
***************************************************************
*/

void get_target(void) {
    //�����µ�Ŀ�������

    if(Car.Position_Pointer<locate_sz){
        Car.x1=Car_Location_Route[Car.Position_Pointer][0];
        Car.y1=Car_Location_Route[Car.Position_Pointer][1];
    }else if(Car.Position_Pointer==locate_sz){
        Car.x1=0;
        Car.y1=0;
    }

}

/*
***************************************************************
*	�� �� ��: Get_Road
* ����˵��: ����·�����ǶȺ����
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************
*/

void get_location(void){
    Car.Position_Pointer++;
    if(Car.Position_Pointer>=locate_sz)
        Car.Position_Pointer=locate_sz;

    charge_locate();
    get_target();
    //������ʽ����ǶȺ;���
    Car.Angel_Target=atan2((Car.x1-Car.x),(Car.y1-Car.y))*180/PI;
    Car.DistanceX=20*(Car.x1-Car.x);
    Car.DistanceY=20*(Car.y1-Car.y);
}

void car_recmode(){
    //����ͼƬλ�øı䳵��λ��
}


void car_omnimove(){
    Car.Angel=(int)eulerAngle.yaw;
    //Car.Speed_X=(int16)(speed_tar * sin(Car.Angel_Target/180 *PI));//((float)speed_tar * sin(Car.Angel_Target/180 *PI)),((float)speed_tar * cos(Car.Angel_Target/180 *PI)),0);
    //Car.Speed_Y=(int16)(speed_tar * cos(Car.Angel_Target/180 *PI));
    Car.Speed_Z=-angel_pid(  Car.Angel,Car.Angel_Target);
    car_omni(0,0,Car.Speed_Z);
    if(abs(Car.MileageX)>abs(Car.DistanceX)&&abs(Car.MileageY)>abs(Car.DistanceY)){
        car_stop();
        rt_mb_send(buzzer_mailbox,1000);
        car_recmode();
        get_location();
        Car.MileageX=0;
        Car.MileageY=0;
    }
}


/*
#include "road.h"
#include "math.h"

#define PI 3.14159265358

rt_uint8_t ture_points_num = 0;

int points_map[22][2] = {0};//���㵽�������λ��
int true_map[22][2] = {0};//ת����������λ��
int points_label[22] = {0};//·������
double turn_angle[22] = {0};//ת��Ƕ�
double map_gap[22] = {0};//�ó�

void find_road(int in_map[][2], int *out_label) {
    double points_gap[21] = {0}; //���ڴ�ŵ㵽��֮��ľ���
    int point_now = 0;           //��ǰָ���
    int pts_label[21] = {0};     //·������
    int road_best = 0;           //�ֲ����ŵ��

    for (int i = 0; i <= ture_points_num; ++i) {
        for (int j = 0; j <= ture_points_num; ++j) {
            points_gap[j] = sqrt(pow((in_map[point_now][0] - in_map[j][0]), now][1] - in_map[j][1]), 2)); //�������
        }
        for (int j = 0; j <= ture_points_num; ++j) {
            unsigned char tag = 0;
            if (road_best == point_now && j != point_now) {
                for (int k = 0; k < i; ++k)
                    if (pts_label[k] == j) tag = 1;
                if (!tag) road_best = j;
            }
            else if (points_gap[j] < points_gap[road_best] && j != point_now) {
                for (int k = 0; k < i; ++k)
                    if (pts_label[k] == j) tag = 1;
                if (!tag) road_best = j;
            }
        }
        point_now = road_best;
        pts_label[i + 1] = road_best;
    }

    rt_memcpy(out_label, pts_label, (ture_points_num+1)*sizeof(int *));//��·����������ָ��
}

//ת������
void map_change(int input[][2], int output[][2], int pts_nums, int *pts_label, int yr, int xb) {
    for (int i = 0; i <= pts_nums; ++i) {
        output[i][0] = input[pts_label[i]][0];
        output[i][1] = input[pts_label[i]][1];
    }//��������

    for (int i = 0; i <= pts_nums; ++i) {
        output[i][0] = abs(output[i][0] - yr);
        output[i][1] = abs(output[i][1] - xb);
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