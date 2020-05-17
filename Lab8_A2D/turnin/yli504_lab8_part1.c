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
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
	DDRD = 0xFF;	PORTD = 0x00;

	unsigned char tempB = 0x00;
	unsigned char tempD = 0x00;
	unsigned short x = 0;
    /* Insert your solution below */
	ADC_init();
    while (1) {
	x = ADC;
	tempB = (char)x;
	tempD = (char)(x >> 8);
	PINB = tempB;
	PIND = tempD;
    }
    return 1;
}
