//
// Created by Jay on 2022/4/7.
//

#ifndef _LOCATION_H_
#define _LOCATION_H_


#include "headfile.h"
#include <stdlib.h>
#include <math.h>


//-----------------------��-----------------------//
#define locate_sz 7             //������������,���ܻ���Ҫ���ģ�Ŀ�������ȷ����(5-20���п���)
//---------------------����-----------------------//
extern int Car_Location[locate_sz][2];
extern int Car_Location_Route[locate_sz][2];
//--------------------ȫ�ֱ���---------------------//
extern struct Location_Goal Car;
extern int CarMode;
extern int key1number;

enum CarMode
{
    ahead,
    forward,
    turnround,
    anticlockwise,
    stop
};
//---------------------�ṹ��---------------------//

typedef struct Route_Dist{//����ṹ��
    int num;//���
    double dist;//����
}Route_Dist;


//��¼��������λ�õĽṹ��
typedef struct Location_Goal
{
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
    int x1;
    int y1;
    //��ǰ��̬
    float Angel;
    //Ŀ����̬
    float Angel_Target;
    //Ŀ�����
    int DistanceX;
    int DistanceY;
    //���ϴ�ת��֮��ǰ���ľ���(��̣�
    float MileageX;
    float MileageY;
    //ģʽ��־λ:1->�н�ģʽ||0->ʶ��ģʽ
    int8_t Mode_Flag;
}Location_Goal;


//-------------------��������---------------------//
void Location_Route(void);           //·���滮����
void Charge_Locate(void);            //���괦����
void Car_Mode(void);
void Car_Return();
void Car_OmniMove(void);
void Car_Move(void);
void Get_Road(void);                 //·�����ֺ���
void Get_Location(void);

#endif 
