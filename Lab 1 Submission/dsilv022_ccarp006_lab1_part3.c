/*	Partner(s) Name & E-mail: David Silva (dsilv022@ucr.edu), Connor Carpenter (ccarp006@ucr.edu)
 *	Lab Section: 024
 *	Assignment: Lab 01  Exercise 03 
 *	Exercise Description: [optional - include for your own benefit]
 *		Extend the previous program to still write the available spaces number, but only to PC3..PC0, and to set
		PC7 to 1 if the lot is full.
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>


int main(void)
{
    
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xCC; PORTC = 0xFF;
    unsigned char cntAvail = 0x00;
	
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
		
		if (cntAvail == 0x00) {
			PORTC = 0x80;
		}
    }
}

