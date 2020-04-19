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

enum states{Start, lock, a3lock, unlockpress, unlockwait, unlockrelease, xpress, xwait, xrelease, ypress, ywait, yrelease, a3press, a3wait, a3release, inpress, inwait, inrelease} state;

void lockstatus(){
	switch(state){ //transitions
		case Start:
			state = lock;
			break;

		case lock:
			if(PINA == 0x00){
				state = lock;
			}
			if(PINA == 0x01){
				state = xpress;
			}
			if(PINA == 0x02){
				state = ypress;
			}
			if(PINA == 0x04){
				state = a3press;
			}
			break;
			if(PINA == 0x80){
				state = inpress;
			}
			break;

		case a3lock:
			if(PINA == 0x00){
				state = a3lock;
			}
			if(PINA == 0x02){
				state = unlockpress;
			}
			else{
				state = lock;
			}
			break;
		
		case unlockpress:
			if(PINA == 0x00){
				state = unlockwait;
			}
			if(PINA == 0x02){
				state = unlockpress;
			}
			else{
				state = lock;
			}
		case unlockwait:
			if(PINA == 0x00){
				state = unlockwait;
				break;
			}
			if(PINA == 0x02){
				state = unlockrelease;
			}
		case unlockrelease:
			if(PINA == 0x00){
				state = unlockrelease;
			}
			if(PINA == 0x02){
				state = unlockpress;
			}
			break;

		case xpress:
			if(PINA == 0x01){
				state = xwait;
			}
			if(PINA == 0x00){
				state = xpress;
			}
			if(PINA == 0x02){
				state = ypress;
			}
			if(PINA == 0x04){
				state = a3press;
			}
			if(PINA == 0x80){
				state = inpress;
			}
			break;
		case xwait:
			if(PINA == 0x01){
				state = xwait;
			}
			if(PINA == 0x00){
				state = xrelease;
			}
			break;
		case xrelease:
			if(PINA == 0x01){
				state = xrelease;
			}
			if(PINA == 0x00){
				state = lock;
			}
			break;
		
		case ypress:
			if(PINA == 0x02){
				state = ywait;
			}
			if(PINA == 0x00){
				state = ypress;
			}
			if(PINA == 0x01){
				state = xpress;
			}
			if(PINA == 0x04){
				state = a3press;
			}
			if(PINA == 0x80){
				state = inpress;
			}
			break;
		case ywait:
			if(PINA == 0x02){
				state = ywait;
			}
			if(PINA == 0x00){
				state = yrelease;
			}
			break;
		case yrelease:
			if(PINA == 0x02){
				state = yrelease;
			}
			if(PINA == 0x00){
				state = lock;
			}
			break;

		case a3press:
			if(PINA == 0x00){
				state = a3wait;
			}
			if(PINA == 0x04){
				state = a3press;
			}
			if(PINA == 0x02){
				state = ypress;
			}
			if(PINA == 0x01){
				state = xpress;
			}
			if(PINA == 0x80){
				state = inpress;
			}
			break;
		case a3wait:
			if(PINA == 0x00){
				state = a3wait;
			}
			else{
				state = a3release;
			}
			break;
		case a3release:
			if(PINA == 0x00){
				state = a3release;
			}
			else{
				state = a3lock;
			}
			break;

		case inpress:
			if(PINA == 0x08){
				state = inwait;
			}
			if(PINA == 0x00){
				state = inpress;
			}
			if(PINA == 0x02){
				state = ypress;
			}
			if(PINA == 0x04){
				state = a3press;
			}
			if(PINA == 0x01){
				state = inpress;
			}
			break;
		case inwait:
			if(PINA == 0x80){
				state = inwait;
			}
			if(PINA == 0x00){
				state = inrelease;
			}
			break;
		case inrelease:
			if(PINA == 0x80){
				state = inrelease;
			}
			if(PINA == 0x00){
				state = lock;
			}
			break;

		default:
			state = Start;
			break;
	}
	switch(state){ //state actions
		case lock:
			PORTB = 0x00;
			break;
		case a3lock:
			PORTB = 0x00;
			break;
		case unlockpress:
			PORTB = 0x01;
			break;
		case unlockwait:
			PORTB = 0x01;
			break;
		case unlockrelease:
			PORTB = 0x01;
			break;
		case xpress:
			PORTB = 0x00;
			break;
		case xwait:
			PORTB = 0x00;
			break;
		case xrelease:
			PORTB = 0x00;
			break;
		case ypress:
			PORTB = 0x00;
			break;
		case ywait:
			PORTB = 0x00;
			break;
		case yrelease:
			PORTB = 0x00;
			break;
		case a3press:
			PORTB = 0x00;
			break;
		case a3wait:
			PORTB = 0x00;
			break;
		case a3release:
			PORTB = 0x00;
			break;
		case inpress:
			PORTB = 0x00;
			break;
		case inwait:
			PORTB = 0x00;
			break;
		case inrelease:
			PORTB = 0x00;
			break;
		default:
			PORTB = 0x00;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
    /* Insert your solution below */
	PORTB = 0x00;
	state = Start;
    while (1) {
	lockstatus();
    }
    return 1;
}
