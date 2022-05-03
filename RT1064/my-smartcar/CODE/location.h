//
// Created by Jay on 2022/4/7.
//

#ifndef _LOCATION_H_
#define _LOCATION_H_


#include "headfile.h"
#include <stdlib.h>
#include <math.h>


//-----------------------��-----------------------//
#define locate_sz 10             //������������,���ܻ���Ҫ���ģ�Ŀ�������ȷ����(5-20���п���)
//---------------------����-----------------------//
extern float location_X[locate_sz];    //x�����Ŵ�
extern float location_Y[locate_sz];    //y�����Ŵ�
//--------------------ȫ�ֱ���---------------------//
extern struct Location_Goal Car;
extern int CarMode;

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
    float Distance;
    //���ϴ�ת��֮��ǰ���ľ���(��̣�
    float mileage;
    //ģʽ��־λ:1->�н�ģʽ||0->ʶ��ģʽ
    int8_t Mode_Flag;
}Location_Goal;


//-------------------��������---------------------//
void Location_Route(void);           //·���滮����
void Charge_Locate(void);            //���괦����
void Car_Mode(void);
void Car_OmniMove(void);
void Car_Move(void);
void Get_Road(void);                 //·�����ֺ���
void Get_Location(void);

#endif 
