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

enum states{Start, init, inc, dec, wait, reset} state;

void status(){
	switch(state){ //transitions
		case Start:
			state = init;
			break;
		case init:
			if(~PINA & 0x02){
				state = dec;
			}
			else if(~PINA & 0x01){
				state = inc;
			}
			else if((~PINA & 0x03) == 0x03){
				state = reset;
			}
			else{
				state = init;
			}
			break;
		case inc:
			if((~PINA & 0x01) && (~PINA & 0x02)){
				state = reset;
			}
			else if(~PINA & 0x01){
				state = wait;
			}
			else{
				state = init;
			}
			break;
		case dec:
			if((~PINA & 0x01) && (~PINA & 0x02)){
				state = reset;
			}
			else if(~PINA & 0x02){
				state = wait;
			}
			else{
				state = init;
			}
			break;
		case wait:
			if(((~PINA & 0x03) == 0x02) || ((~PINA & 0x03) == 0x01)){
				state = wait;
			}
			else{
				state = init;
			}
			break;
		case reset:
			if((~PINA & 0x01) || (~PINA & 0x02)){
				state = wait;
			}
			else{
				state = init;
			}
			break;
		default:
			break;
	}
	switch(state){ //state actions
		case init:
			PORTC;
			break;	
		case inc:
			if(PORTC < 9){
				PORTC = PORTC + 1;
			}
			break;
		case dec:
			if(PORTC > 0){
				PORTC = PORTC - 1;
			}
			break;
		case wait:
			break;
		case reset:
			PORTC = 0x00;
			break;
		default:
			PORTC = 0x00;
			break;
	}
}

int main(void) {
	DDRA = 0x00;	PORTA = 0xFF;
	DDRC = 0xFF;	PORTC = 0x00;

	state = Start;
    while (1) {
	status();
    }
    return 1;
}
