/*	Partner(s) Name & E-mail: David Silva (dsilv022@ucr.edu), Connor Carpenter (ccarp006@ucr.edu)
 *	Lab Section: 024
 *	Assignment: Lab 01  Exercise 02 
 *	Exercise Description: [optional - include for your own benefit]
 *		Port A's pins 3 to 0, each connect to a parking space sensor, 1 meaning a car is parked in the space, of
		a four-space parking lot. Write a program that outputs in binary on port C the number of available spaces
		(Hint: declare a variable "unsigned char cntavail"; you can assign a number to a port as follows: PORTC
		 = cntavail;).
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xCC; PORTC = 0xFF;
	unsigned char cntAvail = 0x00;
    /* Replace with your application code */
    while (1) {
		cntAvail = 0x04;
		if (PINA & 0x01) {
			cntAvail--;
		}
		if (PINA & 0x02) {
			cntAvail--;
		}
		if (PINA & 0x04) {
			cntAvail--;
		}
		if (PINA & 0x08) {
			cntAvail--;
		}
		PORTC = cntAvail;
		
    }
}

