/*
 * LED_prog.c
 *
 *  Created on: Aug 31, 2023
 *      Author: Ahmed Abdelaziz
 */


#include <stdint.h>
#include "stm32f103xx.h"
#include "GPIO_interface.h"

#include "LED_interface.h"





void LED_Init(uint8_t Copy_u8PinNum , uint8_t Copy_u8Port)
{
	GPIO_PinConfig_t LED_Config =      /*Initialize LED Configuration Data*/
	{
		.Output = OUTPUT_PUSH_PULL,
		.Mode = OUTPUT_SPEED_2M,
		.PinNum = Copy_u8PinNum,
		.Port = Copy_u8Port,

	};
	GPIO_u8PinInit(&LED_Config);  /*Initialize Led pin*/


}
void LED_TurnON(uint8_t Copy_u8PinNum ,uint8_t Copy_u8Port)
{
	GPIO_u8SetPinValue(Copy_u8Port, Copy_u8PinNum, PIN_HIGH);
}
void LED_TurnOff(uint8_t Copy_u8PinNum,uint8_t Copy_u8Port)
{
	GPIO_u8SetPinValue(Copy_u8Port, Copy_u8PinNum, PIN_LOW);
}
