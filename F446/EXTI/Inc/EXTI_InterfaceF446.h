#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#include <stdint.h>
#include "Stm32F446xx.h"

typedef enum
{
	EXTI_LIN0,
	EXTI_LIN1,
	EXTI_LIN2,
	EXTI_LIN3,
	EXTI_LIN4,
	EXTI_LIN5,
	EXTI_LIN6,
	EXTI_LIN7,
	EXTI_LIN8,
	EXTI_LIN9,
	EXTI_LIN10,
	EXTI_LIN11,
	EXTI_LIN12,
	EXTI_LIN13,
	EXTI_LIN14,
	EXTI_LIN15,
	EXTI_LIN16,
	EXTI_LIN17,
	EXTI_LIN18,
	EXTI_LIN19,
	EXTI_LIN20,
	EXTI_LIN21,
	EXTI_LIN22
}EXTI_NUM_t;

typedef enum
{
	EXTI_RAISING_TRIGGER,
	EXTI_FALLING_TRIGGER,
	EXTI_RIS_FALL_TRIGGER
}EXTI_Trigger_t;

typedef enum
{
	DISABLE,
	ENABLE
}EXTI_Mode_t;


typedef struct
{
	EXTI_NUM_t Exti_Num;
	EXTI_Trigger_t Trigger;
	EXTI_Mode_t mode;
	void(*CallBackFunc)(void); //ptr to func
}EXTI_PinConfig_t;


uint8_t EXTI_u8PinInit(const EXTI_PinConfig_t* Copy_PinConfig);


uint8_t EXTI_u8SetTrigger(EXTI_NUM_t Copy_EXTI_Num ,EXTI_Trigger_t Copy_TriggerState );


uint8_t EXTI_u8ClearPendingFlag(EXTI_NUM_t Copy_EXTI_Num);


uint8_t EXTI_u8GetPendingFlag(EXTI_NUM_t Copy_EXTI_Num , EXTI_Mode_t *Copy_PenValue);


uint8_t EXTI_voidIntEnable(EXTI_NUM_t Copy_EXTI_Num);


uint8_t EXTI_voidIntDisable(EXTI_NUM_t Copy_EXTI_Num);


#endif /* EXTI_INTERFACE_H_ */
