#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_

#define IRQ_REGSIZE				32U
#define IRQ_PIRSIZE				4U
#define IRQ_SETBIT				1U
#define IRQ_BITMASK				1U
#define IRQ_SHIFTBITS			4U

#define AIRCR_MASK              0xFFFF0700
#define AIRCR_VECTKEY			0x5FA
#define VECTKEY_SHIFTBITS		16U
#define AIRCR_RESET				0xFA050000


#define PRIGROUP_SHIFTBITS		8U


#endif
