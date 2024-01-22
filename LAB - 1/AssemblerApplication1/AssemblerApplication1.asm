   .include "m328def.inc" 
.org 0x0000 ; for reset
           RJMP begin; jump to begin  
.org 0x0034  ; sets R16 register high thru LDI

 begin:    CLI  ; disable interrupts during timed/ avoid interrupts
           LDI    R16,low(RAMEND)
         OUT    SPL,R16 ; set stack pointer to top of ram
           LDI     R16,high(RAMEND) ; load  register(R16) to high
         OUT    SPH, R16                
         LDI    R16,0xFF ; 
         OUT    DDRD, R16   ; Control direction(out/in) of port
           LDI     R16,0xFF ; Turn on as high(loads value 0xFF to the register)
         OUT    PORTD, R16 (Contains value for port + sends data to PORT D as (PORT"D")
           RCALL  Delay ; calls our function delay
           LDI     R16,0x00 ; turn of as low value send,  loads 0x00 to R16
         OUT     PORTD, R16 ; sends 0x00 from register R16 to PORTD as loaded above
           RCALL  Delay

		   ; loading high values to Registers
Delay:     LDI     R17, 0xFF 
			LDI R18, 0xFF                
			LDI R19, 0x1F

; MAde 3 loops as the required delay cant be achieved in hexadecimal with one/two

loop:    DEC     R17 
           BRNE    loop             ; branch if not equal
             
loop2:   LDI R17, 0xFF 
		 dec R18
		 BRNE loop   

loop3:   LDI R18, 0xFF
		 dec R19
		 BRNE loop2		
		 RET                ; return to main
	  
