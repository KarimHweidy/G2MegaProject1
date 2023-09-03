#include <stdint.h>
#include "stm32f446xx.h"
#include "ErrorType.h"

#include "SYSCFG_interface.h"
#include "SYSCFG_prv.h"


void SYSCFG_voidSetEXTIPort( SYSCFG_LineNum copy_PinNum, SYSCFG_Port_t copy_port)
{
	uint8_t Local_u8RegisterNum = copy_PinNum / EXTIS_INSIDE_CR_REG;
	uint8_t Local_u8BitNum = (copy_PinNum % EXTIS_INSIDE_CR_REG) * EXTIS_INSIDE_CR_REG;
	SYSCFG->CR[Local_u8RegisterNum] &= (~(REQUIRED_BITS_MASK<<Local_u8BitNum)); /*clear the required 4 bits */
	SYSCFG->CR[Local_u8RegisterNum] |= (copy_port << Local_u8BitNum); /*Set the port number value*/
}
