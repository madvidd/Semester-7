#ifndef lcd_INCLUDED_
#define lcd_INCLUDED_

//----------------------------------------------------------------------//
//--------------| Char LCD 16*2 Definitions and Examples |--------------//
//----------------------------------------------------------------------//
#define LCD_STM32F10x       /* Char LCD definition */
#define LCD_PORT_B     //LCD connects to Port B
#define LCD_RS     7   //RS connects to PB.7
#define LCD_RW     8   //R/w connects to PB.8
#define LCD_E      9   //En connects to PB.9
#define LCD_DB4    12   //D4 connects to PB.12
#define LCD_DB5    13   //D5 connects to PB.13
#define LCD_DB6    14   //D6 connects to PB.14
#define LCD_DB7    15   //D7 connects to PB.15

//#include "lcd.h" //Edited Library by N. Kazemi (STM32F10x Version of the LPC based Library Taken from: Electrolab.ir)  //Library for 16*2 char LCD

//******************** Some Examples for LCD ********************//
//     lcd_gotoxy(1,1)  |  lcd_gotoxy(1,2)  |  lcd_gotoxy(1,3)  |  ..........  |  lcd_gotoxy(1,16)
//     lcd_gotoxy(2,1)  |  lcd_gotoxy(2,2)  |  lcd_gotoxy(2,3)  |  ..........  |  lcd_gotoxy(2,16)

//     lcd_putsf("My Sentence");

//     lcd_init(); /* This Function Have to be Used in Start */
//     lcd_clear(); /* This Function Have to be Used in Start */

/*     
       int j;
       char ch[]={'*','C','H','A','R',' ','L','C','D',' ','T','e','s','t'};
       for(j=0;j<14;j++)
       {
				lcd_putchar(ch[j]);
				delay(35);
       }
*/

/*
       for(j=0;j<16;j++)
			 {
				lcd_gotoxy(1,j+1);
				lcd_putchar(' ');	
				lcd_gotoxy(2,j+1);	
				lcd_putchar(' ');
				delay(25);	
       }
*/
 
//     lcd_putchar('a');
//***************************************************************//

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//
//----------------------------------------------------------------------//

#ifdef    LCD_STM32F10x
#include "stm32f10x.h"

#ifdef    LCD_PORT_A
#define   PIO_EnableReg			RCC->APB2ENR
#define   PIO_EnableNumber	(1<<2)
#define   PIO_SetOutput     GPIOA->BSRR
#define   PIO_ClearOutput   GPIOA->BRR
#define   PIO_CfgOutputL    GPIOA->CRL
#define   PIO_CfgOutputH    GPIOA->CRH
#endif

#ifdef    LCD_PORT_B
#define   PIO_EnableReg			RCC->APB2ENR
#define   PIO_EnableNumber	(1<<3)
#define   PIO_SetOutput     GPIOB->BSRR   
#define   PIO_ClearOutput   GPIOB->BRR  
#define   PIO_CfgOutputL    GPIOB->CRL
#define   PIO_CfgOutputH    GPIOB->CRH
#endif
#endif



#define F_CPU   12000000

#define clcd_minDelay()   cwait(F_CPU/80000)
#define clcd_Delay()   cwait(F_CPU/8000)
#define clcd_maxDelay()   cwait(F_CPU/12)

void lcd_init(void);
void cwait (volatile int t);
void lcd_putchar(char ch);
void lcd_command(char cmd);
void lcd_gotoxy(char x, char y);
void lcd_clear(void);
void lcd_clear_line(char y);
void lcd_shift_left(char n);
void lcd_shift_right(char n);
void lcd_puts(int num);
void lcd_putsf(char* data);
void lcd_define_char(const char *pc,char char_code);
//============================================================================
void cwait (volatile int t) {
  for (;t; t--);
}
// ============================================================================
void setD4567(char val)
{
   PIO_ClearOutput =((1<<LCD_DB4)|(1<<LCD_DB5)|(1<<LCD_DB6)|(1<<LCD_DB7));
   if (val & 0x80)
      PIO_SetOutput =(1<<LCD_DB7)   ;
   if (val & 0x40)
      PIO_SetOutput =(1<<LCD_DB6);
   if (val & 0x20)
   PIO_SetOutput =(1<<LCD_DB5);
   if (val & 0x10)
   PIO_SetOutput =(1<<LCD_DB4);
}
// ============================================================================
void lcd_putchar(char ch)
{
   PIO_SetOutput =(1<<LCD_RS);
   setD4567(ch);
   PIO_SetOutput=(1<<LCD_E);
   clcd_minDelay();
   PIO_ClearOutput=(1<<LCD_E);
   clcd_minDelay();
   setD4567(ch<<4);
   PIO_SetOutput=(1<<LCD_E);
   clcd_minDelay();
PIO_ClearOutput=(1<<LCD_E);
   clcd_Delay();
}
// ============================================================================
void lcd_command(char cmd)   //Sends Command to LCD
{
   PIO_ClearOutput=(1<<LCD_RS);
   setD4567(cmd);
   PIO_SetOutput =(1<<LCD_E);
   clcd_minDelay();
   PIO_ClearOutput=(1<<LCD_E);
   clcd_minDelay();
   setD4567(cmd<<4);
   PIO_SetOutput =(1<<LCD_E);
   clcd_minDelay();
   PIO_ClearOutput =(1<<LCD_E);
   clcd_Delay();
}
// ============================================================================
void lcd_init()
{
   //uint64_t PIO_CfgSet=0;
	 //uint64_t PIO_CfgClr=0;
   uint32_t PIO_CfgSetL=0;
	 uint32_t PIO_CfgClrL=0;
   uint32_t PIO_CfgSetH=0;
   uint32_t PIO_CfgClrH=0;
   PIO_EnableReg |= PIO_EnableNumber; //Enable GPIOx Clock
   ///* Configure Cfg Variables */
   //PIO_CfgClr=((0xF<<(4*LCD_RS))|(0xF<<(4*LCD_RW))|(0xF<<(4*LCD_E))|(0xF<<(4*LCD_DB4))|(0xF<<(4*LCD_DB5))|(0xF<<(4*LCD_DB6))|(0xF<<(4*LCD_DB7)));
   //PIO_CfgSet=((0x3<<(4*LCD_RS))|(0x3<<(4*LCD_RW))|(0x3<<(4*LCD_E))|(0x3<<(4*LCD_DB4))|(0x3<<(4*LCD_DB5))|(0x3<<(4*LCD_DB6))|(0x3<<(4*LCD_DB7)));
   ///* Configure push-pull output mode for the pins which are connected to the char LCD */
   //PIO_CfgOutputL &= ~((uint32_t)(PIO_CfgClr & 0xFFFFFFFF)); //Clear appropriate bits of the CRL register
   //PIO_CfgOutputL |= ((uint32_t)(PIO_CfgSet & 0xFFFFFFFF)); //Set appropriate bits of the CRL register
   //PIO_CfgOutputH &= ~((uint32_t)(PIO_CfgClr>>32)); //Clear appropriate bits of the CRH register
   //PIO_CfgOutputH |= ((uint32_t)(PIO_CfgSet>>32)); //Set appropriate bits of the CRH register
   ///* -------------------------------------------------------------------------------- */
	 /* Cofigure Cfg Variables */
	 if(LCD_RS<8)
	 {
		 PIO_CfgClrL |= (0xF<<(4*LCD_RS));
		 PIO_CfgSetL |= (0x3<<(4*LCD_RS));
	 }
	 else
	 {
		 PIO_CfgClrH |= (0xF<<(4*(LCD_RS & 0x7)));
		 PIO_CfgSetH |= (0x3<<(4*(LCD_RS & 0x7)));
	 }
	 if(LCD_RW<8)
	 {
		 PIO_CfgClrL |= (0xF<<(4*LCD_RW));
		 PIO_CfgSetL |= (0x3<<(4*LCD_RW));
	 }
	 else
	 {
		 PIO_CfgClrH |= (0xF<<(4*(LCD_RW & 0x7)));
		 PIO_CfgSetH |= (0x3<<(4*(LCD_RW & 0x7)));
	 }
	 if(LCD_E<8)
	 {
		 PIO_CfgClrL |= (0xF<<(4*LCD_E));
		 PIO_CfgSetL |= (0x3<<(4*LCD_E));
	 }
	 else
	 {
		 PIO_CfgClrH |= (0xF<<(4*(LCD_E & 0x7)));
		 PIO_CfgSetH |= (0x3<<(4*(LCD_E & 0x7)));
	 }
	 if(LCD_DB4<8)
	 {
		 PIO_CfgClrL |= (0xF<<(4*LCD_DB4));
		 PIO_CfgSetL |= (0x3<<(4*LCD_DB4));
	 }
	 else
	 {
		 PIO_CfgClrH |= (0xF<<(4*(LCD_DB4 & 0x7)));
		 PIO_CfgSetH |= (0x3<<(4*(LCD_DB4 & 0x7)));
	 }
	 if(LCD_DB5<8)
	 {
		 PIO_CfgClrL |= (0xF<<(4*LCD_DB5));
		 PIO_CfgSetL |= (0x3<<(4*LCD_DB5));
	 }
	 else
	 {
		 PIO_CfgClrH |= (0xF<<(4*(LCD_DB5 & 0x7)));
		 PIO_CfgSetH |= (0x3<<(4*(LCD_DB5 & 0x7)));
	 }
	 if(LCD_DB6<8)
	 {
		 PIO_CfgClrL |= (0xF<<(4*LCD_DB6));
		 PIO_CfgSetL |= (0x3<<(4*LCD_DB6));
	 }
	 else
	 {
		 PIO_CfgClrH |= (0xF<<(4*(LCD_DB6 & 0x7)));
		 PIO_CfgSetH |= (0x3<<(4*(LCD_DB6 & 0x7)));
	 }
	 if(LCD_DB7<8)
	 {
		 PIO_CfgClrL |= (0xF<<(4*LCD_DB7));
		 PIO_CfgSetL |= (0x3<<(4*LCD_DB7));
	 }
	 else
	 {
		 PIO_CfgClrH |= (0xF<<(4*(LCD_DB7 & 0x7)));
		 PIO_CfgSetH |= (0x3<<(4*(LCD_DB7 & 0x7)));
	 }
   /* Configure push-pull output mode for the pins which are connected to the char LCD */
   PIO_CfgOutputL &= ~PIO_CfgClrL; //Clear appropriate bits of the CRL register
   PIO_CfgOutputL |= PIO_CfgSetL; //Set appropriate bits of the CRL register
   PIO_CfgOutputH &= ~PIO_CfgClrH; //Clear appropriate bits of the CRH register
   PIO_CfgOutputH |= PIO_CfgSetH; //Set appropriate bits of the CRH register
   /* -------------------------------------------------------------------------------- */
	 PIO_ClearOutput = (1<<LCD_RW);
   clcd_Delay();
   setD4567(0);
   setD4567((1<<5)|(1<<4));
   PIO_SetOutput=(1<<LCD_E);
   clcd_minDelay();
   PIO_ClearOutput =(1<<LCD_E);
   clcd_Delay();
   setD4567((1<<5)|(1<<4));
   PIO_SetOutput =(1<<LCD_E);
   clcd_minDelay();
   PIO_ClearOutput =(1<<LCD_E);
   clcd_Delay();
   setD4567(1<<5);
   PIO_SetOutput =(1<<LCD_E);
   clcd_minDelay();
   PIO_ClearOutput =(1<<LCD_E);
   clcd_Delay();
   lcd_command(0x28);
   lcd_command(0x0c);
   clcd_Delay();
}
//============================================================================
void lcd_gotoxy(char y, char x)   //Cursor to X Y position
{
   char DDRAMAddr;
x=x-1;
   switch(y)
   {
      case 1: DDRAMAddr = 0x00+x; break;
      case 2: DDRAMAddr = 0x40+x; break;
      case 3: DDRAMAddr = 0x14+x; break;
      case 4: DDRAMAddr = 0x54+x; break;
      default: DDRAMAddr = 0x00+x;
   }
   lcd_command(1<<7 | DDRAMAddr);
   clcd_Delay();
}
// ============================================================================
void lcd_define_char(const char *pc,char char_code)
{
   char a , i;
   a = ((char_code<<3)|0x40) & 0xff;
   for (i = 0; i < 8 ;i++)
   {
      lcd_command(a++);
      clcd_Delay();
      lcd_putchar(pc[i]);
      clcd_Delay();
   }
}
//=============================================================================
void lcd_clear(void)            //Clears LCD
{
   lcd_command(0x01);
   clcd_Delay();
   lcd_command(0x02);
   clcd_maxDelay();
}
//=============================================================================
void lcd_shift_left(char n)   //Scrol n of characters Right
{
   char i;
   for (i = 0 ; i < n ; i++)
   {
      lcd_command(0x1E);
      clcd_Delay();
   }
}
//=============================================================================
void lcd_shift_right(char n)   //Scrol n of characters Left
{
   char q;
   for (q = 0 ;q < n ; q++)
   {
      lcd_command(0x18);
      clcd_Delay();
   }
}
//============================================================================
 void lcd_puts(int num)
{
   int i1,j1;
   int p,f=0;
   char ch[5];
 for(i1=0;i1<5;i1++)
   {
     p=1;
     for(j1=4-i1;j1>0;j1--)
       p = p*10;  
     ch[i1] = (num/p);
    if (num>=p && !f){
     f=1;
    }
     num =num - ch[i1] *p ;
    ch[i1] = ch[i1] +48;
     if(f) lcd_putchar(ch[i1]);
   }
}
// ============================================================================
void lcd_putsf(char* data)   //Outputs string to LCD
{
   char *p;
   p = data;
   if (!p)
      return;
   for(; *p ; )
   {
      lcd_putchar(*p);
      p++;
   }
}
//=============================================================================
void Display_off(void)
{
   lcd_command(0x08);
   clcd_Delay();
}
//=============================================================================
void Display_on(void)
{
   lcd_command(0x0C);
   clcd_Delay();
}
//=============================================================================
void cursor_off(void)
{
   lcd_command(0x0C);
   clcd_Delay();
}
//=============================================================================
void cursor_on(void)
{
   lcd_command(0x0E);
   clcd_Delay();
}
//=============================================================================
void cursor_blink(void)
{
   lcd_command(0x0F);
   clcd_Delay();
}
#endif
