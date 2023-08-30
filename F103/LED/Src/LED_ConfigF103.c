#include "LED_Private.h"
#include "LED_Interface.h"
#include "GPIO_Interface.h"

/* config LED one */
LED_t LEDGreen=
{
.LedPort = LED_GPORT,
.LedPin  = LED_GPIN,
.LedMode = LED_GMODE,
.conn_type=LED_SourceConnnec,
};

/* config LED one */
LED_t LEDRed=
{
.LedPort = LED_RPORT,
.LedPin  = LED_RPIN,
.LedMode = LED_RMODE,
.conn_type=LED_SourceConnnec,
};

