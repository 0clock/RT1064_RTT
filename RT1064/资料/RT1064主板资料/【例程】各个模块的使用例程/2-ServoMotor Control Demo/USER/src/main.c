/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.24
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 * @note
					���߶��壺
					------------------------------------ 
					���         ��Ƭ��
					PWM			 �鿴main.c�ļ��е�PWM4_MODULE2_CHA_C30�궨��
					------------------------------------ 
 ********************************************************************************************************************/


//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�



//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������



#include "SEEKFREE_FONT.h"
#include "headfile.h"

#define S_MOTOR1_PIN   PWM4_MODULE2_CHA_C30       //����������
#define S_MOTOR2_PIN   PWM1_MODULE0_CHA_D12       //����������
#define S_MOTOR3_PIN   PWM1_MODULE0_CHB_D13       //����������


uint16 duty;
int main(void)
{
    
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
	
	systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�
	
	
    //�������   1.5ms/20ms * PWM_DUTY_MAX��PWM_DUTY_MAX��PWM����ռ�ձ�ʱ���ֵ�� PWM_DUTY_MAX��fsl_pwm.h�ļ��� Ĭ��Ϊ50000
    duty = 1.5*50000/20;
    
    pwm_init(S_MOTOR1_PIN,50,duty);
    pwm_init(S_MOTOR2_PIN,50,duty);
    pwm_init(S_MOTOR3_PIN,50,duty);
    //�ر���ʾ����Ķ����������û�а�װ�ڳ�ģ�ϵ�ʱ�򣬲���ʹ��������з�ʽ��
    //�������Ѿ���װ�ڳ�ģ�ϣ�����ʹ�ñ�������Ϊ������ڻ�е��λ�����¿ɻ��ΧС�ܶࡣ
	
    EnableGlobalIRQ(0);

    while(1)
    {
        //������λ�ö��λ��   ��0.5ms - 2.5ms��ms/20ms * 50000��50000��PWM����ռ�ձ�ʱ���ֵ��
        //�����СֵΪ1250   ���ֵΪ6250
        //�����һ�� ��һ����Ϊ����Сת�������򣬲�Ҫת�����ڼ���λ�ã��еĶ���ڼ���λ�����׿�ס
        duty += 10;
        if((6250-100) < duty) duty = (1250+100);
        
        //���ƶ���ﵽָ��λ��
        pwm_duty(S_MOTOR1_PIN,duty);
        pwm_duty(S_MOTOR2_PIN,duty);
        pwm_duty(S_MOTOR3_PIN,duty);
        
        if((1250+100) >= duty)  systick_delay_ms(1000); //����6250��λ��   ��ת��1250��λ��ʱ   Ӧ��ʹ�ýϳ�����ʱ�ȵ�����ﵽָ��λ��
        else                    systick_delay_ms(3);    //
    }

    
}





