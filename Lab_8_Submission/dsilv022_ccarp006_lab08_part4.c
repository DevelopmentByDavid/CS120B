/*	Partner(s) Name & E-mail: David Silva (dsilv022@ucr.edu), Connor Carpenter (ccarp006@ucr.edu)
*	Lab Section: 024
*	Assignment: Lab 08  Exercise 02
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/

#include <avr/io.h>
#include <math.h>

#define MAX (pow(2,6))
#define step (MAX/8)

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}



int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	//unsigned short my_short = 0xABCD;
	//unsigned char my_char = (char)my_short; // my_char = 0xCD
	//my_char = (char)(my_short >> 4); // my_char = 0xBC
	unsigned short photo = 0x00;
	unsigned char tempB = 0x00;
	unsigned char tempD = 0x00;
	ADC_init();
    /* Replace with your application code */
    while (1) 
    {
		photo = ADC;
		tempB = (char) photo;
		tempD = (char) (photo >> 8);
		
		if(photo >0 && photo < step)
			PORTB = 0x01;
		else if(photo >= step && photo < 2 * step)
			PORTB = 0x03;
		else if(photo >= 2* step && photo < 3 * step)
			PORTB = 0x07;
		else if(photo >= 3* step && photo < 4 * step)
			PORTB = 0x0F;
		else if(photo >= 4 * step && photo < 5 * step)
			PORTB = 0x1F;
		else if(photo >= 5 * step && photo < 6 * step)
			PORTB = 0x3F;
		else if(photo >= 6 * step && photo <  7 * step)
			PORTB = 0x7F;
		else if(photo >= 7 * step && photo < 8 * step)
			PORTB = 0xFF;
	
    }
}

