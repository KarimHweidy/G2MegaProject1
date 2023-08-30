#include <stdint.h>
#include "Stm32F446xx.h"
#include "ErrorType.h"

#include "NVIC_interface.h"
#include "NVIC_prv.h"



uint8_t NVIC_u8Enable( NVIC_IRQ_t IRQ_NUM )
{
	uint8_t Local_u8ErrorState = OK;
	uint8_t Local_u8RegNum;
	uint8_t Local_u8BitNum;
	if (IRQ_NUM <= FMPI2C1_error)
	{
		Local_u8RegNum = IRQ_NUM / 32;
		Local_u8BitNum = IRQ_NUM % 32;
		NVIC -> ISER[Local_u8RegNum] = (1 << Local_u8BitNum);

	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}




uint8_t NVIC_u8Disable(NVIC_IRQ_t IRQ_NUM)
{
	uint8_t Local_u8ErrorState = OK;
	uint8_t Local_u8RegNum;
	uint8_t Local_u8BitNum;
	if (IRQ_NUM <= FMPI2C1_error)
	{
		Local_u8RegNum = IRQ_NUM / 32;
		Local_u8BitNum = IRQ_NUM % 32;
		NVIC -> ICER[Local_u8RegNum] = (1 << Local_u8BitNum);

	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}



uint8_t NVIC_u8SetPending(NVIC_IRQ_t IRQ_NUM)
{
	uint8_t Local_u8ErrorState = OK;
	uint8_t Local_u8RegNum;
	uint8_t Local_u8BitNum;
	if (IRQ_NUM <= FMPI2C1_error)
	{
		Local_u8RegNum = IRQ_NUM / 32;
		Local_u8BitNum = IRQ_NUM % 32;
		NVIC -> ISPR[Local_u8RegNum] = (1 << Local_u8BitNum);

	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;

}



uint8_t NVIC_u8ClearPending(NVIC_IRQ_t IRQ_NUM)
{
	uint8_t Local_u8ErrorState = OK;
	uint8_t Local_u8RegNum;
	uint8_t Local_u8BitNum;
	if (IRQ_NUM <= FMPI2C1_error)
	{
		Local_u8RegNum = IRQ_NUM / 32;
		Local_u8BitNum = IRQ_NUM % 32;
		NVIC -> ICPR[Local_u8RegNum] = (1 << Local_u8BitNum);

	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;

}


uint8_t NVIC_u8GitActiveFlag(NVIC_IRQ_t IRQ_NUM, uint32_t* ActiveFlag)
{
	uint8_t Local_u8ErrorState = OK;
	uint8_t Local_u8RegNum;
	uint8_t Local_u8BitNum;
	if (IRQ_NUM <= FMPI2C1_error)
	{
		Local_u8RegNum = IRQ_NUM / 32;
		Local_u8BitNum = IRQ_NUM % 32;
		*ActiveFlag = 1 & ((NVIC -> ICPR[Local_u8RegNum]) >> Local_u8BitNum);

	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;

}


/*Function to Set priority Group options 1- SixteenGroups_OneSub
 *                                       2- EightGroups_TwoSubs
 *                                       3- FourGroups_FourSubs
 *                                       4- TwoGroups_EightSubs
 *                                       5- OneGroup_SixteenSubs */

uint8_t SCB_u8SetPeriorityGroup(SCB_PRGROUP_t PriorityGroup)
{
	uint8_t Local_u8ErrorState = OK;
	if (( PriorityGroup == SixteenGroups_OneSub ) || ( PriorityGroup == EightGroups_TwoSubs ) || ( PriorityGroup == FourGroups_FourSubs ) || ( PriorityGroup == TwoGroups_EightSubs ) || ( PriorityGroup == OneGroup_SixteenSubs ))
	{
		SCB -> AIRCR = PriorityGroup;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}



/*Function to Set priority Level of IRQ, options from Level_0 to Level_15 */


uint8_t NVIC_u8IRQPeriority(NVIC_IRQ_t IRQ_NUM, NVIC_PRLEVELS_t PriorityLevel)
{
	uint8_t Local_u8ErrorState = OK;
	if ((IRQ_NUM <= FMPI2C1_error) && (PriorityLevel <= Level_15))
	{
		NVIC -> IPR[IRQ_NUM]= PriorityLevel << PRIORITY_UNIMPLEMENTED_BITS;   /*PRIORITY_UNIMPLEMENTED_BITS is the first 4 bits of priority bits which not implemented by Stm*/
	}
	else
	{
		Local_u8ErrorState = NOK;

	}
	return Local_u8ErrorState;
}
