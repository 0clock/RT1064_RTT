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

//-----------------------��-----------------------//
//-------------------�ṹ��-----------------------//
struct Location_Goal Car={0};          //С��״̬��λ�ã�Ŀ�꣩�洢�ṹ��
//---------------------����-----------------------//
float location_X[locate_sz]={5,5,0,10,0};
float location_Y[locate_sz]={5,0,5,10,0};
int CarMode;

/*
 * name:·���滮
 */


void Car_Move(){
    if((int)Car.Angel==(int)Car.Angel_Target && (int)Car.Distance==(int)Car.mileage){
        Car_Stop();
        Get_Location();
        Car.mileage=0;
        Beep_flag=1;
    }
    if(Car.Angel!=(int)Car.Angel_Target){
        if(0<Car.Angel_Target-Car.Angel){
            Car_Turnround();
            CarMode=anticlockwise;
        }else{
            Car_Anticlockwise();
            CarMode=turnround;
        }
      }else if(Car.mileage!=Car.Distance){
        Car_Ahead();
        CarMode=ahead;
    }else{
        Car_Stop();
        CarMode=stop;
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
    Car.Angel_Target=atan2((Car.y1-Car.y),(Car.x1-Car.x))*180/PI;
    Car.Distance=20*sqrt((Car.x-Car.x1)*(Car.x-Car.x1)+(Car.y-Car.y1)*(Car.y-Car.y1));
}


