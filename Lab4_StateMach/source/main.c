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

enum states{Start, init, A0press, A0release, A1press, A1release, A0A1press, A0A1release} state;

void status(){
	switch(state){ //transitions
		case Start:
			state = init;
			break;
		case init:
			if(PINA == 0x00){
				state = init;
			}
			else if(PINA == 0x01){
				state = A0press;
			}
			else if(PINA == 0x02){
				state = A1press;
			}
			else if(PINA = 0x03){
				state = A0A1press;
			}
			break;
		case A0press:
			if(PINA == 0x00){
				state = A0release;
			}
			else if(PINA == 0x01){
				state = A0press;
			}
			else if(PINA == 0x03){
				state = A0A1press;
			}
			break;
		case A0release:
			state = init;
			break;
		case A1press:
			if(PINA == 0x00){
				state = A1release;
			}
			else if(PINA = 0x02){
				state = A1press;
			}
			else if(PINA = 0x03){
				state = A0A1press;
			}
			break;
		case A1release:
			state = init;
			break;
		case A0A1press:
			if(PINA = 0x00){
				state = A0A1release;
			}
			if(PINA = 0x03){
				state = A0A1press;
			}
			break;
		case A0A1release:
			state = init;
			break;
	}
	switch(state){ //state actions	
		default:
			PORTC = 0x07;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRC = 0xFF;	PORTC = 0x00;
    /* Insert your solution below */
	PORTC = 0x07;
	state = Start;
    while (1) {
	status();
    }
    return 1;
}
