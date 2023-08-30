#include "Stm32F446xx.h"
#include "BITMATH.h"
#include "ERRORTYPE.h"
#include <stdint.h>

#include <stdint.h>
#include "SYSCFG_Interface.h"
#include "SYSCFG_Private.h"


uint8_t SYSCFG_u8SelEXTI_Line(SYSCFG_NUM_t Copy_PinNum,SYSCFG_Port_t Copy_Port){
	
	uint8_t Local_ErrorState=OK;
	if(EXTI_PIN22 >= Copy_PinNum )
	{
		Local_ErrorState=NOK;
	}
	else{
		/*Choose The Port to Have the EXTI*/
		uint8_t Local_u8IntCnfgReg =  Copy_PinNum/ SYSCFG_REGISTER_SELECTOR;
		uint8_t Local_u8IntCnfgBit = (Copy_PinNum % SYSCFG_Bit_SELECTOR) * SYSCFG_Bit_SELECTOR;
		
		SYSCFG->EXTICR[Local_u8IntCnfgReg] &= ~(EXTI_PORT_MASK<<Local_u8IntCnfgBit);
		SYSCFG->EXTICR[Local_u8IntCnfgReg] |= (Copy_Port<<Local_u8IntCnfgBit);
	}
	
	return Local_ErrorState;
}
