#include "stm32f10x.h"                  // Device header
#include "delay.h"


int main(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	while(1){
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		Delay_ms(1000);
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
		Delay_ms(1000);
	}
	
	return 0;
}
