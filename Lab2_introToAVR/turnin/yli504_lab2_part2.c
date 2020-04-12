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
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRC = 0xFF; PORTC = 0x00; //output

	unsigned char cntavail = 0x00;
    /* Insert your solution below */
    while (1) {
	cntavail = 0;

	if(PINA == 0x00){ 
		cntavail = (cntavail & 0xF8) | 0x04;
	}

	else if(PINA == 0x01){
		cntavail = (cntavail & 0xF8) | 0x03;
	}

	else if(PINA == 0x02){
		cntavail = (cntavail & 0xF8) | 0x02;
	}

	else if(PINA == 0x03){
		cntavail = (cntavail & 0xF8) | 0x01;
	}

	else if(PINA == 0x04){
		cntavail = (cntavail & 0xF8) | 0x00;
	}

	PORTC = cntavail;
    }
    return 1;
}
