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
						1.14IPSģ��ܽ�      	��Ƭ���ܽ�
						SCL                 	�鿴SEEKFREE_IPS114_SPI.h�ļ��е�IPS114_SCL_PIN		�궨��     Ӳ��SPI���Ų��������л�
						SDA                 	�鿴SEEKFREE_IPS114_SPI.h�ļ��е�IPS114_SDA_PIN		�궨��     Ӳ��SPI���Ų��������л�
						RES                 	�鿴SEEKFREE_IPS114_SPI.h�ļ��е�IPS114_REST_PIN	�궨��   
						DC                  	�鿴SEEKFREE_IPS114_SPI.h�ļ��е�IPS114_DC_PIN		�궨��
						CS                  	�鿴SEEKFREE_IPS114_SPI.h�ļ��е�IPS114_CS_PIN		�궨��     Ӳ��SPI���Ų��������л�
						
						��Դ����
						BL  3.3V��Դ������������ţ�Ҳ���Խ�PWM���������ȣ�
						VCC 3.3V��Դ
						GND ��Դ��
						���ֱ���135*240
					------------------------------------ 
						�����ģ��ܽ�      	��Ƭ���ܽ�
						SDA(51��RX)         	�鿴SEEKFREE_MT9V03X_CSI.h�ļ��е�MT9V03X_CSI_COF_UART_TX	�궨��
						SCL(51��TX)         	�鿴SEEKFREE_MT9V03X_CSI.h�ļ��е�MT9V03X_CSI_COF_UART_RX	�궨��
						���ж�(VSY)         	�鿴SEEKFREE_MT9V03X_CSI.h�ļ��е�MT9V03X_CSI_VSYNC_PIN		�궨��
						���ж�(HREF)	    	����Ҫʹ��
						�����ж�(PCLK)      	�鿴SEEKFREE_MT9V03X_CSI.h�ļ��е�MT9V03X_CSI_PCLK_PIN		�궨��
						���ݿ�(D0-D7)			B31-B24 B31��Ӧ����ͷ�ӿ�D0
					------------------------------------ 
						Ĭ�Ϸֱ�����            188*120
						Ĭ��FPS                 50֡
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
	board_init();   	//��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
	systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�
	/*******************************************/
	pit_init();//
	pit_interrupt_ms(PIT_CH0,5);  //��ʼ��pitͨ��0 ����5ms �������ж�
	pit_interrupt_ms(PIT_CH1,10);  //��ʼ��pitͨ��1 ����10ms	���������ڷ����ж�
	pit_interrupt_ms(PIT_CH2,10);  //��ʼ��pitͨ��2 ����10ms	PID�����ж�
	NVIC_SetPriority(PIT_IRQn,1);
	
	GUI_init();
	Motor_Init();
	Encoder_Init();
	Key_Init();
	
	simiic_init();//ģ��IIC�˿ڳ�ʼ��
	icm20602_init();
	
	mt9v03x_csi_init();	//��ʼ������ͷ ʹ��CSI�ӿ�
	//�����Ļһֱ��ʾ��ʼ����Ϣ����������ͷ����
	//���ʹ�����壬һֱ����while(!uart_receive_flag)�������Ƿ�������OK?
	uart_init (USART_8, 115200,UART8_TX_D16,UART8_RX_D17); //��ʼ������
	
	// VOFA+ 
    VOFA* VOFA_pt = vofa_create();       //����VOFA����
    vofa_init(VOFA_pt,                   //��ʼ����ǰ��vofa����
                vofa_ch_data,ch_sz,
       vofa_image,image_sz,
       custom_buf,custom_sz,
       cmd_rxbuf,cmd_sz,
       USART_8,USART_8,USART_8);

	//���ͼ��ֻ�ɼ�һ�Σ����鳡�ź�(VSY)�Ƿ�����OK?
	systick_delay_ms(500);
	systick_start();
	EnableGlobalIRQ(0);


	while(1)
	{
		get_icm20602_accdata();
		get_icm20602_gyro();

        //��Ļ��ʾ
		GUI_icm20602();
		GUI_speed();
		GUI_duty();
	} 
}




