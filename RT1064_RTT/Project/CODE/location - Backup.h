//
// Created by ThinkPad on 2022/6/28.
//

#ifndef _LOCATION_H
#define _LOCATION_H

#include "headfile.h"

//---------------------�ṹ��---------------------//
//��¼��������λ�õĽṹ��
typedef struct location_goal {
    //�ѵ����Ŀ���
    int8_t Position_Pointer;
    //��ǰ�ٶ�
    int Speed_X;
    int Speed_Y;
    int Speed_Z;
    //��ǰλ��
    float x;
    float y;
    //Ŀ��λ��
    float x1;
    float y1;
    //��ǰ��̬
    float Angel;
    //Ŀ����̬
    float Angel_Target;
    //Ŀ�����
    float DistanceX;
    float DistanceY;
    //���ϴ�ת��֮��ǰ���ľ���(��̣�
    float MileageX;
    float MileageY;
    //ģʽ��־λ:1->�н�ģʽ||0->ʶ��ģʽ
    int8_t Mode_Flag;
}location_goal;

extern location_goal Car;

void car_omnimove(void);

void location_route(void);

#endif
