List p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00 ; pc = 0x00

	
DIST macro X1, Y1, X2, Y2, F1,F2
 
    ;count (x1 - x2)^2
    MOVLW X1
    MOVWF 0XFE
    MOVLW X2
    SUBWF 0XFE,W    ;WREG = X1 - X2
    MOVWF 0XFE
    MULWF 0XFE
    MOVFF PRODL,F2  ;[F2] = PRODL1
    MOVFF PRODH,F1  ;[F1] = PRODH1
    
    ;count (y1 - y2)^2
    MOVLW Y1
    MOVWF 0XFF
    MOVLW Y2
    SUBWF 0XFF,W    ;WREG = Y1 - Y2
    MOVWF 0XFF
    MULWF 0XFF
    
    ;add two value
    MOVF F2,W
    ADDWF PRODL,W   ;WREG = PRODL2 + [F2] = PRODL2 + PRODL1
    MOVWF F2
    MOVF F1,W
    ADDWFC PRODH,W  ;WREG = PRODH2 + [F1] + carry of [F2] = PRODH2 + PRODH1 + carry
    MOVWF F1
endm
start:
   DIST 0x05, 0x07, 0x02, 0x03, 0x00, 0x01
end


