/*    Connor Carpenter ccarp006@ucr.edu, David Silva dsilv022@ucr.edu
 *    Lab Section: 024
 *    Assignment: Lab 2  Exercise 1 
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */


#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char tempA = 0x00;
	unsigned char tempB = 0x00;
	unsigned char count = 0x00;
    while (1) 
    {
		tempA = PINA;
		tempB = PINB;
		count = 0x00;
		while(tempA || tempB){
			if(tempA & 0x01) 
				count++;
				
			if(tempB & 0x01) 	
				count++;
			
			tempA = tempA >> 1;
			tempB = tempB >> 1;
		}
		PORTC = count;
    }
}

