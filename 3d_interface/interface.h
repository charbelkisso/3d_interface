#ifndef INTERFACE_H
#define INTERFACE_H

/*
 * Necessary includes
**/
#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <assert.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

/*
 * Define library values of timing resolution and constant
**/
#define resolution 8						//resolution of time measurement
#define mains 50							// this correspond to the AC current frequency in Hz
#define refresh 2 * 1000000 / mains			// refresh rate

// counter increments when over flow interrupt is raised
volatile unsigned long timer0_overflow_count;
// reference value to compare with the refresh rate
volatile unsigned long checkval;

/*
 * used for start/reset the timer values
**/
void start_timer();
/*
 * initialize the interface PORTS and timer
 * this function has internal calls to global interrupt sei() and start_timer()
**/
void init_interface();
/*
 * read the elapsed time taken by plate X to charge
**/
unsigned long read_plate_x();
/*
 * read the elapsed time taken by plate Y to charge
**/
unsigned long read_plate_y();
/*
 * read the elapsed time taken by plate Z to charge
**/
unsigned long read_plate_z();

#endif