#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_


/* cause EXTI5_9 only one, also we can check flag into IRQ*/
#if defined(EXTI5_LINE)||defined(EXTI6_LINE)||defined(EXTI7_LINE)||defined(EXTI8_LINE)||defined(EXTI9_LINE)
#define EXTI9_5_LINES_IRQ   9
#endif

#if defined(EXTI10_LINE)||defined(EXTI11_LINE)||defined(EXTI12_LINE)||defined(EXTI13_LINE)||defined(EXTI14_LINE)||defined(EXTI15_LINE)
#define EXTI15_10_LINES_IRQ 15
#endif

#define EXTI_NUM					16U

#endif /* EXTI_PRIVATE_H_ */
