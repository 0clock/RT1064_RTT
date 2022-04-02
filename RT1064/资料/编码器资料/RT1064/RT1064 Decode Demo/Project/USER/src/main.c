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
 * @date       		2019-10-28
 * @note		    
 					���߶��壺
					------------------------------------ 
					������1 							��Ƭ��
					LSB_A(��������)						QTIMER1_TIMER0_C0
					DIR  (��ת����)��LSB_B(��������)	QTIMER1_TIMER1_C1
						
					������2 							��Ƭ��
					LSB_A(��������)						QTIMER2_TIMER0_C3
					DIR  (��ת����)��LSB_B(��������)	QTIMER2_TIMER3_C25
					------------------------------------ 
 ********************************************************************************************************************/
 


//ͨ�����ߵ���ʱ Live Watch��IAR���� Watch��MDK�����ܣ��鿴 encoder1 encoder2 encoder3 encoder4 ����ֵ���ɡ�
//ʹ�÷������Ҽ������������ encoder1��Add to Live Watch(IAR) �� add��encoder1'to...->watch1(MDK),������watch���ڿ�������ʵʱֵ��

#include "headfile.h"

//������֧�ִ�����ı���������Ҫ��������ı�������


//������Ҫע��һ�£�����Ǵ���������ı���������������LSB����Ӧ����A�����ӣ�DIR����Ӧ����B������ ���ɽ���

int16 encoder1;
int16 encoder2;


int main(void)
{
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
	
	systick_delay_ms(100);	//��ʱ100ms���ȴ��������������ϵ�ɹ�
	
    //һ��QTIMER���� ����������������
    //��ʼ�� QTIMER_1 A��ʹ��QTIMER1_TIMER0_C0 B��ʹ��QTIMER1_TIMER1_C1
    qtimer_quad_init(QTIMER_1,QTIMER1_TIMER0_C0,QTIMER1_TIMER1_C1);
    //��ʼ�� QTIMER_1 A��ʹ��QTIMER2_TIMER0_C3 B��ʹ��QTIMER2_TIMER3_C25
    qtimer_quad_init(QTIMER_2,QTIMER2_TIMER0_C3,QTIMER2_TIMER3_C25);
    
    EnableGlobalIRQ(0);    
    
    while(1)
    {
        //��ȡ����������ֵ
		encoder1 = qtimer_quad_get(QTIMER_1,QTIMER1_TIMER0_C0 ); //������Ҫע��ڶ������������дA������
		encoder2 = qtimer_quad_get(QTIMER_2,QTIMER2_TIMER0_C3 ); //������Ҫע��ڶ������������дA������


            
        qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER0_C0 );
        qtimer_quad_clear(QTIMER_2,QTIMER2_TIMER0_C3 );
	
    
        systick_delay_ms(100);
        //�������������ʾ�ɼ�Ч���Լ����Ա����������Ƿ�������ʵ��ʹ��һ���ǽ��������Ĳɼ������PIT�ж�  ����һ������Ϊ5ms
        
    }
}





