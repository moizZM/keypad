#include <avr/io.h>
#define F_CPU 1000000UL
#include "util/delay.h"
#include "utility.h"
#include "lcd.h"


int main(void)
{
	lcdInit();
	lcdPrint("press a key");
	
	unsigned char butn;
	unsigned char malik[4][4] ={{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}};
	
	for (int i=4; i<8;i++) //output
	{
		DDRC |= (1 << i);
		PORTC &= ~(1 << i);
	}
	for (int j=0; j<4;j++) //input
	{
		DDRC &= ~(1 << j);
		PORTC |= (1 << j);
	}
	DDRA = 0xFF;
	
	
	
	while (1)
	{
		
		
		if(gpio_read_pin(PORTC_ID, 0) == 1 && gpio_read_pin(PORTC_ID, 1) ==1 && gpio_read_pin(PORTC_ID, 2) == 1 && gpio_read_pin(PORTC_ID, 3) == 1){
			PORTA = 0x00;
		}
		else
		{
			for (int j=0; j<4;j++) // read status of colums pins
			{
				
				if ((PINC & (1 << j ))==0)
				{
					butn = j;
				}
			}
			PORTC &= ~(1 << 4);
			PORTC |= (1 << 5);
			PORTC |= (1 << 6);
			PORTC |= (1 << 7);
			if ((gpio_read_pin(PORTC_ID,butn))==1)
			{
				PORTC |= (1 << 4);
				PORTC &= ~(1 << 5);
				PORTC |= (1 << 6);
				PORTC |= (1 << 7);
				if ((gpio_read_pin(PORTC_ID,butn))==1)
				{
					PORTC |= (1 << 4);
					PORTC |= (1 << 5);
					PORTC &= ~(1 << 6);
					PORTC |= (1 << 7);
					if ((gpio_read_pin(PORTC_ID,butn))==1)
					{
						PORTC |= (1 << 4);
						PORTC |= (1 << 5);
						PORTC |= (1 << 6);
						PORTC &= ~(1 << 7);
						if ((gpio_read_pin(PORTC_ID,butn))==1)
						{
							PORTA = 0x00;
						}
						else {
							lcdCmd(0x01);
							lcdCmd(0x0E);
							if (((PINC & (1 << 7))==0 ) && ((PINC & (1 << butn))==0 ))
							{
								lcdPrint("malik4");
								_delay_ms(10);
							}
							
							for (int i =4; i<8;i++)
							{
								PORTC &= ~(1 << i);
							}
							
						}
						
					}
					else {
						lcdPrint("malik3");
						_delay_ms(10);
						for (int i =4; i<8;i++)
						{
							PORTC &= ~(1 << i);
						}
						
					}
				}
				else {
					lcdPrint("malik2");
					_delay_ms(10);
					for (int i =4; i<8;i++)
					{
						PORTC &= ~(1 << i);
					}
					
				}
			}
			else {
				PORTA = malik[3][butn];
				_delay_ms(10);
				for (int i =4; i<8;i++)
				{
					PORTC &= ~(1 << i);
				}
				
			}
		}
		
	}
}



