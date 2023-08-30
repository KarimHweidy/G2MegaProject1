#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

/*
 * USART flags
 */
#define USART_FLAG_TXE 						(1 << USART_SR_TXE)
#define USART_FLAG_RXNE 					(1 << USART_SR_RXNE)
#define USART_FLAG_TC 						(1 << USART_SR_TC)


#define USART_NUM            6u



#define USART_FLAG_TXE 						(1 << USART_SR_TXE)
#define USART_FLAG_RXNE 					(1 << USART_SR_RXNE)
#define USART_FLAG_TC 						(1 << USART_SR_TC)


#define FLAG_SET           1u
#define FLAG_RESET         0u


#endif
