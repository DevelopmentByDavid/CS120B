enum SM_Christmas {SM_start, SM_wait,SM_invert} SM_var;
unsigned char someVar = PINB;
tickFct() {
    switch (SM_var) {
        case SM_start:
            SM_var = SM_wait;
            break;
        case SM_wait:
            if (!(PINA & 0x01)) {
                SM_var = SM_invert;
            } else {
                SM_var = SM_wait;
            }
            break;
        case SM_invert:
            SM_var = SM_wait;
            break;
    }
    switch (SM_var) {
        case SM_wait:
            //do nothing
            break;
        case SM_invert:
            PINB = ~(someVar);
            break;
        default:
            //do nothing
            break;
    }
}
