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
					����&���뿪��    ��Ƭ��               	         
    				SW2				�鿴main.c�е�SW2  �궨��
					SW1             �鿴main.c�е�SW1  �궨��
					S2              �鿴main.c�е�KEY1 �궨��
					S3              �鿴main.c�е�KEY2 �궨��
					S4              �鿴main.c�е�KEY3 �궨��
					S5              �鿴main.c�е�KEY4 �궨��
					------------------------------------
 ********************************************************************************************************************/


//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�



//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������


// �������Ƽ�ʹ��1.8��TFT��ʾ���۲�Ч��������û��1.8��TFT��������ͨ������ʱ��Watch���ڹ۲찴��״̬��
// ͨ�����ߵ���ʱ Live Watch��IAR���� Watch��MDK�����ܣ��鿴 key1_status key2_status key3_status key4_status ����ֵ���ɡ�
// ʹ�÷������Ҽ������������ key1_status ��Add to Live Watch(IAR) �� add��key1_status'to...->watch1(MDK),������watch���ڿ�������ʵʱֵ��
// �ڱ������У�����������ʱ��key1_status ��Ϊ0��


#include "SEEKFREE_FONT.h"
#include "headfile.h"

//���尴������
#define KEY1    C31
#define KEY2    C27
#define KEY3    C26
#define KEY4    C4
//���岦�뿪������
#define SW1     D4
#define SW2     D27


//���뿪��״̬����
uint8 sw1_status;
uint8 sw2_status;

//����״̬����
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;

//��һ�ο���״̬����
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;
uint8 key4_last_status;

//���ر�־λ
uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;
uint8 key4_flag;

uint8 test1,test2,test3,test4;

int main(void)
{
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
	systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�
	
	
    //��ʾģʽ����Ϊ2  ����ģʽ 
    //��ʾģʽ��tft��h�ļ��ڵ�TFT_DISPLAY_DIR�궨������
    lcd_init();     //��ʼ��TFT��Ļ
    //�����Ļû�б�ף�������Ļ����
    //������ʼ��
    gpio_init(KEY1,GPI,0,GPIO_PIN_CONFIG);
    gpio_init(KEY2,GPI,0,GPIO_PIN_CONFIG);
    gpio_init(KEY3,GPI,0,GPIO_PIN_CONFIG);
    gpio_init(KEY4,GPI,0,GPIO_PIN_CONFIG);
    
    //���뿪�س�ʼ��
    gpio_init(SW1,GPI,0,GPIO_PIN_CONFIG);
    gpio_init(SW2,GPI,0,GPIO_PIN_CONFIG);
    
    EnableGlobalIRQ(0);
    lcd_display_chinese(0,0,16,chinese_test[0],4,RED);
    while(1)
    {
        //��ȡ���뿪��״̬
        sw1_status = gpio_get(SW1);
        sw2_status = gpio_get(SW2);

        //��TFT����ʾ���뿪��״̬
        lcd_showstr(0,1,"SW1 STATUS:");     lcd_showint32(12*8,1,sw1_status,1);
        lcd_showstr(0,2,"SW2 STATUS:");     lcd_showint32(12*8,2,sw2_status,1);
        
        //ʹ�ô˷����ŵ����ڣ�����Ҫʹ��while(1) �ȴ������⴦������Դ�˷�
        //���水��״̬
        key1_last_status = key1_status;
        key2_last_status = key2_status;
        key3_last_status = key3_status;
        key4_last_status = key4_status;
        //��ȡ��ǰ����״̬
        key1_status = gpio_get(KEY1);
        key2_status = gpio_get(KEY2);
        key3_status = gpio_get(KEY3);
        key4_status = gpio_get(KEY4);
        
        //��⵽��������֮��  ���ſ���λ��־λ
        if(key1_status && !key1_last_status)    key1_flag = 1;
        if(key2_status && !key2_last_status)    key2_flag = 1;
        if(key3_status && !key3_last_status)    key3_flag = 1;
        if(key4_status && !key4_last_status)    key4_flag = 1;
        
        //��־λ��λ֮�󣬿���ʹ�ñ�־λִ���Լ���Ҫ�����¼�
        if(key1_flag)   
        {
            key1_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
            test1++;
        }
        
        if(key2_flag)   
        {
            key2_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
            test2++;
        }
        
        if(key3_flag)   
        {
            key3_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
            test3++;
        }
        
        if(key4_flag)   
        {
            key4_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
            test4++;
        }
        
        //��TFT����ʾ���Ա���
        lcd_showstr(0,3,"KEY1  TEST:");     lcd_showint32(12*8,3,test1,1);
        lcd_showstr(0,4,"KEY2  TEST:");     lcd_showint32(12*8,4,test2,1);
        lcd_showstr(0,5,"KEY3  TEST:");     lcd_showint32(12*8,5,test3,1);
        lcd_showstr(0,6,"KEY4  TEST:");     lcd_showint32(12*8,6,test4,1);
        
        
        systick_delay_ms(10);//��ʱ����������Ӧ�ñ�֤����ʱ�䲻С��10ms
        
    }

    
}





