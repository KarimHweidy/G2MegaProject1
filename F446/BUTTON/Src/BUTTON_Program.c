#include "GPIO_Interface.h"
#include "BUTTON_Private.h"
#include "BUTTON_Interface.h"

void Button_Init(Port_t BUT_Port,PinNum_t BUT_Pin,PullUpDown_t BUT_PUPD)
{
    GPIO_PinConfig_t Button_Pin;

    /* GPIO Ports Clock Enable */
	/* .....  */
    /*Configure GPIO pin : PA0 */
    Button_Pin.Port=BUT_Port;
	Button_Pin.Pin = BUT_Pin;
    Button_Pin.Mode = INPUT;
    Button_Pin.PullType = BUT_PUPD;
    
    GPIO_u8PinInit(&Button_Pin);
}

uint8_t Button_u8Read(Port_t BUT_Port,PinNum_t BUT_Pin)
{
	uint8_t button_val;
	GPIO_u8ReadpinValue(BUT_Port,BUT_Pin,&button_val);
    return button_val;
}
