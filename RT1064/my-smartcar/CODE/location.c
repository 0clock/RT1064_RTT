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

extern int RecModeTest;
//-----------------------��-----------------------//
//-------------------�ṹ��-----------------------//
struct Location_Goal Car={0};          //С��״̬��λ�ã�Ŀ�꣩�洢�ṹ��
struct Route_Dist Route_D[5];
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
int cmpFunc(const void *aa, const void *bb){//�жϺ����������Ǵ�С����
    return (*(Route_Dist*)aa).dist>(*(Route_Dist*)bb).dist?1:-1;
}

float dis(int aNum){
    float tmpDis;
		//tmpDis= sqrt(pow(Car_Location[aNum][0],2)+ pow(Car_Location[aNum][1],2));   
    return tmpDis;
}

void Location_Route(){

    for(int location_count=0;location_count<locate_sz;++location_count){
        Route_D[location_count].dist = dis(location_count);
        Route_D[location_count].num=location_count;
    }

    qsort(Route_D,locate_sz, sizeof(struct Route_Dist),cmpFunc);//����


//    for(int location_count=0;location_count<locate_sz;++location_count) {
//        Car_Location_Route[location_count][0] = Car_Location[Route_D[location_count].num][0];
//        Car_Location_Route[location_count][1] = Car_Location[Route_D[location_count].num][1];
//    }
}

/*
 * ʶ��ģʽ
 */
void Car_RecMode(){
    do{
      Beep_Set(10,2);
			Car_Stop();
		}while(RecModeTest);
    RecModeTest=1;
}

void Car_OmniMove(){
    Car_SpeedGet();
    Car_Omni(Car.Speed_X,Car.Speed_Y,Car.Speed_Z);
    if(abs(Car.MileageX)>abs(Car.DistanceX)&&abs(Car.MileageY)>abs(Car.DistanceY)){
        Car_Stop();
        Car_RecMode();
        Beep_Set(50,1);
        Get_Location();
        Car.MileageX=0;
        Car.MileageY=0;
    }
}

void Car_Return(){

}

/*��ת�����ܣ���ʱ����
void Car_Move(){
    if((int)Car.Angel==(int)Car.Angel_Target-1 && (int)Car.Distance==(int)Car.mileage){
        Car_Stop();
        Get_Location();
        Car.mileage=0;
        Beep_flag=1;
    }
    if(Car.Angel!=(int)Car.Angel_Target){
        if(0<Car.Angel_Target-1-Car.Angel){
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
*/


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

void Get_Target(void) {
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

void Get_Location(void){
    Car.Position_Pointer++;
    if(Car.Position_Pointer>=locate_sz)
        Car.Position_Pointer=locate_sz;

    Charge_Locate();
    Get_Target();
    //������ʽ����ǶȺ;���
    Car.Angel_Target=atan2((Car.x1-Car.x),(Car.y1-Car.y))*180/PI;
    Car.DistanceX=20*(Car.x1-Car.x);
    Car.DistanceY=20*(Car.y1-Car.y);
}


