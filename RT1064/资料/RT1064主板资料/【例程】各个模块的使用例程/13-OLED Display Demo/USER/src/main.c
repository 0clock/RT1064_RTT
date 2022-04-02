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
					    OLEDҺ��    ��Ƭ��                        
    					D0          �鿴SEEKFREE_OLED�ļ��ڵ�OLED_SCL_PIN   �궨��
    					D1          �鿴SEEKFREE_OLED�ļ��ڵ�OLED_SDA_PIN   �궨��            
    					RES         �鿴SEEKFREE_OLED�ļ��ڵ�OLED_RST_PIN   �궨��    
    					DC          �鿴SEEKFREE_OLED�ļ��ڵ�OLED_DC_PIN    �궨��
						CS          �鿴SEEKFREE_OLED�ļ��ڵ�OLED_CS_PIN    �궨��
					------------------------------------ 
 ********************************************************************************************************************/


//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�



//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������


#include "SEEKFREE_FONT.h"
#include "headfile.h"




int main(void)
{
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
	systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�
	
	
    oled_init();     //��ʼ��OLED��Ļ
    
    EnableGlobalIRQ(0);
    while(1)
    {
        oled_p6x8str(0,0,"seekfree.taobao.com");//��ʾ�ַ���
        oled_printf_int32(0,1,5693,5);          //��ʾһ������  ȥ����Ч0λ
        
        oled_printf_float(0,2,56.356,5,2);      //��ʾһ�������� ȥ����Ч0λ  ����λ��ʾ5λ  С��λ��ʾ2λ

        //������ʾ��X Y����������������һ�£�������ʾ��������x y����������Ϊ��λ
        //��������ʹ��λ�õ��ڸ�������
        oled_print_chinese(0,3,16,oled_16x16_chinese[0],4);
        

        systick_delay_ms(20);
    }

    
}





