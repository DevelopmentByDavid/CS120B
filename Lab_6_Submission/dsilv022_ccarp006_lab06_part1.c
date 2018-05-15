/*	Partner(s) Name & E-mail: David Silva (dsilv022@ucr.edu), Connor Carpenter (ccarp006@ucr.edu)
*	Lab Section: 024
*	Assignment: Lab 06  Exercise 01
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"

enum INC_States {INC_SMStart, INC_init, INC_wait, INC_s0, INC_s0Wait, INC_s1, INC_s1Wait, INC_reset} INC_State;
unsigned char inc_button = 0;
unsigned char dec_button = 0;
unsigned char count = 0;

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s
	// AVR output compare register OCR1A.
	OCR1A = 125;    // Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}


void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}



void TickFct_IncToggle() {
	static unsigned char i = 0; //counter for holding inc or dec
	inc_button = ~PINA & 0x01;
	dec_button = ~PINA & 0x02;
	
	switch(INC_State) {
		case INC_SMStart:
			INC_State = INC_init;
		break;
			case INC_init:
		INC_State = INC_wait;
			break;
		case INC_wait:
			if (inc_button && !dec_button) {
				INC_State = INC_s0;
			} else if (dec_button && !inc_button) {
				INC_State = INC_s1;
			} else if (dec_button && inc_button) {
				INC_State = INC_reset;
			}
			break;
		case INC_s0:
			if(inc_button){
				if(dec_button){
					INC_State = INC_reset;
				}
				else{
					INC_State = INC_s0;
					++i;
				}
			}
			else{
				INC_State = INC_s0Wait;
			}
			break;
		case INC_s1:
			if(dec_button){
				if(inc_button){
					INC_State = INC_reset;
					
				}
				else{
					INC_State = INC_s1;
					++i;
				}
			}
			else{
				INC_State = INC_s1Wait;
			}
			break;
		case INC_s0Wait:
			if(dec_button && inc_button){
				INC_State = INC_reset;
			}
			else if (dec_button || inc_button) {
				INC_State = INC_s0Wait;
			} else {
				INC_State = INC_wait;
			}
			break;
		case INC_s1Wait:
			if(dec_button && inc_button){
				INC_State = INC_reset;
			}
			else if (dec_button || inc_button) {
				INC_State = INC_s1Wait;
			} else {
				INC_State = INC_wait;
			}
			break;
		case INC_reset:
			if (dec_button || inc_button) {
				INC_State = INC_reset;
			} else {
				INC_State = INC_wait;
			}
			break;
			default: INC_State = INC_SMStart;
				break;
	}
	switch(INC_State) {
		case INC_init:
				count = 0x00;
				i = 0;
			break;
		case INC_wait:
			//do nothing and wait
			break;
		case INC_s0:
			if (count < 0x09 && (i % 10 == 0 || i == 1) && i != 0)
				count += 1;
			break;
		case INC_s1:
			if (count > 0 && (i % 10 == 0 || i == 1) && i != 0)
				count -= 1;
			break;
		case INC_reset:
			count = 0x00;
			i = 0;
			break;
		case INC_s0Wait:
			i = 0;
			break;
		case INC_s1Wait:
			i = 0;
			break;
		default:
		//do nothing
		break;
	}
	LCD_ClearScreen();
	LCD_Cursor(1);
	LCD_WriteData(count + '0');
	
}

int main(void)
{
	INC_State = INC_SMStart;
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	TimerSet(100);
	TimerOn();
	LCD_init ();
	/* Replace with your application code */
	while (1)
	{
		TickFct_IncToggle();
		while (!TimerFlag){}
			TimerFlag = 0;
	}
}
