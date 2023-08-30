#include "LED_Private.h"
#include "LED_Interface.h"
#include "GPIO_Interface.h"

/* config LED one */
LED_t LEDOne=
{
.LedPin.Port=PORTA,
.LedPin.Pin=PIN5,
.LedPin.Mode=LED_MODE,
.LedPin.speed=LED_SPEED,
.LedPin.OutputType= LED_OUTPTYPE,
.LedPin.PullType= LED_PULLTYPE,
.conn_type=LED_SourceConnnec,
};
