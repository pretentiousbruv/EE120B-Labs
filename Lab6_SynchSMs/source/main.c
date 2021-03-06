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
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag =  0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char i = 0;
unsigned char flag = 0;

void TimerOn(){
	TCCR1B = 0x0B;
	
	OCR1A = 125;
	
	TIMSK1 = 0x02;

	TCNT1 = 0;

	_avr_timer_cntcurr = _avr_timer_M;
	
	SREG |= 0x80;
}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum states{Start, state1, state2, state3, button, pause, buttonagain} state;

void status(){
	switch(state){
		case Start:
			state = state1;
			break;
		case state1:
			if(flag == 1){
				state = pause;
			}
			if(flag == 2){
				state = state2;
			}
			if(flag == 3){
				state = state3;
			}
			if(~PINA & 0x01){
				state = button;
			}
			if(i == 1){
				state = state2;
			}
			i = i + 1;
			break;
		case state2:
			if(flag == 1){
				state = state1;
			}
			if(flag == 2){
				state = pause;
			}
			if(flag == 3){
				state = state3;
			}
			if(~PINA & 0x01){
				state = button;
			}
			if(i == 2){
				state = state3;
			}
			i = i + 1;
			break;
		case state3:
			if(flag == 1){
				state = state1;
			}
			if(flag == 2){
				state = state2;
			}
			if(flag == 3){
				state = pause;
			}
			if(~PINA & 0x01){
				state = button;
			}
			if(i == 3){
				i = 0;
				state = state1;
			}
			i = i + 1;
			break;
		case button:
			if(~PINA & 0x01){
				state = button;
			}
			if(~PINA & 0x00){
				state = pause;
			}
			break;
		case pause:
			if(~PINA & 0x01){
				flag = 0;
				state = buttonagain;
			}
			if(PORTB & 0x01){
				flag = 1;
				break;
			}
			if(PORTB & 0x02){
				flag = 2;
				break;
			}
			if(PORTB & 0x04){
				flag = 3;
				break;
			}
			break;
		case buttonagain:
			if(~PINA & 0x01){
				state = buttonagain;
			}
			else if(PORTB & 0x01){
				state = state1;
			}
			else if(PORTB & 0x02){
				state = state2;
			}
			else if(PORTB & 0x04){
				state = state3;
			}
		default:
			break;
	}
	
	switch(state){
		case state1:
			PORTB = 0x01;
			break;
		case state2:
			PORTB = 0x02;
			break;
		case state3:
			PORTB = 0x04;
			break;
		case button:
			PORTB;
			break;
		case pause:
			PORTB;
			break;
		default:
			break;
	}
			
}

int main(void) {
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(300);
	TimerOn();	
    while (1) {
	status();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
