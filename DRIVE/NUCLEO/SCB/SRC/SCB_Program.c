/*
 * SCB_Program.c
 *
 *  Created on: Jul 7, 2023
 *      Author: AhmedMaher
 */
#include <stdio.h>
#include <stdlib.h>
#include "ERR_TYPE.h"
#include "STM32F446xx.h"
#include "SCB_Private.h"
#include "SCB_Interface.h"



/**
 * @brief : Function To Set Group Priority
 * @pre :
 * @post :
 * @param   GroupPriority
 * @return: LocalErrorStatus
 */
uint8_t SCB_U8SetPriorityGroup(PRIORTY_E GroupPriority)
{

	uint8_t LocalErrorState = OK;

	SCB_AIRCR=GroupPriority;


	return LocalErrorState ;

}

