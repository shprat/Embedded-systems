#include <avr/io.h>
#define F_CPU 16000000UL             // Setting CPU Frequency 16MHz
#include <util/delay.h>              // delay library
#include<avr/interrupt.h>

int clear;

void setup_adc()
{
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // enabling ADEN and prescaler setting to 128 div
	ADMUX = (1<<REFS0) | (0<<REFS1); // setting ADMUX for Avcc with external capacitor
}

int main(void)
{
	DDRD = 0xFF;
	setup_adc();
	
	
	
    while (1) {
		ADCSRA |= (1<<ADSC); // enabling ADSC
		while(ADCSRA & (1<<ADSC)); // checking loop until the value is zero
		PORTD = ADCL; // giving output acc to change
		clear = ADCH;  // clearing other value and deleting it
	}
}
