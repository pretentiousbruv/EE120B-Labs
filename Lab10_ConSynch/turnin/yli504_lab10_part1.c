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
unsigned int count = 0;
unsigned int sig = 0;

void threeLEDs(){
	switch(state1){
		case start1:
			state1 = init1;
			break;
		case init1:
			if(count >= 0 && count <= 1000){
				state1 = LED1;
			}
			else if(count >= 1001 && count <= 2000){
				state1 = LED2;
			}
			else if(count >= 2001 && count <= 3000){
				state1 = LED3;
			}
			break;
		case LED1:
			count++;
			break;
		case LED2:
			count++;
			break;
		case LED3:
			count++;
			if(count >= 3000){
				count = 0;
			}
			break;
		default:
			break;		
	}

	switch(state1){
		case LED1:
			LEDpos = (LEDpos & 0x00) | 0x01;
			break;
		case LED2:
			LEDpos = (LEDpos & 0x00) | 0x02;
			break;
		case LED3:
			LEDpos = (LEDpos & 0x00) | 0x04;
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
			if(sig >= 0 && sig <= 1000){
				state2 = Off;
			}
			else if(sig >= 1001 && sig <= 2000){
				state2 = On;
			}
			break;
		case Off:
			sig++;
			break;
		case On:
			sig++;
			if(sig >= 2000){
				sig = 0;
			}
			break;
		default:
			break;
	}
	
	switch(state2){
		case On:
			OnOff = (OnOff & 0x00) | 0x08;
			break;
		case Off:
			OnOff = OnOff & 0x00;
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
	TimerSet(1);
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
