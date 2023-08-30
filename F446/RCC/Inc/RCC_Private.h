/*
 * RCC_Private.h
 *
 *  Created on: May 3, 2023
 *      Author: DELL
 */

#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

#define STARTUP_TIMEOUT          	5000 // val for time out

#define RCC_BASE_ADDRESS          	0x40023800 // RCC Base address

/* RCC Registers Reset values*/
#define RCC_CR_RESETVAL           	0x00000083
#define RCC_PLLCFGR_RESETVAL      	0x24003010
#define RCC_CFGR_RESETVAL      		0x00000000
#define RCC_AHB1ENR_RESETVAL      	0x00000000
#define RCC_AHB2ENR_RESETVAL      	0x00000000
#define RCC_AHB3ENR_RESETVAL      	0x00000000
#define RCC_APB1ENR_RESETVAL      	0x00000000
#define RCC_APB2ENR_RESETVAL      	0x00000000
#define RCC_AHB1LPENR_RESETVAL      0x606790FF

//the default value for HSI TRIM	(0x0F<<RCC_CR_HSITRIM_0)   ~  will be 0F0
#define RCC_HSITRIM_RESETVAL      	(0x0FU << RCC_CR_HSITRIM_0)  // when take complement 0b10000 --> 16

/* PLL VCO frequency calculation macro */
#define RCC_PLL_VCO_FREQ(f_pll_in, pll_n, pll_m) 	((f_pll_in) * (pll_n) / (pll_m))
/* PLL general clock output frequency calculation macro */
#define RCC_PLL_GENCLK_FREQ(vco_freq, pll_p) 		((vco_freq) / (pll_p))
/* USB OTG FS and SDIO clock frequency calculation macro */
#define RCC_OTGFS_SDIO_FREQ(vco_freq, pll_q) 		((vco_freq) / (pll_q))


/********** RCC_PLLCFGR register masks *********/
#define RCC_PLLCFGR_PLLM_MASK  		(0x3FU << RCC_PLLCFGR_PLLM_0) 		// << 0
#define RCC_PLLCFGR_PLLN_MASK  		(0x1FFU << RCC_PLLCFGR_PLLN_0) 		// << 6
#define RCC_PLLCFGR_PLLP_MASK  		(0x03U << RCC_PLLCFGR_PLLP_0)		// << 16
#define RCC_PLLCFGR_PLLSRC_MASK  	(0x1U << RCC_PLLCFGR_PLLSRC)		// << 22
#define RCC_PLLCFGR_PLLQ_MASK  		(0x0FU << RCC_PLLCFGR_PLLQ_0)		// << 24
#define RCC_PLLCFGR_PLLR_MASK  		(0x07U << RCC_PLLCFGR_PLLR_0)		// << 28


/* RCC_CFGR register masks */
#define RCC_CFGR_SW_MASK 			(0x3U << RCC_CFGR_SW_0)				// << 0
#define RCC_CFGR_SWS_MASK 			(0x3U << RCC_CFGR_SWS_0)			// << 2
#define RCC_CFGR_HPRE_MASK 			(0xFU << RCC_CFGR_HPRE_0)			// << 4
#define RCC_CFGR_PPRE1_MASK 		(0x7U << RCC_CFGR_PPRE1_0)			// << 10
#define RCC_CFGR_PPRE2_MASK 		(0x7U << RCC_CFGR_PPRE2_0)			// << 13
#define RCC_CFGR_RTCPRE_MASK 		(0x1FU << RCC_CFGR_RTCPRE_0)		// << 16
#define RCC_CFGR_MCO1_MASK 			(0x3U << RCC_CFGR_MCO1_0)			// << 21
#define RCC_CFGR_MCO1PRE_MASK 		(0x7U << RCC_CFGR_MCO1PRE_0)		// << 24
#define RCC_CFGR_MCO2PRE_MASK 		(0x7U << RCC_CFGR_MCO2PRE_0)		// << 27
#define RCC_CFGR_MCO2_MASK 			(0x3U << RCC_CFGR_MCO1_0)			// << 30



#endif /* RCC_PRIVATE_H_ */
