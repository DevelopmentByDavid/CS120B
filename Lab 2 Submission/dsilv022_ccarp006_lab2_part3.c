/*    Connor Carpenter ccarp006@ucr.edu, David Silva dsilv022@ucr.edu
 *    Lab Section: 024
 *    Assignment: Lab 2  Exercise 3
 *    
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */

#include <avr/io.h>


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
    DDRC = 0xFF; PORTC = 0x00;
	unsigned char fuelLevel = 0x00;
	unsigned char lowLight = 0x00;
	unsigned char keyIn = 0x00;
	unsigned char seatbelt = 0x00;
	unsigned char seated = 0x00;
	unsigned char tempC = 0x00;
    while (1) 
    {
		switch(PINA & 0x0F){
			case 0x00:	fuelLevel = 0x00;
						lowLight = 0x01;
						break;
			case 0x01: 
			case 0x02: fuelLevel = 0x20;
						lowLight = 0x01;
				break;
			case 3:
			case 4: fuelLevel = 0x30;
					lowLight = 0x01;
				break;
			case 5:
			case 6: fuelLevel = 0x38;
					lowLight = 0x00;
				break;
			case 7:
			case 8:
			case 9: fuelLevel = 0x3C;
					lowLight = 0x00;
				break;
			case 10:
			case 11:
			case 12: fuelLevel = 0x3E;
					 lowLight = 0x00;
				break;
			case 13:
			case 14:
			case 15: fuelLevel = 0x3F;
					 lowLight = 0x00;
				break;	
		}
		
		
		tempC = fuelLevel;
		if(lowLight)
			tempC = tempC | 0x40;
			
		keyIn = PINA & 0x10;
		seated = PINA & 0x20;
		seatbelt = PINA & 0x40;
		if(keyIn && seated && !seatbelt)
			tempC = tempC | 0x80;
		PORTC = tempC;
    }
}

