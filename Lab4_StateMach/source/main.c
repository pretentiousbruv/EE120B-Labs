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
#include "RIMS.h"
#endif

enum LED_States{Start, A0off, A0on} LED_State;

void LED_Status(){
	switch(LED_State}{ //transitions
		case Start:
			LED_State = A0off;
			break;
		case A0off:
			if(A0){
				LED_State = A0on;
				break;
			}
			else{
				LED_State = A0off;
				break;
			}
		case A0on:
			if(A0){
				LED_State = A0off;
				break;
			}
			else{
				LED_State = A0on;
				break;
			}
		default:
			LED_State = Start;
			break;
	}
	switch(LED_State){ //state actions
		case A0off:
			PORTB = 0x01;
			break;
		case A0on:
			PORTB = 0x02;
			break;
		default:
			PORTB = 0x01;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
    /* Insert your solution below */
	PORTB = 0x01;
	LED_State = Start;
    while (1) {
	LED_Status();
    }
    return 1;
}
