#include <stdint.h>
#include "stm32f446xx.h"
#include "ErrorType.h"

#include "USART_interface.h"
#include "USART_private.h"

static USART_RegDef_t *USARTNUM[USART_NUM] = {USART1,USART2,USART3,UٍART4,USART5,USART6};

uint8_t USART_u8Init(USART_Handle_t *pUSARTHandle)
{
	uint8_t Local_u8ErrorState = OK;
	if(pUSARTHandle != NULL)
	{
	uint32_t tempreg = 0;


	//Configuration of CR1
	// enable USART
	tempreg |= (1<<USART_CR1_UE);

	//Enable USART Tx and Rx engines according to the USART_Mode configuration item
	if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
	{
		//Implement the code to enable the Receiver bit field
		tempreg|= (1 << USART_CR1_RE);
	}
	else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX) {
		//Implement the code to enable the Transmitter bit field
		tempreg |= (1 << USART_CR1_TE);
	}
	else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX) {
		//Implement the code to enable the both Transmitter and Receiver bit fields
		tempreg |= ((1 << USART_CR1_RE) | (1 << USART_CR1_TE));
	}
	//Implement the code to configure the Word length configuration item
	tempreg |= (pUSARTHandle->USART_Config.USART_WordLength) << USART_CR1_M ;

	//Configuration of parity control bit fields
	if ( pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN) {
		//Implement the code to enale the parity control
		tempreg |= (1 << USART_CR1_PCE);

		//Implement the code to enable EVEN parity
		//Not required because by default EVEN parity will be selected once you enable the parity control
	}
	else if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD ) {
		//Implement the code to enable the parity control
		tempreg |= (1 << USART_CR1_PCE);

		//Implement the code to enable ODD parity
		tempreg |= (1 << USART_CR1_PS);
	}

	//Implement the code to configure the over sampling configuration item
	tempreg |= (pUSARTHandle->USART_Config.USART_Oversampling) << USART_CR1_OVER8;

	//Program the CR1 register
	USARTNUM[pUSARTHandle->USARTx]->CR1 = tempreg;

	//Configuration of CR2
	tempreg = 0;

	//Implement the code to configure the number of stop bits inserted during USART frame transmission
	tempreg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP;

	//Implement the code to configure weather the peripheral Work as Sycnh or Asynch
    tempreg |= pUSARTHandle->USART_Config.USART_SynchMode << USART_CR2_CLKEN;

	//Program the CR2 register
    USARTNUM[pUSARTHandle->USARTx]->CR2 = tempreg;

	//Configuration of CR3
	tempreg=0;

	//Configuration of USART hardware flow control
	if ( pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS) {
		//Implement the code to enable CTS flow control
		tempreg |= (1 << USART_CR3_CTSE);
	}
	else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS) {
		//Implement the code to enable RTS flow control
		tempreg |= (1 << USART_CR3_RTSE);
	}
	else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS) {
		//Implement the code to enable both CTS and RTS Flow control
		tempreg |= ((1 << USART_CR3_CTSE) | (1 << USART_CR3_RTSE));
	}

	USARTNUM[pUSARTHandle->USARTx]->CR3 = tempreg;

	//Implement the code to configure the baud rate
	USART_u8SetBaudRate(USARTNUM[pUSARTHandle->USARTx], pUSARTHandle->USART_Config.USART_Baud);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}


/* @fn				- USART_SendData
 * @brief			- This function send data
 * @param[in]		- Base address of the USART peripheral
 * @param[in]		- buffer when transmit data
 * @param[in]		- Data length
 * @return			- ERROR STATE
 */
uint8_t USART_u8SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Length)
{

	uint8_t Local_u8ErrorState = OK;

	if((pUSARTHandle != NULL) && (pTxBuffer != NULL))
	{
	uint16_t *pdata;
   //Loop over until "Length" number of bytes are transferred
	for (uint32_t i = 0; i < Length; i++) {
		//Implement the code to wait until TXE flag is set in the SR
		while(!USART_u8GetFlagStatus(USARTNUM[pUSARTHandle->USARTx], USART_FLAG_TXE));

         //Check the USART_WordLength item for 9BIT or 8BIT in a frame
		if (pUSARTHandle->USART_Config.USART_WordLength == USART_WORD_WIDTH_9BITS ) {
			//if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits
			pdata = (uint16_t*)pTxBuffer;
			USARTNUM[pUSARTHandle->USARTx]->DR = (*pdata & (uint16_t)0x01FF);

			//check for USART_ParityControl
			if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE) {
				//No parity is used in this transfer. 9bits of user data will be sent
				//Implement the code to increment pTxBuffer twice
				pTxBuffer++;
				pTxBuffer++;
			}
			else {
				//Parity bit is used in this transfer. 8bits of user data will be sent
				//The 9th bit will be replaced by parity bit by the hardware
				pTxBuffer++;
			}
		}
		else {
			//This is 8bit data transfer
			USARTNUM[pUSARTHandle->USARTx]->DR = (*pTxBuffer  & (uint8_t)0xFF);

			//Implement the code to increment the buffer address
			pTxBuffer++;
		}
	}

	//Implement the code to wait till TC flag is set in the SR
	while(!USART_u8GetFlagStatus(USARTNUM[pUSARTHandle->USARTx], USART_FLAG_TC));
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;

	}
	return Local_u8ErrorState;
}


/* @fn				- USART_ReceiveData
 * @brief			- This function receive data
 * @param[in]		- Base address of the USART peripheral
 * @param[in]		- buffer when receive data
 * @param[in]		- Data length
 * @return			- Error state
 */
uint8_t USART_u8ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Length)
{


	uint8_t Local_u8Errorstate =OK;
	if((pUSARTHandle != NULL) && (pRxBuffer != NULL))
	{

   //Loop over until "Length" number of bytes are transferred
	for (uint32_t i = 0 ; i < Length; i++)
	{
		//Implement the code to wait until RXNE flag is set in the SR
		while(!USART_u8GetFlagStatus(USARTNUM[pUSARTHandle->USARTx], USART_FLAG_RXNE));

		//Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
		if (pUSARTHandle->USART_Config.USART_WordLength == USART_WORD_WIDTH_9BITS) {
			//We are going to receive 9bit data in a frame
			//check are we using USART_ParityControl control or not
			if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE) {
				//No parity is used. All 9bits will be of user data
				//read only first 9 bits. so, mask the DR with 0x01FF
				*((uint16_t*) pRxBuffer) = (USARTNUM[pUSARTHandle->USARTx]->DR  & (uint16_t)0x01FF);

				//Now increment the pRxBuffer two times
				pRxBuffer++;
				pRxBuffer++;
			}
			else {
				//Parity is used, 8bits will be of user data and 1 bit is parity
				 *pRxBuffer = (USARTNUM[pUSARTHandle->USARTx]->DR  & (uint8_t)0xFF);

				 //Increment the pRxBuffer
				 pRxBuffer++;
			}
		}
		else {
			//We are going to receive 8bit data in a frame
			//check are we using USART_ParityControl control or not
			if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE) {
				//No parity is used, so all 8bits will be of user data
				//read 8 bits from DR
				 *pRxBuffer = (uint8_t) (USARTNUM[pUSARTHandle->USARTx]->DR  & (uint8_t)0xFF);
			}
			else {
				//Parity is used, 7 bits will be of user data and 1 bit is parity
				//read only 7 bits, hence mask the DR with 0X7F
				 *pRxBuffer = (uint8_t) (USARTNUM[pUSARTHandle->USARTx]->DR  & (uint8_t)0x7F);
			}

			//increment the pRxBuffer
			pRxBuffer++;
		}
	}
	}
	else
	{
		Local_u8Errorstate = NULL_PTR_ERR;
	}
	return Local_u8Errorstate;

}


uint8_t USART_u8SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{
	
	#define UART_DIV_SAMPLING8(_PCLK_, _BAUD_)             ((uint32_t)((((uint64_t)(_PCLK_))*25U)/(2U*((uint64_t)(_BAUD_)))))
#define UART_DIVMANT_SAMPLING8(_PCLK_, _BAUD_)         (UART_DIV_SAMPLING8((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING8(_PCLK_, _BAUD_)         ((((UART_DIV_SAMPLING8((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) * 100U)) * 8U)\
                                                         + 50U) / 100U)
/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + ((UART DIVFRAQ & 0xF8) << 1) + (UART DIVFRAQ & 0x07U) */
#define UART_BRR_SAMPLING8(_PCLK_, _BAUD_)             ((UART_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) << 4U) + \
                                                        ((UART_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0xF8U) << 1U) + \
                                                        (UART_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0x07U))

	
	
	
	UART_BRR_SAMPLING8(42000000U,115200);
	uint8_t Local_u8ErrorState = OK;
	if (pUSARTx != NULL)
	{
		//Variable to hold the APB clock
			uint32_t PCLKx;

			uint32_t usartdiv;

			//variables to hold Mantissa and Fraction values
			uint32_t M_part, F_part;

			uint32_t tempreg=0;
			  //Get the value of APB bus clock in to the variable PCLKx
				 if (pUSARTx == USART1 || pUSARTx == USART6) {
					   //USART1 and USART6 are hanging on APB2 bus
					   PCLKx = 90000000u;
				  }
				  else {
					   PCLKx = 45000000u;
				  }
					// 24.414 
				  //Check for OVER8 configuration bit
				  if (pUSARTx->CR1 & (1 << USART_CR1_OVER8)) {
					   //OVER8 = 1 , over sampling by 8
					   usartdiv = ((25 * PCLKx) / (2 *BaudRate));
				  }
				  else {
					   //Over sampling by 16
					  usartdiv = ((25 * PCLKx) / (4 *BaudRate));
				  }

				  //Calculate the Mantissa part
				  M_part = usartdiv/100;

				  //Place the Mantissa part in appropriate bit position. refer USART_BRR
				  tempreg |= M_part << 4;

				  //Extract the fraction part
				  F_part = (usartdiv - (M_part * 100));

				  //Calculate the final fractional
				  if (pUSARTx->CR1 & ( 1 << USART_CR1_OVER8)) {
					  //OVER8 = 1 , over sampling by 8
					  F_part = ((( F_part * 8)+ 50) / 100)& ((uint8_t)0x07);
				  }
				  else {
					   //over sampling by 16
					   F_part = ((( F_part * 16)+ 50) / 100) & ((uint8_t)0x0F);
				   }

				  //Place the fractional part in appropriate bit position . refer USART_BRR
				  tempreg |= F_part;

				  //copy the value of tempreg in to BRR register
				//  pUSARTx->BRR = tempreg;
				pUSARTx->BRR = ( 11 <<0 ) | ( 8<<4 ); //for 16Mhz same as HSI  

	}
	else
	{
	Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;


}


uint8_t USART_u8GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName)
{
	if (pUSARTx->SR & StatusFlagName) {
		return FLAG_SET;
	}
	return FLAG_RESET;
}

