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
#include "timer.h"
#endif

enum states1{start1, init1, LED1, LED2, LED3} state1;
enum states2{start2, init2, On, Off} state2;
enum states3{start3, combineLED} state3;

unsigned char LEDpos = 0x00;
unsigned char OnOff = 0x00;
unsigned char count = 0x01;
unsigned char sig = 0x00;

void threeLEDs(){
	switch(state1){
		case start1:
			state1 = init1;
			break;
		case init1:
			if(count & 0x01){
				state1 = LED1;
			}
			if(count & 0x02){
				state1 = LED2;
			}
			if(count & 0x04){
				state1 = LED3;
			}
			else{
				state1 = init1;
			}
			break;
		case LED1:
			count = 0x02;
			break;
		case LED2:
			count = 0x04;
			break;
		case LED3:
			count = 0x01;
			break;
		default:
			break;		
	}

	switch(state1){
		case LED1:
			LEDpos = 0x01;
			break;
		case LED2:
			LEDpos = 0x02;
			break;
		case LED3:
			LEDpos = 0x04;
			break;
		default:
			break;
	}
}

void blinkingLED(){
	switch(state2){
		case start2:
			state2 = init2;
			break;
		case init2:
			if(sig & 0x01){
				state2 = On;
			}
			if(sig & 0x00){
				state2 = Off;
			}
			else{
				state2 = init2;
			}
			break;
		case On:
			sig = 0x00;
			break;
		case Off:
			sig = 0x01;
			break;
		default:
			break;
	}
	
	switch(state2){
		case On:
			OnOff = 0x08;
			break;
		case Off:
			OnOff = 0x00;
			break;
		default:
			break;
	}
}

void combine(){
	switch(state3){
		case start3:
			state3 = combineLED;
			break;
		case combineLED:
			break;
		default:
			break;
	}

	switch(state3){
		case combineLED:
			PINB = LEDpos | OnOff;
			break;
		default:
			break;
	}
}

int main(void){
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
    /* Insert your solution below */
	TimerSet(1000);
	TimerOn();
    while (1){
	threeLEDs();
	blinkingLED();
	combine();
	while(!TimerFlag){
		TimerFlag = 0;
	}
    }
    return 1;
}
