#include "key.h"

//-----------------------��-----------------------//
/*BUTTON*/
#define KEY1 C31 
#define KEY2 C27 
#define KEY3 C26 
#define KEY4 C4 

/*Dial_switch*/
#define Dial_switch1 D27
#define Dial_switch2 D4

void keyinit(void){
	//�����жϳ�ʼ��
	gpio_init(C31, GPI, 1, GPIO_PIN_CONFIG);
	gpio_init(C27, GPI, 1, GPIO_PIN_CONFIG);
	gpio_init(C26, GPI, 1, GPIO_PIN_CONFIG);
	gpio_init(C4, GPI, 1, GPIO_PIN_CONFIG);
	//���뿪�����ų�ʼ��
	gpio_init(D27, GPI, 1, GPIO_PIN_CONFIG);
	gpio_init(D4, GPI, 1, GPIO_PIN_CONFIG);
}