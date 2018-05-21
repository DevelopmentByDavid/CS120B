/*	Partner(s) Name & E-mail: David Silva (dsilv022@ucr.edu), Connor Carpenter (ccarp006@ucr.edu)
*	Lab Section: 024
*	Assignment: Lab 10  Exercise 03
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/

#include <avr/io.h>
#include <bit.h>
#include <keypad.h>
#include <avr/interrupt.h>
#include <timer.h>
#include <scheduler.h>
#include <io.h>
#include <io.c>

task tasks[2];

const unsigned char tasksNum = 2;
const unsigned long tasksPeriodLCD = 100;
const unsigned long tasksPeriodKeyPad = 100;
const unsigned long tasksPeriodGCD = 100;

unsigned char cKey = 0;

enum SM_Update {SM_start, SM_wait, SM_display} SM_updateVar;
int TickFct_KeyPad(int state);

enum LCD_States {LCD_start, LCD_wait, LCD_display} LCD_state;
int TickFct_LCD(int state);


int main(void)
{
	DDRB = 0xFF; PORTB = 0x00; // PORTB set to output, outputs init 0s
	DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
	unsigned char  i = 0;
	tasks[i].state = SM_start;
	tasks[i].period = tasksPeriodKeyPad;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &TickFct_KeyPad;
	++i;
	tasks[i].state = LCD_start;
	tasks[i].period = tasksPeriodLCD;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &TickFct_LCD;
	
	TimerSet(tasksPeriodGCD);
	TimerOn();
	LCD_init();
	LCD_Cursor(1);
	while(1) {
		while(!TimerFlag) {
			unsigned char u;
			for (u = 0; u < tasksNum; ++u) { // Heart of the scheduler code
				if ( tasks[u].elapsedTime >= tasks[u].period ) { // Ready
					tasks[u].state = tasks[u].TickFct(tasks[u].state);
					tasks[u].elapsedTime = 0;
				}
				tasks[u].elapsedTime += tasksPeriodGCD;
			}
			tasks[u].state = tasks[u].TickFct(tasks[u].state);
		}
	}
}

int TickFct_LCD(int state) {
	static unsigned char myKey;
	switch (state) {
		case LCD_start:
			state = LCD_wait;
			break;
		case LCD_wait:
			if (myKey == cKey) {
				state = LCD_wait;
			} else {
				state = LCD_display;
			}
			break;
		case LCD_display:
			state = LCD_wait;
		default:
			state = LCD_start;
	}
	switch (state) {
		case LCD_wait:
		//do nothing
		break;
		case LCD_display:
			LCD_WriteData(cKey);
			break;
	}
	return state;
}



int TickFct_KeyPad(int state) {
	unsigned char key = GetKeypadKey();
 	switch (state) {
		case SM_start:
			state = SM_wait;
		break;
		case SM_wait:
		if (key == '\0') {
			state = SM_wait;
		} else {
			state = SM_display;
		}
		break;
		case SM_display:
		if (key == '\0') {
			state = SM_wait;
			} else {
			state = SM_display;
		}
		break;
		default:
		state = SM_start;
		break;
	}
	switch (state) {
		case SM_wait:
			//do nothing
		break;
		case  SM_display:
			switch (key) {
				case '1': cKey = "1"; break;
				case '2': cKey = "2"; break;
				case '3': cKey = "3"; break;
				case '4': cKey = "4"; break;
				case '5': cKey = "5"; break;
				case '6': cKey = "6"; break;
				case '7': cKey = "7"; break;
				case '8': cKey = "8"; break;
				case '9': cKey = "9"; break;
				case 'A': cKey = "A"; break;
				case 'B': cKey = "B"; break;
				case 'C': cKey = "C"; break;
				case 'D': cKey = "D"; break;
				case '*': cKey = "*"; break;
				case '0': cKey = "0"; break;
				case '#': cKey = "#"; break;
			}
			break;
	}
	return state;
}

