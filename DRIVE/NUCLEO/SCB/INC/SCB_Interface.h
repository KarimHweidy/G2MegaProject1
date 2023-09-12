/*
 * SCB_Interface.h
 *
 *  Created on: Jul 7, 2023
 *      Author: AhmedMaher
 */

#ifndef SCB_INTERFACE_H_
#define SCB_INTERFACE_H_

/**
 * @brief : Enum For Group Priority & Subpriority
 */
typedef enum
{
	GROUP4SUB0=0x05FA0300,/**< GROUP4SUB0 */
	GROUP3SUB1=0x05FA0400,/**< GROUP3SUB1 */
	GROUP2SUB2=0x05FA0500,/**< GROUP2SUB2 */
	GROUP1SUB3=0x05FA0600,/**< GROUP1SUB3 */
	GROUP0SUB4=0x05FA0700 /**< GROUP0SUB4 */
}PRIORTY_E;


/**
 * @brief : Function To Set Group Priority
 * @pre :
 * @post :
 * @param   GroupPriority
 * @return: LocalErrorStatus
 */
uint8_t SCB_U8SetPriorityGroup(PRIORTY_E GroupPriority);




#endif /* SCB_INTERFACE_H_ */
