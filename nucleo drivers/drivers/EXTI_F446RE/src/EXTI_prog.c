#include <stdint.h>
#include "stm32f446xx.h"
#include "ErrorType.h"
#include "EXTI_interface.h"
#include "EXTI_prv.h"

/*Global array of pointer to function to hold callback functions*/
static void(*EXTI_CallBackFunc[EXTI_LINE_NUM])(void)={NULL};


uint8_t EXTI_u8Init(EXTI_config_t* copy_cfg)
{
	uint8_t Local_u8ErrorState = OK;
	if (copy_cfg->PinNum <= EXTI_LINE_NUM)
	{
		if (copy_cfg != NULL)
		{
			/*setting trigger source configuration*/
			switch(copy_cfg->TigSrc)
			{
			case RISING_TRIG:
				EXTI->FTSR &= (~(1<<(copy_cfg->PinNum)));
				EXTI->RTSR |= 1<< (copy_cfg->PinNum);
				break;
			case FALLING_TRIG:
				EXTI->RTSR &= (~(1<<(copy_cfg->PinNum)));
				EXTI->FTSR |= 1<< (copy_cfg->PinNum);
				break;
			case FALLING_RISING_TRIG:
				EXTI->RTSR |= 1<< (copy_cfg->PinNum);
				EXTI->FTSR |= 1<< (copy_cfg->PinNum);
				break;
			default: Local_u8ErrorState = NOK;break;
			}


			/*set interrupt enable/disable initial state*/
			if (copy_cfg->InitState == ENABLED)
			{
				EXTI->IMR |= (1<<(copy_cfg->PinNum));
			}
			else if (copy_cfg->InitState == DISABLED)
			{
				EXTI->IMR &= (~(1<<(copy_cfg->PinNum)));
			}
			else
			{
				Local_u8ErrorState = NOK;
			}

			/*setting callback function pointer*/
			if (copy_cfg->CallBackFunc != NULL)
			{
				EXTI_CallBackFunc[copy_cfg->PinNum] = copy_cfg->CallBackFunc;

			}
			else
			{
				Local_u8ErrorState = NULL_PTR_ERR;
			}
		}
		else
		{
			Local_u8ErrorState = NULL_PTR_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}


uint8_t EXTI_u8SetTrigSrc(EXTI_TrigSrc_t copy_TrigSrc, EXTI_LineNum copy_PinNum)
{
	uint8_t Local_u8ErrorState = OK;
	switch(copy_TrigSrc)
	{
	case RISING_TRIG:
		EXTI->FTSR &= (~(1<<(copy_PinNum)));
		EXTI->RTSR |= 1<< (copy_PinNum);
		break;
	case FALLING_TRIG:
		EXTI->RTSR &= (~(1<<(copy_PinNum)));
		EXTI->FTSR |= 1<< (copy_PinNum);
		break;
	case FALLING_RISING_TRIG:
		EXTI->RTSR |= 1<< (copy_PinNum);
		EXTI->FTSR |= 1<< (copy_PinNum);
		break;
	default: Local_u8ErrorState = NOK;break;
	}

	return Local_u8ErrorState;
}

uint8_t EXTI_u8EnableInt(EXTI_LineNum copy_line)
{

	uint8_t Local_u8ErrorState = OK;
	if (copy_line <= EXTI_LINE_NUM)
	{
		EXTI->IMR |= (1<<(copy_line));
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;

}


uint8_t EXTI_u8DisableInt(EXTI_LineNum copy_line)
{
	uint8_t Local_u8ErrorState = OK;
	if (copy_line <= EXTI_LINE_NUM)
	{
		EXTI->IMR &= (~(1<<(copy_line)));
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}


uint8_t EXTI_u8ClearPendingFlag(EXTI_LineNum copy_line)
{
	uint8_t Local_u8ErrorState = OK;
	if (copy_line <= EXTI_LINE_NUM)
	{
		EXTI->PR = 1 << copy_line;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}


uint8_t EXTI_u8GetPendingFlag(EXTI_LineNum copy_line, uint8_t* copy_FlagStatus)
{
	uint8_t Local_u8ErrorState = OK;
	if (copy_line <= EXTI_LINE_NUM)
	{
		if (copy_FlagStatus != NULL)
		{
			*copy_FlagStatus = ((EXTI->PR >> copy_line)&1);
		}
		else
		{
			Local_u8ErrorState = NULL_PTR_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;

}


void EXTI0_IRQHandler(void)
{
	EXTI_u8ClearPendingFlag(EXTI_PIN0);
	EXTI_CallBackFunc[EXTI_PIN0]();
}
void EXTI1_IRQHandler(void)
{
	EXTI_u8ClearPendingFlag(EXTI_PIN1);
	EXTI_CallBackFunc[EXTI_PIN1]();
}
void EXTI2_IRQHandler(void)
{
	EXTI_u8ClearPendingFlag(EXTI_PIN2);
	EXTI_CallBackFunc[EXTI_PIN2]();
}
void EXTI3_IRQHandler(void)
{
	EXTI_u8ClearPendingFlag(EXTI_PIN3);
	EXTI_CallBackFunc[EXTI_PIN3]();
}
void EXTI4_IRQHandler(void)
{
	EXTI_u8ClearPendingFlag(EXTI_PIN4);
	EXTI_CallBackFunc[EXTI_PIN4]();
}
void EXTI9_5_IRQHandler(void)
{
	if((((EXTI->PR)>>EXTI_PIN5) & 1) == 1)
	{
		EXTI_u8ClearPendingFlag(EXTI_PIN5);
		EXTI_CallBackFunc[EXTI_PIN5]();
	}
	if((((EXTI->PR)>>EXTI_PIN6) & 1) == 1)
	{
		EXTI_u8ClearPendingFlag(EXTI_PIN6);
		EXTI_CallBackFunc[EXTI_PIN6]();
	}
	if((((EXTI->PR)>>EXTI_PIN7) & 1) == 1)
	{
		EXTI_u8ClearPendingFlag(EXTI_PIN7);
		EXTI_CallBackFunc[EXTI_PIN7]();
	}
	if((((EXTI->PR)>>EXTI_PIN8) & 1) == 1)
	{
		EXTI_u8ClearPendingFlag(EXTI_PIN8);
		EXTI_CallBackFunc[EXTI_PIN8]();
	}
	if((((EXTI->PR)>>EXTI_PIN9) & 1) == 1)
	{
		EXTI_u8ClearPendingFlag(EXTI_PIN9);
		EXTI_CallBackFunc[EXTI_PIN9]();
	}
}
void EXTI15_10_IRQHandler(void)
{
	if((((EXTI->PR)>>EXTI_PIN10) & 1) == 1)
	{
		EXTI_u8ClearPendingFlag(EXTI_PIN10);
		EXTI_CallBackFunc[EXTI_PIN10]();
	}
	if((((EXTI->PR)>>EXTI_PIN11) & 1) == 1)
	{
		EXTI_u8ClearPendingFlag(EXTI_PIN11);
		EXTI_CallBackFunc[EXTI_PIN11]();
	}
	if((((EXTI->PR)>>EXTI_PIN12) & 1) == 1)
	{
		EXTI_u8ClearPendingFlag(EXTI_PIN12);
		EXTI_CallBackFunc[EXTI_PIN12]();
	}
	if((((EXTI->PR)>>EXTI_PIN13) & 1) == 1)
	{
		EXTI_u8ClearPendingFlag(EXTI_PIN13);
		EXTI_CallBackFunc[EXTI_PIN13]();
	}
	if((((EXTI->PR)>>EXTI_PIN14) & 1) == 1)
	{
		EXTI_u8ClearPendingFlag(EXTI_PIN14);
		EXTI_CallBackFunc[EXTI_PIN14]();
	}
	if((((EXTI->PR)>>EXTI_PIN15) & 1) == 1)
	{
		EXTI_u8ClearPendingFlag(EXTI_PIN15);
		EXTI_CallBackFunc[EXTI_PIN15]();
	}
}

