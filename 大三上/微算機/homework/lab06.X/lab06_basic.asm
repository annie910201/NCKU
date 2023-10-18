List p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	CONFIG LVP = OFF
	L1	EQU 0x14
	L2	EQU 0x15
	org 0x00 ; pc = 0x00
DELAY macro num1, num2 
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
    MOVWF ADCON1    ;all digital
    CLRF PORTB
    BSF TRISB, 0    ;set RB0 to input
    CLRF LATA
    BCF TRISA, 0    ;set RA0 to output
    BCF TRISA, 1    ;set RA1 to output
    BCF TRISA, 2    ;set RA2 to output
    BCF TRISA, 3    ;set RA3 to output
state_1:
    BTFSC PORTB, 0
	BRA state_1
    DELAY d'200', d'100' ;delay 0.25s
    BTG PORTA,0
state_2:
    BTFSC PORTB, 0
	BRA state_2
    DELAY d'200', d'100' ;delay 0.25s
    BTG PORTA,1
state_3:
    BTFSC PORTB, 0
	BRA state_3
    DELAY d'200', d'100' ;delay 0.25s
    BTG PORTA,2
state_4:
    BTFSC PORTB, 0
	BRA state_4
    DELAY d'200', d'100' ;delay 0.25s
    BTG PORTA,3
state_5:
    BTFSC PORTB, 0
	BRA state_5
    DELAY d'200', d'180' ;delay 0.25s
    CLRF PORTA
    BRA state_1
    
end


