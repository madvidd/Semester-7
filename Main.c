#include "stm32f10x.h"
void delay(int d){
int n;
for(n=0;n<(1000000*d);n++);
}
int main()
{
GPIO_InitTypeDef Gpio_cfg;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
Gpio_cfg.GPIO_Pin = 1<<14;
Gpio_cfg.GPIO_Mode = GPIO_Mode_Out_PP; 
Gpio_cfg.GPIO_Speed = GPIO_Speed_50MHz; 
GPIO_Init(GPIOC,&Gpio_cfg);
while(1){
GPIO_SetBits(GPIOC,1<<14);
delay(1);
GPIO_ResetBits(GPIOC,1<<14);
delay(1);
}
} 
