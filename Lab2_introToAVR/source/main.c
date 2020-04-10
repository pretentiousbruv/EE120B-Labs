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
	DDRB = 0xFF; PORTB = 0x00; //output

	unsigned char tempB = 0x00;
    /* Insert your solution below */
    while (1) {
	if(PINA == 0x01)
		tempB = (tempB & 0xFC) | 0x01;
	else
		tempB = (tempB & 0xFC) | 0x00;
	PORTB = tempB;
    }
    return 1;
}
