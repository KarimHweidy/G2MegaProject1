#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

#include "SPI_Interface.h"

typedef enum {
    CPHA_BIT = 0,
    CPOL_BIT,
    MSTR_BIT,
    BR_0_BIT,
    SPE_BIT=6,
    LSB_BIT,
    SSI_BIT,
    SSM_BIT,
	RX_ONLY_BIT,
    DFF_BIT,
	CRC_NEXT_BIT,
    CRC_EN_BIT,
    BIDI_OE_BIT,
    BIDI_MODE_BIT
} EN_CR1Bits_t;

typedef enum {
    RXDMAEN_BIT = 0,
    TXDMAEN_BIT,
    SSOE_BIT,
    Res1,
    Res2,
    ERRIE_BIT,
    RXNEIE_BIT,
    TXEIE_BIT
} EN_CR2Bits_t ;

typedef enum {
    RXNE_BIT = 0,
    TXE_BIT,
    CHSIDE_BIT,
    UDR_BIT,
    CRCERR_BIT,
    MODF_BIT,
	OVR_BIT,
	BSY_BIT,
}EN_SRBits_t;

typedef enum
{
    SPI_IT_TXE ,
    SPI_IT_RXNE,
    SPI_IT_ERR ,
    SPI_IT_MAX_NUM ,
} SPI_IT_SRC_t;


typedef enum
{
    SPI_NO_IRQ_SRC ,
    SPI_TRANSCEIVE_DATA_IRQ_SRC ,
    SPI_TRANSCEIVE_BUFFER_IRQ_SRC , 
} SPI_IRQ_SRC_t;

typedef enum
{
    SPI_ROLE_TRANSMIT ,
    SPI_ROLE_RECEIVE ,
} SPI_ROLE_DIR_t;



#define SPI_MAX_NUM    						4
#define SPI_BUFFER_SIZE_NOT_REACHED	 		0
#define SPI_BUFFER_SIZE_REACHED 			1

static uint8_t SPI_HANDLE_IT(SPI_Num_t SPINumber);


#endif
