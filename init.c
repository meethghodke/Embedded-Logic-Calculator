
/*
This file contains all init steps in one function.
To call this function just use init();
*/

#include <avr/io.h>
#include "init.h"

void init(void){

    DDRB &= ~(1<<DDB0);  //connect push button 0 to PB0
	DDRB &= ~(1<<DDC0);  //connect push button 1 to PB1
	PORTB |= (1<<PB0);   //enable the pullup
	PORTB |= (1<<PC0);   //enable the pullup

}
