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
	DDRA = 0x00;	PORTA = 0xFF;

	DDRC = 0xFF;	PORTC = 0x00;/* Insert DDR and PORT initializations */

	unsigned char tempA = 0x00;
	unsigned char tempC = 0x00;
    /* Insert your solution below */
    while (1) {
	tempA = PINA;
	
	if((tempA < 16) && (tempA > 12)){
		tempC = 0x3F;
	}
	if((tempA < 13) && (tempA > 9)){
		tempC = 0x3E;
	}
	if((tempA < 10) && (tempA > 6)){
		tempC = 0x3C;
	}
	if((tempA < 7) && (tempA > 4)){
		tempC = 0x38;
	}
	if((tempA < 5) && (tempA > 2)){
		tempC = 0x70;
	}
	if((tempA < 3) && (tempA > 0)){
		tempC = 0x60;
	}
	PORTC = tempC;
    }
    return 1;
}
