/*
 * dsilv022_ccarp006_lab10_part1.c
 *
 * Created: 5/14/2018 1:34:06 PM
 * Author : David
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
const unsigned long tasksPeriodLCD = 1000;
const unsigned long tasksPeriodKeyPad = 1000;
const unsigned long tasksPeriodGCD = 1000;

unsigned char cKey = 0; //current key displayed
unsigned char pKey = 0; //current key pressed

enum KPAD_States {KPAD_start, KPAD_wait,KPAD_display, KPAD_waitRelease} KPAD_State;
int TickFct_KeyPad(int state);

enum LCD_States {LCD_start, LCD_wait, LCD_display} LCD_state;
int TickFct_LCD(int state);


int main(void)
{
	DDRA = 0xFF; PORTA = 0x00; 
	DDRC = 0x00; PORTC = 0xFF; 
	DDRD = 0xFF; PORTC = 0x00;
	unsigned char  i = 0;
	tasks[i].state = KPAD_start;
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
			
		}
		unsigned char u;
		for (u = 0; u < tasksNum; ++u) { // Heart of the scheduler code
			if ( tasks[u].elapsedTime >= tasks[u].period ) { // Ready
				tasks[u].state = tasks[u].TickFct(tasks[u].state);
				tasks[u].elapsedTime = 0;
			}
			tasks[u].elapsedTime += tasksPeriodGCD;
		}
		tasks[u].state = tasks[u].TickFct(tasks[u].state);
		TimerFlag = 0;
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
			myKey = cKey;
			break;
	}
	return state;
}



int TickFct_KeyPad(int state) {
	unsigned char key = GetKeypadKey();
 	switch (state) {
		case KPAD_start:
			state = KPAD_wait;
		break;
		case KPAD_wait:
		if (key == '\0') {
			state = KPAD_wait;
		} else {
			state = KPAD_display;
		}
		break;
		case KPAD_display:
		if (key == '\0') {
			state = KPAD_wait;
		} else {
			state = KPAD_waitRelease;
		}
		break;
		case KPAD_waitRelease:
			state = KPAD_wait;
			break;
		default:
		state = KPAD_start;
		break;
	}
	switch (state) {
		case KPAD_wait:
			//do nothing
		break;
		case  KPAD_display:
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

