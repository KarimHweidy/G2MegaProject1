/*
 * LED_interface.h
 *
 *  Created on: Aug 31, 2023
 *      Author: Ahmed Abdelaziz
 */

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_






void LED_Init(uint8_t Copy_u8PinNum, uint8_t Copy_u8Port);

void LED_TurnON(uint8_t Copy_u8PinNum, uint8_t Copy_u8Port);
void LED_TurnOff(uint8_t Copy_u8PinNum, uint8_t Copy_u8Port);

#endif /* LED_INTERFACE_H_ */
