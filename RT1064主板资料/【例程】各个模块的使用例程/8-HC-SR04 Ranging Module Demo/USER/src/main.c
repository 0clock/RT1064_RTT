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
					HC-SR04				��Ƭ��
					TRIG				�鿴main.c�ļ��е�TRIG_PIN�궨��
					ECHO				�鿴main.c�ļ��е�ECHO_PIN�궨��
					------------------------------------
 ********************************************************************************************************************/


//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�



//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������



#include "headfile.h"

#define TRIG_PIN B9                //���峬�����������Ŷ˿�
#define ECHO_PIN B10               //���峬�����������Ŷ˿�

long wait_time = 0;                //��ʱ������
uint32 distance_time = 0;          //����ʱ�����
uint32 distance = 0;               //ת�������ľ���  ��λΪ����

int main(void)
{
    
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
	systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�
	
	
    //��ʼ��IO�˿�Ϊ���ģʽ������
    gpio_init(TRIG_PIN, GPO, 0, GPIO_PIN_CONFIG);

    //��ʼ��IO�˿�Ϊ���ģʽ������
    gpio_init(ECHO_PIN, GPI, 0, GPIO_PIN_CONFIG);
	
    //ʹ��pit �����ȳ�ʼ�� Ȼ���ڵ���pit��������ʹ�ö�Ӧ�Ĺ���
    pit_init();
    
    EnableGlobalIRQ(0);

    for(;;)
	{
        gpio_set(TRIG_PIN,1);                           //������������ߵ�ƽ
        systick_delay_us(10);                           //��ʱ10us    
        gpio_set(TRIG_PIN,0);
        
        while(!gpio_get(ECHO_PIN));                     //��⵽��������Ϊ�ߵ�ƽ��ʼ��ʱ
        pit_start(PIT_CH0);
        wait_time = 0;
        while(gpio_get(ECHO_PIN))                       //��⵽��������Ϊ�͵�ƽ�������ʱ
        {
            wait_time++;                                //��ʱ���
            systick_delay(5);
            if(wait_time>200000) break;                 //�����ȴ�ʱ��
        }
        if(wait_time<200000) distance_time = pit_get_us(PIT_CH0); //��ȡ��ʱ��ʱ��
        else                  distance_time = 200000;
        pit_close(PIT_CH0);                             //�رն�ʱ���������ʱ
        
        
        distance = distance_time*340/2/1000;            //�������  ��λ����
		
		//ͨ�����ߵ���ʱ Live Watch��IAR���� Watch��MDK�����ܣ��鿴 distance ����ֵ���ɡ�
		//ʹ�÷������Ҽ������������ distance ��Add to Live Watch(IAR) �� add��distance'to...->watch1(MDK),������watch���ڿ�������ʵʱֵ��
		
        systick_delay_ms(10);
        
	}

    
}





