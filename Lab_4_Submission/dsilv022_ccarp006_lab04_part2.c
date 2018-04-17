/*	Partner(s) Name & E-mail: David Silva (dsilv022@ucr.edu), Connor Carpenter (ccarp006@ucr.edu)
 *	Lab Section: 024
 *	Assignment: Lab 04  Exercise 02
 *	Exercise Description: [optional - include for your own benefit]
 *		Buttons are connected to PA0 and PA1. Output for PORTC is initially 7. Pressing PA0
		increments PORTC once (stopping at 9). Pressing PA1 decrements PORTC once
		(stopping at 0). If both buttons are depressed (even if not initially simultaneously),
		PORTC resets to 0.
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

enum INC_States {INC_SMStart, INC_init, INC_wait, INC_s0, INC_s0Wait, INC_s1, INC_s1Wait, INC_reset} INC_State;

void TickFct_IncToggle() {
	switch(INC_State) {
		case INC_SMStart:
			INC_State = INC_init;
			break;
		case INC_init:
			INC_State = INC_wait;
			break;
		case INC_wait:
			if ((PINA & 0x03) == 0x02) {
				INC_State = INC_s0;
			} else if ((PINA & 0x03) == 0x01) {
				INC_State = INC_s1;
			} else if ((PINA & 0x03) == 0x00) {
				INC_State = INC_reset;
			}
			break;
		case INC_s0:
			INC_State = INC_s0Wait;
			break;
		case INC_s1:
			INC_State = INC_s1Wait;
			break;
		case INC_s0Wait:
			if ((PINA & 0x03) != 0x03) {
				INC_State = INC_s0Wait;
			} else {
				INC_State = INC_wait;
			}
			break;
		case INC_s1Wait:
			 if ((PINA & 0x03) != 0x03) {
				 INC_State = INC_s1Wait;
			 } else {
				INC_State = INC_wait;
			 }
			break;
		case INC_reset:
			 if ((PINA & 0x03) != 0x03) {
				 INC_State = INC_reset;
			 } else {
				 INC_State = INC_wait;
			 }
			break;
	}
	switch(INC_State) {
		case INC_init:
			PORTC = 0x07;
			break;
		case INC_wait:
		//do nothing and wait
			break;
		case INC_s0:
			if (PORTC < 0x09)
				PORTC += 1;
			break;
		case INC_s1:
			if (PORTC > 0)
				PORTC -= 1;
			break;
		case INC_reset:
			PORTC = 0x00;
			break;
		case INC_s0Wait:
			//do nothing
			break;
		case INC_s1Wait:
			//do nothing
			break;
		default:
			//do nothing
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
    /* Replace with your application code */
    while (1) 
    {
		TickFct_IncToggle();
    }
}

