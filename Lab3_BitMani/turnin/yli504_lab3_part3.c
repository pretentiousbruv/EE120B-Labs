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
	
	tempA2 = tempA2 >> 4;
	tempA = tempA & 0x0F;
	if((tempA2 == 0) || (tempA2 == 1) || (tempA2 == 2) || (tempA2 == 4) || (tempA2 == 5) || (tempA2 == 6) || (tempA2 == 7)){
		if((tempA < 16) && (tempA > 12)){
			tempC = 0x3F;
		}
		else if((tempA < 13) && (tempA > 9)){
			tempC = 0x3E;
		}
		else if((tempA < 10) && (tempA > 6)){
			tempC = 0x3C;
		}
		else if((tempA < 7) && (tempA > 4)){
			tempC = 0x38;
		}
		else if((tempA < 5) && (tempA > 2)){
			tempC = 0x70;
		}
		else if((tempA < 3) && (tempA > 0)){
			tempC = 0x60;
		}
		else{
			tempC = 0x40;
		}
	}
	else{
		if((tempA < 16) && (tempA > 12)){
			tempC = 0xBF;
	}
		else if((tempA < 13) && (tempA > 9)){
			tempC = 0xBE;
	}
		else if((tempA < 10) && (tempA > 6)){
			tempC = 0xBC;
	}
		else if((tempA < 7) && (tempA > 4)){
			tempC = 0xB8;	
	}
		else if((tempA < 5) && (tempA > 2)){			
			tempC = 0xF0;
	}
		else if((tempA < 3) && (tempA > 0 )){
			tempC = 0xE0;
	}
		else{
			tempC = 0xC0;
		}		
	}
	
	PORTC = tempC;
    }
    return 1;
}
