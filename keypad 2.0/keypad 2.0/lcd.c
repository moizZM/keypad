
#include "lcd.h"
#include <avr/io.h>
#define F_CPU 1000000UL
#include "util/delay.h"

void lcdInit()
{
	DDRA = 0xFF;
	DDRB |= (1 << RS);
	DDRB |= (1 << RS);
	
	PORTB &= ~(1 << EN);
	// sending initialization commands
	lcdCmd(TOW_LINES_EIGHT_BIT_MODE);
	lcdCmd(DISPLAY_ON_CURSOR_BLINKING);
	lcdCmd(CLEAR_DISPLAY_SCREEN);
	lcdCmd(INCREAMENT_CURSOR);
	lcdCmd(FORCE_CURSOR_BEGINNING_FIRST_LINE);
	_delay_ms(2);
}

void enable(){
	PORTB |= (1 << EN);
	_delay_ms(10);
	PORTB &= ~(1 << EN);
	_delay_ms(10);
}

void lcdCmd(char u8Cmd)
{
	PORTB &= ~(1 << RS);
	PORTA = u8Cmd;
	
enable();
}

void lcdData(char u8Data){
	PORTB |= (1 << RS);
	PORTA = u8Data;
	enable();
}

void lcdPrint(char *str)
{
	uint8_t u8Index = 0;
	while(str[u8Index] != '\0')
	{
		lcdData(str[u8Index]);
		u8Index++;
		_delay_ms(30);
	}
}