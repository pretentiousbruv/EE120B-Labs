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
	DDRB = 0x00;	PORTB = 0xFF;

	DDRC = 0xFF;	PORTC = 0x00;/* Insert DDR and PORT initializations */

	unsigned char tempA = 0x00;
	unsigned char tempB = 0x00;
	unsigned char countA = 0x00;
	unsigned char countB = 0x00;
    /* Insert your solution below */
    while (1) {
	tempA = PINA;
	tempB = PINB;
	countA = 0x00;
	countB = 0x00;
	
	while(tempA > 0){
		if((tempA & 0x01) == 1){
			countA = countA + 1;
			tempA = tempA >> 1;
		}
		else{
			tempA = tempA >> 1;
		}
	}

	while(tempB > 0){
		if((tempB & 0x01) == 1){
			countB = countB + 1;
			tempB = tempB >> 1;
		}
		else{
			tempB = tempB >> 1;
		}
	}
	PORTC = countA + countB;
    }
    return 1;
}
