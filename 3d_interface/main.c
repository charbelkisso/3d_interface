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



#define resolution 10
#define mains 50
#define refresh 2 * 1000000 / mains


void init_display(){
	lcd_init(LCD_DISP_ON);
}

void init (void)
{
	DDRC &= (0 << PC0);         // pins 0 of PORTC as input
	
	DDRC &= (0 << PC4);         // pins 4 of PORTC as input
	
	DDRC &= (0 << PC5);         // pins 5 of PORTC as input
	
	// run 8-bit TIMER on f_cpu
	// normal operation
	
	TCCR0A = (0 << COM0A1) | (0 << COM0A0) | (0 << COM0B1) | (0 << COM0B0)
	| (0 << WGM01) | (0 << WGM00 );							// set mode
	TCCR0B = (0 << WGM02)  //| (0 << WGM13)
	| (0 << CS02) | (1 << CS01) | (1 << CS00);				// set prescaler clk/64
	TIMSK0 = (0 << OCIE0B) | (0 << OCIE0A) | (1 << TOIE0 ); // interrupt on Timer 0 overflow
	
}

volatile unsigned long timer0_overflow_count;
volatile unsigned long checkval;

void startTimer() {
	timer0_overflow_count = 0;
	TCNT0 = 0;
}

void ReadPlateX(){
	unsigned long count = 0;
	unsigned long total = 0;
	char y[20];
	
	while(checkval < refresh) {

		DDRC |= (1 << PC0);         // pin 0 of PORTC as output
		PORTC = 0x00;				// switch PC0 to low output
		
		DDRC &= ~(1 << PC0);         // pin 0 of PORTC as input
		
		while((PINC & 0b00000001) == 0){
			count++;
		}
		total++;
	}
	
	startTimer();
	

	lcd_gotoxy(0,0);
	utoa(((count << resolution)/total), y, 10);
	lcd_puts(y);
	_delay_ms(5);

}

void ReadPlateY(){
	unsigned long count = 0;
	unsigned long total = 0;
	char y[20];
	
	while(checkval < refresh) {
		
		DDRC |= (1 << PC4);         // pin 0 of PORTC as output
		PORTC = 0x00;				// switch PC0 to low output
		
		DDRC &= ~(1 << PC4);         // pin 0 of PORTC as input
		
		while((PINC & 0b00010000) == 0){
			count++;
		}
		total++;

	}
	
	startTimer();
	
	
	lcd_gotoxy(6,0);
	utoa(((count << resolution)/total), y, 10);
	lcd_puts(y);
	_delay_ms(5);

}

void ReadPlateZ(){
	unsigned long count = 0;
	unsigned long total = 0;
	char y[20];
	
	while(checkval < refresh) {
	
		DDRC |= (1 << PC5);         // pin 0 of PORTC as output
		PORTC = 0x00;				// switch PC0 to low output
		
		DDRC &= ~(1 << PC5);        // pin 0 of PORTC as input
		
		while((PINC & 0b00100000) == 0){
			count++;
		}
		total++;
		
	}
	
	startTimer();
	
	//lcd_clrscr();
	lcd_gotoxy(0,1);
	utoa(((count << resolution)/total), y, 10);
	lcd_puts(y);
	_delay_ms(5);

}



ISR(TIMER0_OVF_vect) {
	static unsigned long timer0_millis = 0;
	static unsigned char timer0_fract = 0;
	
	timer0_millis += 1;
	timer0_fract += 3;
	
	if (timer0_fract >= 125) {
		timer0_fract -= 125;
		timer0_millis += 1;
	}
	
	timer0_overflow_count++;
	checkval = ((timer0_overflow_count << 8) + TCNT0) << 2;  //time in milliSec ?
}

int main (void) {
	init();
	sei();
	init_display();
	startTimer();


	while (1)            // infinite main loop
	{
		
		
		ReadPlateX();
		ReadPlateY();
		ReadPlateZ();
		
	}
	
}

