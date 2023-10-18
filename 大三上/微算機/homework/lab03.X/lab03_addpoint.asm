List p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00 ; pc = 0x00
MOVLW 0XF5
MOVWF 0X10 ;[010] = 0XF5
MOVLW 0X5A
MOVWF 0X11 ;[011] = 0X5A
	
MOVLW 0X01 
MOVWF 0X12 ;MCD

MOVLW 0X01
MOVWF 0X13 ;multiple 

MOVLW 0X00
MOVWF 0X22 ;quotient of 0x5A

; put the smaller one into 0x14
MOVF 0X10,W
CPFSGT 0X11
    MOVFF 0X11,0X14 
CPFSLT 0X11
    MOVFF 0X10,0X14 

start:
    INCF 0X13
    MOVFF 0X10,0X20	;[020] = 0XF5
    MOVFF 0X11,0X21	;[021] = 0X5A
    CLRF 0X22
sub_case1:
    MOVF 0X13,W	;WREG = 0X13 
    SUBWF 0X20,F	;[020] = [020] - WREG
    CPFSLT 0X20
	GOTO sub_case1	;[020]>WREG
    CLRF WREG
    CPFSEQ 0X20	
	GOTO not_devisor    ;[020] != 0
    GOTO  sub_case2	     ;[020] = 0
sub_case2:
    MOVF 0X13,W	 ;WREG = 0X13 
    SUBWF 0X21,F       ;[021] = [021] - WREG
    INCF 0X22
    CPFSLT 0X21
	GOTO sub_case2 ;[021]>WREG
    CLRF WREG
    CPFSGT 0X21	
	MOVFF 0X13,0X12  ;if [020] = 0, MCD = [013]
    CPFSGT 0X21
	MOVFF 0X22,0X23  ;if [020] = 0, quotient of d2(MCD) = [022]
    GOTO not_devisor	   ;if [020] != 0
not_devisor:
    MOVF 0X13,W	    ;WREG = [013]
    CPFSEQ 0X14
	GOTO start	    ;if [013]<[014], back to start; else,continue
multiple:
    MOVF 0X10,W	   ;WREG = [010]  
    MULWF 0X23	    ;[010] * [023] 
    MOVFF PRODH,0X00
    MOVFF PRODL,0X01
end


