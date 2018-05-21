/*	Partner(s) Name & E-mail: David Silva (dsilv022@ucr.edu), Connor Carpenter (ccarp006@ucr.edu)
*	Lab Section: 024
*	Assignment: Lab 10  Exercise 01
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/

#include <avr/io.h>
#include <bit.h>
#include <keypad.h>
#include <avr/interrupt.h>
#include <timer.h>
#include <scheduler.h>

task tasks;

const unsigned char tasksNum = 1;
//const unsigned long tasksPeriodUpdate = 100;
//const unsigned long tasksPeriodGCD = 100;

enum SM_Update {SM_start, SM_wait, SM_display} SM_updateVar;
int TickFct_Update(int state);

//enum Check_States {Check_start, Check_col1, Check_col2, Check_col3, Check_col4} Check_checkVar;
//int TickFct_Check(int state);

// Returns '\0' if no key pressed, else returns char '1', '2', ... '9', 'A', ...
// If multiple keys pressed, returns leftmost-topmost one
// Keypad must be connected to port C
/* Keypad arrangement
        PC4 PC5 PC6 PC7
   col  1   2   3   4
row
PC0 1   1 | 2 | 3 | A
PC1 2   4 | 5 | 6 | B
PC2 3   7 | 8 | 9 | C
PC3 4   * | 0 | # | D
*/
//unsigned char GetKeypadKey() {
//
	//PORTC = 0xEF; // Enable col 4 with 0, disable others with 1’s
	//asm("nop"); // add a delay to allow PORTC to stabilize before checking
	//if (GetBit(PINC,0)==0) { return('1'); }
	//if (GetBit(PINC,1)==0) { return('4'); }
	//if (GetBit(PINC,2)==0) { return('7'); }
	//if (GetBit(PINC,3)==0) { return('*'); }
//
	//// Check keys in col 2
	//PORTC = 0xDF; // Enable col 5 with 0, disable others with 1’s
	//asm("nop"); // add a delay to allow PORTC to stabilize before checking
	//if (GetBit(PINC,0)==0) { return('2'); }
	//if (GetBit(PINC,1)==0) { return('5'); }
	//if (GetBit(PINC,2)==0) { return('8'); }
	//if (GetBit(PINC,3)==0) { return('0'); }
	//// ... *****FINISH*****
//
	//// Check keys in col 3
	//PORTC = 0xBF; // Enable col 6 with 0, disable others with 1’s
	//asm("nop"); // add a delay to allow PORTC to stabilize before checking
	//// ... *****FINISH*****
	//if (GetBit(PINC,0)==0) { return('3'); }
	//if (GetBit(PINC,1)==0) { return('6'); }
	//if (GetBit(PINC,2)==0) { return('9'); }
	//if (GetBit(PINC,3)==0) { return('#'); }
//
	//// Check keys in col 4	
	//// ... *****FINISH*****
	//PORTC = 0x7F; // Enable col 6 with 0, disable others with 1’s
	//asm("nop"); // add a delay to allow PORTC to stabilize before checking
	//// ... *****FINISH*****
	//if (GetBit(PINC,0)==0) { return('A'); }
	//if (GetBit(PINC,1)==0) { return('B'); }
	//if (GetBit(PINC,2)==0) { return('C'); }
	//if (GetBit(PINC,3)==0) { return('D'); }
		//
	//return('\0'); // default value
//
//}

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00; // PORTB set to output, outputs init 0s
	DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
	unsigned char  i = 0;
	tasks.state = SM_start;
	//tasks[i].period = tasksPeriodUpdate;
	//tasks[i].elapsedTime = 0;
	tasks.TickFct = &TickFct_Update;
	
	//TimerSet(tasksPeriodGCD);
	//TimerOn();
	
	while(1) {
		//while(!TimerFlag){
			//unsigned char u;
			//for (u = 0; u < tasksNum; ++u) { // Heart of the scheduler code
				//if ( tasks[u].elapsedTime >= tasks[u].period ) { // Ready
					//tasks[u].state = tasks[u].TickFct(tasks[u].state);
					//tasks[u].elapsedTime = 0;
				//}
				//tasks[u].elapsedTime += tasksPeriodGCD;
			//}
			tasks.state = tasks.TickFct(tasks.state);
		//}
	}
}

int TickFct_Update(int state) {
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
			PORTB = 0x1F;
		break;
		case  SM_display:
			switch (key) {
				case '1': PORTB = 0x01; break;
				case '2': PORTB = 0x02; break;
				case '3': PORTB = 0X03; break;
				case '4': PORTB = 0x04; break;
				case '5': PORTB = 0x05; break;
				case '6': PORTB = 0x06; break;
				case '7': PORTB = 0x07; break;
				case '8': PORTB = 0x08; break;
				case '9': PORTB = 0x09; break;
				case 'A': PORTB = 0x0A; break;
				case 'B': PORTB = 0x0B; break;
				case 'C': PORTB = 0x0C; break;
				case 'D': PORTB = 0x0D; break;
				case '*': PORTB = 0x0E; break;
				case '0': PORTB = 0x00; break;
				case '#': PORTB = 0x0F; break;
			}
			break;
	}
	return state;
}

