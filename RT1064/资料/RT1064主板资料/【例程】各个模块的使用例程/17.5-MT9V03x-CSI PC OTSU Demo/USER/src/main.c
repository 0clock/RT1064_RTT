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
						ģ��ܽ�         	��Ƭ���ܽ�
						SDA(51��RX)         �鿴SEEKFREE_MT9V03X_CSI.h�ļ��е�MT9V03X_CSI_COF_UART_TX	�궨��
						SCL(51��TX)         �鿴SEEKFREE_MT9V03X_CSI.h�ļ��е�MT9V03X_CSI_COF_UART_RX	�궨��
						���ж�(VSY)         �鿴SEEKFREE_MT9V03X_CSI.h�ļ��е�MT9V03X_CSI_VSYNC_PIN		�궨��
						���ж�(HREF)	    ����Ҫʹ��
						�����ж�(PCLK)      �鿴SEEKFREE_MT9V03X_CSI.h�ļ��е�MT9V03X_CSI_PCLK_PIN		�궨��
						���ݿ�(D0-D7)		B31-B24 B31��Ӧ����ͷ�ӿ�D0
						Ĭ�Ϸֱ�����        188*120
						Ĭ��FPS           	50֡
					------------------------------------ 
 ********************************************************************************************************************/



//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������



#include "headfile.h"
#include "math.h"


uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row)
{
    #define GrayScale 256
    uint16 width = col;
    uint16 height = row;
    int pixelCount[GrayScale];
    float pixelPro[GrayScale];
    int i, j, pixelSum = width * height;
    uint8 threshold = 0;
    uint8* data = image;  //ָ���������ݵ�ָ��
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���  
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            pixelCount[(int)data[i * width + j]]++;  //������ֵ��Ϊ����������±�
        }
    }

    //����ÿ������������ͼ���еı���  
    float maxPro = 0.0;
    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
        if (pixelPro[i] > maxPro)
        {
            maxPro = pixelPro[i];
        }
    }

    //�����Ҷȼ�[0,255]  
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    for (i = 0; i < GrayScale; i++)     // i��Ϊ��ֵ
    {
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = 0; j < GrayScale; j++)
        {
            if (j <= i)   //��������  
            {
                w0 += pixelPro[j];
                u0tmp += j * pixelPro[j];
            }
            else   //ǰ������  
            {
                w1 += pixelPro[j];
                u1tmp += j * pixelPro[j];
            }
        }
        u0 = u0tmp / w0;
        u1 = u1tmp / w1;
        u = u0tmp + u1tmp;
        deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
        if (deltaTmp > deltaMax)
        {
            deltaMax = deltaTmp;
            threshold = i;
        }
    }

    return threshold;
}

uint8 image_threshold;  //ͼ����ֵ
uint32 use_time;     

int main(void)
{
    int i;
    uint8 *p;
    
    DisableGlobalIRQ();
    board_init();   	//��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
	systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�
	
	
    mt9v03x_csi_init();	//��ʼ������ͷ ʹ��CSI�ӿ�
    
    pit_init();     	//ʹ��pit �����ȳ�ʼ�� Ȼ���ڵ���pit��������ʹ�ö�Ӧ�Ĺ���
    
    //���ڳ�ʼ�� ����Ĭ�Ͽ�����printf���ܣ������board_init�Ѿ���ʼ���˴���1 ��˱����̲��ٳ�ʼ��
    
    EnableGlobalIRQ(0);
    while(1)
    {
        if(mt9v03x_csi_finish_flag)
        {
			mt9v03x_csi_finish_flag = 0;
			
            pit_start(PIT_CH0);
            image_threshold = otsuThreshold(mt9v03x_csi_image[0],MT9V03X_CSI_W,MT9V03X_CSI_H);  //��򷨼�����ֵ
            use_time = pit_get_us(PIT_CH0);                        //�����򷨳�������ʱ�䣬��λ΢�롣
			
			//�����̴��ʱ����Ժܳ�����ֱ���ñ�Ȼ�����У��������Ż���
			//����˵����զ��ֱ���Ż����ء���˵�����������Ҫ��Ҫ��ֱ�Ӱѳ����ø��㰡��
            pit_close(PIT_CH0);

            
            //���Ͷ�ֵ��ͼ������λ��
            p = mt9v03x_csi_image[0];
            uart_putchar(USART_1,0x00);uart_putchar(USART_1,0xff);uart_putchar(USART_1,0x01);uart_putchar(USART_1,0x01);//��������
            for(i=0; i<MT9V03X_CSI_W*MT9V03X_CSI_H; i++)
            {
                if(p[i]>image_threshold)    uart_putchar(USART_1,0xff);
                else                        uart_putchar(USART_1,0x00);
            }   
        }   
    }
}





