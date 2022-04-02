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
						2.0��IPSģ��ܽ�            ��Ƭ���ܽ�
						D0                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_D0_PIN 	�궨��
						D1                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_D1_PIN 	�궨��
						D2                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_D2_PIN 	�궨��
						D3                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_D3_PIN 	�궨��
						D4                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_D4_PIN 	�궨��
						D5                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_D5_PIN 	�궨��
						D6                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_D6_PIN 	�궨��
						D7                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_D7_PIN 	�궨��
																							
						BL                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_BL_PIN 	�궨��
						CS                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_CS_PIN 	�궨��
						RD                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_RD_PIN 	�궨��
						WR                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_WR_PIN 	�궨��
						RS                  �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_RS_PIN 	�궨��
						RST                 �鿴SEEKFREE_IPS200_PARALLEL8.H�ļ��ڵ�IPS200_RST_PIN 	�궨��
	
						��Դ����
						VCC 3.3V��Դ
						GND ��Դ��
						���ֱ���240*320
					------------------------------------ 
						����ͷFLEXIO�ӿ�    ��Ƭ���ܽ�
						SDA(����ͷ��RX)     �鿴SEEKFREE_SCC8660.h�ļ��е�SCC8660_COF_UART_TX�궨��
						SCL(����ͷ��TX)     �鿴SEEKFREE_SCC8660.h�ļ��е�SCC8660_COF_UART_RX�궨��
                        ���ж�(VSY)         �鿴SEEKFREE_SCC8660.h�ļ��е�SCC8660_VSYNC_PIN�궨��
						���ж�(HREF)		�鿴SEEKFREE_SCC8660.h�ļ��е�SCC8660_HREF_PIN�궨��
						�����ж�(PCLK)      �鿴SEEKFREE_SCC8660.h�ļ��е�SCC8660_PCLK_PIN�궨��
						���ݿ�(D0-D7)		�鿴SEEKFREE_SCC8660.h�ļ��е�SCC8660_DATA_PIN�궨��
					------------------------------------ 
						����ͷCSI�ӿ�       ��Ƭ���ܽ�
						SDA(����ͷ��RX)     �鿴SEEKFREE_SCC8660_CSI.h�ļ��е�SCC8660_CSI_COF_UART_TX�궨��
						SCL(����ͷ��TX)     �鿴SEEKFREE_SCC8660_CSI.h�ļ��е�SCC8660_CSI_COF_UART_RX�궨��
						���ж�(VSY)         �鿴SEEKFREE_SCC8660_CSI.h�ļ��е�SCC8660_CSI_VSYNC_PIN�궨��
						���ж�(HREF)        ������İ����ӣ����գ�
						�����ж�(PCLK)      �鿴SEEKFREE_SCC8660_CSI.h�ļ��е�SCC8660_CSI_PCLK_PIN�궨��
						���ݿ�(D0-D7)       B31-B24 B31��Ӧ����ͷ�ӿ�D0
					------------------------------------ 
					
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
// ��ע�ⱾRT1064�������̵�2.0����Ļ�����뿪Դ���е����Ŷ��岢����ͬ��
// ����������Ϊ�˷���ʹ��˫�㣬�����ݶ˿ڷ���Ϊ���鲻ͬIO�ڵ�����4�����š�
// ���Լ��������壬��IO��������ʱ���뾡��ʹ��ͬһ��IO������8�����ţ����� C8-C15�����������ʾ���ܡ�
//
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************




// �������غ�Ĭ����ʾ CSI �ӿڵ�ͼ�񣬰��� C4 ����������������ͷ�л�




#include "SEEKFREE_FONT.h"
#include "headfile.h"

#define KEY	C4

uint8 key_flag = 0u;


int main(void)
{
	DisableGlobalIRQ();
    board_init();//��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
	
	systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�
	
	
	gpio_init(KEY,GPI,0,GPIO_PIN_CONFIG);								// ��ʼ��C4����
	ips200_init();														// ��ʼ��2.0��IPS��Ļ
	
	ips200_showstr(0,0,"Initialize CSI Camera...");						// ��Ļ��ʾ���ڳ�ʼ��CSI�ӿ�����ͷ����
	scc8660_csi_init();													// ��ʼ��CSI�ӿ����������ͷ
	ips200_showstr(0,1,"CSI Camera OK.");								// ��Ļ��ʾ��ʼ���ɹ�����
	ips200_showstr(0,2,"Initialize FlexIO Camera...");					// ��Ļ��ʾ���ڳ�ʼ��FlexIO�ӿ�����ͷ����
	scc8660_init();														// ��ʼ��FlexIO�ӿ����������ͷ
	ips200_showstr(0,3,"FlexIO Camera OK.");							// ��Ļ��ʾ��ʼ���ɹ�����
	
    EnableGlobalIRQ(0);
    while (1)
    {
		if(!gpio_get(KEY))												// �жϰ�������
		{
			systick_delay_ms(20);
			if(!gpio_get(KEY))
			{
				while(!gpio_get(KEY));
				key_flag = !key_flag;
			}
		}
		if(!key_flag && scc8660_csi_finish_flag)						//CSI����ͷ�ɼ����
		{
			scc8660_csi_finish_flag = 0;								//����ɼ���ɱ�־λ
			ips200_displayimage8660_zoom1(scc8660_csi_image[0],SCC8660_CSI_PIC_W,SCC8660_CSI_PIC_H, 0, 0, 320, 240);	//��ʾͼ��
		}
		if(key_flag && scc8660_finish_flag)								//FlexIO����ͷ�ɼ����
		{
			scc8660_finish_flag = 0;									//����ɼ���ɱ�־λ
			ips200_displayimage8660_zoom1(scc8660_image[0],SCC8660_PIC_W,SCC8660_PIC_H, 0, 0, 320, 240);	//��ʾͼ��
		}

    }
}




