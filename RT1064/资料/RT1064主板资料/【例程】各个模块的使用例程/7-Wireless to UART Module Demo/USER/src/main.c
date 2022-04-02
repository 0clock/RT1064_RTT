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
					����ת����       ��Ƭ��                        
    				RX              �鿴SEEKFREE_WIRELESS.h�ļ��е�WIRELESS_UART_TX�궨��
    				TX              �鿴SEEKFREE_WIRELESS.h�ļ��е�WIRELESS_UART_RX�궨��
    				RTS             �鿴SEEKFREE_WIRELESS.h�ļ��е�RTS_PIN�궨��
    				CMD             �鿴SEEKFREE_WIRELESS.h�ļ��е�CMD_PIN�궨��
					------------------------------------ 
 ********************************************************************************************************************/


//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�



//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������



#include "headfile.h"


uint8 test1[] = "seekfree wireless to uart test\n";
uint8 test2[] = "seekfree.taobao.com\n";

int main(void)
{
    
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
	systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�
	
	
    //����ת����ģ��������Ŷ����� wireless.h�ļ���
    seekfree_wireless_init();
	
    
    //������ν�������ת���ڵ����ݣ���ʵ�ײ��Ѿ�д���ˣ�������Զ࿴��wireless.c�ļ�����Ҫ�����жϽ��յķ�ʽ
    EnableGlobalIRQ(0);

    while(1)
    {
        
        seekfree_wireless_send_buff(test1,sizeof(test1)-1);//����sizeof�����ַ����ĳ��Ȱ��������һ��0�������Ҫ��һ
        seekfree_wireless_send_buff(test2,sizeof(test2)-1);
        systick_delay_ms(1000); 
        
    }

    
}





