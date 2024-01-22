#include <avr/io.h>
#define F_CPU 16000000UL // Define CPU clock as 16Mhz
#include <util/delay.h>
#include <avr/interrupt.h>

int clear;
int buttonpress;

int main(void)
{

	DDRB = 0xFF;
	TCNT1 = 0;  // Set timer initially to 0
	
	// FOR POTENTIOMETER
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // enabling ADEN and prescaler setting to 128 div
	ADMUX = (1<<REFS0) | (0<<REFS1); // setting ADMUX for Avcc with external capacitor

	// FOR BUTTON
	EICRA = (0<<ISC01) | (1<<ISC00);
	EIMSK = 0b00000001;
	sei();
	
	TCCR1A = (1<<COM1A1) | (0<<COM1A0) | (1<<COM1B1) | (0<<COM1B0) |(1<<WGM11) | (1<<WGM10); // for timer comparison and fast pwm
	TCCR1B = (0 << WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS10); // for FAst PWM mode and prescaler
	
	ICR1 = 0x03FF; // input capture register , measure length of pulse
	//OCR1A = 0xf;  // for pin D9(OC1A) output compare register
	//OCR1B = 0xf;	
	//making brightness high and low in a loop
	while(1)
	{	
		PORTB = 0x00;
		
	}
}

ISR(INT0_vect)
{
	
		if(buttonpress == 0)
		{
			OCR1A = 0xf;
			ADCSRA |= (1<<ADSC);
			while(ADCSRA & (1<<ADSC));
			OCR1A = ADCL;
			clear = ADCH;		
			buttonpress++;
		}
		
		else if(buttonpress != 0)
		{
			OCR1B = 0xf;
			ADCSRA |= (1<<ADSC);
			while(ADCSRA & (1<<ADSC));
			OCR1B = ADCL;
			clear = ADCH;
		}
		
		else
		{
			PORTB = 0x00;
		}
}