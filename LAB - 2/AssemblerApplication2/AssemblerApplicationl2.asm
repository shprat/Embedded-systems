   .include "m328def.inc" 
.org 0x0000
           RJMP begin; jump to begin  

.org 0x0004;identify the push-button/change
		   RJMP exint1;jump to sub-routine to do the job when button pressed

.org 0x0034 
 begin:    CLI
           LDI    R16,low(RAMEND)
         OUT    SPL,R16      ; stack pointer low
           LDI     R16,high(RAMEND)
         OUT    SPH, R16     ; stack pointer high
		 
		 ; whenever working with registers , load EICRA and EIMSK
		 
		 ; EICRA
		 LDI R16, (0<<ISC11) | (1<<ISC10) ; load EICRA for logical change to register
		 STS EICRA, R16 ; load for EICRA using STS as LDI doesnt work for registers

		 ;EIMSK
		 LDI R16, (1<<INT1) ; load INT1 to 1 as we using pin INT1(D3)
		 OUT EIMSK, R16  ; output 
		 

         LDI    R16,0x00
         OUT    DDRD, R16  ;data direction for all D pins

		 LDI	R16, 0xFF
		 OUT	DDRB, R16 // data direction for all B pins

		 sei ; always use sei after interrupt 

main:
           LDI     R16,0xFF 
         OUT    PORTB, R16   
           RCALL  Delay

           LDI     R16,0x00 ;r16 on
         OUT     PORTB, R16  ; activate d pins to give a value
           RCALL  Delay

		   RJMP main

; gets active when interrupt sensed(button pressed)  
exint1:;func to turn led off for a while when button pressed
	LDI R16, 0x00
	out PORTB, R16
	
	RCALL Delay
	reti

	
Delay:     LDI     R17, 0xFF 
			LDI R18, 0xFF                ; MAde 3 loops as the req val cant be achieved in hexad (for that high delay of 1s)
			LDI R19, 0x1F

loop:    DEC     R17 
           BRNE    loop             ; branch if not equal
             
		  
loop2:   LDI R17, 0xFF 
		 dec R18
		 BRNE loop   

loop3:   LDI R18, 0xFF
		 dec R19
		 BRNE loop2		
		 RET 