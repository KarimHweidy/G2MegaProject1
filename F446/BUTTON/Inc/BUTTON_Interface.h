#ifndef BUTTON_INTERFACE_H
#define BUTTON_INTERFACE_H

#include "GPIO_Interface.h"
#include <stdint.h>

void Button_Init(Port_t BUT_Port,PinNum_t BUT_Pin,PullUpDown_t BUT_PUPD);

uint8_t Button_u8Read(Port_t BUT_Port,PinNum_t BUT_Pin);

#endif
