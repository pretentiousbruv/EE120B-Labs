/*	Author: yli504
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	part 1 demo: https://drive.google.com/open?id=19xJOCvinmSx4nY_r6JZ3kDifcBLq8k0R
 *	part 2 demo:
 *	part 3 demo:
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

int main(void) {
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(1000);
	TimerOn();
	unsigned char tempB = 0x01;
	unsigned char i = 0;  
    while (1) {
	if(i == 0){
		tempB = 0x01;
	}

	if(i == 1){
		tempB = 0x02;
	}

	if(i == 2){
		tempB = 0x04;
	}
	
	i = i + 1;
	if(i == 3){
		i = 0;
	}

	PORTB = tempB;
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
