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
int key1number=0;
//-----------------------��-----------------------//
//-------------------�ṹ��-----------------------//
struct Location_Goal Car={0};          //С��״̬��λ�ã�Ŀ�꣩�洢�ṹ��
struct Route_Dist Route_D[5];
//---------------------����-----------------------//
int Car_Location[locate_sz][2]={//����ԭʼ����
        10,15,
    1,1,
    9,8,
    2,3,
    13,20,
    3,6,
    0,0,
    -10,-10,
    0,0
};

int Car_Location_Route[locate_sz][2]={};//��ž���·���滮�㷨֮�����������
int CarMode;

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

double dis(int aNum){
    double tmpDis= sqrt(pow(Car_Location[aNum][0],2)+ pow(Car_Location[aNum][1],2));
    return tmpDis;
}

void Location_Route(){
    for(int i=0;i<locate_sz;++i){
        Route_D[i].dist= dis(i);
        Route_D[i].num=i;
       }
    qsort(Route_D,locate_sz, sizeof(struct Route_Dist),cmpFunc);//����
    //printf("--˳���λ--\n");
    for(int i=0;i<locate_sz;++i) {
        //printf("(%d,%d)\n",Car_Location[Route_D[i].num][0],Car_Location[Route_D[i].num][1]);//����������a(x,y), x=a[D[i].num][0] y=a[D[i].num][1]
        Car_Location_Route[i][0] = Car_Location[Route_D[i].num][0];
        Car_Location_Route[i][1] = Car_Location[Route_D[i].num][1];
    }
}
/*
 * ʶ��ģʽ
 */
void Car_RecMode(){
    while(key1number);
}


void Car_OmniMove(){
    Car_SpeedGet();
    Car_Omni(Car.Speed_X,Car.Speed_Y,Car.Speed_Z);
    if(abs(Car.MileageX)>=abs(Car.DistanceX)&&abs(Car.MileageY)>=abs(Car.DistanceY)||(Car.x1==-10&&Car.y1==-10)){
        Car_Stop();
        Car_RecMode();
        Get_Location();
        Car.MileageX=0;
        Car.MileageY=0;
        Beep_flag=1;
    }
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
    Car.x+=Car.MileageX/20;
    Car.y+=Car.MileageY/20;
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
    if (Car.Position_Pointer == 0){
        Car.x=0;
        Car.y=0;
    }else{
        Car.x=Car_Location[Car.Position_Pointer-1][0];
        Car.y=Car_Location[Car.Position_Pointer-1][1];
    }


    Car.x1=Car_Location[Car.Position_Pointer][0];
    Car.y1=Car_Location[Car.Position_Pointer][1];
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
    Car.Angel_Target=atan2((Car.x1-Car.x),(Car.y1-Car.y))*180/PI;
    Car.DistanceX=20*(Car.x1-Car.x);
    Car.DistanceY=20*(Car.y1-Car.y);
}


