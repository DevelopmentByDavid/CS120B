/*	Partner(s) Name & E-mail: David Silva (dsilv022@ucr.edu), Connor Carpenter (ccarp006@ucr.edu)
 *	Lab Section: 024
 *	Assignment: Lab 03  Exercise 01 
 *	Exercise Description: [optional - include for your own benefit]
 *		PB0 and PB1 each connect to an LED, and PB0's LED is initially on. Pressing a button
		connected to PA0 turns off PB0's LED and turns on PB1's LED, staying that way after
		button release. Pressing the button again turns off PB1's LED and turns on PB0's LED.
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>

enum LT_States {LT_SMStart, LT_wait, LT_s0, LT_s1} LT_State; 
	
void TickFct_LightToggle() {
	switch (LT_State) {
		case LT_SMStart: 
			LT_State = LT_s0;
			break;
		case LT_s0:
			if (PINA & 0x01) {
				LT_State = LT_s0;
			} else if ((PINA & 0x01) == 0x00) {
				LT_State = LT_wait;
			}
			break;
		case LT_s1:
			if (PINA & 0x01) {
				LT_State = LT_s1;
			} else if ((PINA & 0x01) == 0x00) {
				LT_State = LT_wait;
			}
			break;
		case LT_wait:
			if (PINA & 0x01) {
				if (PORTB == 0x01) {
					LT_State = LT_s1;
				} else if (PORTB == 0x02) {
					LT_State = LT_s0;
				}
			}
	}
	switch(LT_State) {
		case LT_s0:
			PORTB = 0x01;
			break;
		case LT_s1:
			PORTB = 0x02;
			break;
		default:
			PORTB = 0x01;
			break;
	}
} 

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
    /* Replace with your application code */
    while (1) 
    {
		TickFct_LightToggle();
    }
}

