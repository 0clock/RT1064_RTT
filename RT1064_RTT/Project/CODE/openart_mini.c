#include "openart_mini.h"

enum picture_type{
    apple,
    banana,
    sedan,//С�γ�
    cat,
    cow,
    bus,//���
    dog,
    durian,
    grape,
    horse,
    orange,
    pig,
    plane,
    ship,
    trains
}picture_type;



uint8               openart_rx_buffer;
lpuart_transfer_t   openart_receivexfer;
lpuart_handle_t     openart_g_lpuartHandle;

uint8 openartBuffer;

void openart_uart1_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_LPUART_RxIdle == status)
    {
        //openart_rx_buffer;    //�����յ����ݺ���Զ����뵽���Ȼ���ȡopenart_rx_buffer�������ɶ�ȡ�����յ�������
        openartBuffer=openart_rx_buffer;
    }
    
    handle->rxDataSize = openart_receivexfer.dataSize;  //��ԭ����������
    handle->rxData = openart_receivexfer.data;          //��ԭ��������ַ
}



void openart_mini(void)
{
    uart_init(USART_1, 115200, UART1_TX_B12, UART1_RX_B13);
    
    //���ô��ڽ��յĻ�����������������
    openart_receivexfer.dataSize = 1;
    openart_receivexfer.data = &openart_rx_buffer;
    
    //�����жϺ����������
    uart_set_handle(USART_1, &openart_g_lpuartHandle, openart_uart1_callback, NULL, 0, openart_receivexfer.data, 1);
    
    NVIC_SetPriority(LPUART4_IRQn, 14);         //���ô����ж����ȼ� ��Χ0-15 ԽС���ȼ�Խ��
    uart_rx_irq(USART_1, 1);
}