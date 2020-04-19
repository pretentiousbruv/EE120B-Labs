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

enum LED_States{Start, offrelease, onpress, onrelease, offpress} LED_State;

void LED_Status(){
	switch(LED_State){ //transitions
		case Start:
			LED_State = offrelease;
			break;
		case offrelease:
			if(PINA == 0x01){
				LED_State = onpress;
			}
			if(PINA == 0x00){
				LED_State = offrelease;
			}
			break;
		case onpress:
			if(PINA == 0x01){
				LED_State = onpress;
			}
			if(PINA == 0x00){
				LED_State = onrelease;
			}
			break;
		case onrelease:
			if(PINA == 0x01){
				LED_State = offpress;
			}
			if(PINA == 0x00){
				LED_State = onrelease;
			}
			break;
		case offpress:
			if(PINA == 0x01){
				LED_State = offpress;
			}
			if(PINA == 0x00){
				LED_State = offrelease;
			}
			break;
		default:
			LED_State = Start;
			break;
	}
	switch(LED_State){ //state actions
		case offrelease:
			PORTB = 0x01;
			break;
		case onpress:
			PORTB = 0x02;
			break;
		case onrelease:
			PORTB = 0x02;
			break;
		case offpress:
			PORTB = 0x01;
			break;
		default:
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
