#include "GPIO_Interface.h"
#include "LED_Private.h"
#include "LED_Interface.h"
/*
void LED_HAL_Init(Port_t LED_Port,PinNum_t LED_Pin) {
	GPIO_PinConfig_t LedPin1;
	LedPin1.Port=LED_Port;
	LedPin1.Pin=LED_Pin;
	LedPin1.Mode=OUTPUT;
	LedPin1.speed=LOW;
	LedPin1.OutputType=PUSH_PULL;
	LedPin1.PullType=NOPULL;
    GPIO_u8PinInit(&LedPin1);
}

void LED_HAL_SetValue(Port_t LED_Port, PinNum_t LED_PinNum, uint8_t LED_PinVal) {
    GPIO_u8setpinValue(LED_Port, LED_PinNum, LED_PinVal);
}

void LED_HAL_Toggle(Port_t LED_Port, PinNum_t LED_Pin) {
    GPIO_u8TogglepinValue(LED_Port, LED_Pin);
}
*/

void LED_HAL_Init(const LED_t * LED_Config)
{
    GPIO_u8PinInit(&LED_Config->LedPin);
	switch(LED_Config->conn_type)
	{
	case LED_SourceConnnec	: GPIO_u8setpinValue(LED_Config->LedPin.Port,LED_Config->LedPin.Pin,PIN_LOW); break; /* turn off led*/
	case LED_SinkConnec  	: GPIO_u8setpinValue(LED_Config->LedPin.Port,LED_Config->LedPin.Pin,PIN_HIGH); break;  /* turn off led*/
	default: break;
	}

}

void LED_HAL_TurnOn(const LED_t * LED_Config)
{
	switch(LED_Config->conn_type)
	{
	case LED_SourceConnnec	: GPIO_u8setpinValue(LED_Config->LedPin.Port,LED_Config->LedPin.Pin,PIN_HIGH); break;
	case LED_SinkConnec  	: GPIO_u8setpinValue(LED_Config->LedPin.Port,LED_Config->LedPin.Pin,PIN_LOW); break;
	default: break;
	}

}

void LED_HAL_TurnOff(const LED_t * LED_Config)
{
	switch(LED_Config->conn_type)
	{
	case LED_SourceConnnec	: GPIO_u8setpinValue(LED_Config->LedPin.Port,LED_Config->LedPin.Pin,PIN_LOW); break; /* turn off led*/
	case LED_SinkConnec  	: GPIO_u8setpinValue(LED_Config->LedPin.Port,LED_Config->LedPin.Pin,PIN_HIGH); break;  /* turn off led*/
	default: break;
	}
}

void LED_HAL_Toggle(const LED_t * LED_Config)
{
	GPIO_u8TogglepinValue(LED_Config->LedPin.Port,LED_Config->LedPin.Pin);
}
