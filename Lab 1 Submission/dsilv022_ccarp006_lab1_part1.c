/*	Partner(s) Name & E-mail: David Silva (dsilv022@ucr.edu), Connor Carpenter (ccarp006@ucr.edu)
 *	Lab Section: 024
 *	Assignment: Lab 01  Exercise 01 
 *	Exercise Description: [optional - include for your own benefit]
 *		Garage open at night-- A garage door sensor connects to PA0 (1 means door open), and a light sensor
		connects to PA1 (1 means light is sensed). Write a program that illuminates an LED connected to PB0 (1
		means illuminate) if the garage door is open at night.
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	unsigned char garage = 0x00;
	unsigned char lSens = 0x00;
    while(1)
    {
        //TODO:: Please write your application code 
		
		
		garage = PINA & 0x01;
		lSens = PINA & 0x02;
		PORTB = garage & !lSens;
    }
}