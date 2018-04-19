#include <avr/io.h>

enum SM_Christmas {SM_start, SM_wait,SM_invert, SM_button_wait} SM_var;
unsigned char someVar = 0;
void tickFct() {
	someVar = PINB;
    switch (SM_var) {
        case SM_start:
            SM_var = SM_wait;
			PINB = 0x0A;
            break;
        case SM_wait:
            if (!(PINA & 0x01)) {
                SM_var = SM_invert;
            } else {
                SM_var = SM_wait;
            }
            break;
        case SM_invert:
            SM_var = SM_button_wait;
            break;
		case SM_button_wait: SM_var = !(PINA & 0x01) ? SM_button_wait : SM_wait;
		break;
    }
    switch (SM_var) {
        case SM_wait:
            //do nothing
            break;
        case SM_invert:
            PORTB = 0x00; PORTB = ~((someVar) & 0x0F);
            break;
        default:
            //do nothing
            break;
    }
}

int main(void)
{
	SM_var = SM_start;
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	while (1)
	{
		tickFct();		
	}
}
