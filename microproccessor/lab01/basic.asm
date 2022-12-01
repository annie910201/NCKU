 List p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00
;??
;MOVLW 0x7C
MOVLW 0xFC	
MOVWF 0X00 ; [000] = 0x7C
MOVLW 0x04
MOVWF 0X01 ; [001] = 0x04
MOVLW 0xFF
MOVWF 0X02 ; [002] = 0xFF
;???+1
COMF 0x00   
INCF 0x00    ;[000] = 0x84/0x04
	
CLRF WREG        ;clear WREG
ADDWF 0x00 , 0  ;add [000] to WREG
CPFSEQ 0x01      
    INCF 0x02       ;if WREG != [001]
CPFSEQ 0x01
    INCF 0x02     ;if WREG != [001]
end
    
 
