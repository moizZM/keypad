
#define LCD_H_
#include <avr/io.h>
#define F_CPU 1000000UL
#include "util/delay.h"

#define RS 0
#define EN 1

#define TOW_LINES_EIGHT_BIT_MODE 0x38
#define DISPLAY_ON_CURSOR_BLINKING 0x0E
#define CLEAR_DISPLAY_SCREEN 0x01
#define INCREAMENT_CURSOR 0x06
#define FORCE_CURSOR_BEGINNING_FIRST_LINE 0x80

void lcdInit(void);
void lcdCmd(char u8Cmd);
void lcdData(char u8Data);
void lcdPrint(char *str);
