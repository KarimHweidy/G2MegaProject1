#include "Stm32F103xx.h"
#include "BITMATH.h"
#include "ERRORTYPE.h"
#include <stdint.h>

#include "SPI_Private.h"
#include "SPI_Interface.h"


/* SPI Peripherals Base Addresses */
static SPI_RegDef_t *ArrSPI[SPI_MAX_NUM] = {SPI_1, SPI_2 };

/* SPI Interrupt Pointers to Functions */
static void (*SPI_PTR_TO_FUNC[SPI_MAX_NUM][SPI_IT_MAX_NUM])(void) = {NULL};

/* SPI Transceive Data To Be Received To Use In ISR */
static uint16_t *SPI_TransceiveDataToBeReceived[SPI_MAX_NUM] = {NULL};

/* SPI Transceive Buffer To Be Received To Use In ISR */
static uint8_t *SPI_TransceiveBufferToBeReceived[SPI_MAX_NUM] = {NULL};

/* SPI Transceive Buffer To Be Sent To Use In ISR */
static uint8_t *SPI_TransceiveBufferToBeSent[SPI_MAX_NUM] = {NULL};

/* SPI Transceive Buffer Size To Use In ISR */
static uint16_t SPI_TransceiveBufferSize[SPI_MAX_NUM] = {0};

/* SPI Transceive Buffer Node Role To Check On In ISR */
/* SPI_MASTER or SPI_SLAVE */
static SPI_Mode_t SPI_TransceiveBufferNodeRole[SPI_MAX_NUM] = {0};

/* SPI Transceive Buffer Role Direction To Check On In ISR */
/* SPI_ROLE_TRANSMIT or SPI_ROLE_RECEIVE */
static SPI_ROLE_DIR_t SPI_TransceiveBufferRoleDirection[SPI_MAX_NUM] = {0};

/* SPI IRQ Sources To Use In ISR */
/* SPI_NO_IRQ_SRC or SPI_TRANSCEIVE_DATA_IRQ_SRC or SPI_TRANSCEIVE_BUFFER_IRQ_SRC */
static SPI_IRQ_SRC_t IRQ_SRC[SPI_MAX_NUM] = {SPI_NO_IRQ_SRC};

uint8_t SPI_u8Init( SPI_Config_t* Copy_SPI)
{
	uint8_t Local_u8StateError=OK;
	/*Make sure  the peripheral is disabled*/
	CLRBIT(ArrSPI[Copy_SPI->SPI_Num]->CR1,SPE_BIT);

	if ( NULL != Copy_SPI)
    {
        /* Set The BaudRate */
        /* For Master Role Only */
        if (Copy_SPI->Mode == SPI_MASTER)
        {
            ArrSPI[Copy_SPI->SPI_Num]->CR1 &= ~(0b11<<BR_0_BIT);
            ArrSPI[Copy_SPI->SPI_Num]->CR1 |= (Copy_SPI->Prescaler << BR_0_BIT);
        }
		
        /* Set Clock Polarity & Clock Phase*/
        ArrSPI[Copy_SPI->SPI_Num]->CR1 &= (~(0b11 << CPHA_BIT));
		ArrSPI[Copy_SPI->SPI_Num]->CR1 |= (Copy_SPI->ClockPolpha<< CPHA_BIT);
		
		/* set communication mode */
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
	
        /* Set Direction */
        ArrSPI[Copy_SPI->SPI_Num]->CR1 &= ~(1 << LSB_BIT);
        ArrSPI[Copy_SPI->SPI_Num]->CR1 |= ( Copy_SPI->DataOrder <<LSB_BIT);
		
        /* For Slave Only */
        if (Copy_SPI->Mode == SPI_SLAVE)
        {
            ArrSPI[Copy_SPI->SPI_Num]->CR1 &= (~(1 << MSTR_BIT));
            ArrSPI[Copy_SPI->SPI_Num]->CR1 |= (Copy_SPI->NSS_mode << MSTR_BIT);
        }

        /* Set Mode */
        ArrSPI[Copy_SPI->SPI_Num]->CR1 &= (~(1 << MSTR_BIT));
        ArrSPI[Copy_SPI->SPI_Num]->CR1 |= (Copy_SPI->Mode << MSTR_BIT);

        /* Set The Data Width */
        ArrSPI[Copy_SPI->SPI_Num]->CR1 &= (~(1 << DFF_BIT));
        ArrSPI[Copy_SPI->SPI_Num]->CR1 |= (Copy_SPI->DataSize << DFF_BIT ) ;

        /* Set Slave Select Output Type */
        /* For Master Only */
        if (Copy_SPI->Mode == SPI_MASTER)
        {
            ArrSPI[Copy_SPI->SPI_Num]->CR2 &= (~(1 << SSOE_BIT));
            ArrSPI[Copy_SPI->SPI_Num]->CR2 |= (Copy_SPI->SSOE_Type << SSOE_BIT);
        }

        /* SPI Interrupts */
		/* Set Tx Buffer Empty Interrupt */
        ArrSPI[Copy_SPI->SPI_Num]->CR2 &= (~(1 << TXEIE_BIT));
        ArrSPI[Copy_SPI->SPI_Num]->CR2 |= (Copy_SPI->InterruptEnable.TXE << TXEIE_BIT);

        /* Set Rx Buffer Not Empty Interrupt */
        ArrSPI[Copy_SPI->SPI_Num]->CR2 &= (~(1 << RXNEIE_BIT));
        ArrSPI[Copy_SPI->SPI_Num]->CR2 |= (Copy_SPI->InterruptEnable.RXNE << RXNEIE_BIT);

        /* Set Error Interrupt */
        ArrSPI[Copy_SPI->SPI_Num]->CR2 &= (~(1 << ERRIE_BIT));
        ArrSPI[Copy_SPI->SPI_Num]->CR2 |= (Copy_SPI->InterruptEnable.ERR << ERRIE_BIT);
	
        /* Enable SPI Peripheral */
        ArrSPI[Copy_SPI->SPI_Num]->CR1 |= (1 << SPE_BIT);
    }
    else
    {
    	Local_u8StateError = NOK;
    }

	return Local_u8StateError;
}

SPI_FLAG_STATUS_t SPI_u8ReadFlag(SPI_Num_t Copy_SPI, SPI_FLAG_t Flag)
{
	return ((ArrSPI[Copy_SPI]->SR >> Flag) & 0x01);
}

void SPI_voidWaitUntilFlagSet(SPI_Num_t SPINum, SPI_FLAG_t Flag)
{
    SPI_FLAG_STATUS_t Local_u8FlagState = SPI_FLAG_RESET;
    while (SPI_FLAG_SET != Local_u8FlagState)
    {
    	Local_u8FlagState=SPI_u8ReadFlag(SPINum, Flag);
    }
}

void SPI_voidNSSControlSW(SPI_Num_t Copy_SPI,SPI_SW_SLAVE_STATUS_t state)
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

uint8_t SPI_u8TransceiveData(SPI_Config_t *Copy_SPI, uint16_t *ReceivedData, uint16_t DataToSend)
{
	uint8_t Local_u8StateError=OK;
    if(NULL == ReceivedData || NULL == Copy_SPI)
	{
		Local_u8StateError=NULL_POINTER_ERR;
	}
	else
	{
		/* Sending Data is Required */
		/* Wait Until The Transmit Buffer is Empty */
		SPI_voidWaitUntilFlagSet(Copy_SPI->SPI_Num, SPI_TRANSMIT_BUFFER_E_FLAG);
	
		/* Both Master & Slave Can Send Data */
		ArrSPI[Copy_SPI->SPI_Num]->DR = DataToSend;
		
		/* Receiving Data is Required */  
		/* Wait Until The Receive Buffer is Not Empty */
		SPI_voidWaitUntilFlagSet(Copy_SPI->SPI_Num, SPI_RECEIVE_BUFFER_NE_FLAG);
	
		/* Read Received Data */
		*ReceivedData = ArrSPI[Copy_SPI->SPI_Num]->DR;
    }
    return Local_u8StateError;
}


uint8_t SPI_u8TransceiveBuffer(SPI_Config_t *Copy_SPI, uint8_t *ReceviedBuffer, uint8_t *BufferToSend, uint16_t BufferSize)
{
    uint8_t Local_u8StateError=OK;

    uint16_t Local_u16Counter = 0;

    if( NULL == BufferToSend || NULL == ReceviedBuffer || NULL == Copy_SPI)
	{
		Local_u8StateError=NULL_POINTER_ERR;
	}
    else
    {
        /* Correct Parameters */

        for (Local_u16Counter = 0; Local_u16Counter < BufferSize; Local_u16Counter++)
        {
            SPI_u8TransceiveData(Copy_SPI, (uint16_t *)&ReceviedBuffer[Local_u16Counter], (uint16_t )BufferToSend[Local_u16Counter]);
        }
    }
    return Local_u8StateError;
}


uint8_t SPI_u8TransceiveData_IT(SPI_Config_t *Copy_SPI, uint16_t *ReceivedData, uint16_t *DataToSend, void(*ARG_pvoidfUserFunction)(void))
{
    uint8_t Local_u8StateError = OK;

	if (ARG_pvoidfUserFunction != NULL)
	{
		/* Setting IRQ Source */
		IRQ_SRC[Copy_SPI->SPI_Num] = SPI_TRANSCEIVE_DATA_IRQ_SRC;
	
		/* Set The Call Back Function */
		SPI_PTR_TO_FUNC[Copy_SPI->SPI_Num][SPI_IT_RXNE] = ARG_pvoidfUserFunction;
	
		/* Receive Data is Required */
		if (ReceivedData != NULL)
		{
			/* Set Received Data Globally */
			SPI_TransceiveDataToBeReceived[Copy_SPI->SPI_Num] = ReceivedData;
	
			/* Master Can't Receive Data , So Send Any Value to Initiate Communication */
			if (Copy_SPI->Mode == SPI_MASTER)
			{
				/* Wait Until The Transmit Buffer is Empty */
				SPI_voidWaitUntilFlagSet(Copy_SPI->SPI_Num, SPI_TRANSMIT_BUFFER_E_FLAG);
	
				/* Sending Data is Required */
				if (DataToSend != NULL)
				{
					/* Both Master & Slave Can Send Data */
					/* Send Data */
					ArrSPI[Copy_SPI->SPI_Num]->DR = *DataToSend;
				}
				else
				{
					/* Send Any Value to Initiate Communication */
					ArrSPI[Copy_SPI->SPI_Num]->DR = 0xFF;
				}
				/* Enable Rx Buffer Not Empty Interrupt */
				ArrSPI[Copy_SPI->SPI_Num]->CR2 |= (1 << RXNEIE_BIT);
			}
			else if (Copy_SPI->Mode == SPI_SLAVE)
			{
				/* Enable Rx Buffer Not Empty Interrupt */
				ArrSPI[Copy_SPI->SPI_Num]->CR2 |= (1 << RXNEIE_BIT);
			}
			/* Both Master & Slave Can Receive Data By Enabling Rx Buffer Not Empty Interrupt */
		}
//		/* Sending Data is Required */
//		if (DataToSend != NULL)
//		{
//			/* Both Master & Slave Can Send Data */
//			/* Send Data */
//			ArrSPI[Copy_SPI->SPI_Num]->DR = *DataToSend;
//
//			/* Enable Rx Buffer Not Empty Interrupt */
//			ArrSPI[Copy_SPI->SPI_Num]->CR2 |= (1 << RXNEIE_BIT);
//		}
	}
	else
	{
		Local_u8StateError = NULL_POINTER_ERR;
	}
	
    return Local_u8StateError;
}


uint8_t SPI_u8TransceiveBuffer_IT(SPI_Config_t *Copy_SPI, uint8_t *ReceivedBuffer, uint8_t *BufferToSend, uint16_t BufferSize, void (*ARG_pvoidfUserFunction)(void))
{
    uint8_t Local_u8StateError = OK;

    /* Correct Parameters */
    /* Set IRQ Source */
    IRQ_SRC[Copy_SPI->SPI_Num] = SPI_TRANSCEIVE_BUFFER_IRQ_SRC;
 
    /* Set Call Back Function */
    SPI_PTR_TO_FUNC[Copy_SPI->SPI_Num][SPI_IT_RXNE] = ARG_pvoidfUserFunction;
 
    /* Set Buffer Size Globally */
    SPI_TransceiveBufferSize[Copy_SPI->SPI_Num] = BufferSize;
 
    /* Receive Buffer is Required */
    if (NULL != ReceivedBuffer)
    {
        /* Set Direction Globally */
        SPI_TransceiveBufferRoleDirection[Copy_SPI->SPI_Num] = SPI_ROLE_RECEIVE;
 
        /* Set ReceivedBuffer Globally */
        SPI_TransceiveBufferToBeReceived[Copy_SPI->SPI_Num] = ReceivedBuffer;
 
        /* Check on The Node Role */
        if (Copy_SPI->Mode == SPI_SLAVE)
        {
            /* Set Role Globally */
            SPI_TransceiveBufferNodeRole[Copy_SPI->SPI_Num] = SPI_SLAVE;
 
            /* Enable Receive Buffer Not Empty Interrupt */
            ArrSPI[Copy_SPI->SPI_Num]->CR2 |= (1 << RXNEIE_BIT);
        }
        else if (Copy_SPI->Mode == SPI_MASTER)
        {
            /* Set Role Globally */
            SPI_TransceiveBufferNodeRole[Copy_SPI->SPI_Num] = SPI_MASTER;
 
            /* Wait Until The Transmit Buffer is Empty */
            SPI_voidWaitUntilFlagSet(Copy_SPI->SPI_Num, SPI_TRANSMIT_BUFFER_E_FLAG);
 
            /* Send Any Value to Initiate Communication */
            ArrSPI[Copy_SPI->SPI_Num]->DR = 0xFF;
 
            /* Enable Receive Buffer Not Empty Interrupt */
            ArrSPI[Copy_SPI->SPI_Num]->CR2 |= (1 << RXNEIE_BIT);
        }
    }
    else{
    	Local_u8StateError=NULL_POINTER_ERR;
    }
 
    /* Sending Buffer is Required */
    if (BufferToSend != NULL)
    {
        /* Set Direction Globally */
        SPI_TransceiveBufferRoleDirection[Copy_SPI->SPI_Num] = SPI_ROLE_TRANSMIT;
 
        /* Set Buffer To Send Globally */
        SPI_TransceiveBufferToBeSent[Copy_SPI->SPI_Num] = BufferToSend;
 
        /* wait Until The Transmit Buffer is Empty */
        SPI_voidWaitUntilFlagSet(Copy_SPI->SPI_Num, SPI_TRANSMIT_BUFFER_E_FLAG);
 
        /* Send First Data Item */
        ArrSPI[Copy_SPI->SPI_Num]->DR = SPI_TransceiveBufferToBeSent[Copy_SPI->SPI_Num][0];
 
        /* Enable Receive Buffer Not Empty Interrupt */
        ArrSPI[Copy_SPI->SPI_Num]->CR2 |= (1 << RXNEIE_BIT);
    }
 
    return Local_u8StateError;
}


static uint8_t SPI_HANDLE_IT(SPI_Num_t SPINumber)
{
    uint8_t Local_u8ErrorStatus = OK;
    /* IF The IRQ Source is Transceive Data */
    if (IRQ_SRC[SPINumber] == SPI_TRANSCEIVE_DATA_IRQ_SRC)
    {
        /* Clear IRQ Source */
//        IRQ_SRC[SPINumber] = SPI_NO_IRQ_SRC;

        /* Reading is Required Only */
        /* Read the Received Data */
        if (SPI_TransceiveDataToBeReceived[SPINumber] != NULL)
        {
            *(SPI_TransceiveDataToBeReceived[SPINumber]) = ArrSPI[SPINumber]->DR;
        }

        /* Disable  Rx Buffer Not Empty Interrupt */
//        ArrSPI[SPINumber]->CR2 &= (~(1 << RXNEIE_BIT));

        /* Invoke Call Back Function */
        if (SPI_PTR_TO_FUNC[SPINumber][SPI_IT_RXNE] != NULL)
        {
            SPI_PTR_TO_FUNC[SPINumber][SPI_IT_RXNE]();
        }
    }

    /* IF The IRQ Source is Transceive Buffer */
    else if (IRQ_SRC[SPINumber] == SPI_TRANSCEIVE_BUFFER_IRQ_SRC)
    {
        /* Variable to Indicate if The Buffer Size is Reached or Not */
        static uint8_t BufferSizeReached = SPI_BUFFER_SIZE_NOT_REACHED;

        /* Counter to Indicate The Number of Data Sent or Received For Slave Role */
        static uint16_t TransmitCounterSlave = 1;
        static uint16_t ReceiveCounterSlave = 0;

        /* Counter to Indicate The Number of Data Sent or Received For Master Role */
        static uint16_t TransmitCounterMaster = 1;
        static uint16_t ReceiveCounterMaster = 0;

        switch (SPI_TransceiveBufferNodeRole[SPINumber])
        {
        case SPI_SLAVE:

            /* Slave is Transmitter */
            if (SPI_TransceiveBufferRoleDirection[SPINumber] == SPI_ROLE_TRANSMIT)
            {

                /* if Buffer Size is Reached */
                if (TransmitCounterSlave == SPI_TransceiveBufferSize[SPINumber])
                {
                    BufferSizeReached = SPI_BUFFER_SIZE_REACHED;
                    /* Reset Counter */
                    TransmitCounterSlave = 1;
                }
                else
                {
                    /* Send Next Data */
                    ArrSPI[SPINumber]->DR = SPI_TransceiveBufferToBeSent[SPINumber][TransmitCounterSlave++];
                }
            }
            /* Slave is Receiver */
            else if (SPI_TransceiveBufferRoleDirection[SPINumber] == SPI_ROLE_RECEIVE)
            {

                /* Receive the Data */
                SPI_TransceiveBufferToBeReceived[SPINumber][ReceiveCounterSlave++] = ArrSPI[SPINumber]->DR;

                /* if Buffer Size is Reached */
                if (ReceiveCounterSlave == SPI_TransceiveBufferSize[SPINumber])
                {
                    BufferSizeReached = SPI_BUFFER_SIZE_REACHED;
                    /* Reset Counter */
                    ReceiveCounterSlave = 0;
                }
            }

            break;

        case SPI_MASTER:

            /* Master is Transmitter */
            if (SPI_TransceiveBufferRoleDirection[SPINumber] == SPI_ROLE_TRANSMIT)
            {
                if (TransmitCounterMaster == SPI_TransceiveBufferSize[SPINumber])
                {
                    BufferSizeReached = SPI_BUFFER_SIZE_REACHED;
                    /* Reset Counter */
                    TransmitCounterMaster = 1;
                }
                else
                {
                    /* Send Next Data */
                    ArrSPI[SPINumber]->DR = SPI_TransceiveBufferToBeSent[SPINumber][TransmitCounterMaster++];
                }
            }
            /* Master is Receiver */
            else if (SPI_TransceiveBufferRoleDirection[SPINumber] == SPI_ROLE_RECEIVE)
            {

                /* Receive the Data */
                SPI_TransceiveBufferToBeReceived[SPINumber][ReceiveCounterMaster++] = ArrSPI[SPINumber]->DR;

                if (ReceiveCounterMaster == SPI_TransceiveBufferSize[SPINumber])
                {
                    BufferSizeReached = SPI_BUFFER_SIZE_REACHED;
                    /* Reset Counter */
                    ReceiveCounterMaster = 0;
                }
                else
                {
                    /* Send Any Value to Initiate Communication */
                    ArrSPI[SPINumber]->DR = 0xFF;
                }
            }
            break;
        }
        /* If Buffer Size is Reached  , Disable Rx Buffer Not Empty Interrupt & Invoke Call Back Function */
        if (BufferSizeReached == SPI_BUFFER_SIZE_REACHED)
        {

            /* Clear IRQ Source */
            IRQ_SRC[SPINumber] = SPI_NO_IRQ_SRC;

            /* Disable  Rx Buffer Not Empty Interrupt */
            ArrSPI[SPINumber]->CR2 &= (~(1 << RXNEIE_BIT));

            /* Invoke Call Back Function */
            if (SPI_PTR_TO_FUNC[SPINumber][SPI_IT_RXNE] != NULL)
            {
                SPI_PTR_TO_FUNC[SPINumber][SPI_IT_RXNE]();
            }
            /* Reset Variables*/
            BufferSizeReached = SPI_BUFFER_SIZE_NOT_REACHED;
        }
    }

    return Local_u8ErrorStatus;
}

/* SPI1 Interrupt Handler */
void SPI1_IRQHandler(void)
{
    SPI_HANDLE_IT(SPI_NUM1);
}
