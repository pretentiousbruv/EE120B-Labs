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

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
    /* Insert your solution below */
	unsigned char tempA = 0x00;
	unsigned char button = 0x00;
	unsigned char count = 0x00;
    while (1) {
	tempA = PINA;
	
	if(tempA == 0x01){
		button = 0x01;
		count = count + 1;
		if(count > 3){
			button = 0x00;
			count = 0x00;
		}
	}
	if(button == 0x01){
		PORTB = 0x02;	
	}
	if(button == 0x00){
		PORTB = 0x01;
	}
    }
    return 1;
}
