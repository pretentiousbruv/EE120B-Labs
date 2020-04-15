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
	DDRB = 0xFE;	PORTB = 0xF1;
	DDRD = 0x00;	PORTD = 0xFF;
	DDRA = 0xFF;	PORTA = 0x00;
	DDRC = 0x01;	PORTC = 0xFE;
	
	unsigned char tempA = 0x00;
	unsigned char tempBi = 0x00;
	unsigned char tempBo = 0x00;
	unsigned char tempC = 0x00;
	unsigned char tempD = 0x00;
	unsigned short weight = 0;

    while (1) {
	weight = 0;
	tempBo = 0x00;
	tempBi = PINB;
	tempD = PIND;
	weight = tempBi + tempD;
	
	if(weight >= 70){
		tempBo = tempBo | 0x02;
	}
	else if((weight > 5) && (weight < 70)){
		tempBo = tempBo | 0x04;
	}
	else{
		tempBo = o;
	}
	weight = tempC;
	tempC = tempC & 0x01;
	tempA  = weight >> 1;

	PORTA = tempA;
	PORTB = tempBo;
	PORTC = tempC;
    }
    return 1;
}
