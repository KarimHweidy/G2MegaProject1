#include "Stm32F446xx.h"
#include "BITMATH.h"
#include "ERRORTYPE.h"
#include <stdint.h>

#include "EXTI_Interface.h"
#include "EXTI_Private.h"

/*Global Array of Pointers to function to take The CallBack Functions*/
static void (*CallBackFuncArr[EXTI_NUM])(void)={NULL}; //arr[23]

uint8_t EXTI_u8PinInit(const EXTI_PinConfig_t* Copy_PinConfig)
{
	uint8_t Local_ErrorState=OK;
	if(NULL == Copy_PinConfig || NULL == Copy_PinConfig->CallBackFunc )
	{
		Local_ErrorState=NULL_POINTER_ERR;
	}
	else
	{
		if( EXTI_LIN22 >= Copy_PinConfig->Exti_Num){
			/*Choose Trigger Type*/
			switch(Copy_PinConfig->Trigger)
			{
				case EXTI_RAISING_TRIGGER: 	EXTI->RTSR |= 1<< Copy_PinConfig->Exti_Num;
											EXTI->FTSR &= ~(1<< Copy_PinConfig->Exti_Num); break;
				case EXTI_FALLING_TRIGGER: 	EXTI->FTSR |= 1<< Copy_PinConfig->Exti_Num;
											EXTI->RTSR &= ~(1<< Copy_PinConfig->Exti_Num); break;
				case EXTI_RIS_FALL_TRIGGER: EXTI->RTSR |= 1<< Copy_PinConfig->Exti_Num;
											EXTI->FTSR |= 1<< Copy_PinConfig->Exti_Num; 	  break;
				default: Local_ErrorState = NOK;
			}
			if( ENABLE ==Copy_PinConfig->mode){
				EXTI->IMR |= 1 << Copy_PinConfig->Exti_Num ;
			}
			else{
				EXTI->IMR &= ~(1 << Copy_PinConfig->Exti_Num );
			}
			/*Pass the CallBack Function to The Global Array*/
			CallBackFuncArr[Copy_PinConfig->Exti_Num] = Copy_PinConfig->CallBackFunc;
		}
		else {
			Local_ErrorState = NOK;
		}
	}
	return Local_ErrorState;
}

uint8_t EXTI_u8SetTrigger(EXTI_NUM_t Copy_EXTI_Num ,EXTI_Trigger_t Copy_TriggerState ){
	uint8_t Local_ErrorState=OK;
	if(EXTI_LIN22 <= Copy_EXTI_Num )
	{
		Local_ErrorState=NOK;
	}
	else{
		switch(Copy_TriggerState)
			{
				case EXTI_RAISING_TRIGGER: 	EXTI->RTSR |= 1<< Copy_EXTI_Num;
											EXTI->FTSR &= ~(1<<Copy_EXTI_Num); break;
				case EXTI_FALLING_TRIGGER: 	EXTI->FTSR |= 1<< Copy_EXTI_Num;
											EXTI->RTSR &= ~(1<< Copy_EXTI_Num); break;
				case EXTI_RIS_FALL_TRIGGER: EXTI->RTSR |= 1<< Copy_EXTI_Num;
											EXTI->FTSR |= 1<< Copy_EXTI_Num; 	  break;
				default: Local_ErrorState = NOK;
			}
	}
	
	return Local_ErrorState;
}

uint8_t EXTI_u8ClearPendingFlag(EXTI_NUM_t Copy_EXTI_Num){
	uint8_t Local_ErrorState=OK;
	if(EXTI_LIN22 <= Copy_EXTI_Num )
	{
		Local_ErrorState=NOK;
	}
	else{
		/*Clear Pending Flag*/
		EXTI->PR = 1<<Copy_EXTI_Num; /* 0 doesn't affect */
	}
	
	return Local_ErrorState;
}


uint8_t EXTI_u8GetPendingFlag(EXTI_NUM_t Copy_EXTI_Num , EXTI_Mode_t *Copy_PenValue){
	uint8_t Local_ErrorState=OK;
	if(EXTI_LIN22 <= Copy_EXTI_Num )
	{
		Local_ErrorState=NOK;
	}
	else{
		/* Set bit */
		*Copy_PenValue= (EXTI->PR >> Copy_EXTI_Num) & 1 ;
	}
	
	return Local_ErrorState;
}


uint8_t EXTI_u8IntEnable(EXTI_NUM_t Copy_EXTI_Num){
	uint8_t Local_ErrorState=OK;
	if(EXTI_LIN22 <= Copy_EXTI_Num )
	{
		Local_ErrorState=NOK;
	}
	else{
		/* Set bit enable  */
		EXTI->IMR |= 1<<Copy_EXTI_Num;
	}
	
	return Local_ErrorState;
}


uint8_t EXTI_u8IntDisable(EXTI_NUM_t Copy_EXTI_Num){
	uint8_t Local_ErrorState=OK;	
	if(EXTI_LIN22 <= Copy_EXTI_Num )
	{
		Local_ErrorState=NOK;
	}
	else{
		/* Set bit enable  */
		EXTI->IMR &= ~(1<<Copy_EXTI_Num);
	}
	return Local_ErrorState;
}	


void EXTI0_IRQHandler (void)
{
	/*Make Sure That CallBack Function No Null*/
	if(CallBackFuncArr[EXTI_LIN0] !=NULL)
	{
		/*Clear Pending Flag*/
		EXTI_u8ClearPendingFlag(EXTI_LIN0);
		/*Call The Call Back Function*/
		CallBackFuncArr[EXTI_LIN0]();
	}
	else
	{
		/*Do Nothing*/
	}
}

void EXTI1_IRQHandler (void)
{
	/*Make Sure That CallBack Function No Null*/
	if(CallBackFuncArr[EXTI_LIN1] !=NULL)
	{
		/*Clear Pending Flag*/
		EXTI_u8ClearPendingFlag(EXTI_LIN1);
		/*Call The Call Back Function*/
		CallBackFuncArr[EXTI_LIN1]();
	}
	else
	{
		/*Do Nothing*/
	}
}

void EXTI2_IRQHandler (void)
{
	/*Make Sure That CallBack Function No Null*/
	if(CallBackFuncArr[EXTI_LIN2] !=NULL)
	{
		/*Clear Pending Flag*/
		EXTI_u8ClearPendingFlag(EXTI_LIN2);
		/*Call The Call Back Function*/
		CallBackFuncArr[EXTI_LIN2]();
	}
	else
	{
		/*Do Nothing*/
	}
}

void EXTI3_IRQHandler (void)
{
	/*Make Sure That CallBack Function No Null*/
	if(CallBackFuncArr[EXTI_LIN3] !=NULL)
	{
		/*Clear Pending Flag*/
		EXTI_u8ClearPendingFlag(EXTI_LIN3);
		/*Call The Call Back Function*/
		CallBackFuncArr[EXTI_LIN3]();
	}
	else
	{
		/*Do Nothing*/
	}
}

void EXTI4_IRQHandler (void)
{
	/*Make Sure That CallBack Function No Null*/
	if(CallBackFuncArr[EXTI_LIN4] !=NULL)
	{
		/*Clear Pending Flag*/
		EXTI_u8ClearPendingFlag(EXTI_LIN4);
		/*Call The Call Back Function*/
		CallBackFuncArr[EXTI_LIN4]();
	}
	else
	{
		/*Do Nothing*/
	}
}

void EXTI9_5_IRQHandler (void)
{
	/* MACRO TO READ PF5  */
	if( EXTIX_FLAG(EXTI->PR,EXTI_PR_PR5_Pos) == 1 ){
		/*Clear Pending Flag*/
		EXTI->PR = 1<<EXTI_PR_PR5_Pos;
		/*Call The Call Back Function*/
		CallBackFuncArr[EXTI_LIN5]();
	}
	else {	}
	
	/* MACRO TO READ PF6  */
	if( EXTIX_FLAG(EXTI->PR,EXTI_PR_PR6_Pos) == 1 ){
		/*Clear Pending Flag*/
		EXTI->PR = 1<<EXTI_PR_PR6_Pos;
		/*Call The Call Back Function*/
		CallBackFuncArr[EXTI_LIN6]();
	}
	else {	}
	
	/* MACRO TO READ PF7  */
	if( EXTIX_FLAG(EXTI->PR,EXTI_PR_PR7_Pos) == 1 ){
		/*Clear Pending Flag*/
		EXTI->PR = 1<<EXTI_PR_PR7_Pos;
		/*Call The Call Back Function*/
		CallBackFuncArr[EXTI_LIN7]();
	}
	else {	}

	/* MACRO TO READ PF8  */
	if( EXTIX_FLAG(EXTI->PR,EXTI_PR_PR8_Pos) == 1 ){
		/*Clear Pending Flag*/
		EXTI->PR = 1<<EXTI_PR_PR8_Pos;
		/*Call The Call Back Function*/
		CallBackFuncArr[EXTI_LIN8]();
	}
	else {	}
	/* MACRO TO READ PF9  */
	if( EXTIX_FLAG(EXTI->PR,EXTI_PR_PR9_Pos) == 1 ){
		/*Clear Pending Flag*/
		EXTI->PR = 1<<EXTI_PR_PR9_Pos;
		/*Call The Call Back Function*/
		CallBackFuncArr[EXTI_LIN9]();
	}
	else {	}
	
}

void EXTI15_10_IRQHandler(void)
{
	/* MACRO TO READ PF10  */
	if( EXTIX_FLAG(EXTI->PR,EXTI_PR_PR10_Pos) == 1 ){
		/*Clear Pending Flag*/
		EXTI->PR = 1<<EXTI_PR_PR10_Pos;
		/*Call The Call Back Function*/
		CallBackFuncArr[EXTI_LIN10]();
	}
	else {	}
	
	/* MACRO TO READ PF11  */
	if( EXTIX_FLAG(EXTI->PR,EXTI_PR_PR11_Pos) == 1 ){
		/*Clear Pending Flag*/
		EXTI->PR = 1<<EXTI_PR_PR11_Pos;
		/*Call The Call Back Function*/
		CallBackFuncArr[EXTI_LIN11]();
	}
	else {	}
	
	/* MACRO TO READ PF12  */
	if( EXTIX_FLAG(EXTI->PR,EXTI_PR_PR12_Pos) == 1 ){
		/*Clear Pending Flag*/
		EXTI->PR = 1<<EXTI_PR_PR12_Pos;
		/*Call The Call Back Function*/
		CallBackFuncArr[EXTI_LIN12]();
	}
	else {	}

	/* MACRO TO READ PF13  */
	if( EXTIX_FLAG(EXTI->PR,EXTI_PR_PR13_Pos) == 1 ){
		/*Clear Pending Flag*/
		EXTI->PR = 1<<EXTI_PR_PR13_Pos;
		/*Call The Call Back Function*/
		CallBackFuncArr[EXTI_LIN13]();
	}
	else {	}
	/* MACRO TO READ PF14  */
	if( EXTIX_FLAG(EXTI->PR,EXTI_PR_PR14_Pos) == 1 ){
		/*Clear Pending Flag*/
		EXTI->PR = 1<<EXTI_PR_PR14_Pos;
		/*Call The Call Back Function*/
		CallBackFuncArr[EXTI_LIN14]();
	}
	else {	}
	/* MACRO TO READ PF15  */
	if( EXTIX_FLAG(EXTI->PR,EXTI_PR_PR15_Pos) == 1 ){
		/*Clear Pending Flag*/
		EXTI->PR = 1<<EXTI_PR_PR15_Pos;
		/*Call The Call Back Function*/
		CallBackFuncArr[EXTI_LIN15]();
	}
	else {	}
	
}
