//
// Created by Jay on 2022/4/7.
//
/***************************************************
*
* @file         location.c
* @brief        ���������ݴ����ļ�
* @version      v1.0
* @date         2022/3/14
***************************************************/
#include "location.h"
#include <string.h>
//-----------------------��-----------------------//
//-------------------�ṹ��-----------------------//
struct Location_Goal Car={0};          //С��״̬��λ�ã�Ŀ�꣩�洢�ṹ��
//---------------------����-----------------------//
float location_X[locate_sz]={0,5,10,10};
float location_Y[locate_sz]={0,5,5,10};
int CarMode;

void Car_Move(){
    if(Car.Angel==Car.Angel_Target||Car.Distance==Car.mileage){
        Car_Stop();
    }
    if(Car.Angel!=Car.Angel_Target){
        if(0<Car.Angel_Target-Car.Angel){
            Car_Anticlockwise();
        }else{
            Car_Turnround();
        }
      }else if(Car.mileage!=Car.Distance){
        Car_Ahead();
    }else{
        Car_Stop();
    }
}


void Car_Mode(){
    switch (CarMode) {
        case ahead:Car_Ahead();break;
        case forward:Car_Back();break;
        case turnround:Car_Turnround();break;
        case anticlockwise:Car_Anticlockwise();break;
        case stop:Car_Stop();break;
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

void Charge_Locate(void)
{
    //��ȡ��ǰ����
    Car.x+=Car.mileage*sin(Car.Angel);
    Car.y+=Car.mileage*sin(Car.Angel);
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

void Get_Target(void)
{
    //�����µ�Ŀ�������
    Car.x1=location_X[Car.Position_Pointer];
    Car.y1=location_Y[Car.Position_Pointer];
    //��һ��Ŀ���
    Car.Position_Pointer++;
}
 
/*
***************************************************************
*	�� �� ��: Get_Road
* ����˵��: ����·�����ǶȺ����
*	��    ��: ��
*	�� �� ֵ: ��
***************************************************************
*/

void Get_Location(void)
{
    Get_Target();
    //������ʽ����ǶȺ;���
    Car.Angel_Target=tan((Car.x1-Car.x)/(Car.y1-Car.y));
    Car.Distance=20*sqrt((Car.x-Car.x1)*(Car.x-Car.x1)+(Car.y-Car.y1)*(Car.y-Car.y1));
}


