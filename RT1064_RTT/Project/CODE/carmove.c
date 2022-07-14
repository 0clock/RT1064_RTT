//
// Created by Jay on 2022/7/11.
//
#include "carmove.h"
#include "location.h"
#include "motor.h"
#include "buzzer.h"
#include "attitude_solution.h"
#include "smotor.h"
extern const float PI;
int nextpoint=0;

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
    Car.x=Car.x1;
    Car.y=Car.y1;
//    //��ȡ��ǰ����
//    if (Car.Position_Pointer == 0){ //λ�����1
//        Car.x=0;
//        Car.y=0;
//    }else if(Car.Position_Pointer < locate_sz){
//        Car.x=Car_Location_Route[Car.Position_Pointer-1][0];
//        Car.y=Car_Location_Route[Car.Position_Pointer-1][1];
//    } else if (Car.Position_Pointer==locate_sz){
//        Car.x=Car_Location_Route[locate_sz-1][0];
//        Car.y=Car_Location_Route[locate_sz-1][1];
//    }

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

void get_target() {
    //�����µ�Ŀ�������
    nextpoint=locate_route();
    Car.x1=originMap[nextpoint][0];
    Car.y1=originMap[nextpoint][1];
    if(Car.Position_Pointer>=locate_sz){
        Car.x1=0;
        Car.y1=0;
    }
//    if(Car.Position_Pointer<locate_sz){
//        Car.x1=Car_Location_Route[Car.Position_Pointer][0];
//        Car.y1=Car_Location_Route[Car.Position_Pointer][1];
//    }else if(Car.Position_Pointer==locate_sz){
//        Car.x1=0;
//        Car.y1=0;
//    }

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
    charge_locate();
    get_target();
    //������ʽ����ǶȺ;���
    Car.Angel_Target=atan2((Car.x1-Car.x),(Car.y1-Car.y))*180/PI;
    Car.DistanceX=20*(Car.x1-Car.x);
    Car.DistanceY=20*(Car.y1-Car.y);
}

void omni_banyun(){
    //��ͷ��ǰ��ͼƬ���˵�ָ��λ��

    //����Ҫ�ı�Car.x,Car.y
}

void car_recmode(){
    //����ͼƬλ�øı䳵��λ��,��������ͨ���������ʶ��λ�õģ�������̫���ˣ�Ŀǰ���뷨��ͨ��openart��ʶ��ͼƬ�ù����ڷ���λ���ٽ���λ��
    rt_thread_delay(2500);
    grab_picture();//�ȴ�ʶ����ɺ�������ȡͼƬ
    //rt_thread_delay(2500);
    rt_mb_send(buzzer_mailbox,233);
    //omni_banyun();//��ȡ��ɺ����ͼƬ��ָ��λ��
}


void car_omnimove(){
    bool x_flag,y_flag;
    Car.Angel=eulerAngle.yaw;
    if(abs(Car.MileageX)<abs(Car.DistanceX)){
        Car.Speed_X=(int16)(speed_tar * sin(Car.Angel_Target/180 *PI));//((float)speed_tar * sin(Car.Angel_Target/180 *PI)),((float)speed_tar * cos(Car.Angel_Target/180 *PI)),0);
        x_flag=false;
    }else{
        Car.Speed_X=0;
        x_flag=true;
    }
    if(abs(Car.MileageY)<abs(Car.DistanceY)){
        Car.Speed_Y=(int16)(speed_tar * cos(Car.Angel_Target/180 *PI));
        y_flag=false;
    }else{
        Car.Speed_Y=0;
        y_flag=true;
    }
    //Car.Speed_Z=-angel_pid(  Car.Angel,-Car.Angel_Target);//�ٶȻ�

    if(x_flag && y_flag){
        car_stop();
        car_recmode();
        //rt_mb_send(buzzer_mailbox,1000);
        x_flag=false;
        y_flag=false;

        get_location();
        Car.MileageX=0;
        Car.MileageY=0;
        Car.Position_Pointer++;
    }
}




