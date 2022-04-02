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
                        MPU6050				��Ƭ��
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
	
	
    simiic_init();
    //�������Ӳ鿴SEEKFREE_IIC h�ļ������Ŷ���
    mpu6050_init();
    
    EnableGlobalIRQ(0);
    while(1)
    {
        //��ȡ���ٶ�����
        get_accdata();
        get_gyro();
        systick_delay_ms(1);
		
		// ͨ�����ߵ���ʱ Live Watch��IAR���� Watch��MDK�����ܣ��鿴 mpu_gyro_x mpu_gyro_y mpu_gyro_z mpu_acc_x mpu_acc_y mpu_acc_z ����ֵ���ɡ�
		//mpu_gyro_x,mpu_gyro_y,mpu_gyro_z
		//mpu_acc_x,mpu_acc_y,mpu_acc_z
		
		// ʹ�÷������ڵ���ģʽ���Ҽ������������ mpu_gyro_x ��Add to Live Watch(IAR) �� add��mpu_gyro_x'to...->watch1(MDK),������watch���ڿ�������ʵʱֵ��
    }

    
}





