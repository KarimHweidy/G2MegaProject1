#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#include "GPIO_Interface.h"
#include <stdint.h>

#define LED_SourceConnnec		 0 // to turn on need high pin
#define LED_SinkConnec  		 1 // to turn on need LOW pin



typedef struct
{
	GPIO_PinConfig_t LedPin;
	uint8_t conn_type; /* connection type */
}LED_t;

void LED_HAL_Init(const LED_t * LED_Config);

void LED_HAL_TurnOn(const LED_t * LED_Config);

void LED_HAL_TurnOff(const LED_t * LED_Config);

void LED_HAL_Toggle(const LED_t * LED_Config);

extern LED_t LEDOne ;


#endif
