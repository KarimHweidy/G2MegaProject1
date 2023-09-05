#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H

#define NUMOF_LCDPINS 						6
/* commands */
#define LCD_START_LINE_1					0x80
#define LCD_START_LINE_2					0xC0
#define LCD_CLEAR_DISPLAY 					0x01
#define LCD_CURSOR_ON 						0x0E
#define LCD_CURSOR_OFF			 			0x0C
#define LCD_SHIFT_RIGHT 					0x18
#define LCD_SHIFT_LEFT 						0x1C
#define LCD_MOVE_LEFT 						0x10
#define LCD_MOVE_RIGHT 						0x14
#define ENABLE_4BIT_MODE 					0x32
#define LCD_FUNCTION_SET					0x28
#define LCD_ENTRY_MODE_SET 					0x06
#define LCD_DISPLAY_OFF 					0x08
#define LCD_INIT 							0x33
#define HLCD_DISPLAY_ON 					0x0FU


#define RS(x) 								GPIO_u8setpinValue(LCD_RSPORT,LCD_RSPIN,x)
#define EN(x) 								GPIO_u8setpinValue(LCD_ENPORT,LCD_ENPIN,x)
#define D4(x) 								GPIO_u8setpinValue(LCD_DATAPORT,LCD_D4PIN,x)
#define D5(x) 								GPIO_u8setpinValue(LCD_DATAPORT,LCD_D5PIN,x)
#define D6(x) 								GPIO_u8setpinValue(LCD_DATAPORT,LCD_D6PIN,x)
#define D7(x) 								GPIO_u8setpinValue(LCD_DATAPORT,LCD_D7PIN,x)


#endif
