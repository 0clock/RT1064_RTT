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
					ģ��					��Ƭ��
					MOTOR1_A			    �鿴zf_pwn.h�ļ��е�PWM2_MODULE3_CHA_D2     �궨��
					MOTOR1_B			    �鿴zf_pwn.h�ļ��е�PWM1_MODULE3_CHA_D0     �궨��      
					MOTOR2_A			    �鿴zf_pwn.h�ļ��е�PWM1_MODULE3_CHB_D1     �궨��
                    MOTOR2_B                �鿴zf_pwn.h�ļ��е�PWM2_MODULE3_CHB_D3     �궨��              
                    MOTOR3_A                �鿴zf_pwn.h�ļ��е�PWM1_MODULE0_CHA_D12    �궨��   
                    MOTOR3_B                �鿴zf_pwn.h�ļ��е�PWM1_MODULE1_CHA_D14    �궨��  
                    MOTOR4_A                �鿴zf_pwn.h�ļ��е�PWM1_MODULE0_CHB_D13    �궨��
                    MOTOR4_B                �鿴zf_pwn.h�ļ��е�PWM1_MODULE1_CHB_D15    �궨��                          
					------------------------------------      
 ********************************************************************************************************************/


//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�



//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������



#include "headfile.h"

#define MOTOR1_A   PWM2_MODULE3_CHA_D2   //����1�����תPWM����
#define MOTOR1_B   PWM1_MODULE3_CHA_D0   //����1�����תPWM����
                        
#define MOTOR2_A   PWM1_MODULE3_CHB_D1   //����2�����תPWM����
#define MOTOR2_B   PWM2_MODULE3_CHB_D3   //����2�����תPWM����
    
#define MOTOR3_A   PWM1_MODULE0_CHA_D12  //����3�����תPWM����
#define MOTOR3_B   PWM1_MODULE1_CHA_D14  //����3�����תPWM����
    
#define MOTOR4_A   PWM1_MODULE0_CHB_D13  //����4�����תPWM����
#define MOTOR4_B   PWM1_MODULE1_CHB_D15  //����4�����תPWM����

int32 speed1_power;
int32 speed2_power;
int32 speed3_power;
int32 speed4_power;
int main(void)
{
    
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
	systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�
	
	
    //��ʼ�����PWM����
    
    //�����������У�����������Ƶ��ѡ��13K-17K
    //���ռ�ձ�ֵPWM_DUTY_MAX ������fsl_pwm.h�ļ����޸� Ĭ��Ϊ50000
    //����һ��PWMģ�� ����������ͨ��ֻ�����Ƶ��һ�� ռ�ձȲ�һ���� PWM RT1021ֻ������PWMģ�� ÿ��ģ����8��ͨ��
	pwm_init(MOTOR1_A,17000,0);
    pwm_init(MOTOR1_B,17000,0);
    pwm_init(MOTOR2_A,17000,0);
    pwm_init(MOTOR2_B,17000,0);
    pwm_init(MOTOR3_A,17000,0);
    pwm_init(MOTOR3_B,17000,0);
    pwm_init(MOTOR4_A,17000,0);
    pwm_init(MOTOR4_B,17000,0);
    
    EnableGlobalIRQ(0);

    
    //����һ��8��ͨ�����ֱ����4�����������ת
    //������Ҫע�⣬��Ƭ�����޷�ֱ����������ģ���Ƭ��ֻ�ܸ��������źţ��������źŸ�����ģ�飬����ģ�������ѹʹ�õ��ת��
    //�ɲ鿴���ǵ���MOS������ģ��
    

    //����Ĭ���ٶ�  Ҳ����ͨ�����ߵ���ֱ���޸Ĵ�ֵ  �仯����ٶ�
    speed1_power = 5000;
    speed2_power = 5000;
    speed3_power = 5000;
    speed4_power = 5000;
    
    while(1)
    {
        //��ο��Ƶ��������ת
        //ÿ������������������źţ���ʵ���ǿ��������������źŵ�ռ�ձȣ����ߵ�ƽʱ�䣩
        //���籾������ʹ�ö�ʱ��1��0��1ͨ����������������0ռ�ձ�Ϊ50%��1ͨ��Ϊ%0,��ô�����ת
        //����0ռ�ձ�Ϊ0%��1ͨ��Ϊ%50,��ô�����ת�������Ϊ0������ֹͣ
        
        if(0<=speed1_power) //���1   ��ת ����ռ�ձ�Ϊ �ٷ�֮ (1000/TIMER1_PWM_DUTY_MAX*100)
        {
            pwm_duty(MOTOR1_A, speed1_power);
            pwm_duty(MOTOR1_B, 0);
        }
        else                //���1   ��ת
        {
            pwm_duty(MOTOR1_A, 0);
            pwm_duty(MOTOR1_B, -speed1_power);
        }
        
        if(0<=speed2_power) //���2   ��ת
        {
            pwm_duty(MOTOR2_A, speed2_power);
            pwm_duty(MOTOR2_B, 0);
        }
        else                //���2   ��ת
        {
            pwm_duty(MOTOR2_A, 0);
            pwm_duty(MOTOR2_B, -speed2_power);
        }
        
        if(0<=speed3_power) //���3   ��ת
        {
            pwm_duty(MOTOR3_A, speed3_power);
            pwm_duty(MOTOR3_B, 0);
        }
        else                //���3   ��ת
        {
            pwm_duty(MOTOR3_A, 0);
            pwm_duty(MOTOR3_B, -speed3_power);
        }
        
        if(0<=speed4_power) //���3   ��ת
        {
            pwm_duty(MOTOR4_A, speed4_power);
            pwm_duty(MOTOR4_B, 0);
        }
        else                //���3   ��ת
        {
            pwm_duty(MOTOR4_A, 0);
            pwm_duty(MOTOR4_B, -speed4_power);
        }
        
    }

    
}





