#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

/***************/
/*
 * @Port_t enum
 */
typedef enum
{
	GPIO_PORTA=0,
	GPIO_PORTB,
	GPIO_PORTC,
	GPIO_PORTD,
	GPIO_PORTE,
	GPIO_PORTF,
	GPIO_PORTG,
	GPIO_PORTH
}GPIO_Port_t;

/***************/
/*
 * @Pin_t enum
 */
typedef enum 
{
	GPIO_PIN0=0,
	GPIO_PIN1,
	GPIO_PIN2,
	GPIO_PIN3,
	GPIO_PIN4,
	GPIO_PIN5,
	GPIO_PIN6,
	GPIO_PIN7,
	GPIO_PIN8,
	GPIO_PIN9,
	GPIO_PIN10,
	GPIO_PIN11,
	GPIO_PIN12,
	GPIO_PIN13,
	GPIO_PIN14,
	GPIO_PIN15
	
}GPIO_Pin_t;

typedef enum
{
	INPUT=0,
	OUTPUT,
	ALTERNATE_FUNCTION,
	ANALOG
}Mode_t;

typedef enum
{
	LOW=0,
	MWDIUM,
	FAST,
	HIGH
}OutputSpeed_t;

typedef enum
{
	PUSH_PULL=0,
	OPEN_DRAIN
}OutputType_t;

typedef enum
{
	NOPULL=0,
	PULLUP,
	PULLDOWN
}PullUpDown_t;

typedef enum
{
	AF0=0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}AltFunc_t;

/***************/
/*
 * @PinVal_t enum
 */
typedef enum
{
	PIN_LOW=0,
	PIN_HIGH
}PinVal_t;
typedef struct
{
	GPIO_Port_t Port;
	GPIO_Pin_t  PinNum;
	Mode_t Mode;
	OutputSpeed_t Speed;
	OutputType_t OutputType;
	PullUpDown_t PullType;
	AltFunc_t  AlFunc;
}GPIO_PinConfig_t;

uint8_t GPIO_u8PinInit(const GPIO_PinConfig_t *PinConfig);

uint8_t GPIO_u8SetPinValue(GPIO_Port_t Port, GPIO_Pin_t PinNum, PinVal_t PinVal);

uint8_t GPIO_u8TogglePinValue(GPIO_Port_t Port, GPIO_Pin_t PinNum);

uint8_t GPIO_u8ReadPinValue(GPIO_Port_t Port, GPIO_Pin_t PinNum, PinVal_t* PinVal);

#endif
