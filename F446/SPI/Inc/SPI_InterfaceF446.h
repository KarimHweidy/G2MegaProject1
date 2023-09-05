#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_


typedef enum
{
    SPI_NUM1 ,
    SPI_NUM2 ,
    SPI_NUM3 ,
    SPI_NUM4 ,
} SPI_Num_t;

typedef enum
{
    SPI_SLAVE = 0,
    SPI_MASTER

} SPI_Mode_t;

typedef enum
{
    SPI_DFF_1BYTE = 0,
    SPI_DFF_2BYTE,
} SPI_DATA_SIZE_t;

typedef enum
{
    SPI_POLPHA_NONINVERTING_LEADING	,	
    SPI_POLPHA_NONINVERTING_TAILLING,	
	SPI_POLPHA_INVERTING_LEADING	,	
    SPI_POLPHA_INVERTING_TAILLING	,	
} SPI_CPOLPHA_t;

typedef enum
{
    SPI_NSS_HW_MANAGE,
    SPI_NSS_SW_MANAGE,
} SPI_SLAVE_MANAGEMENT_t;

typedef enum
{
    SPI_PERIPH_CLK_BY2   ,
    SPI_PERIPH_CLK_BY4   ,
    SPI_PERIPH_CLK_BY8   ,
    SPI_PERIPH_CLK_BY16  ,
    SPI_PERIPH_CLK_BY32  ,
    SPI_PERIPH_CLK_BY64  ,
    SPI_PERIPH_CLK_BY128 ,
    SPI_PERIPH_CLK_BY256 ,
} SPI_PRESCALER_t;

typedef enum
{
    SPI_MSB_FIRST = 0,
    SPI_LSB_FIRST,
} SPI_DIRECTION_t;

typedef enum
{
    SPI_COMMUNI_MODE_FULL_DUPLEX          	 ,
    SPI_COMMUNI_MODE_DATA_TRANSMIT_ONLY   	 ,
    SPI_COMMUNI_MODE_DATA_RECEIVE_ONLY    	 ,
    SPI_COMMUNI_MODE_BIDIRECTIONAL_DATA_WIRE ,
    
} SPI_COMMUNICATION_Mode_t;

typedef enum
{
    SPI_SLAVE_SELECTED = 0,
    SPI_SLAVE_NOT_SELECTED,
} SPI_SW_SLAVE_STATUS_t;

typedef enum
{
    SPI_IT_DISABLED = 0,
    SPI_IT_ENABLED,
} SPI_IT_STATUS_t;

typedef enum
{
    SPI_SS_OUT_DIS = 0,
    SPI_SS_OUT_EN,

} SPI_SS_OTYPE_t;

typedef enum
{
    SPI_FLAG_RESET = 0,
    SPI_FLAG_SET = 1,

} SPI_FLAG_STATUS_t;

typedef enum
{
    SPI_RECEIVE_BUFFER_NE_FLAG ,
    SPI_TRANSMIT_BUFFER_E_FLAG ,
    SPI_UNDERRUN_FLAG,
    SPI_CRC_ERROR_FLAG ,
    SPI_MODE_FAULT_FLAG ,
    SPI_OVERRUN_FLAG ,
    SPI_BUSY_FLAG ,
    SPI_FRAME_ERROR_FLAG ,

} SPI_FLAG_t; 


typedef struct
{
    SPI_FLAG_STATUS_t RXNE;
    SPI_FLAG_STATUS_t TXE;
    SPI_FLAG_STATUS_t ERR;
} SPI_IT_ENABLE_t;

 
typedef struct 
{
	SPI_Num_t 					SPI_Num; // SPI1 or SPI2
	SPI_Mode_t 					Mode; // Master or slave
	SPI_DATA_SIZE_t 			DataSize; // 8-bit or 16 bit 
	SPI_CPOLPHA_t				ClockPolpha; // 
	SPI_SLAVE_MANAGEMENT_t  	NSS_mode; // SW or HW --> SSM = 0 or 1 
	SPI_PRESCALER_t 			Prescaler; // 2:256
	SPI_DIRECTION_t 		 	DataOrder; // LSB or MSB
	SPI_COMMUNICATION_Mode_t 	CommunicationMode; // full duplex ,, only trans only receive
	SPI_SS_OTYPE_t 				SSOE_Type;
	SPI_IT_ENABLE_t 			InterruptEnable;
	// uint8_t Status;  // Enabled or Disabled
	
}SPI_Config_t;



uint8_t SPI_u8Init( SPI_Config_t* Copy_SPI);

SPI_FLAG_STATUS_t 	SPI_u8ReadFlag(SPI_Num_t  Copy_SPI, SPI_FLAG_t  Flag);
void 				SPI_voidWaitUntilFlagSet(SPI_Num_t SPINum, SPI_FLAG_t Flag);
void 				SPI_voidNSSControlSW(SPI_Num_t Copy_SPI,SPI_SW_SLAVE_STATUS_t SSI_State);

uint8_t 	SPI_u8TransceiveData(SPI_Config_t *Copy_SPI, uint16_t *ReceivedData, uint16_t DataToSend);
uint8_t 	SPI_u8TransceiveBuffer(SPI_Config_t *Copy_SPI, uint8_t *ReceviedBuffer, uint8_t *BufferToSend, uint16_t BufferSize);

uint8_t 	SPI_u8TransceiveData_IT(SPI_Config_t *Copy_SPI, uint16_t *ReceivedData, uint16_t *DataToSend, void(*ARG_pvoidfUserFunction)(void));
uint8_t 	SPI_u8TransceiveBuffer_IT(SPI_Config_t *Copy_SPI, uint8_t *ReceivedBuffer, uint8_t *BufferToSend, uint16_t BufferSize, void (*ARG_pvoidfUserFunction)(void));





#endif
