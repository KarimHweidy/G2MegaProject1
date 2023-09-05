#include <stdint.h>

#include "BITMATH.h"
#include "ERRORTYPE.h"
#include "GPIO_Interface.h"
#include "SYSTICK_Interface.h"

#include "LCD_Private.h"
#include "LCD_Interface.h"
#include "LCD_Config.h"

/*****************************************************************************
* Function Name: LCD_init
* Purpose      : initialize LCD - enable mode 4-bit mode - enable both lines - cursor off
* Parameters   : void
* Return value : void
*****************************************************************************/
static LCD_Config LDC_arr[NUMOF_LCDPINS]={
	{LCD_DATAPORT,LCD_D4PIN},{LCD_DATAPORT,LCD_D5PIN},{LCD_DATAPORT,LCD_D6PIN},{LCD_DATAPORT,LCD_D7PIN},{LCD_RSPORT,LCD_RSPIN},{LCD_ENPORT,LCD_ENPIN}
};

void LCD_init(void){

	for(uint8_t i=0; i< NUMOF_LCDPINS;i++)
	{
		GPIO_u8PinInit(LDC_arr[i].port,LDC_arr[i].pin,GPO_PUSH_PULL_02_MHZ);
	}
	
	
	STK_voidDelayms(40) ;

	LCD_write_command(LCD_INIT);//send most first
	STK_voidDelayms(5);
	LCD_write_command(ENABLE_4BIT_MODE);//send most first
	STK_voidDelayus(100);
	LCD_write_command(LCD_FUNCTION_SET);//send most first
	STK_voidDelayus(100);
	LCD_write_command(LCD_CURSOR_OFF);
	STK_voidDelayus(200);


	LCD_write_command(LCD_ENTRY_MODE_SET);
	LCD_write_command(HLCD_DISPLAY_ON);
	LCD_write_command(LCD_CLEAR_DISPLAY);
	STK_voidDelayms(2);


}

/*****************************************************************************
* Function Name: LCD_write_command
* Purpose      : send a specific command to LCD
* Parameters   : uint8_t: the value of command
* Return value : void
*****************************************************************************/

void LCD_write_command(uint8_t com){

	// send last 4 bits in com after enable command
	RS(0);
	D4(READBIT(com,4));
	D5(READBIT(com,5));
	D6(READBIT(com,6));
	D7(READBIT(com,7));
	EN(1);
	STK_voidDelayus(30);
	EN(0);
	STK_voidDelayus(50);

	// send first 4 bits in com after enable command
	D4(READBIT(com,0));
	D5(READBIT(com,1));
	D6(READBIT(com,2));
	D7(READBIT(com,3));
	EN(1);
	STK_voidDelayus(30);
	EN(0);
	STK_voidDelayus(50);
}
/*****************************************************************************
* Function Name: LCD_write_char
* Purpose      : write a char (by ascii) on LCD
* Parameters   : uint8_t: the value of ascii of the char
* Return value : void
*****************************************************************************/

void LCD_write_char(char data){
	// send first 4 bits in com after enable command
	RS(1);
	D4(READBIT(data,4));
	D5(READBIT(data,5));
	D6(READBIT(data,6));
	D7(READBIT(data,7));
	EN(1);
	STK_voidDelayus(30);
	EN(0);
	STK_voidDelayus(50);

	// send last 4 bits in com after enable command
	D4(READBIT(data,0));
	D5(READBIT(data,1));
	D6(READBIT(data,2));
	D7(READBIT(data,3));
	EN(1);
	STK_voidDelayus(30);
	EN(0);
	STK_voidDelayus(50);
}
/************************************************************************
* Function Name: LCD_write_num
* Purpose      : display a specific number on LCD
* Parameters   : uint16_t: 5 digit number or less
* Return value : void
*************************************************************************/

void LCD_write_num(uint16_t num){
	if (num ==0) {LCD_write_char('0');return;}
	uint8_t n[5]; int8_t i=0;
	//save every digit of num in our array separately
	for(;num!=0;i++)
	{
		n[i]=(num%10) +'0';
		num/=10;
	}
	i--;
	while(i!=-1){
		LCD_write_char(n[i]);
		i--;
	}
}
/*****************************************************************************
* Function Name: LCD_write_string
* Purpose      : display a specific string on LCD
* Parameters   : uint8_t*: array of string which must end with null
* Return value : void
*****************************************************************************/

void LCD_write_string(char *str)
{	
	uint8_t i =0;
	if(str != NULL )
	{
		for(;str[i]!='\0';i++){
			LCD_write_char(str[i]);
		}
	}
	else{
		/* error */
	}
	
}
/*****************************************************************************
* Function Name: LCD_Set_cur
* Purpose      : Set cursor on specific index on LCD
* Parameters   : uint8_t: row ,amd col arguments
* Return value : void
*****************************************************************************/

void LCD_Set_cur(uint8_t row, uint8_t col)
{
    switch (row)
    {
        case 0:
            col |= LCD_START_LINE_1;
            break;
        case 1:
            col |= LCD_START_LINE_2;
            break;
    }

    LCD_write_command(col);
    STK_voidDelayms(1);
}
/*****************************************************************************
* Function Name: LCD_clear
* Purpose      : Clear LCD
* Parameters   : void
* Return value : void
*****************************************************************************/

void LCD_clear (void)
{
	LCD_write_command(0x01);
	STK_voidDelayms(1);
}

