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
int led[] = {0x01, 0x02, 0x04, 0x02, 0x01, 0x02, 0x04, 0x02}; 

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

enum states{start, init, button, pause, buttonagain} state;

void status(){
	switch(state){
		case start:
			state = init;
			break;

		case init:
			if(~PINA & 0x01){
				state = button;
			}
			break;

		case button:
			if(~PINA & 0x01){ 
				state = button;
			}
			else{ 
				state = pause;
			}
			break;

		case pause:
			if(~PINA & 0x01){ 
				state = buttonagain;
			}
			else{
				state = pause;
			}
			break;

		case buttonagain:
			if(~PINA & 0x01){ 
				state = buttonagain;
			}
			else{
				state = init;
			}

		default:
			break;
	}
	
	switch(state){
		case init:
			PORTB = led[i];
			i++;
			if(i >= 8){ 
				i = 0;
			}
			break;
		default:
			break;
	}
			
}

int main(void) {
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x01;
	TimerSet(300);
	TimerOn();	
    while (1) {
	status();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
