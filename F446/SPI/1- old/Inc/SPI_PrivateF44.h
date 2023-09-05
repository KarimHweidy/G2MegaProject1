#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

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
    FRF_BIT,
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
	FRE_BIT,
}EN_SRBits_t;

#endif