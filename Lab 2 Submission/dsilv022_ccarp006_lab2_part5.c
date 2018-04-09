/*    Connor Carpenter ccarp006@ucr.edu, David Silva dsilv022@ucr.edu
 *    Lab Section: 024
 *    Assignment: Lab 2  Exercise 5
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */
#include <avr/io.h>


int main(void)
{
    DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0xFE; PORTB = 0x01;
	unsigned short weight = 0x00;
	unsigned char airbag = 0x00;
    while (1) 
    {
		weight = PIND;
		weight = (weight << 1) + (PINB & 0x01);
		if (weight > 0x05){
			airbag = weight >= 70 ? 0x02 : 0x04;	
			PORTB = airbag + PINB0;
			//PORTB |= ( !airbag << 2);
		}
		else{
			PORTB &= 0b00000001; 	
		}
    }
}

