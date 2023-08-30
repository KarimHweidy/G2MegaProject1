#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

#include "stm32f446xx.h"
/*
 * Bit position definitions USART_CR1
 */
#define USART_CR1_SBK						0
#define USART_CR1_RWU 						1
#define USART_CR1_RE  						2
#define USART_CR1_TE 						3
#define USART_CR1_IDLEIE 					4
#define USART_CR1_RXNEIE  					5
#define USART_CR1_TCIE						6
#define USART_CR1_TXEIE						7
#define USART_CR1_PEIE 						8
#define USART_CR1_PS 						9
#define USART_CR1_PCE 						10
#define USART_CR1_WAKE  					11
#define USART_CR1_M 						12
#define USART_CR1_UE 						13
#define USART_CR1_OVER8  					15



/*
 * Bit position definitions USART_CR2
 */
#define USART_CR2_ADD   					0
#define USART_CR2_LBDL   					5
#define USART_CR2_LBDIE  					6
#define USART_CR2_LBCL   					8
#define USART_CR2_CPHA   					9
#define USART_CR2_CPOL   					10
#define USART_CR2_CLKEN                     11
#define USART_CR2_STOP   					12
#define USART_CR2_LINEN   					14


/*
 * Bit position definitions USART_CR3
 */
#define USART_CR3_EIE   					0
#define USART_CR3_IREN   					1
#define USART_CR3_IRLP  					2
#define USART_CR3_HDSEL   					3
#define USART_CR3_NACK   					4
#define USART_CR3_SCEN   					5
#define USART_CR3_DMAR  					6
#define USART_CR3_DMAT   					7
#define USART_CR3_RTSE   					8
#define USART_CR3_CTSE   					9
#define USART_CR3_CTSIE   					10
#define USART_CR3_ONEBIT   					11


/*
 * Bit position definitions USART_SR
 */
#define USART_SR_PE        					0
#define USART_SR_FE        					1
#define USART_SR_NE        					2
#define USART_SR_ORE       					3
#define USART_SR_IDLE       				4
#define USART_SR_RXNE        				5
#define USART_SR_TC        					6
#define USART_SR_TXE        				7
#define USART_SR_LBD        				8
#define USART_SR_CTS        				9





/*
 *@USART_Mode
 *Possible options for USART_Mode
 */
typedef enum 
{
	USART_MODE_ONLY_TX,
	USART_MODE_ONLY_RX,
	USART_MODE_TXRX
}USART_Mode_t;

/*
 *@USART_Baud
 *Possible options for USART_Baud
 */
typedef enum{
USART_BAUD_1200 = 1200,
USART_BAUD_2400 = 2400,
USART_BAUD_9600 = 9600,
USART_BAUD_19200 = 19200,
USART_BAUD_38400 = 38400,
USART_BAUD_57600 = 57600,
USART_BAUD_115200 = 115200,
USART_BAUD_230400 =	230400,
USART_BAUD_460800 = 460800,
USART_BAUD_921600 = 921600,
USART_BAUD_2M = 2000000,
SUART_BAUD_3M = 3000000
}USART_BaudeRate_t;

/*
 *@USART_ParityControl
 *Possible options for USART_ParityControl
 */
 typedef enum {
	USART_PARITY_DISABLE=0,
	USART_PARITY_EN_EVEN,
	USART_PARITY_EN_ODD
 }USART_Parity_t;
 
 /*
 *@USART_WordLength
 *Possible options for USART_WordLength
 */
 
 typedef enum{
	USART_WORD_WIDTH_8BITS=0,
	USART_WORD_WIDTH_9BITS
 }USART_WordWidth_t;
 
 /*
 *@USART_NoOfStopBits
 *Possible options for USART_NoOfStopBits
 */
 typedef enum{
USART_STOPBITS_1=0,
USART_STOPBITS_0_5,  				
USART_STOPBITS_2,    				
USART_STOPBITS_1_5
 }USART_StopBits_t;
 
 
 /*
 *@USART_HWFlowControl
 *Possible options for USART_HWFlowControl
 */
 typedef enum{
USART_HW_FLOW_CTRL_NONE = 0,
USART_HW_FLOW_CTRL_CTS,
USART_HW_FLOW_CTRL_RTS,
USART_HW_FLOW_CTRL_CTS_RTS
 }USART_HWFlowControl_t;
 

 /*
 *@USART_SynchMode
 *Possible options for SynchMode
 */
 typedef enum{
	 ASYNCH =0,
     SYNCH 
 }USART_SynchMode_t;
 
 /*
  *@USART_Number
  *Possible options for USARTNumber
  */
 typedef enum{
	 USART_1=0,
	 USART_2,
	 USART_3,
	 UART_4,
	 UART_5,
	 USART_6
 }USART_Number_t;

 /*
   *@USART_Oversampling
   *Possible options for USARTOversampling
   */
 typedef enum
 {
 	USART_OVERSAMPLING_16,
 	USART_OVERSAMPLING_8
 }USART_Oversampling_t;


 /*
 * Configuration structure for USARTx peripheral
 */
typedef struct {
	USART_Mode_t USART_Mode;
	USART_BaudeRate_t USART_Baud;
	USART_StopBits_t USART_NoOfStopBits;
	USART_WordWidth_t USART_WordLength;
	USART_Parity_t USART_ParityControl;
	USART_HWFlowControl_t USART_HWFlowControl;
	USART_SynchMode_t USART_SynchMode;
	USART_Oversampling_t USART_Oversampling;
}USART_Config_t;

/*
 * Handle structure for USARTx peripheral
 */
typedef struct {
	USART_Number_t	 USARTx;
	USART_Config_t   USART_Config;
	uint8_t 		*pTxBuffer;
	uint8_t 		*pRxBuffer;
}USART_Handle_t;
 
 


uint8_t USART_u8Init(USART_Handle_t *pUSARTHandle);
uint8_t USART_u8SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Length);
uint8_t USART_u8ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Length);
uint8_t USART_u8SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate);
uint8_t USART_u8GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName);


#endif
