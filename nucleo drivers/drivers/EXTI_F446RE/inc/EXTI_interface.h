#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

typedef enum
{
	EXTI_PIN0,
	EXTI_PIN1,
	EXTI_PIN2,
	EXTI_PIN3,
	EXTI_PIN4,
	EXTI_PIN5,
	EXTI_PIN6,
	EXTI_PIN7,
	EXTI_PIN8,
	EXTI_PIN9,
	EXTI_PIN10,
	EXTI_PIN11,
	EXTI_PIN12,
	EXTI_PIN13,
	EXTI_PIN14,
	EXTI_PIN15

}EXTI_LineNum;

typedef enum
{
	FALLING_TRIG,
	RISING_TRIG,
	FALLING_RISING_TRIG
}EXTI_TrigSrc_t;

typedef enum
{
	ENABLED,
	DISABLED
}EXTI_InitState_t;

typedef struct
{
	EXTI_LineNum PinNum;
	EXTI_TrigSrc_t TigSrc;
	EXTI_InitState_t InitState;
	void (*CallBackFunc)(void);

}EXTI_config_t;




uint8_t EXTI_u8Init(EXTI_config_t* copy_cfg);
uint8_t EXTI_u8SetTrigSrc(EXTI_TrigSrc_t copy_TrigSrc, EXTI_LineNum copy_line);
uint8_t EXTI_u8EnableInt(EXTI_LineNum copy_line);
uint8_t EXTI_u8DisableInt(EXTI_LineNum copy_line);
uint8_t EXTI_u8ClearPendingFlag(EXTI_LineNum copy_line);
uint8_t EXTI_u8GetPendingFlag(EXTI_LineNum copy_line, uint8_t* copy_FlagStatus);



#endif
