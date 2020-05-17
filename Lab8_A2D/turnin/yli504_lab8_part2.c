/*	Author: yli504
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;	PORTB = 0x00;
	unsigned short x = 0;
    /* Insert your solution below */
	ADC_init();
    while (1) {
	x = ADC;

	if(x >= (251 / 2)){
		PINB = 0x01;
	}
	if(x < (251 / 2)){
		PINB = 0x00;
	}
    }
    return 1;
}
