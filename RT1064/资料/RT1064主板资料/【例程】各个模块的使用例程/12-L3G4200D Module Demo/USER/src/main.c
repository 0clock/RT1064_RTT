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
                        L3G4200			    ��Ƭ��
                        SCL					�鿴SEEKFREE_IIC.h�ļ��ڵ�SEEKFREE_SCL�궨��
                        SDA             	�鿴SEEKFREE_IIC.h�ļ��ڵ�SEEKFREE_SDA�궨��
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
	
	
    simiic_init();//��ʼ��ģ��IIC
    //�������Ӳ鿴SEEKFREE_IIC h�ļ������Ŷ���
    l3g4200d_init();
    
    EnableGlobalIRQ(0);
    while(1)
    {
        //��ȡ����������
        get_l3g4200d();
        
		//ͨ�����ߵ��Բ鿴 gyro_x gyro_y gyro_z
		//ģ��ת��Խ�죬��Ӧ����ֵԽ��

        systick_delay_ms(5);
    }
}





