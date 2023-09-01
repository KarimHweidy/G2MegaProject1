/*
 * BUZZER_interfac.h
 *
 *  Created on: Aug 31, 2023
 *      Author: Ahmed Abdelaziz
 */

#ifndef BUZZER_INTERFACE_H_
#define BUZZER_INTERFACE_H_




void BUZZER_Init(uint8_t Copy_u8PinNum, uint8_t Copy_u8Port);

void BUZZER_TurnON(uint8_t Copy_u8PinNum, uint8_t Copy_u8Port);
void BUZZER_TurnOff(uint8_t Copy_u8PinNum, uint8_t Copy_u8Port);

#endif /* BUZZER_INTERFACE_H_ */
