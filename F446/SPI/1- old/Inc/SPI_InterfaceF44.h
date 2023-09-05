#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_



#define SPI_DFF_8BIT										0U
#define SPI_DFF_16BIT										1U
					
#define SPI_DATA_MSB										0U
#define SPI_DATA_LSB										1U
					
#define SPI_SLAVE											0U
#define SPI_MASTER  	              						1U 

#define SPI_POLPHA_NONINVERTING_LEADING						0U
#define SPI_POLPHA_NONINVERTING_TAILLING					1U
#define SPI_POLPHA_INVERTING_LEADING						2U
#define SPI_POLPHA_INVERTING_TAILLING						3U

#define SPI_RATE_FOSC_2   			    					0U
#define SPI_RATE_FOSC_4  			    					1U
#define SPI_RATE_FOSC_8  			    					2U
#define SPI_RATE_FOSC_16 			    					3U
#define SPI_RATE_FOSC_32   			    					4U
#define SPI_RATE_FOSC_64   			    					5U
#define SPI_RATE_FOSC_128  			    					6U
#define SPI_RATE_FOSC_256  			    					7U
  
  
#define SPI_COMMUNI_MODE_FULL_DUPLEX          				0U
#define SPI_COMMUNI_MODE_DATA_TRANSMIT_ONLY   				1U
#define SPI_COMMUNI_MODE_DATA_RECEIVE_ONLY    				2U
#define SPI_COMMUNI_MODE_BIDIRECTIONAL_DATA_WIRE 			3U 

#define SPI_NSS_HW											0U
#define SPI_NSS_SW											1U 
								 
#define SPI_MODE_DISABLED 									0U
#define SPI_MODE_ENABLED									1U

#define SPI_NUM1											0U								 
#define SPI_NUM2 											1U

 
typedef struct 
{
	uint8_t SPI_Num; // SPI1 or SPI2
	uint8_t Mode; // Master or slave
	uint8_t DataSize; // 8-bit or 16 bit 
	uint8_t ClockPolpha; // 
	uint8_t NSS_mode; // SW or HW --> SSM = 0 or 1 
	uint8_t Prescaler; // 2:256
	uint8_t DataOrder; // LSB or MSB
	uint8_t CommunicationMode; // full duplex ,, only trans only receive
	uint8_t Status;  // Enabled or Disabled
}SPI_Config_t;



uint8_t SPI_u8Init( SPI_Config_t* Copy_SPI);

void 	SPI_voidEnableSPI(uint8_t Copy_SPI);
void 	SPI_voidDisableSPI(uint8_t Copy_SPI);
void 	SPI_voidEnableTXInterrupt(uint8_t Copy_SPI);
void 	SPI_voidDisableTXInterrupt(uint8_t Copy_SPI);
void 	SPI_voidEnableRXInterrupt(uint8_t Copy_SPI);
void 	SPI_voidDisableRXInterrupt(uint8_t Copy_SPI);

void	SPI_voidWaitForTXE(uint8_t Copy_SPI);
void 	SPI_voidWaitForRXNE(uint8_t Copy_SPI);
uint8_t SPI1_u8GetBusyFlagSate(uint8_t Copy_SPI);

void 	SPI_voidNSSControlSW(uint8_t Copy_SPI,uint8_t SSI_state);

uint8_t SPI_charTranceive(uint8_t ARG_u8CharData, uint8_t Copy_SPI);

uint8_t SPI_u8SetCallback(void (*ARG_pvoidfUserFunction)(uint8_t Data));


#endif
