#include <stdint.h>
#include "Stm32F446xx.h"

#include "RCC_Private.h"
#include "RCC_Interface.h"
#include "BITMATH.h"



/*****************************************************************************
* Function Name: RCC_SetClksts
* Purpose      : Set the status of any clock Type Enable or Disable
* Parameters   : EN_CLKType_t ClkType to be Set , EN_CLKStatus_t ClkStatus 
* Return value : EN_CLK_Return_t 
*****************************************************************************/
EN_CLK_Return_t RCC_SetClksts( EN_CLKType_t ClkType, EN_CLKStatus_t ClkStatus){
	uint32_t Local_TimeoutAmount = STARTUP_TIMEOUT;
	/* Enable the selected CLK Type  */
	if(ClkStatus == CLK_STATUS_ON )
	{
		switch (ClkType)
		{
		case CLK_TYPE_PLL:
			SETBIT(RCC->CR, RCC_CR_PLLON);
			while(!READBIT(RCC->CR, RCC_CR_PLLRDY) && --Local_TimeoutAmount);
			if( READBIT(RCC->CR, RCC_CR_PLLRDY)==0 ) return ERROR_TIMEOUT; // Not RDY  Error time out
			break;
		case CLK_TYPE_HSEBYP:
		case CLK_TYPE_HSE:
			SETBIT(RCC->CR, RCC_CR_HSEON);
			while(!READBIT(RCC->CR, RCC_CR_HSERDY) && --Local_TimeoutAmount);
			if( READBIT(RCC->CR, RCC_CR_HSERDY)==0 ) return ERROR_TIMEOUT; // Not RDY  Error time out
			/* Enable HSE By Pass in case of CLK_TYPE_HSEBYP */
			if(ClkType == CLK_TYPE_HSEBYP){
				CLRBIT(RCC->CR, RCC_CR_HSEON);  // Disable the HSE oscillator
				SETBIT(RCC->CR,RCC_CR_HSEBYP);  // Configure the HSE oscillator to bypass mode
				SETBIT(RCC->CR, RCC_CR_HSEON);  // Enable the HSE oscillator again
			}
			break;
		case CLK_TYPE_HSI:
			SETBIT(RCC->CR, RCC_CR_HSION);
			while(!READBIT(RCC->CR, RCC_CR_HSIRDY) && --Local_TimeoutAmount);
			if( READBIT(RCC->CR, RCC_CR_HSIRDY)==0 ) return ERROR_TIMEOUT; // Not RDY  Error time out
			break;
		default: return WRONG_OPTION; // Wrong Clk Type option
		}
	}
	/* Enable the selected CLK Type  */
	else if (ClkStatus == CLK_STATUS_OFF){
		switch (ClkType){
		case CLK_TYPE_PLL:
			CLRBIT(RCC->CR, RCC_CR_PLLON);
			while(READBIT(RCC->CR, RCC_CR_PLLRDY));
			break;
		case CLK_TYPE_HSEBYP:
		case CLK_TYPE_HSE:
			CLRBIT(RCC->CR, RCC_CR_HSEON);
			while(READBIT(RCC->CR, RCC_CR_HSERDY));
			break;
		case CLK_TYPE_HSI:
			CLRBIT(RCC->CR, RCC_CR_HSION);
			while(READBIT(RCC->CR, RCC_CR_HSIRDY));
			break;
		default: return WRONG_OPTION; // Wrong Clk Type option
		}
	}
	return OK;
}

/*****************************************************************************
* Function Name: RCC_SetSysClk
* Purpose      : Set the system clock 
* Parameters   : EN_SystemSourceMux_t System_Clk  
* Return value : Void 
*****************************************************************************/
/*  Set the system clock   */
void RCC_SetSysClk( EN_SystemSourceMux_t System_Clk ){
	switch(System_Clk){
	case SystemSourceMux_HSI:
	case SystemSourceMux_HSE:
	case SystemSourceMux_PLL_P:
	case SystemSourceMux_PLL_R:
		RCC->CFGR &= ~RCC_CFGR_SW_MASK; // CLEAR SW bits
		RCC->CFGR |= (System_Clk << RCC_CFGR_SW_0); // set the value
		break;
	default :
		break; // Wrong option
	}
}

/*****************************************************************************
* Function Name: RCC_configure_PLL
* Purpose      : Configure the PLLCFGR Register  
* Parameters   : RCC_PLLM_t , RCC_PLLN_t , RCC_PLLP_t , RCC_PLLQ_t ,
				 EN_PLLSRC_t , RCC_PLLR_t 
* Return value : Void 
*****************************************************************************/
/* NOTE before Configuration of PLL it must be OFF */
void RCC_configure_PLL(RCC_PLLM_t PLL_M, RCC_PLLN_t PLL_N, RCC_PLLP_t PLL_P, RCC_PLLQ_t PLL_Q,EN_PLLSRC_t PLL_SRC, RCC_PLLR_t PLL_R){
	/* Note there is Domain For PLLM , PLLN ... etc */
	/* Clear PLLM PLLN PLLP PLLQ PLLSRC */
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLR_MASK | RCC_PLLCFGR_PLLQ_MASK | RCC_PLLCFGR_PLLSRC_MASK | RCC_PLLCFGR_PLLP_MASK | RCC_PLLCFGR_PLLN_MASK | RCC_PLLCFGR_PLLM_MASK ) ;


	/* Set Modify the RCC_PLLCFGR with value of parameters */
	RCC->PLLCFGR |= ( (PLL_R << RCC_PLLCFGR_PLLR_0) | (PLL_Q << RCC_PLLCFGR_PLLQ_0) | (PLL_SRC << RCC_PLLCFGR_PLLSRC) | (PLL_P << RCC_PLLCFGR_PLLP_0) | (PLL_N << RCC_PLLCFGR_PLLN_0) | (PLL_M << RCC_PLLCFGR_PLLM_0) );
	//CLRBIT(RCC->PLLCFGR,5);
}

/*****************************************************************************
* Function Name: RCC_voidAHB1EnablePeripheralClock
* Purpose      : Enable Any AHB1 Peripheral  
* Parameters   : EN_AHB1_Peripheral_t the peripheral   
* Return value : Void 
*****************************************************************************/
void RCC_voidAHB1EnablePeripheralClock( EN_AHB1_Peripheral_t Peripheral ){
	RCC-> AHB1ENR |= (1<< Peripheral);
}

/*****************************************************************************
* Function Name: RCC_voidAHB1DisablePeripheralClock
* Purpose      : Disable Any AHB1 Peripheral  
* Parameters   : EN_AHB1_Peripheral_t the peripheral   
* Return value : Void 
*****************************************************************************/
void RCC_voidAHB1DisablePeripheralClock( EN_AHB1_Peripheral_t Peripheral){
	RCC-> AHB1ENR &= ~(1<< Peripheral);
}

/*****************************************************************************
* Function Name: RCC_voidAHB2EnablePeripheralClock
* Purpose      : Enable Any AHB2 Peripheral  
* Parameters   : EN_AHB2_Peripheral_t the peripheral   
* Return value : Void 
*****************************************************************************/
void RCC_voidAHB2EnablePeripheralClock( EN_AHB2_Peripheral_t Peripheral){
	RCC-> AHB2ENR |= (1<< Peripheral);
}

/*****************************************************************************
* Function Name: RCC_voidAHB2DisablePeripheralClock
* Purpose      : Disable Any AHB2 Peripheral  
* Parameters   : EN_AHB2_Peripheral_t the peripheral   
* Return value : Void 
*****************************************************************************/
void RCC_voidAHB2DisablePeripheralClock( EN_AHB2_Peripheral_t Peripheral){
	RCC-> AHB2ENR &= ~(1<< Peripheral);
}

/*****************************************************************************
* Function Name: RCC_voidAHB3EnablePeripheralClock
* Purpose      : Enable Any AHB3 Peripheral  
* Parameters   : EN_AHB3_Peripheral_t the peripheral   
* Return value : Void 
*****************************************************************************/
void RCC_voidAHB3EnablePeripheralClock( EN_AHB3_Peripheral_t Peripheral){
	RCC-> AHB3ENR |= (1<< Peripheral);
}

/*****************************************************************************
* Function Name: RCC_voidAHB3DisablePeripheralClock
* Purpose      : Disable Any AHB3 Peripheral  
* Parameters   : EN_AHB3_Peripheral_t the peripheral   
* Return value : Void 
*****************************************************************************/
void RCC_voidAHB3DisablePeripheralClock( EN_AHB3_Peripheral_t Peripheral){
	RCC-> AHB3ENR &= ~(1<< Peripheral);
}

/*****************************************************************************
* Function Name: RCC_voidAPB1EnablePeripheralClock
* Purpose      : Enable Any APB1 Peripheral  
* Parameters   : EN_APB1_Peripheral_t the peripheral   
* Return value : Void 
*****************************************************************************/
void RCC_voidAPB1EnablePeripheralClock( EN_APB1_Peripheral_t Peripheral){
	RCC-> APB1ENR |= (1<< Peripheral);
}

/*****************************************************************************
* Function Name: RCC_voidAPB1DisablePeripheralClock
* Purpose      : Disable Any APB1 Peripheral  
* Parameters   : EN_APB1_Peripheral_t the peripheral   
* Return value : Void 
*****************************************************************************/
void RCC_voidAPB1DisablePeripheralClock( EN_APB1_Peripheral_t Peripheral){
	RCC-> APB1ENR &= ~(1<< Peripheral);
}

/*****************************************************************************
* Function Name: RCC_voidAPB1EnablePeripheralClock
* Purpose      : Enable Any APB2 Peripheral  
* Parameters   : EN_APB2_Peripheral_t the peripheral   
* Return value : Void 
*****************************************************************************/
void RCC_voidAPB2EnablePeripheralClock( EN_APB2_Peripheral_t Peripheral){
	RCC-> APB2ENR |= (1<< Peripheral);
}

/*****************************************************************************
* Function Name: RCC_voidAPB2DisablePeripheralClock
* Purpose      : Disable Any APB2 Peripheral  
* Parameters   : EN_APB2_Peripheral_t the peripheral   
* Return value : Void 
*****************************************************************************/
void RCC_voidAPB2DisablePeripheralClock( EN_APB2_Peripheral_t Peripheral){
	RCC-> APB2ENR &= ~(1<< Peripheral);
}



/*
void RCC_voidAHB1EnablePeripheralClock(EN_AHB1_Peripheral_t peripheral)
{
	RCC-> AHB1ENR |= (1<< peripheral);
}*/
