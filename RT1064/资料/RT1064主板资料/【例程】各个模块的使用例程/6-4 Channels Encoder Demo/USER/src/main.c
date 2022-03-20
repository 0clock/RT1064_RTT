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


							// ������ �ؿ� ��������
							// ������ �ؿ� ��������
							// ������ �ؿ� ��������
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//
// ��ע�ⱾRT1064���� ������4 �������2 �������� 2.0��IPS��Ļ�������š�
// ��ʹ�ñ�����ʱ��ȡ��2.0��IPS����������ֳ�ͻ��
//
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************



#include "headfile.h"

int16 encoder1;
int16 encoder2;
int16 encoder3;
int16 encoder4;

int main(void)
{
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
	
	systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�
	
	
    //һ��QTIMER���� ���������������룬�䶨����zf_qtimer.h�ļ���
    //������Ҫע��һ�£�����Ǵ���������ı���������������LSB����Ӧ����A������ DIR����Ӧ����B������ ���ɽ���
    
    //��ʼ�� QTIMER_1 A��ʹ��QTIMER1_TIMER0_C0 B��ʹ��QTIMER1_TIMER1_C1
    qtimer_quad_init(QTIMER_1,QTIMER1_TIMER0_C0,QTIMER1_TIMER1_C1);
    
    //��ʼ�� QTIMER_1 A��ʹ��QTIMER1_TIMER2_C2 B��ʹ��QTIMER1_TIMER3_C24
    qtimer_quad_init(QTIMER_1,QTIMER1_TIMER2_C2,QTIMER1_TIMER3_C24);
    
    qtimer_quad_init(QTIMER_2,QTIMER2_TIMER0_C3,QTIMER2_TIMER3_C25);
    qtimer_quad_init(QTIMER_3,QTIMER3_TIMER2_B18,QTIMER3_TIMER3_B19);
    
    
    //���ֱ�����ӱ�������A B�࣬��ô�����ֱ�Ӳɼ�����������
    
    EnableGlobalIRQ(0);    
    
    while(1)
    {
        //��ȡ����������ֵ
		encoder1 = qtimer_quad_get(QTIMER_1,QTIMER1_TIMER0_C0 ); //������Ҫע��ڶ������������дA������
		encoder2 = qtimer_quad_get(QTIMER_1,QTIMER1_TIMER2_C2 );
		encoder3 = qtimer_quad_get(QTIMER_2,QTIMER2_TIMER0_C3 );
        encoder4 = qtimer_quad_get(QTIMER_3,QTIMER3_TIMER2_B18);
		
		//ͨ�����ߵ���ʱ Live Watch��IAR���� Watch��MDK�����ܣ��鿴 encoder1 encoder2 encoder3 encoder4 ����ֵ���ɡ�
		//ʹ�÷������Ҽ������������ encoder1��Add to Live Watch(IAR) �� add��encoder1'to...->watch1(MDK),������watch���ڿ�������ʵʱֵ��
            
        qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER0_C0 );
        qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER2_C2 );
        qtimer_quad_clear(QTIMER_2,QTIMER2_TIMER0_C3 );
        qtimer_quad_clear(QTIMER_3,QTIMER3_TIMER2_B18);		
    
        systick_delay_ms(100);
        //�������������ʾ�ɼ�Ч���Լ����Ա����������Ƿ�������ʵ��ʹ��һ���ǽ��������Ĳɼ������PIT�ж�  ����һ������Ϊ5ms
        
    }
}





