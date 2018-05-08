/*	Partner(s) Name & E-mail: David Silva (dsilv022@ucr.edu), Connor Carpenter (ccarp006@ucr.edu)
*	Lab Section: 024
*	Assignment: Lab 08  Exercise 01
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/

#include <avr/io.h>

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
	unsigned short potent = 0x00;
	unsigned char tempB = 0x00;
	unsigned char tempA = 0x00;
	ADC_init();
    /* Replace with your application code */
    while (1) 
    {
		potent = ADC;
		tempB = (char) potent;
		tempA = (char) (potent >> 8);
		PORTD = tempA;
		PORTB = tempB;
		
    }
}

