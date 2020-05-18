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
//#include "timer.h"
#endif

void set_PWM(double frequency){ //this function sets frequency output on OC3A(PB6)
	static double current_frequency;

	if(frequency != current_frequency){
		if(!frequency){
			TCCR3B &= 0x08;
		}
		else{
			TCCR3B |= 0x03;
		}

		if(frequency < 0.954){
			OCR3A = 0xFFFF;
		}
		else if(frequency > 31250){
			OCR3A = 0x0000;
		}
		else{
			OCR3A = (short)(8000000 / (128 * frequency)) - 1;
		}

		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on(){
	TCCR3A = (1 << COM3A0);
	
	TCCR3B = (1 << WGM32) |( 1 << CS31) | (1 << CS30);

	set_PWM(0);
}

void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

enum states{start, init, button1, button2, button3} state;

void status(){
	switch(state){
		case start:
			state = init;
			break;

		case init:
			if((~PINA & 0x03) == 0x03 || (~PINA & 0x05) == 0x05 || (~PINA & 0x06) == 0x06 || (~PINA & 0x07) == 0x07){
				state = init;
			}
			else if(~PINA & 0x01){
				state = button1;
			}
			else if(~PINA & 0x02){
				state = button2;
			}
			else if(~PINA & 0x04){
				state = button3;
			}			
			break;

		case button1:
			if((~PINA & 0x03) == 0x03 || (~PINA & 0x05) == 0x05 || (~PINA & 0x06) == 0x06 || (~PINA & 0x07) == 0x07){
				state = init;
			}
			else if(~PINA & 0x01){ 
				state = button1;
			}
			else{ 
				state = init;
			}
			break;
		case button2:
			if((~PINA & 0x03) == 0x03 || (~PINA & 0x05) == 0x05 || (~PINA & 0x06) == 0x06 || (~PINA & 0x07) == 0x07){
				state = init;
			}
			else if(~PINA & 0x02){ 
				state = button2;
			}
			else{ 
				state = init;
			}
			break;

		case button3:
			if((~PINA & 0x03) == 0x03 || (~PINA & 0x05) == 0x05 || (~PINA & 0x06) == 0x06 || (~PINA & 0x07) == 0x07){
				state = init;
			}
			else if(~PINA & 0x04){ 
				state = button3;
			}
			else{ 
				state = init;
			}
			break;
		default:
			break;
	}
	
	switch(state){
		case init:
			set_PWM(0);
			break;

		case button1:
			set_PWM(261.63);
			break;

		case button2:
			set_PWM(293.66);
			break;

		case button3:
			set_PWM(329.63);
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
	PWM_on();
    while (1) {
	status();
    }
    return 1;
}
