List p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	CONFIG LVP = OFF
	L1	EQU 0x14
	L2	EQU 0x15
	org 0x00 ; pc = 0x00
delay macro num1, num2 
    local LOOP1 
    local LOOP2
    MOVLW num2
    MOVWF L2
    LOOP2:
	MOVLW num1
	MOVWF L1
    LOOP1:
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	DECFSZ L1, 1
	BRA LOOP1
	DECFSZ L2, 1
	BRA LOOP2
endm

start:
int:
    MOVLW 0x0f
    MOVWF ADCON1
    CLRF PORTB
    BSF TRISB, 0    ;set RB0 to input
    CLRF LATD
    BCF TRISD, 0    ;set RA0 to OUTput
    BCF TRISD, 1    ;set RA1 to input
    BCF TRISD, 2    ;set RA2 to input
    BCF TRISD, 3    ;set RA3 to input
state_1:
    BTFSC PORTB, 0
	BRA state_1
    delay d'200', d'100' ;delay 0.5s
    BTG PORTD,0
    BTG PORTD,1
    delay d'200', d'100' ;delay 0.5s
    BTG PORTD,0
    BTG PORTD,2
    delay d'200', d'100' ;delay 0.5s
    BTG PORTD,1
    BTG PORTD,3
    delay d'200', d'100' ;delay 0.5s
    BTG PORTD,0
    BTG PORTD,2
    delay d'200', d'100' ;delay 0.5s
    CLRF PORTD
state_2:
    BTFSC PORTB, 0
	BRA state_2
    delay d'200', d'100' ;delay 0.5s
    BTG PORTD,1
    BTG PORTD,2
    delay d'200', d'100' ;delay 0.5s
    BTG PORTD,1
    BTG PORTD,3
    delay d'200', d'100' ;delay 0.5s
    BTG PORTD,0
    BTG PORTD,2
    delay d'200', d'100' ;delay 0.5s
    BTG PORTD,1
    BTG PORTD,3
    delay d'200', d'100' ;delay 0.5s
    CLRF PORTD
state_3:
    BTFSC PORTB, 0
	BRA state_3
    delay d'200', d'100' ;delay 0.5s
    BTG PORTD,2
    BTG PORTD,3
    delay d'200', d'100' ;delay 0.5s
    BTG PORTD,0
    BTG PORTD,2
    delay d'200', d'100' ;delay 0.5s
    BTG PORTD,1
    BTG PORTD,3
    delay d'200', d'100' ;delay 0.5s
    BTG PORTD,0
    BTG PORTD,2
    delay d'200', d'100' ;delay 0.5s
    CLRF PORTD  
state_4:
    BTFSC PORTB, 0
	BRA state_4
    delay d'200', d'100' ;delay 0.5s
    BTG PORTD,0
    BTG PORTD,3
    delay d'200', d'100' ;delay 0.5s
    BTG PORTD,1
    BTG PORTD,3
    delay d'200', d'100' ;delay 0.5s
    BTG PORTD,0
    BTG PORTD,2
    delay d'200', d'100' ;delay 0.5s
    BTG PORTD,1
    BTG PORTD,3
    delay d'200', d'100' ;delay 0.5s
    CLRF PORTD
    BRA state_1
end





