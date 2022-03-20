/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.24
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-01-09
 * @note		
 					���߶��壺
					------------------------------------ 
                    ģ��ܽ�            ��Ƭ���ܽ�
                    1DIR                ��鿴main.c�е�DIR_1�궨��
                    1PWM                ��鿴main.c�е�PWM_1�궨��
					2DIR                ��鿴main.c�е�DIR_2�궨��
                    2PWM                ��鿴main.c�е�PWM_2�궨��
 ********************************************************************************************************************/



//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�



//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������

//���ش���ǰ������Լ�ʹ�õ��������ڹ���������������Ϊ�Լ���ʹ�õ�

#include "headfile.h"

#define DIR_1 D0
#define DIR_2 D1
#define PWM_1 PWM2_MODULE3_CHA_D2
#define PWM_2 PWM2_MODULE3_CHB_D3

#define DIR_3 D14
#define DIR_4 D15
#define PWM_3 PWM1_MODULE0_CHA_D12
#define PWM_4 PWM1_MODULE0_CHB_D13

uint8 dir;
int32 duty;

int main(void)
{
	DisableGlobalIRQ();
    board_init();//��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
	
	//�˴���д�û�����(���磺�����ʼ�������)
	
	gpio_init(DIR_1, GPO, 0, GPIO_PIN_CONFIG); 		//��Ƭ���˿�D0 ��ʼ��DIR_1			GPIO
	gpio_init(DIR_2, GPO, 0, GPIO_PIN_CONFIG); 		//��Ƭ���˿�D1 ��ʼ��DIR_2			GPIO
	pwm_init(PWM_1, 17000, 0);      				//��Ƭ���˿�D2 ��ʼ��PWM_1����10K ռ�ձ�0
	pwm_init(PWM_2, 17000, 0);     					//��Ƭ���˿�D3 ��ʼ��PWM_2����10K ռ�ձ�0
    
    gpio_init(DIR_3, GPO, 0, GPIO_PIN_CONFIG);      //��Ƭ���˿�D0 ��ʼ��DIR_1          GPIO
    gpio_init(DIR_4, GPO, 0, GPIO_PIN_CONFIG);      //��Ƭ���˿�D1 ��ʼ��DIR_2          GPIO
    pwm_init(PWM_3, 17000, 0);                      //��Ƭ���˿�D2 ��ʼ��PWM_1����10K ռ�ձ�0
    pwm_init(PWM_4, 17000, 0);                      //��Ƭ���˿�D3 ��ʼ��PWM_2����10K ռ�ձ�0
	
	
	//���ж������
    EnableGlobalIRQ(0);
    while (1)
    {
		if(dir)
        {
            duty += 10;
            if(50000<=duty)   dir = 0;
        }
        else
        {
            duty -= 10;
            if(-50000>=duty)   dir = 1;
        } 
		
        systick_delay_ms(1);
       
        if(duty>=0) //��ת
        {
			gpio_set(DIR_1,0);
            pwm_duty(PWM_1,duty);
			
			gpio_set(DIR_2,0);
            pwm_duty(PWM_2,duty);

            gpio_set(DIR_3,0);
            pwm_duty(PWM_3,duty);
            
            gpio_set(DIR_4,0);
            pwm_duty(PWM_4,duty);
        }
        else        //��ת
        {
			gpio_set(DIR_1,1);
            pwm_duty(PWM_1,-duty);
			
			gpio_set(DIR_2,1);
            pwm_duty(PWM_2,-duty);

            gpio_set(DIR_3,1);
            pwm_duty(PWM_3,-duty);
            
            gpio_set(DIR_4,1);
            pwm_duty(PWM_4,-duty);
        }
    }
}





