 #include <avr/io.h>

// 5.1.1 and 5.1.2
int main(void)
{	
	DDRB = 0xFF;
	TCNT1 = 0;
	OCR1A = 15625; //16mghz divided by the number of freq in pre-scaler i.e 1024 in this case
    TCCR1A =(1<<COM1A0) | (0<<COM1A1); // the timer counter comparison 
	
	// WGM12 is 1 for CTC mode, CSnn for prescaler frequency
    TCCR1B = (1<<WGM12)|(1<<CS12) | (1<<CS10);
    
  
    while (1) 
    {
		
    }
}



// to use with an interrupt
/*
ISR(TIMER1_COMPA_vect){
	
}*/

   // WITH INTERRUPY
   /*TIMSK1 = (1<<OCIE1A); // interrupt
   sei();*/
   