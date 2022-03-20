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
					���߶���
					------------------------------------ 
					ģ��ܽ�            ��Ƭ���ܽ�
					SDA(����ͷ��RX)     �鿴SEEKFREE_SCC8660.h�ļ��е�SCC8660_COF_UART_TX�궨��
					SCL(����ͷ��TX)     �鿴SEEKFREE_SCC8660.h�ļ��е�SCC8660_COF_UART_RX�궨��
					���ж�(VSY)         �鿴SEEKFREE_SCC8660.h�ļ��е�SCC8660_VSYNC_PIN�궨��
					���ж�(HREF)        ������İ����ӣ����գ�
					�����ж�(PCLK)      �鿴SEEKFREE_SCC8660.h�ļ��е�SCC8660_PCLK_PIN�궨��
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
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
	systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�
	
	
    scc8660_init();//��ʼ������ͷ ʹ��FLEXIO�ӿ�
    
    EnableGlobalIRQ(0);
    while(1)
    {
        if(scc8660_finish_flag)
        {
			scc8660_finish_flag = 0;
            csi_seekfree_sendimg_scc8660(USART_1,scc8660_image[0],SCC8660_PIC_W,SCC8660_PIC_H);//���ڳ�ʼ�� ����Ĭ�Ͽ�����printf���ܣ������board_init�Ѿ���ʼ���˴���1 ��˱����̲��ڳ�ʼ��
            
        }
        
    }

    
}





