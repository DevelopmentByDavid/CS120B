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

task tasks[1];

const unsigned char tasksNum = 1;
//const unsigned long tasksPeriodLCD = 100;
const unsigned long tasksPeriodKeyPad = 100;
const unsigned long tasksPeriodGCD = 100;

unsigned char cKey; //current key displayed

enum KPAD_States {KPAD_start, KPAD_wait, KPAD_waitRelease, KPAD_set} KPAD_State;
int TickFct_KeyPad(int state);

//enum LCD_States {LCD_start, LCD_wait, LCD_display} LCD_state;
//int TickFct_LCD(int state);


int main(void)
{
	DDRA = 0xFF; PORTA = 0x00; //output
	DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
	DDRD = 0xFF; PORTC = 0x00; //output
	unsigned char  i = 0;
	tasks[i].state = KPAD_start;
	tasks[i].period = tasksPeriodKeyPad;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &TickFct_KeyPad;
	//++i;
	//tasks[i].state = LCD_start;
	//tasks[i].period = tasksPeriodLCD;
	//tasks[i].elapsedTime = 0;
	//tasks[i].TickFct = &TickFct_LCD;
	
	TimerSet(tasksPeriodGCD);
	TimerOn();
	LCD_init();
	LCD_Cursor(1);
	
	unsigned char u;
	while(1) {
		for (u = 0; u < tasksNum; u++) { // Heart of the scheduler code
			if ( tasks[u].elapsedTime >= tasks[u].period ) { // Ready
				tasks[u].state = tasks[u].TickFct(tasks[u].state);
				tasks[u].elapsedTime = 0;
			}
			tasks[u].elapsedTime += tasksPeriodGCD;
		}
		while(!TimerFlag) {}
		TimerFlag = 0;
	}
}

//int TickFct_LCD(int state) {
	//switch (state) {
		//case LCD_start:
			//state = LCD_wait;
			//break;
		//case LCD_wait:
			//if (cKey) {
				//state = LCD_display;
			//} else {
				//state = LCD_wait;
			//}
			//break;
		//case LCD_display:
			//state = LCD_wait;
			//break;
		//default:
			//state = LCD_start;
	//}
	//switch (state) {
		//case LCD_wait:
			////do nothing
			//break;
		//case LCD_display:
			////LCD_DisplayString(1,cKey);
			////cKey = NULL;
			//break;
	//}
	//return state;
//}



int TickFct_KeyPad(int state) {
	unsigned char key = GetKeypadKey();
	static unsigned char prevKey;
 	switch (state) {
		case KPAD_start:
			state = KPAD_wait;
		break;
		case KPAD_wait:
		if (key == '\0' || prevKey == key) {
			state = KPAD_wait;
		} else {
			state = KPAD_waitRelease;
			prevKey = key;
		}
		break;
		case KPAD_waitRelease:
			if (key == '\0') {
				state = KPAD_set;
			} else {
				state = KPAD_waitRelease;
			}
			break;
		case KPAD_set:
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
		case KPAD_waitRelease:
			//do nothing
		break;
		case KPAD_set:
			switch (prevKey) {
				case '1': LCD_DisplayString(1, "1"); break;
				case '2': LCD_DisplayString(1, "2"); break;
				case '3': LCD_DisplayString(1, "3"); break;
				case '4': LCD_DisplayString(1, "4"); break;
				case '5': LCD_DisplayString(1, "5"); break;
				case '6': LCD_DisplayString(1, "6"); break;
				case '7': LCD_DisplayString(1, "7"); break;
				case '8': LCD_DisplayString(1, "8"); break;
				case '9': LCD_DisplayString(1, "9"); break;
				case 'A': LCD_DisplayString(1, "A"); break;
				case 'B': LCD_DisplayString(1, "B"); break;
				case 'C': LCD_DisplayString(1, "C"); break;
				case 'D': LCD_DisplayString(1, "D"); break;
				case '*': LCD_DisplayString(1, "*"); break;
				case '0': LCD_DisplayString(1, "0"); break;
				case '#': LCD_DisplayString(1, "#"); break;
			}
			break;
	}
	return state;
}

