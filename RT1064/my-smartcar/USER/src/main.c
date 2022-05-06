#include "headfile.h"



int main(void)
{
	DisableGlobalIRQ();
	board_init();   	//��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
	systick_delay_ms(300);	//��ʱ300ms���ȴ��������������ϵ�ɹ�
	/*******************************************/
	pit_init();//
	pit_interrupt_ms(PIT_CH0,5);  //��ʼ��pitͨ��0 ����5ms �������ж�
	pit_interrupt_ms(PIT_CH1,5);  //��ʼ��pitͨ��1 ����10ms	���������ڷ����ж�
	pit_interrupt_ms(PIT_CH2,10);  //��ʼ��pitͨ��2 ����10ms	PID�����ж�
    pit_interrupt_ms(PIT_CH3,5);  //��ʼ��pitͨ��3 ����10ms	icm�ж�
	NVIC_SetPriority(PIT_IRQn,1);


	
	Motor_Init();
	Encoder_Init();
    RCEncoder_Init();
	Key_Init();

    icm20602_init_spi();
    icmOffsetInit();//icm��Ư����
	GUI_init();
	//mt9v03x_csi_init();	//��ʼ������ͷ ʹ��CSI�ӿ�
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

    mt9v03x_csi_init();		//��ʼ������ͷ	ʹ��CSI�ӿ�
	//���ͼ��ֻ�ɼ�һ�Σ����鳡�ź�(VSY)�Ƿ�����OK?
	systick_delay_ms(500);
	systick_start();
	EnableGlobalIRQ(0);

    Beep_flag=1;
	while(1)
	{
        if(mt9v03x_csi_finish_flag)			//ͼ��ɼ����
        {
            mt9v03x_csi_finish_flag = 0;	//����ɼ���ɱ�־λ

            //ʹ��������ʾ����������ԭʼͼ���С �Լ�������Ҫ��ʾ�Ĵ�С�Զ��������Ż��߷Ŵ���ʾ
            //�����ɼ�����ͼ��ֱ���Ϊ 188*120 ��2.0��IPS����ʾ�ֱ���Ϊ 320*240 ��ͼ������ȫ����ʾ��
            ips114_displayimage032_zoom(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H, 240, 135);	//��ʾ����ͷͼ��
        }


        Car.Angel=-(int)cpmangle_z;
        //Car_Move();

       // Car_Omni((speed_tar *sin(45/180 *PI)),(speed_tar *cos(45/180 *PI)),0);
        Car_OmniMove();
        //��Ļ��ʾ
        GUI_icm20602();
				GUI_speed();
				GUI_duty();
    }
}




