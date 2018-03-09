#define  F_CPU 1000000UL // defines the clock frequency as 1 MHz (unsigned long)
#include "cube.h"

void initCube(){
	DDRD = 0b11111111;
	DDRB = 0b11110000;
}

void led_on(uint16_t led_index){


	// check given indexes
	if((led_index < 0 || led_index > 8)){
		error_handle();
		exit(EXIT_FAILURE);
	}

	// this may look trivial but to keep the change of the connection logic
	// of the led cube easy
	switch (led_index){
		case 0 :
		SETON(led1_port, led1_pin);
		break;
		case 1 :
		SETON(led2_port, led2_pin);
		break;
		case 2 :
		SETON(led3_port, led3_pin);
		break;
		case 3 :
		SETON(led4_port, led4_pin);
		break;
		case 4 :
		SETON(led5_port, led5_pin);
		break;
		case 5 :
		SETON(led6_port, led6_pin);
		break;
		case 6 :
		SETON(led7_port, led7_pin);
		break;
		case 7 :
		SETON(led8_port, led8_pin);
		break;
		case 8 :
		SETON(led9_port, led9_pin);
		break;
	}
}

void led_off(uint16_t led_index){

	// check given indexes
	if((led_index < 0 || led_index > 8)){
		error_handle();
		exit(EXIT_FAILURE);
	}

	// activate the led
	switch (led_index){
		case 0 :
		SETOFF(led1_port, led1_pin);
		break;
		case 1 :
		SETOFF(led2_port, led2_pin);
		break;
		case 2 :
		SETOFF(led3_port, led3_pin);
		break;
		case 3 :
		SETOFF(led4_port, led4_pin);
		break;
		case 4 :
		SETOFF(led5_port, led5_pin);
		break;
		case 5 :
		SETOFF(led6_port, led6_pin);
		break;
		case 6 :
		SETOFF(led7_port, led7_pin);
		break;
		case 7 :
		SETOFF(led8_port, led8_pin);
		break;
		case 8 :
		SETOFF(led9_port, led9_pin);
		break;
	}
}

void led_toggle(uint16_t led_index){
	// check given indexes
	if((led_index < 0 || led_index > 8)){
		error_handle();
		exit(EXIT_FAILURE);
	}

	// activate the led
	switch (led_index){
		case 0 :
		TOGGLE(led1_port, led1_pin);
		break;
		case 1 :
		TOGGLE(led2_port, led2_pin);
		break;
		case 2 :
		TOGGLE(led3_port, led3_pin);
		break;
		case 3 :
		TOGGLE(led4_port, led4_pin);
		break;
		case 4 :
		TOGGLE(led5_port, led5_pin);
		break;
		case 5 :
		TOGGLE(led6_port, led6_pin);
		break;
		case 6 :
		TOGGLE(led7_port, led7_pin);
		break;
		case 7 :
		TOGGLE(led8_port, led8_pin);
		break;
		case 8 :
		TOGGLE(led9_port, led9_pin);
		break;
		default:
		break;
	}
}

void layer_on(uint16_t layer_index){

	if((layer_index < 0 || layer_index > 2)){
		error_handle();
		exit(EXIT_FAILURE);
	}


	switch(layer_index){
		case 0:
		SETON(layer1_port, layer1_pin);
		break;
		case 1:
		SETON(layer2_port, layer2_pin);
		break;
		case 2:
		SETON(layer3_port, layer3_pin);
		break;
		default:
		break;
	}
}

void layer_off(uint16_t layer_index){

	//check the given index
	if((layer_index < 0 || layer_index > 2)){
		error_handle();
		exit(EXIT_FAILURE);
	}

	switch(layer_index){
		case 0:
		SETOFF(layer1_port, layer1_pin);
		break;
		case 1:
		SETOFF(layer2_port, layer2_pin);
		break;
		case 2:// assert and stop if violate.
		SETOFF(layer3_port, layer3_pin);
		break;
		default:
		break;
	}

}

void layer_toggle(uint16_t layer_index){

	//check the given index
	//int check = (layer_index < 0 && layer_index > 8);

	// assert and stop if violate.
	if((layer_index < 0 || layer_index > 2)){
		error_handle();
		exit(EXIT_FAILURE);
	}

	switch(layer_index){
		case 0:
		TOGGLE(layer1_port, layer1_pin);
		break;
		case 1:
		TOGGLE(layer2_port, layer2_pin);
		break;
		case 2:
		TOGGLE(layer3_port, layer3_pin);
		break;
		default:
		break;
	}
}

void test_cube(){	
	
	uint16_t i, j;
	for (i = 0; i < LAYER_SIZE; i++){
		layer_toggle(i);
		for (j = 0; j < LED_SIZE; j++){
			led_toggle(j);
			_delay_ms(100);
		}
		for (j = 0; j < LED_SIZE; j++){
			led_toggle(j);
			_delay_ms(100);
		}
		layer_toggle(i);
		_delay_ms(100);
	}
}


void error_handle(){
	reset();
	layer_on(1);
	led_on(4);	
}

void reset(){
	int i,j;
	for (i = 0; i< LAYER_SIZE; i++){
		for(j =0 ; j< LED_SIZE ; j++){
			led_off(j);
		}
		layer_off(i);
	}
}
