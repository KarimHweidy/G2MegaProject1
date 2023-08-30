#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

#include <stdint.h>

typedef enum{
	OK,ERROR_TIMEOUT,WRONG_OPTION
} EN_CLK_Return_t;

/* used to for Func that set ON or OFF  */
typedef enum {
    CLK_TYPE_HSI=0,
	CLK_TYPE_HSE=1,
    CLK_TYPE_HSEBYP=2,
    CLK_TYPE_PLL=3
} EN_CLKType_t;

/* used for Select the System Source Mux  */
typedef enum {
	SystemSourceMux_HSI,
	SystemSourceMux_HSE,
	SystemSourceMux_PLL_P,
	SystemSourceMux_PLL_R
} EN_SystemSourceMux_t;

typedef enum {
	CLK_STATUS_OFF,
	CLK_STATUS_ON
} EN_CLKStatus_t;

/* PLL Source Mux HSI OR HSE */
typedef enum {
	PLLSRC_HSI,
	PLLSRC_HSE
} EN_PLLSRC_t;

/* PLL input frequency division factor (PLLM) enumeration , 2 ≤ PLLM ≤ 63  */
typedef enum {
    RCC_PLLM_DIV2 = 2,
    RCC_PLLM_DIV3 ,
    RCC_PLLM_DIV4 ,
    RCC_PLLM_DIV5 ,
    RCC_PLLM_DIV6 ,
    RCC_PLLM_DIV7 ,
    RCC_PLLM_DIV8 ,
    RCC_PLLM_DIV9 ,
    RCC_PLLM_DIV10 ,
    RCC_PLLM_DIV11 ,
    RCC_PLLM_DIV12 ,
    RCC_PLLM_DIV13 ,
    RCC_PLLM_DIV14 ,
    RCC_PLLM_DIV15 ,
    RCC_PLLM_DIV16 ,
    RCC_PLLM_DIV17 ,
    RCC_PLLM_DIV18 ,
    RCC_PLLM_DIV19 ,
    RCC_PLLM_DIV20 ,
    RCC_PLLM_DIV21 ,
    RCC_PLLM_DIV22 ,
    RCC_PLLM_DIV23 ,
    RCC_PLLM_DIV24 ,
    RCC_PLLM_DIV25 ,
    RCC_PLLM_DIV26 ,
    RCC_PLLM_DIV27 ,
    RCC_PLLM_DIV28 ,
    RCC_PLLM_DIV29 ,
    RCC_PLLM_DIV30
	/*  to  63*/
} RCC_PLLM_t;

/* PLL multiplication factor (PLLN) enumeration , 50 ≤ PLLN ≤ 432 */
typedef enum {
	RCC_PLLN_MUL50 = 50,
	RCC_PLLN_MUL51,
	RCC_PLLN_MUL52,
	RCC_PLLN_MUL53,
	RCC_PLLN_MUL54,
	RCC_PLLN_MUL55,
	RCC_PLLN_MUL56,
	RCC_PLLN_MUL57,
	RCC_PLLN_MUL58,
	RCC_PLLN_MUL59,
	RCC_PLLN_MUL60,
	RCC_PLLN_MUL61,
	RCC_PLLN_MUL62,
	RCC_PLLN_MUL63,
	RCC_PLLN_MUL64,
	RCC_PLLN_MUL65,
	RCC_PLLN_MUL66,
	RCC_PLLN_MUL67,
	RCC_PLLN_MUL68,
	RCC_PLLN_MUL69,
	RCC_PLLN_MUL70,
	RCC_PLLN_MUL71,
	RCC_PLLN_MUL72,
	RCC_PLLN_MUL73,
	RCC_PLLN_MUL74,
	RCC_PLLN_MUL75,
	RCC_PLLN_MUL76,
	RCC_PLLN_MUL77,
	RCC_PLLN_MUL78,
	RCC_PLLN_MUL79,
	RCC_PLLN_MUL80,
	RCC_PLLN_MUL81,
	RCC_PLLN_MUL82,
	RCC_PLLN_MUL83,
	RCC_PLLN_MUL84,
	RCC_PLLN_MUL85,
	RCC_PLLN_MUL86,
	RCC_PLLN_MUL87,
	RCC_PLLN_MUL88,
	RCC_PLLN_MUL89,
	RCC_PLLN_MUL90,
	RCC_PLLN_MUL91,
	RCC_PLLN_MUL92,
	RCC_PLLN_MUL93,
	RCC_PLLN_MUL94,
	RCC_PLLN_MUL95,
	RCC_PLLN_MUL96,
	RCC_PLLN_MUL97,
	RCC_PLLN_MUL98,
	RCC_PLLN_MUL99,
	RCC_PLLN_MUL100,
	RCC_PLLN_MUL101,
	RCC_PLLN_MUL102,
	RCC_PLLN_MUL103,
	RCC_PLLN_MUL104,
	RCC_PLLN_MUL105,
	RCC_PLLN_MUL106,
	RCC_PLLN_MUL107,
	RCC_PLLN_MUL108,
	RCC_PLLN_MUL109,
	RCC_PLLN_MUL110,
	RCC_PLLN_MUL111,
	RCC_PLLN_MUL112,
	RCC_PLLN_MUL113,
	RCC_PLLN_MUL114,
	RCC_PLLN_MUL115,
	RCC_PLLN_MUL116,
	RCC_PLLN_MUL117,
	RCC_PLLN_MUL118,
	RCC_PLLN_MUL119,
	/*  to  432*/
} RCC_PLLN_t;

/* PLL main division factor (PLLP) enumeration */
typedef enum {
    RCC_PLLP_DIV2 = 0,
    RCC_PLLP_DIV4 ,
    RCC_PLLP_DIV6 ,
    RCC_PLLP_DIV8
} RCC_PLLP_t;

/* PLL general clock output division factor (PLLQ) enumeration , 2 ≤ PLLQ ≤ 15 */
typedef enum {
    RCC_PLLQ_DIV2 = 2,
    RCC_PLLQ_DIV3,
    RCC_PLLQ_DIV4,
    RCC_PLLQ_DIV5,
    RCC_PLLQ_DIV6,
    RCC_PLLQ_DIV7,
    RCC_PLLQ_DIV8,
    RCC_PLLQ_DIV9,
    RCC_PLLQ_DIV10,
    RCC_PLLQ_DIV11,
    RCC_PLLQ_DIV12,
    RCC_PLLQ_DIV13,
    RCC_PLLQ_DIV14,
    RCC_PLLQ_DIV15
} RCC_PLLQ_t;

/* PLLR clock output division factor enumeration , 2 ≤ PLLR ≤ 7 */
typedef enum {
    RCC_PLLR_DIV2 = 2,
    RCC_PLLR_DIV3,
    RCC_PLLR_DIV4,
    RCC_PLLR_DIV5,
    RCC_PLLR_DIV6,
    RCC_PLLR_DIV7
} RCC_PLLR_t;

/* AHB1 Peripherals */
typedef enum {
	AHB1_GPIOA = 0,
	AHB1_GPIOB ,
	AHB1_GPIOC ,
	AHB1_GPIOD ,
	AHB1_GPIOE ,
	AHB1_GPIOF ,
	AHB1_GPIOG ,
	AHB1_GPIOH ,
	AHB1_CRC=12,
	AHB1_BKPSRAM=18,
	AHB1_DMA1=21,
	AHB1_DMA2,
	AHB1_OTGHS=29,
	AHB1_OTGHSULPI
}EN_AHB1_Peripheral_t;

/* AHB2 Peripherals */
typedef enum {
	AHB2_DCMI=0,
	AHB2_OTGFS=7
}EN_AHB2_Peripheral_t;

/* AHB3 Peripherals */
typedef enum {
	AHB3_FMC=0,
	AHB3_QSPI,
}EN_AHB3_Peripheral_t;

/* APB1 Peripherals */
typedef enum {
	APB1_TIM2 =0,
	APB1_TIM3,
	APB1_TIM4,
	APB1_TIM5,
	APB1_TIM6,
	APB1_TIM7,
	APB1_TIM12,
	APB1_TIM13,
	APB1_TIM14,
	APB1_WWDG=11,
	APB1_SPI2=14,
	APB1_SPI3,
	APB1_SPDIFRX,
	APB1_USART2,
	APB1_USART3,
	APB1_UART4,
	APB1_UART5,
	APB1_I2C1,
	APB1_I2C2,
	APB1_I2C3,
	APB1_FMPI2C1,
	APB1_CAN1,
	APB1_CAN2,
	APB1_CEC,
	APB1_PWR,
	APB1_DAC,
}EN_APB1_Peripheral_t;

/* APB2 Peripherals */
typedef enum {
    APB2_TIM1 = 0,
    APB2_TIM8,
    APB2_USART1 = 4,
    APB2_USART6,
    APB2_ADC1 = 8,
    APB2_ADC2,
    APB2_ADC3,
    APB2_SDIO,
    APB2_SPI1,
    APB2_SYSCFG = 14,
    APB2_TIM9 = 16,
    APB2_TIM10,
    APB2_TIM11,
    APB2_SPI4,
    APB2_SPI5,
    APB2_SAI1 = 22,
    APB2_SAI2,
    APB2_DFSDM,
    APB2_LTDC = 26,
    APB2_DSI
} EN_APB2_Peripheral_t;

/***********************************************
 ***************** RCC_CR bits *****************
 ***********************************************/
typedef enum {
	RCC_CR_HSION = 0,
	RCC_CR_HSIRDY,
	RCC_CR_HSITRIM_0=3,
	RCC_CR_HSICAL_0=8,
	RCC_CR_HSEON = 16,
	RCC_CR_HSERDY,
	RCC_CR_HSEBYP,
	RCC_CR_CSSON,
	RCC_CR_PLLON = 24,
	RCC_CR_PLLRDY,
	RCC_CR_PLLI2SON,
	RCC_CR_PLLI2SRDY,
	RCC_CR_PLLSAION,
	RCC_CR_PLLSAIRDY
}EN_RCC_CR_BITS;

/****************************************************
 ***************** RCC_PLLCFGR bits *****************
 ****************************************************/
typedef enum {
	RCC_PLLCFGR_PLLM_0,
	RCC_PLLCFGR_PLLN_0=6,
	RCC_PLLCFGR_PLLP_0=16,
	RCC_PLLCFGR_PLLSRC=22,
	RCC_PLLCFGR_PLLQ_0=24,
	RCC_PLLCFGR_PLLR_0=28
}EN_RCC_PLLCFGR_BITS;

/*************************************************
 ***************** RCC_CFGR bits *****************
 *************************************************/
typedef enum {
	RCC_CFGR_SW_0 = 0,
	RCC_CFGR_SWS_0 = 2,
	RCC_CFGR_HPRE_0 = 4,
	RCC_CFGR_PPRE1_0 = 10,
	RCC_CFGR_PPRE2_0 = 13,
	RCC_CFGR_RTCPRE_0 = 16,
	RCC_CFGR_MCO1_0 = 21,
	RCC_CFGR_MCO1PRE_0 = 24,
	RCC_CFGR_MCO2PRE_0 = 27,
	RCC_CFGR_MCO2_0 = 30
}EN_RCC_CFGR_BITS;



EN_CLK_Return_t RCC_SetClksts( EN_CLKType_t , EN_CLKStatus_t );

void RCC_SetSysClk( EN_SystemSourceMux_t );

void RCC_configure_PLL(RCC_PLLM_t PLL_M, RCC_PLLN_t PLL_N, RCC_PLLP_t PLL_P, RCC_PLLQ_t PLL_Q,EN_PLLSRC_t PLL_SRC, RCC_PLLR_t PLL_R);

void RCC_voidAHB1EnablePeripheralClock( EN_AHB1_Peripheral_t );

void RCC_voidAHB1DisablePeripheralClock( EN_AHB1_Peripheral_t );

void RCC_voidAHB2EnablePeripheralClock( EN_AHB2_Peripheral_t );

void RCC_voidAHB2DisablePeripheralClock( EN_AHB2_Peripheral_t );

void RCC_voidAHB3EnablePeripheralClock( EN_AHB3_Peripheral_t );

void RCC_voidAHB3DisablePeripheralClock( EN_AHB3_Peripheral_t );

void RCC_voidAPB1EnablePeripheralClock( EN_APB1_Peripheral_t );

void RCC_voidAPB1DisablePeripheralClock( EN_APB1_Peripheral_t );

void RCC_voidAPB2EnablePeripheralClock( EN_APB2_Peripheral_t );

void RCC_voidAPB2DisablePeripheralClock( EN_APB2_Peripheral_t );





//void RCC_voidAHB1EnablePeripheralClock(uint8_t peripheral);

#endif