#include "motor.h"

#define DIR_1 D14
#define DIR_2 D0
#define DIR_3 D1
#define DIR_4 D15
#define PWM_1 PWM1_MODULE0_CHA_D12
#define PWM_2 PWM2_MODULE3_CHA_D2
#define PWM_3 PWM2_MODULE3_CHB_D3
#define PWM_4 PWM1_MODULE0_CHB_D13

void motor_init(void)
{
    gpio_init(DIR_1, GPO, 0, GPIO_PIN_CONFIG); 		//��Ƭ���˿�D0 ��ʼ��DIR_1			GPIO
    gpio_init(DIR_2, GPO, 0, GPIO_PIN_CONFIG); 		//��Ƭ���˿�D1 ��ʼ��DIR_2			GPIO
    pwm_init(PWM_1, 17000, 0);      							//��Ƭ���˿�D2 ��ʼ��PWM_1����10K ռ�ձ�0
    pwm_init(PWM_2, 17000, 0);     								//��Ƭ���˿�D3 ��ʼ��PWM_2����10K ռ�ձ�0
    gpio_init(DIR_3, GPO, 0, GPIO_PIN_CONFIG);     //��Ƭ���˿�D0 ��ʼ��DIR_1          GPIO
    gpio_init(DIR_4, GPO, 0, GPIO_PIN_CONFIG);     //��Ƭ���˿�D1 ��ʼ��DIR_2          GPIO
    pwm_init(PWM_3, 17000, 0);                     //��Ƭ���˿�D2 ��ʼ��PWM_1����10K ռ�ձ�0
    pwm_init(PWM_4, 17000, 0);                     //��Ƭ���˿�D3 ��ʼ��PWM_2����10K ռ�ձ�0											// PWM ͨ��4 ��ʼ��Ƶ��10KHz ռ�ձȳ�ʼΪ0
}

void motor_pid(int16 expect_speed)
{
    
}


void motor_control(int32 duty_l, int32 duty_r)
{
    //��ռ�ձ��޷�
	duty_l = limit(duty_l, PWM_DUTY_MAX);
	duty_r = limit(duty_r, PWM_DUTY_MAX);
    
    if(duty_l >= 0)											// �����ת
    {
        gpio_set(DIR_L, GPIO_HIGH);							// DIR����ߵ�ƽ
        pwm_duty(PWM_L, duty_l);						    // ����ռ�ձ�
    }
    else													// ��෴ת
    {
        gpio_set(DIR_L, GPIO_LOW);							// DIR����͵�ƽ
        pwm_duty(PWM_L, -duty_l);							// ����ռ�ձ�
    }
    
    if(duty_r >= 0)											// �Ҳ���ת
    {
        gpio_set(DIR_R, GPIO_HIGH);							// DIR����ߵ�ƽ
        pwm_duty(PWM_R, duty_r);							// ����ռ�ձ�
    }
    else													// �Ҳ෴ת
    {
        gpio_set(DIR_R, GPIO_LOW);							// DIR����͵�ƽ
        pwm_duty(PWM_R, -duty_r);							// ����ռ�ձ�
    }
}