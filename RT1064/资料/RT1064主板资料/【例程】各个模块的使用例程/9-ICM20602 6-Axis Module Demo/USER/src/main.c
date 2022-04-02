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
                        ICM20602ģ��ܽ�			��Ƭ���ܽ�
                        SCL					    �鿴SEEKFREE_ICM20602.h�ļ��е�SPI_SCK_PIN  �궨��
                        SDA                     �鿴SEEKFREE_ICM20602.h�ļ��е�SPI_MOSI_PIN �궨��
                        SA0                     �鿴SEEKFREE_ICM20602.h�ļ��е�SPI_MISO_PIN �궨��
                        CS                      �鿴SEEKFREE_ICM20602.h�ļ��е�SPI_CS_PIN   �궨��
					------------------------------------ 
 ********************************************************************************************************************/


//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�



//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������


#include "headfile.h"


int main(void)
{
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
	systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�
	
	
    //�����̽���ʹ��Ӳ��SPI�������ݲɼ�����ICM20602�ļ��ڣ���д�õ�Ӳ��IIC��ģ��IICͨѶ��ʽ
    
    //�������ſ��Բ鿴ICM20602�ļ��еĺ궨��
    icm20602_init_spi();
    
    EnableGlobalIRQ(0);
    while(1)
    {
        get_icm20602_accdata_spi();
        get_icm20602_gyro_spi();
        
        systick_delay_ms(10);//��ʱ
		
		// ͨ�����ߵ���ʱ Live Watch��IAR���� Watch��MDK�����ܣ��鿴 icm_gyro_x icm_gyro_y icm_gyro_z icm_acc_x icm_acc_y icm_acc_z ����ֵ���ɡ�
		//icm_gyro_x,icm_gyro_y,icm_gyro_z;	����������ֵ
        //icm_acc_x,icm_acc_y,icm_acc_z;	������ٶȼ�ֵ
		
		// ʹ�÷������ڵ���ģʽ���Ҽ������������ icm_gyro_x ��Add to Live Watch(IAR) �� add��icm_gyro_x'to...->watch1(MDK),������watch���ڿ�������ʵʱֵ��
		
    }    
}





