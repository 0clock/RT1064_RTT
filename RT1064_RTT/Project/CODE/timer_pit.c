#include "encoder.h"
#include "motor.h"
#include "timer_pit.h"
#include "elec.h"
#include "MahonyAHRS.h"
#include "attitude_solution.h"
#include "location.h"
#include "imgproc.h"
#include "flash_param.h"
#include "carmove.h"


void Find_Edge_1(void);

extern image_t img_raw;
extern image_t img_thres;
extern image_t img_line;

void timer1_pit_entry(void *parameter)
{
    static uint32 time;
    time++;

    //�ɼ����������� 
    //Mahony_computeAngles();
    ICM_getEulerianAngles();


    //��ȡ��������ֵ
    encoder_get();


    Car.Speed_Z=-angel_pid(  eulerAngle.yaw,-0);//omnimoveģʽ��Ŀ�귽��һֱΪ0
    car_omni(Car.Speed_X,Car.Speed_Y,Car.Speed_Z);

    //���Ƶ��ת��
    motor_control(true);
}


void timer_pit_init(void)
{
    rt_timer_t timer;
    
    //����һ����ʱ�� ��������
    timer = rt_timer_create("timer1", timer1_pit_entry, RT_NULL, 1, RT_TIMER_FLAG_PERIODIC);

    //������ʱ��
    if(RT_NULL != timer)
    {
        rt_timer_start(timer);
    }
}