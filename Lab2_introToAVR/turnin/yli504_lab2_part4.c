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
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;

	DDRD = 0xFF; PORTD = 0x00; //output
	
	unsigned char tempA = 0x00;
	unsigned char tempB = 0x00;
	unsigned char tempC = 0x00;
	unsigned char tempD = 0x00;
	unsigned short weight = 0;
	
    /* Insert your solution below */
    while (1) {
	tempA = PINA;
	tempB = PINB;
	tempC = PINC;
	tempD = 0x00;
	weight = 0;

	weight = tempA + tempB + tempC;
	tempD = weight & 0xFC;
	
	if(weight > 140){
		tempD = tempD | 0x01;
	}
	
	if((tempA - tempC) > 80 || (tempC - tempA)){
		tempD = tempD | 0x02;
	}
	PORTD = tempD;
    }
    return 1;
}
