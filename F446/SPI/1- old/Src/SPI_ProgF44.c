#include "Stm32F446xx.h"
#include "BITMATH.h"
#include "ERRORTYPE.h"
#include <stdint.h>

#include "SPI_Private.h"
#include "SPI_Interface.h"


static SPI_RegDef_t * ArrSPI[2]= {SPI_1,SPI_2};

static volatile void(*pvoidfCallBack)(uint8_t Data);


uint8_t SPI_u8Init( SPI_Config_t* Copy_SPI)
{
	uint8_t Local_u8StateError=OK;
	/*Make sure  the peripheral is disabled*/
	CLRBIT(ArrSPI[Copy_SPI->SPI_Num]->CR1,SPE_BIT);

	/* Common configurations */ 
	ArrSPI[Copy_SPI->SPI_Num]->CR1 =0x00;    // clear   					// DFF common
	ArrSPI[Copy_SPI->SPI_Num]->CR1 |= (Copy_SPI->ClockPolpha << CPHA_BIT ) | (Copy_SPI->DataSize << DFF_BIT ) | ( Copy_SPI->DataOrder <<LSB_BIT) | ( Copy_SPI->NSS_mode << SSM_BIT); 
	
	if( SPI_COMMUNI_MODE_FULL_DUPLEX==Copy_SPI->CommunicationMode || SPI_COMMUNI_MODE_DATA_TRANSMIT_ONLY==Copy_SPI->CommunicationMode)
	{
		/* In full-duplex (BIDIMODE=0 and RXONLY=0)  */
		CLRBIT(ArrSPI[Copy_SPI->SPI_Num]->CR1,BIDI_MODE_BIT); // Clear BIDMODE bit
		CLRBIT(ArrSPI[Copy_SPI->SPI_Num]->CR1,RX_ONLY_BIT); // Clear RXONLY  bit
	}
	else if ( SPI_COMMUNI_MODE_DATA_RECEIVE_ONLY == Copy_SPI->CommunicationMode )
	{
		CLRBIT(ArrSPI[Copy_SPI->SPI_Num]->CR1,BIDI_MODE_BIT); // Clear BIDMODE bit
		SETBIT(ArrSPI[Copy_SPI->SPI_Num]->CR1,RX_ONLY_BIT); // Set RXONLY  bit
	}
	else if( SPI_COMMUNI_MODE_BIDIRECTIONAL_DATA_WIRE == Copy_SPI->CommunicationMode)
	{
		SETBIT(ArrSPI[Copy_SPI->SPI_Num]->CR1,BIDI_MODE_BIT); // Sets BIDMODE bit
	}
	
	/* Configuration depend on MCu mode */
	if(SPI_MASTER == Copy_SPI->Mode )
	{
		/*Master mode configurations*/
		//ArrSPI[Copy_SPI->SPI_Num]->CR1 &= ~(0xFF); // clear   				
		/* set prescaler enable master bit set SSM  */
		ArrSPI[Copy_SPI->SPI_Num]->CR1 |= (Copy_SPI->Prescaler << BR_0_BIT ) | ( 1 <<MSTR_BIT) ;
		//SETBIT(ArrSPI[Copy_SPI->SPI_Num]->CR1, SSI_BIT); //SSI  -- NSS using SW

		/* if master and SSM = 0 HW then we can use SSOE auto trigger we can add if condition here */
		if( Copy_SPI->NSS_mode == 0)
		{
			SETBIT(ArrSPI[Copy_SPI->SPI_Num]->CR2, SSOE_BIT); //SSOE
		}
	}
	else 
	{
		/*Slave mode configurations*/
		CLRBIT(ArrSPI[Copy_SPI->SPI_Num]->CR1,MSTR_BIT); // Clear MSTR  bit
		//CLRBIT(ArrSPI[Copy_SPI->SPI_Num]->CR1,SSI_BIT); // Clear SSI  bit

	}
	/* Start Mode of the peripheral*/
	ArrSPI[Copy_SPI->SPI_Num]->CR1 |= (Copy_SPI->Status << SPE_BIT ); // start mode enabled or disabled

	return Local_u8StateError;
}


void SPI_voidEnableSPI(uint8_t Copy_SPI)
{
    // Enable the SPI peripheral
    SETBIT(ArrSPI[Copy_SPI]->CR1, SPE_BIT);
	
}

void SPI_voidDisableSPI(uint8_t Copy_SPI)
{
	SPI_voidWaitForTXE(Copy_SPI); // TXNE =1
	while( GETBIT(ArrSPI[Copy_SPI]->SR , BSY_BIT) ); // BSY = 0 must to disable
	
    // Disable the SPI peripheral
    CLRBIT(ArrSPI[Copy_SPI]->CR1, SPE_BIT);
}

void SPI_voidEnableTXInterrupt(uint8_t Copy_SPI)
{   
	// Enable TXE interrupt
    SETBIT(ArrSPI[Copy_SPI]->CR2, TXEIE_BIT);
}

void SPI_voidDisableTXInterrupt(uint8_t Copy_SPI)
{
	// Disable TXE interrupt 
    CLRBIT(ArrSPI[Copy_SPI]->CR2, TXEIE_BIT);
}

void SPI_voidEnableRXInterrupt(uint8_t Copy_SPI)
{   
	// Enable RXNE interrupt
    SETBIT(ArrSPI[Copy_SPI]->CR2, RXNEIE_BIT);
}

void SPI_voidDisableRXInterrupt(uint8_t Copy_SPI)
{
	// Disable RXNE interrupt
    CLRBIT(ArrSPI[Copy_SPI]->CR2, RXNEIE_BIT);
}

uint8_t SPI_u8SetCallback(void (*ARG_pvoidfUserFunction)(uint8_t Data))
{
	uint8_t Local_u8StateError=OK;
	if( NULL !=ARG_pvoidfUserFunction) 
	{
		pvoidfCallBack= ARG_pvoidfUserFunction;
	}
	else
	{
		Local_u8StateError=NOK;
	}
    return Local_u8StateError;
}

void SPI_voidWaitForTXE(uint8_t Copy_SPI)
{
    while ( !GETBIT(ArrSPI[Copy_SPI]->SR , TXE_BIT) );
}

void SPI_voidWaitForRXNE(uint8_t Copy_SPI)
{
    while ( !GETBIT(ArrSPI[Copy_SPI]->SR , RXNE_BIT) );
}

uint8_t SPI1_u8GetBusyFlagSate(uint8_t Copy_SPI)
{
	return GETBIT(ArrSPI[Copy_SPI]->SR, BSY_BIT);
}

void SPI_voidNSSControlSW(uint8_t Copy_SPI,uint8_t state)
{
  if (1== state )
  {
    // SSI bits
    SETBIT(ArrSPI[Copy_SPI]->CR1, SSI_BIT);
  }
  else
  {
    // Clear SSI bit
    CLRBIT(ArrSPI[Copy_SPI]->CR1, SSI_BIT);
  }
}

uint8_t SPI_charTranceive(uint8_t ARG_u8CharData, uint8_t Copy_SPI)
{
	uint8_t L_u8DataReceived=0;
    
	// Wait for the transmit buffer to be empty
    SPI_voidWaitForTXE(Copy_SPI);
    // Write data to the data register
    ArrSPI[Copy_SPI]->DR = ARG_u8CharData;
    
    // Wait for the receive buffer to be full
    SPI_voidWaitForRXNE(Copy_SPI);
	// Read received data from the data register
	L_u8DataReceived = ArrSPI[Copy_SPI]->DR;
    
    return L_u8DataReceived;
}

void SPI1_IRQHandler()
{
	pvoidfCallBack(SPI_1->DR); // Pass DR value as parameter
	
}
