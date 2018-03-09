#define  F_CPU 16000000UL // defines the clock frequency
#include "interface.h"



void start_timer(){
	timer0_overflow_count = 0;
	TCNT0 = 0;
}


void init_interface(){
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
	
	sei();
	
	start_timer();
}

unsigned long read_plate_x(){
	
	unsigned long count = 0;
	unsigned long total = 0;
	
	while(checkval < refresh) {

		DDRC |= (1 << PC0);         // pin 0 of PORTC as output
		PORTC = 0x00;				// switch PORTC to low output
		
		DDRC &= ~(1 << PC0);         // pin 0 of PORTC as input
		
		while((PINC & 0b00000001) == 0){
			count++;
		}
		total++;
	}
	
	start_timer();
	
	return (count << resolution)/total;
}

unsigned long read_plate_y(){
	
	unsigned long count = 0;
	unsigned long total = 0;
	
	while(checkval < refresh) {
		
		DDRC |= (1 << PC4);         // pin 0 of PORTC as output
		PORTC = 0x00;				// switch PORTC to low output
		
		DDRC &= ~(1 << PC4);         // pin 0 of PORTC as input
		
		while((PINC & 0b00010000) == 0){
			count++;
		}
		total++;

	}
	
	start_timer();
		
	return (count << resolution)/total;
}

unsigned long read_plate_z(){
	
	unsigned long count = 0;
	unsigned long total = 0;
	
	while(checkval < refresh) {
		
		DDRC |= (1 << PC5);         // pin 0 of PORTC as output
		PORTC = 0x00;				// switch PORTC to low output
		
		DDRC &= ~(1 << PC5);        // pin 0 of PORTC as input
		
		while((PINC & 0b00100000) == 0){
			count++;
		}
		total++;
		
	}
	
	start_timer();
	
	return (count << resolution)/total;
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
