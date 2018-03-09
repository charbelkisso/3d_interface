/*
ATmega8, 48, 88, 168, 328
/Reset  PC6|1   28|PC5		 Plate Z
		PD0|2   27|PC4		 Plate Y
		PD1|3   26|PC3		 6 R/W LCD Read/Write
		PD2|4   25|PC2		 5 E LCD Enable
		PD3|5   24|PC1		 3 RS LCD Register select
		PD4|6   23|PC0		 Plat X
		Vcc|7   22|Gnd
		Gnd|8   21|Aref
		PB6|9   20|AVcc
		PB7|10  19|PB5 SCK    13 DB7 LCD Data bit 7
		PD5|11  18|PB4 MISO   14 DB6 LCD Data bit 6
		PD6|12  17|PB3 MOSI   11 DB5 LCD Data bit 5
		PD7|13  16|PB2		  12 DB4 LCD Data bit 4
        PB0|14  15|PB1		  17 S1 Switch 1
*/

#define  F_CPU 16000000UL // defines the clock frequency

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "lcd.h"
#include "cube.h"
#include "interface.h"




void init_display(){
	lcd_init(LCD_DISP_ON);
}


int main (void) {
	
	init_interface();
	init_display();

	while (1)            // infinite main loop
	{
		char text[20];
		//lcd_clrscr();
		lcd_gotoxy(0,0);
		utoa(read_plate_x(), text, 10);
		lcd_puts(text);
		_delay_ms(5);
		/*
		lcd_gotoxy(6,0);
		utoa(read_plate_y(), text, 10);
		lcd_puts(text);
		_delay_ms(5);
		lcd_gotoxy(0,1);
		utoa(read_plate_z(), text, 10);
		lcd_puts(text);
		_delay_ms(5);
		*/
	}
	
}

