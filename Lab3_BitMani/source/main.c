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
	DDRB = 0xFF;	PORTB = 0x00;
	DDRC = 0xFF;	PORTC = 0x00;/* Insert DDR and PORT initializations */

	unsigned char tempA = 0x00;
	unsigned char tempA2 = 0x00;
	unsigned char tempB = 0x00;
	unsigned char tempC = 0x00;
    /* Insert your solution below */
    while (1) {
	tempA = PINA;
	tempA2 = PINA;
	tempB = PORTB;
	tempC = PORTC;
	
	tempA = tempA >> 4;
	tempA2 = tempA2 << 4;
	tempB = (tempB & 0xF0) | tempA;
	tempC = (tempC & 0x0F) | tempA2;
	
	PORTB = tempB;
	PORTC = tempC; 
	
    }
    return 1;
}
