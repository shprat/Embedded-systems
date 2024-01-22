#include <avr/io.h>
#define F_CPU 16000000UL // Define CPU clock as 16Mhz
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
  DDRB = 0xFF;
  DDRD = 0xFF;
  TCNT1 = 0;  // Set timer initially to 0
  
  
  TCCR1A = (1<<COM1A1) | (0<<COM1A0) | (1<<WGM11) | (1<<WGM10); // for timer comparison and fast pwm
  TCCR1B = (0 << WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS10); // for FAst PWM mode and prescaler
  
  ICR1 = 0x03FF; // input capture register , measure length of pulse
  OCR1A = 0xf;  // for pin D9(OC1A) output compare register
  
  // making brightness high and low in a loop
  while(1)
  {
	  OCR1A += 10; 
	  _delay_ms(50);
	  
	  // if max, make led brightness low again
	  if(OCR1A >= 0x03FF)
	  {
		  OCR1A = 0xf;
	  }
	  
  }
  
}



