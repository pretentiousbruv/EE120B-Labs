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
#include "io.h"
#endif

volatile unsigned char TimerFlag =  0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char i = 0;

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
			LCD_Cursor(1);
			LCD_WriteData(i + '0');
			break;	
		case inc:
			if(i < 9){
				i = i + 1;
				LCD_Cursor(1);
				LCD_WriteData(i + '0');
			}
			break;
		case dec:
			if(i > 0){
				i = i - 1;
				LCD_Cursor(1);
				LCD_WriteData(i + '0');
			}
			break;
		case reset:
			i = 0;
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRC = 0xFF;	PORTC = 0x00;
	DDRD = 0xFF;	PORTD = 0x00;
    /* Insert your solution below */
	TimerSet(1000);
	TimerOn();
    while (1) {
	continue;
	status();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
