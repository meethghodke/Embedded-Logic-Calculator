/**
	@author Meet Hemant Ghodke
	@version 0.1
	@file main.c
	@brief Software for experiment Simple Calculator
*/

/**
	@brief The CPU speed in Hz
*/
#define F_CPU 8000000UL 
/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd.h"
#include "init.h"
#include <avr/interrupt.h>
/******************************************************************************/
 
	    uint32_t value_1 = 0, value_2 = 0;
        uint32_t sum = 0 ;
		uint32_t product = 1; 
		int32_t difference = 0;
        uint32_t sqr1 = 1, sqr2 = 1;
		char line[16];
int main(void)
{
	DDRB &= ~(1<<DDB0);
	DDRB &= ~(1<<DDC0);
	PORTB |= (1<<PB0);
    PORTC |= (1<<PC0);
      PCICR |= (1<<PCIE0)|(1<<PCIE1);
      PCMSK0 |= (1<<PCINT0);
      PCMSK1 |= (1<<PCINT8);
	ADMUX = (1<<REFS0); //PC0 as potentiometers
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);   //Enable the ADC with 64 prescaler division factor
	lcd_init();
       sei();
	for(;;)
	{
		ADMUX |= (1<<MUX0);
		ADCSRA |= (1<<ADSC);
		while(ADCSRA &(1<<ADSC));
		value_1 = ADCW; 
        if(value_1>1000) 
		{
			value_1=999;
		}
		ADMUX &= ~ (1<<MUX0);
		ADMUX |= (1<<MUX1);
		ADCSRA |= (1<<ADSC);
		while(ADCSRA &(1<<ADSC));
		value_2 = ADCW;
         if(value_2>1000)
		 {
		 value_2=999;
		 }
		 else if(value_2 < 0)
		 {
			 value_2 = 1;
		 }
         ADMUX &= ~(1<<MUX1);
         sum = value_1 + value_2;
         difference = value_1 - value_2;
         product = value_1*value_2;
         lcd_clear();
 		 lcd_setcursor(0,1);
		sprintf(line,"%3ld +%4ld - %3ld",value_1,sum , difference);
		lcd_string(line);
        lcd_setcursor(0,2);
		sprintf(line,"%3ld *%6ld /%ld.%ld",value_2,product ,value_1/value_2 ,((value_1%value_2)*10)/value_2);
		lcd_string(line);
		 _delay_ms(700);
	}
	return 0;
}
       
        ISR(PCINT0_vect)
         { 
        sqr1 = value_1*value_1;
		sqr2 = value_2*value_2;
        lcd_clear();
		sprintf(line, "SQR1: %7ld",sqr1);
	    lcd_setcursor(0,1);
	    lcd_string(line);
		sprintf(line, "SQR2: %7ld",sqr2);
	    lcd_setcursor(0,2);
	    lcd_string(line);
		_delay_ms(1500);
          }
       ISR(PCINT1_vect)
         {
        lcd_clear();
		sprintf(line, "No.1 HEX: %x",value_1);
	    lcd_setcursor(0,1);
	    lcd_string(line);
		sprintf(line, "No.2 HEX: %x",value_2);
	    lcd_setcursor(0,2);
	    lcd_string(line);
		_delay_ms(1500);
          }
		
		
	
	
