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
 ********************************************************************************************************************/


//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�



//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������



#include "SEEKFREE_FONT.h"
#include "headfile.h"

//����ADCͨ�������ţ��䶨����zf_adc.h�ļ���

#define POWER_ADC1_MOD  ADC_1       //����ͨ��һ ADCģ���
#define POWER_ADC1_PIN  ADC1_CH3_B14//����ͨ��һ ADC����
                                                     
#define POWER_ADC2_MOD  ADC_1       //����ͨ���� ADCģ���
#define POWER_ADC2_PIN  ADC1_CH4_B15//����ͨ���� ADC����

#define POWER_ADC3_MOD  ADC_1       //����ͨ���� ADCģ���
#define POWER_ADC3_PIN  ADC1_CH10_B21//����ͨ���� ADC����

#define POWER_ADC4_MOD  ADC_1       //����ͨ���� ADCģ���
#define POWER_ADC4_PIN  ADC1_CH12_B23//����ͨ���� ADC����




uint16  ad_value1;
uint16  ad_value2;
uint16  ad_value3;
uint16  ad_value4;


int main(void)
{
    
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
	systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�
	
	
    
    adc_init(POWER_ADC1_MOD,POWER_ADC1_PIN,ADC_8BIT);  //ͬһ��ADCģ��ֱ���Ӧ������Ϊһ���ģ�������ò�һ���������һ����ʼ��ʱ���õķֱ�����Ч
    adc_init(POWER_ADC2_MOD,POWER_ADC2_PIN,ADC_8BIT);
    adc_init(POWER_ADC3_MOD,POWER_ADC3_PIN,ADC_8BIT);
    adc_init(POWER_ADC4_MOD,POWER_ADC4_PIN,ADC_8BIT);
	
    
    EnableGlobalIRQ(0);
	
    while(1)
    {
        //�ɼ�ADC����
        ad_value1 = adc_mean_filter(POWER_ADC1_MOD,POWER_ADC1_PIN,10);
        ad_value2 = adc_mean_filter(POWER_ADC2_MOD,POWER_ADC2_PIN,10);
        ad_value3 = adc_mean_filter(POWER_ADC3_MOD,POWER_ADC3_PIN,10);
        ad_value4 = adc_mean_filter(POWER_ADC4_MOD,POWER_ADC4_PIN,10);
		
        //ͨ�����ߵ���ʱ Live Watch��IAR���� Watch��MDK�����ܣ��鿴ad_value1 ad_value2 ad_value3 ad_value4����ֵ���ɡ�
		//ʹ�÷������Ҽ������������ad_value1��Add to Live Watch(IAR) �� add��ad_value1'to...->watch1(MDK),������watch���ڿ�������ʵʱֵ��
		
		//���������ʣ�ΪɶADC������������ֵ�أ���Ӧ����0��
		//�ҵĻش��ǵģ����յ�ʱ������ֵ��������ֻ�����𰸣�����Ϊʲô����Լ��о�ADC�Ľṹ�������ס�
		
        systick_delay_ms(10);
    }

    
}





