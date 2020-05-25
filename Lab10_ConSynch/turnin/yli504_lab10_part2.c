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
unsigned char i = 0;
unsigned char three = 0x00;

void status(){
	switch(state){
		case Start:
			state = state1;
			break;
		case state1:
			if(i == 1){
				state = state2;
			}
			i = i + 1;
			break;
		case state2:
			if(i == 2){
				state = state3;
			}
			i = i + 1;
			break;
		case state3:
			if(i == 3){
				i = 0;
				state = state1;
			}
			i = i + 1;
			break;
		default:
			break;
	}
	
	switch(state){
		case state1:
			three = 0x01;
			break;
		case state2:
			three = 0x02;
			break;
		case state3:
			three = 0x04;
			break;
		default:
			break;
	}
			
}

enum states22{start2, On, Off} state22;
unsigned char j = 0;
unsigned char blink = 0x00;

void blinkingLED(){
	switch(state2){
		case start2:
			state22 = Off;
			break;
		case Off:
			if(j == 1){
				state22 = On;
			}
			j = j + 1;
			break;
		case On:
			if(j == 2){
				j = 0;
				state22 = Off;
			}
			j = j + 1;
		default:
			break;
	}
	
	switch(state2){
		case Off:
			blink = ~blink;
			break;
		case On:
			blink = ~blink;
			break;
		default:
			break;
	}
}

void combine(){
	if(blink == 0xFF){
		PORTB  = three | 0x08;
	}
	else{
		PORTB = three;
	}
}
int main(void) {
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	volatile unsigned long LED_elapsedTime = 300;
	volatile unsigned long blink_elapsedTime = 1000;
	volatile unsigned long combinetogether = 100;
	PORTB = 0x00;
	TimerSet(100);
	TimerOn();	
    while (1) {
	if(LED_elapsedTime >= 1000){
		status();
		LED_elapsedTime = 0;
	}
	if(blink_elapsedTime >= 1000){
		blinkingLED();
		blink_elapsedTime = 0;
	}
	if(combinetogether >= 100){
		combine();
		combinetogether = 0;
	}

	while(!TimerFlag){
	}
		LED_elapsedTime += 1000;
		blink_elapsedTime += 100;
		combinetogether += 100;
		TimerFlag = 0;
    }
    return 1;
}
