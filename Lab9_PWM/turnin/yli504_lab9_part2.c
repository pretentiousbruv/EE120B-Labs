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

unsigned char i = 0;
unsigned char j = 0;
int notes[] = {261.63, 293.66, 329.63, 349.23, 392, 440, 493.88, 523.25};
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

enum states{start, init, button1, button2, button3, wait} state;

void status(){
	switch(state){
		case start:
			state = init;
			break;

		case init:
			if(~PINA & 0x01){
				state = button1;
			}	
			else if(~PINA & 0x02){
				state = button2;
			}
			else if(~PINA & 0x04){
				state = button3;
			}
			else{
				state = init;
			}		
			break;

		case button1:
			if(~PINA & 0x01){
				state = wait;
			}
			else{
				state = init;
			}
			break;
		case button2:
			if(~PINA & 0x02){
				state = wait;
			}
			else{
				state = init;
			}
			break;

		case button3:
			if(~PINA & 0x04){
				state = wait;
			}
			else{
				state = init;
			}
			break;

		case wait:
			if((~PINA & 0x01) || (~PINA & 0x02) || (~PINA & 0x04)){
				state = wait;
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
			set_PWM(notes[i]);
			break;

		case button1:
			if(j == 0){
				j = 1;
				PWM_off();
				break;
			}
			else if(j == 1){
				j = 0;
				PWM_on();
				break;
			}

		case button2:
			if(i < 7){
				i++;
			}
			set_PWM(notes[i]);
			break;

		case button3:
			if(i > 0){
				i--;
			}
			set_PWM(notes[i]);
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
