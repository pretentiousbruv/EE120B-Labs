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
	unsigned char tempA2 = 0x00;
	unsigned char tempC = 0x00;
    /* Insert your solution below */
    while (1) {
	tempA = PINA;
	tempA2 = PINA;
	
	tempA = tempA >> 4;
	tempA2 = tempA2 << 4;
	tempC = tempA + tempA2;
	
	PORTC = tempC;
    }
    return 1;
}
