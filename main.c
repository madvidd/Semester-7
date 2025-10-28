//In The Name Of GOD
//External Interupts With LEDs

#include "stm32f10x.h"

volatile int F=0; // Flag = 0
volatile int S=0;

void delay (int tc);

int main (void)
{
	GPIO_InitTypeDef GPIO_x;
	EXTI_InitTypeDef EXTI_x; //External Interrupt
	NVIC_InitTypeDef NVIC_x; //Priority Ext Interrupt
	
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB,ENABLE); //Activating Port B Clock 
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOE,ENABLE); //Activating Port E Clock 
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOF,ENABLE); //Activating Port F Clock 
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOG,ENABLE); //Activating Port G Clock 
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_AFIO,ENABLE); //Activating Interrupt Clock 
	
	//Key 1 <--> PE3
	GPIO_x.GPIO_Mode = GPIO_Mode_IPU; // Port E --> Interrupt Pull Up
	GPIO_x.GPIO_Pin = GPIO_Pin_3; // Pin = 3
	GPIO_x.GPIO_Speed = GPIO_Speed_50MHz; // Speed = 50 MHz
	GPIO_Init (GPIOE,&GPIO_x); // Relating To Port E
	
	//LED 1 <--> PF11 
	GPIO_x.GPIO_Mode = GPIO_Mode_Out_PP; // Port F --> Output Push-Pull
	GPIO_x.GPIO_Pin = GPIO_Pin_11; // Pin = 11
	GPIO_x.GPIO_Speed = GPIO_Speed_50MHz; // Speed = 50 MHz
	GPIO_Init (GPIOF,&GPIO_x); // Relating To Port F
	
	//lED 2 <--> PG7
	GPIO_x.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_x.GPIO_Pin = GPIO_Pin_7;
	GPIO_x.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOG,&GPIO_x);
	
	//LED 3 <--> PF6
	GPIO_x.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_x.GPIO_Pin = GPIO_Pin_6;
	GPIO_x.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOF,&GPIO_x);
	
	//LED 4 <--> PB0
	GPIO_x.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_x.GPIO_Pin = GPIO_Pin_0;
	GPIO_x.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOB,&GPIO_x);
	
	//External Interrupt
	GPIO_EXTILineConfig (GPIO_PortSourceGPIOE,GPIO_PinSource3); // Pin E3 = EXT Interrupt
	
	EXTI_x.EXTI_Line = EXTI_Line3; // Line 3 Of Int
	EXTI_x.EXTI_LineCmd = ENABLE; // Status : Active
	EXTI_x.EXTI_Mode = EXTI_Mode_Interrupt; // Mode = EXT Int
	EXTI_x.EXTI_Trigger = EXTI_Trigger_Falling; // Int Has Falling Edge
	EXTI_Init(&EXTI_x); 
	
	//NVIC
	NVIC_PriorityGroupConfig (NVIC_PriorityGroup_2); // Has No Priority
	
	NVIC_x.NVIC_IRQChannel = EXTI3_IRQn; // Channel 3 Of Int
	NVIC_x.NVIC_IRQChannelCmd = ENABLE; // Status : Activate
	NVIC_x.NVIC_IRQChannelPreemptionPriority = 1; // Main Priority
	NVIC_x.NVIC_IRQChannelSubPriority = 1; // Sub Priority
	NVIC_Init (&NVIC_x);
	
	while (1)
	{
		switch (S) 
			{
				case 0: //Not Pushing Botton Or One More Time After Four Multiple (Like 5,9,13, ...)
					
						GPIO_ResetBits (GPIOF,GPIO_Pin_11); //LED 1 Off
						GPIO_ResetBits (GPIOG,GPIO_Pin_7); //LED 2 Off
						GPIO_ResetBits (GPIOF,GPIO_Pin_6); //LED 3 Off
						GPIO_ResetBits (GPIOB,GPIO_Pin_0); //LED 4 Off
				
				break;
				case 1: //1 Time Of Pushing Botton
					
						GPIO_SetBits (GPIOF,GPIO_Pin_11); //LED 1 On
						GPIO_ResetBits (GPIOG,GPIO_Pin_7); //LED 2 Off
						GPIO_ResetBits (GPIOF,GPIO_Pin_6); //LED 3 Off
						GPIO_ResetBits (GPIOB,GPIO_Pin_0); //LED 4 Off
						
				break;
				case 2: //2 Times Of Pushing Botton
					
						GPIO_SetBits (GPIOF,GPIO_Pin_11); //LED 1 On
						GPIO_SetBits (GPIOG,GPIO_Pin_7); //LED 2 On
						GPIO_ResetBits (GPIOF,GPIO_Pin_6); //LED 3 Off
						GPIO_ResetBits (GPIOB,GPIO_Pin_0); //LED 4 Off
				
				break;
				case 3: //3 Times Of Pushing Botton
				
						GPIO_SetBits (GPIOF,GPIO_Pin_11); //LED 1 On
						GPIO_SetBits (GPIOG,GPIO_Pin_7); //LED 2 On
						GPIO_SetBits (GPIOF,GPIO_Pin_6); //LED 3 On
						GPIO_ResetBits (GPIOB,GPIO_Pin_0); //LED 4 Off
				
				break;
				case 4: //4 Times Of Pushing Botton
			    	GPIO_SetBits (GPIOF,GPIO_Pin_11); //LED 1 On
						GPIO_SetBits (GPIOG,GPIO_Pin_7); //LED 2 On
						GPIO_SetBits (GPIOF,GPIO_Pin_6); //LED 3 On
						GPIO_SetBits (GPIOB,GPIO_Pin_0); //LED 4 On
				
				break;
				
				default:
					;
			}
	}
}
void EXTI3_IRQHandler (void)
{
	F++;
	S = F%5 ; //For Finishing Each Round
	delay (1); //Little Delay For Bounceing Of Push Botton
	EXTI_ClearFlag (EXTI_Line3); // Clearing Channel 3 Of Int
}
	
void delay (int tc)
{
	int n;
	for (n=0 ; n<(1000000*tc) ; n++);
}