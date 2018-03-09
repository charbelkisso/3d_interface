#ifndef CUBE_H
#define CUBE_H


#define assert(expression)
/*
 * necessary library include
*/
#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <assert.h>
/*
 * constants for the cube size
*/
#define LED_SIZE 9
#define LAYER_SIZE 3
#define CUBE_SIZE LED_ZIZE * LAYER_SIZE

/*
 * define control port and pin for led in single layer
 * this is used globally change it with care
 *
*/
#define led1_port PORTD
#define led1_pin PD0 
#define led2_port PORTD
#define led2_pin PD1  
#define led3_port PORTD
#define led3_pin PD2  
#define led4_port PORTD
#define led4_pin PD3  
#define led5_port PORTD
#define led5_pin PD4  
#define led6_port PORTD
#define led6_pin PD5  
#define led7_port PORTD
#define led7_pin PD6 
#define led8_port PORTD
#define led8_pin PD7  
#define led9_port PORTB
#define led9_pin PB0

/*
 * define control port and pin for layers
 * this is used globally change it with care
*/
#define layer1_port PORTB
#define layer1_pin PB1
#define layer2_port PORTB
#define layer2_pin PB2
#define layer3_port PORTB
#define layer3_pin PB3

/*
 * define macros for bit manipulation
 * Don't change
*/
#define DDR(x) (*(&x - 1))								// set the DDRx
#define SETON(port, pin) (port |= (1 << pin))			// set pin on port on
#define SETOFF(port, pin) (port &= (1 << pin))			// set pin on port off
#define TOGGLE(port, pin) (port ^= (1 << pin))			// toggle pin on port
#define BIT_IS_SET(byte, bit) (byte & (1 << bit))		// check if the pin is on
#define BIT_IS_CLEAR(byte, bit) (!(byte & (1 << bit)))	// check if the pin is off


void initCube();
/*
 *  @brief:: this function help to set the led on without
 * 			 taking care of the ports and pin configuration
 *
 * 	@Param:: led_index for single led in a layer
 *
 * 	@return:: void
 */
void led_on(uint16_t led_index);
/*
 *  @brief:: this function help to set the led off without
 * 			 taking care of the ports and pin configuration
 *
 * 	@Param:: led_index for single led in a layer
 *
 * 	@return:: void
 */
void led_off(uint16_t led_index);
/*
 *  @brief:: this function help to toggle the led on/off without
 * 			 taking care of the ports and pin configuration
 *
 * 	@Param:: led_index for single led in a layer
 *
 * 	@return:: void
 */
void led_toggle(uint16_t led_index);
/*
 *  @brief:: this function help to activate the layer on without
 * 			 taking care of the ports and pin configuration
 *
 * 	@Param:: layer_index for single led in a layer
 *
 * 	@return:: void
 */
void layer_on(uint16_t layer_index);
/*
 *  @brief:: this function help to deactivate the layer off without
 * 			 taking care of the ports and pin configuration
 *
 * 	@Param:: layer_index for single led in a layer
 *
 * 	@return:: void
 */
void layer_off(uint16_t layer_index);
/*
 *  @brief:: this function help to toggle the layer on/of without
 * 			 taking care of the ports and pin configuration
 *
 * 	@Param:: layer_index for single led in a layer
 *
 * 	@return:: void
 */
void layer_toggle(uint16_t layer_index);
/*
 *  @brief run the led to insure that no led require to replace
 *
 * */
void test_cube();
/*
 * @brief: light the letter error as error handle
*/
void error_handle();

void reset();
#endif
