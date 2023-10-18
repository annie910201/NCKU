List p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00 ; pc = 0x00
start:
    MOVLW 0X01
    MOVWF 0X00	;[000] = s
    MOVLW 0X03
    MOVWF 0X01	;[001] = r
    MOVLW 0X02
    MOVWF 0X03
    MOVFF 0X00,0X10	;to calculate s*r^2, initialized to be s
    rcall GP
    rcall finish
GP:
    ;calculate sr^2
    MOVF 0X10,W	;WEEG = [[010] 
    MULWF 0X01	
    MOVFF PROD,0X10	;[010] = [010] * [001]
    MOVLW GP
    DECFSZ 0X03
	MOVWF PCL	;use loop to calculate s*r^2, [010] stores current data 
	
    ;calculate sr
    MOVF 0X00,W
    MULWF 0X01
    
    ;add s, sr, sr^2
    MOVF PROD,W
    ADDWF 0X10,W
    ADDWF 0X00,W
    MOVWF 0X02
    RETURN
finish:
    NOP
    
end


