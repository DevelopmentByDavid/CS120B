/*	Partner(s) Name & E-mail: David Silva (dsilv022@ucr.edu), Connor Carpenter (ccarp006@ucr.edu)
*	Lab Section: 024
*	Assignment: Lab 10  Exercise 02
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/
#include <avr/io.h>
#include <timer.h>
#include <io.h>
#include <scheduler.h>
#include "io.c"


const unsigned long tasksPeriod = 1000;
const unsigned long tasksPeriodGCD = 1000;
const unsigned char tasksNum = 1;

unsigned char size = 37;
unsigned char screenSize = 31;
unsigned char myString[] = "CS120B is Legend... wait for it DARY!";
enum SM_scroll {SM_start, SM_advance, SM_clear} mySM;
	
task myTask;

int myTick (int state) {
	static unsigned char q = 17;
	unsigned char stringIndex = 0;
	switch(state) {
		case SM_start:
			state = SM_advance;
			break;
		case SM_advance:
			if (q < size) {
				state = SM_advance;
			} else {
				state = SM_clear;
			}
			break;
		case SM_clear:
			state = SM_advance;
			break;
		default:
			state = SM_start;
			break;
	}
	switch(state) {
		case SM_advance:
		if (q > 15) {
			stringIndex = q - 17;
		}
		for (unsigned char p = 0; p < 15; p++) {
			LCD_Cursor(p);
			if (stringIndex < q) {
				LCD_WriteData(myString[stringIndex]);
			}
			stringIndex++;
		}
		q++;
			break;
		case SM_clear:
			q = 0;
			LCD_ClearScreen();
			break;
	}
	return state;
}


int main(void)
{
	DDRD = 0xFF; PORTD = 0x00;
	DDRA = 0xFF; PORTA = 0x00;
	 LCD_init();
	unsigned char i = 0;
	myTask.state = SM_start;
	myTask.period = tasksPeriod;
	myTask.elapsedTime = 0;
	myTask.TickFct = &myTick;

	TimerSet(tasksPeriodGCD);
	TimerOn();
    while (1) 
    {
		while(!TimerFlag) {
			unsigned char u;
			for (u = 0; u < tasksNum; ++u) { // Heart of the scheduler code
				if ( myTask.elapsedTime >= myTask.period ) { // Ready
					myTask.state = myTask.TickFct(myTask.state);
					myTask.elapsedTime = 0;
				}
					myTask.elapsedTime += tasksPeriodGCD;
				}
			myTask.state = myTask.TickFct(myTask.state);
		}
    }
}

