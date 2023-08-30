#include "Stm32F103xx.h"
#include "BITMATH.h"
#include "ERRORTYPE.h"
#include <stdint.h>

#include "EXTI_Interface.h"
#include "EXTI_Private.h"

static void (*EXTI_CallBack[EXTI_NUM])(void);

uint8_t EXTI_u8ConfigLine (uint8_t Copy_u8EXTI_Line , uint8_t Copy_u8TriggeringMode)
{
  uint8_t Local_u8ErrorState=OK;
  
	if (Copy_u8EXTI_Line > 18) 
	{
		Local_u8ErrorState=NOK;
	}
	else{
		switch (Copy_u8TriggeringMode)
		{
			case RISING_EDGE_TRIGGERING :
			  SETBIT(EXTI->RTSR , Copy_u8EXTI_Line);
			  CLRBIT(EXTI->FTSR , Copy_u8EXTI_Line); break;
			case FALLING_EDGE_TRIGGERING:
			  SETBIT(EXTI->FTSR , Copy_u8EXTI_Line);
			  CLRBIT(EXTI->RTSR , Copy_u8EXTI_Line); break;
			case ON_CHANGE_TRIGGERING   :
			  SETBIT(EXTI->RTSR , Copy_u8EXTI_Line);
			  SETBIT(EXTI->FTSR , Copy_u8EXTI_Line); break;
			default                     :
			  Local_u8ErrorState=NOK;;
		}
    }  
  return Local_u8ErrorState;
}

/*-----------------------------------------------------------------*/

uint8_t EXTI_u8EnableLineIRQ    (uint8_t Copy_u8EXTI_Line)
{
	uint8_t Local_u8ErrorState=OK;
	if (Copy_u8EXTI_Line > 18)
	{
		Local_u8ErrorState=NOK;
	}
	else
	{
		SETBIT(EXTI->IMR , Copy_u8EXTI_Line);
	}
	return Local_u8ErrorState;
}
uint8_t EXTI_u8DisableLineIRQ    (uint8_t Copy_u8EXTI_Line)
{
	uint8_t Local_u8ErrorState=OK;
	if (Copy_u8EXTI_Line > 18)
	{
		Local_u8ErrorState=NOK;
	}
	else
	{
		CLRBIT(EXTI->IMR , Copy_u8EXTI_Line);
	}
	return Local_u8ErrorState;
}
/*-----------------------------------------------------------------*/
uint8_t EXTI_u8EnableLineEvent  (uint8_t Copy_u8EXTI_Line)
{
	uint8_t Local_u8ErrorState=OK;
	if (Copy_u8EXTI_Line > 18)
	{
		Local_u8ErrorState=NOK;
	}
	else
	{
		SETBIT(EXTI->EMR , Copy_u8EXTI_Line);
	}
	return Local_u8ErrorState;
}
uint8_t EXTI_u8DisableLineEvent  (uint8_t Copy_u8EXTI_Line)
{
	uint8_t Local_u8ErrorState=OK;
	if (Copy_u8EXTI_Line > 18)
	{
		Local_u8ErrorState=NOK;
	}
	else
	{
		CLRBIT(EXTI->EMR , Copy_u8EXTI_Line);
	}
	return Local_u8ErrorState;
}
/*-----------------------------------------------------------------*/
uint8_t EXTI_u8SetSoftWareTrig  (uint8_t Copy_u8EXTI_Line)
{
    uint8_t Local_u8ErrorState=OK;
	if (Copy_u8EXTI_Line > 18)
	{
		Local_u8ErrorState=NOK;
	}
	else
	{
		SETBIT(EXTI->SWIER , Copy_u8EXTI_Line);
	}
	return Local_u8ErrorState;
}
uint8_t EXTI_u8ClrPendingFlag   (uint8_t Copy_u8EXTI_Line)
{
	uint8_t Local_u8ErrorState=OK;
	if (Copy_u8EXTI_Line > 18)
	{
		Local_u8ErrorState=NOK;
	}
	else
	{
		SETBIT(EXTI->PR , Copy_u8EXTI_Line);
	}
	return Local_u8ErrorState;
}
void EXTI_voidSetCallBackFn (uint8_t Copy_u8EXTI_Line , void (*pvoidfCallback)(void))
{
	uint8_t Local_u8ErrorState=OK;
	if(NULL == pvoidfCallback)
	{
		Local_u8ErrorState=NULL_POINTER_ERR;
	}
	else
	{
		if (Copy_u8EXTI_Line > 18)
		{
			Local_u8ErrorState=NOK;
		}
		else
		{
			EXTI_CallBack[Copy_u8EXTI_Line] = pvoidfCallback;
		}
	}
	return Local_u8ErrorState;
}

/******************************************************************************/
/********************* Handlers definition for EXTI IRQs *********************/
/******************************************************************************/
#ifdef EXTI0_LINE
void EXTI0_IRQHandler(void){
	(EXTI_CallBack[EXTI0_LINE])();
	SETBIT( EXTI->PR , EXTI0_LINE );
}
#endif

#ifdef EXTI1_LINE
void EXTI1_IRQHandler(void){
	(EXTI_CallBack[EXTI1_LINE])();
	SETBIT( EXTI->PR , EXTI1_LINE );
}
#endif

#ifdef EXTI2_LINE
void EXTI2_IRQHandler(void){
	(EXTI_CallBack[EXTI2_LINE])();
	SETBIT( EXTI->PR , EXTI2_LINE );
}
#endif

#ifdef EXTI3_LINE
void EXTI3_IRQHandler(void){
	(EXTI_CallBack[EXTI3_LINE])();
	SETBIT( EXTI->PR , EXTI3_LINE );
}
#endif

#ifdef EXTI4_LINE
void EXTI4_IRQHandler(void){
	(EXTI_CallBack[EXTI4_LINE])();
	SETBIT( EXTI->PR , EXTI4_LINE );
}
#endif

#ifdef EXTI9_5_LINES_IRQ
void EXTI9_5_IRQHandler(void){
	(EXTI_CallBack[EXTI9_5_LINES_IRQ])();
	SETBIT( EXTI->PR , EXTI9_5_LINES_IRQ );
}
#endif

#ifdef EXTI15_10_LINES_IRQ
void EXTI15_10_IRQHandler(void){
	(EXTI_CallBack[EXTI15_10_LINES_IRQ])();
	BIT_H( EXTI->EXTI_PR , EXTI15_10_LINES_IRQ );
}
#endif
