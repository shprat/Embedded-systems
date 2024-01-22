#include <avr/io.h>
#define F_CPU 16000000UL // Define CPU clock as 16Mhz
#include <util/delay.h>
#include <avr/interrupt.h>
#include<stdlib.h>
/*
Haider Qaizar Hussain
hhussain@jacobs-university.de
*/


/*

3-LED's DARK TO BRIGHT INITIALLY
POTENTIOMETER - MAX BRIGHTNESS
BUTTON -> D-B
		B-D
		
As the input wasnot specified and led's were to show same behaviour,
I used one led ouptut (OCR1A)

*/

char c;

void D_B()
{
	c = 'y';
	// taking max brightness from potentiometer( set start conversion bit)
	ADCSRA |= (1<<ADSC); // enabling ADSC
	OCR1A += 10; // increasing brightness
	_delay_ms(50);
	
	// if max, make led brightness low again
	if(OCR1A >= ADC*64)
	{
		OCR1A = 0xf;// decreasing again to maintain flow
		sei();  // enabling input so new input can be taken
	}
}
void B_D()
{
	c = 'n';
	ADCSRA |= (1<<ADSC); //enabling ADSC
	OCR1A = ADC * 64; // setting value for comparison
	while(1)
	{
		OCR1A -= 10;
		_delay_ms(50);
		ADCSRA |= 1 << ADSC;
		// if low, make led brightness high again
		if(OCR1A <= 0xf)
		{
			OCR1A = ADC * 64;
			sei(); // enabling interrupt so new input can be taken
		}
	}
}

int main(void)
{
	DDRB = 0xFF;

	TCNT1 = 0;  // Set timer initially to 0

	
	// Setting up external interrupt
	EIMSK  = 0b000000001;	// Enable external interrupt (INT0)
	EICRA  = 0b000000001;	// Trigger on rising edge
	DDRD   &= (0 << 2); // setting INT0 to input
	sei(); // enabling interrupt
	
	// Working for potentiometer control(ADC)
	ADCSRA = 0b10000111;	// Enable Analog Digital Converter, set prescaler to 128
	ADCSRB = 0b00000000;	// Free Running mode
	ADMUX  = 0b00000000;	// Select ADC0 as input, AREF pin to be V_Ref
	DDRC = 0x00; // setting port D as input for potentiometer
	
		
	TCCR1A = (1<<COM1A1) | (0<<COM1A0) | (1<<WGM11) | (1<<WGM10); // for timer comparison and fast pwm
	TCCR1B = (0 << WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS10); // for FAst PWM mode and prescaler
	


	ICR1 = 0x3FF; // input capture register , measure length of pulse
	OCR1A = 0xf;  // for pin D9(OC1A) output compare register
	
	// making brightness high and low in a loop
	while(1)
	{
		// taking max brightness from potentiometer( set start conversion bit)
		ADCSRA |= (1<<ADSC);
		OCR1A += 10; // increasing brightness
		_delay_ms(50);
		
		// if max, make led brightness low again
		if(OCR1A >= ADC*64)
		{
			OCR1A = 0xf;// decreasing again to maintain flow
		}
	}
	
}

// external interrupt
ISR(INT0_vect)
{
	while(1)
	{
		//To alter brightness with ADC
		ADCSRA = 0b10000111;	// Enable Analog Digital Converter, set prescaler to 128
		ADCSRB = 0b00000000;	// Free Running mode
		ADMUX  = 0b00000000;	// Select ADC0 as input, AREF pin to be V_Ref
		DDRC = 0x00; // setting port D as input for potentiometer
		
		
		if(c == 'y') // checking if the method for dark - bright is on
		{
			B_D(); // calling bright - dark function
			cli(); // disable interrupt so new input can be taken
		}
		
		else // checking if bright - dark
		{
			D_B(); // calling dark - bright function
			cli();// disable interrupt so new input can be taken
		}
	}
}
