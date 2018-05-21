/*
 * dsilv022_ccarp006_lab10_part2.c
 *
 * Created: 5/20/2018 7:40:22 PM
 * Author : David
 */ 

#include <avr/io.h>
#include <timer.h>
#include <io.h>
#include <io.c>


int main(void)
{
	DDRD = 0xFF; PORTD = 0x00;
	DDRA = 0xFF; PORTA = 0x00;
	
	LCD_init();
	
	LCD_DisplayString(1, "hello world");
    /* Replace with your application code */
    while (1) 
    {
		continue;
    }
}

