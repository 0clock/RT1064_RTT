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
						1.8TFTģ��ܽ�      ��Ƭ���ܽ�
						SCL                 �鿴SEEKFREE_18TFT.H�ļ��е�TFT_SCL  	�궨��     Ӳ��SPI���Ų��������л�
						SDA                 �鿴SEEKFREE_18TFT.H�ļ��е�TFT_SDA		�궨��     Ӳ��SPI���Ų��������л�
						RES                 �鿴SEEKFREE_18TFT.H�ļ��е�REST_PIN	�궨��   
						DC                  �鿴SEEKFREE_18TFT.H�ļ��е�DC_PIN		�궨�� 
						CS                 	�鿴SEEKFREE_18TFT.H�ļ��е�TFT_CS		�궨��     Ӳ��SPI���Ų��������л�
						
						��Դ����
						BL  3.3V��Դ������������ţ�Ҳ���Խ�PWM���������ȣ�
						VCC 3.3V��Դ
						GND ��Դ��
						���ֱ���128*160
					------------------------------------ 
						ģ��ܽ�            ��Ƭ���ܽ�
						SDA(����ͷ��RX)     �鿴SEEKFREE_SCC8660_CSI.h�ļ��е�SCC8660_CSI_COF_UART_TX�궨��
						SCL(����ͷ��TX)     �鿴SEEKFREE_SCC8660_CSI.h�ļ��е�SCC8660_CSI_COF_UART_RX�궨��
						���ж�(VSY)         �鿴SEEKFREE_SCC8660_CSI.h�ļ��е�SCC8660_CSI_VSYNC_PIN�궨��
						���ж�(HREF)        ������İ����ӣ����գ�
						�����ж�(PCLK)      �鿴SEEKFREE_SCC8660_CSI.h�ļ��е�SCC8660_CSI_PCLK_PIN�궨��
						���ݿ�(D0-D7)       B31-B24 B31��Ӧ����ͷ�ӿ�D0
					------------------------------------ 
						Ĭ�Ϸֱ���               160*120
						Ĭ��FPS                  50֡

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
	
    //��ʾģʽ����Ϊ3  ����ģʽ
    //��ʾģʽ��SEEKFREE_18TFT.h�ļ��ڵ�TFT_DISPLAY_DIR�궨������
    lcd_init();     	//��ʼ��TFT��Ļ
    lcd_showstr(0,0,"SEEKFREE SCC8660");
    lcd_showstr(0,1,"Initializing... ");
    //�����Ļû���κ���ʾ��������Ļ����
    
    scc8660_csi_init();	//��ʼ������ͷ ʹ��CSI�ӿ�
    //�����Ļһֱ��ʾ��ʼ����Ϣ����������ͷ����
    //���ʹ�����壬һֱ����while(!uart_receive_flag)�������Ƿ�������OK?
    //���ͼ��ֻ�ɼ�һ�Σ����鳡�ź�(VSY)�Ƿ�����OK?
    
    lcd_showstr(0,1,"     OK...      ");
    systick_delay_ms(500);
    
    EnableGlobalIRQ(0);
    while(1)
    {
        if(scc8660_csi_finish_flag)		//ͼ��ɼ����
        {
			scc8660_csi_finish_flag = 0;	//����ɼ���ɱ�־λ
			
			//ʹ��������ʾ����������ԭʼͼ���С �Լ�������Ҫ��ʾ�Ĵ�С�Զ��������Ż��߷Ŵ���ʾ
			//������Ĭ�ϲɼ��ֱ���Ϊ160*120����ʾ�ֱ���Ϊ160*128����������ȫ��
            lcd_displayimage8660_zoom(scc8660_csi_image[0],SCC8660_CSI_PIC_W,SCC8660_CSI_PIC_H,160,128);
        }
    }
}





