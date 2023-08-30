#ifndef _DMA_PRIVATE_H_
#define _DMA_PRIVATE_H_


#define STREAMS_NUM    8
#define CHANNELS_NUM   8
#define INTERRUPTS_NUM 6

typedef enum
{
  EN = 0,      // DMA stream enable
  DMEIE,   // Direct mode error interrupt enable
  TEIE ,    // Transfer error interrupt enable
  HTIE ,    // Half transfer interrupt enable
  TCIE ,    // Transfer complete interrupt enable
  PFCTRL,  // Peripheral flow controller
  DIR ,    // Data transfer direction
  CIRC = 8,    // Circular mode
  PINC  ,  // Peripheral increment mode
  MINC  ,  // Memory increment mode
  PSIZE ,  // Peripheral data size
  MSIZE = 13,  // Memory data size
  PINCOS = 15, // Peripheral increment offset size
  PL = 16,     // Priority level
  DBM = 18,    // Double buffer mode  HINT: This bit can be written only if EN = 0
  CT = 19,     // Current target (only in double buffer mode) HINT: This bit can be written only if EN = 0
  PBURST = 21, // Peripheral burst transfer configuration
  MBURST = 23, // Memory burst transfer configuration
  CHSEL = 25,  // Channel selection
} DMA_SCR_BITS_t;

#define NDT  		0 // Number of data items to transfer
//#define PA_R  		0 // Peripheral address
#define M0A  		0 // Memory 0 address
#define M1A  		0 // Memory 0 address

#define FTH  		0   // FIFO threshold selection
#define DMDIS 		2 // Direct mode disable
#define FS 			3    // FIFO status
#define FEIE 		7  // FIFO error interrupt enable

#define FourBitMask	 		0b1111
#define ThreeBitMask	 	0b111
#define TwoBitMask	 		0b11
#define OneBitMask	 		0b1


#endif
