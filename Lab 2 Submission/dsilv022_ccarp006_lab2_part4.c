/*    Connor Carpenter ccarp006@ucr.edu, David Silva dsilv022@ucr.edu
 *    Lab Section: 024
 *    Assignment: Lab 2  Exercise 4
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

#include <avr/io.h>


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; 
    DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char upper = 0x00;
	unsigned char lower = 0x00;
    while (1) 
    {
		upper = PINA & 0xF0;
		lower = PINA & 0x0F;
		
		upper = upper >> 4;
		lower = lower << 4;
		
		PORTB = upper;
		PORTC = lower;
		
    }
}

