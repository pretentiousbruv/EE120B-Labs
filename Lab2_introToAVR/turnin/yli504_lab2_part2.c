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

	if(PINA == 0x00)
		cntavail = (cntavail & 0xF0) | 0x04;
	else if((PINA == 0x01) || (PINA == 0x02) || (PINA == 0x04) || (PINA == 0x08))
		cntavail = (cntavail & 0xF0) | 0x03;
	else if((PINA == 0x03) || (PINA == 0x05) || (PINA == 0x06) || (PINA == 0x09) || (PINA == 0x0A) || (PINA == 0x0C))
		cntavail = (cntavail & 0xF0) | 0x02;
	else if((PINA == 0x07) || (PINA == 0x0B) || (PINA == 0x0D) || (PINA == 0x0E))
		cntavail = (cntavail & 0xF0) | 0x01;
	else if(PINA == 0x0F)
		cntavail = 0x00;
		/*cntavail = 0x80;*/

	PORTC = cntavail;
    }
    return 1;
}
