List p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00 ; pc = 0x00
;N = 1, ans = 1
;N = 2, ans = 3
;N = 3, ans = 7
;N = 4, ans = 15
;N = 5, ans = 31
;N = 6, ans = 63
MOVLW 0X04 ;N = 4
MOVWF 0X01 
	
MOVLW 0X01 ;a1 = 1
MOVWF 0X00
RCALL Hanoitower
RCALL finish

Hanoitower: ;An = 2*An-1 +1
    DCFSNZ 0X01 ;do N-1 times
	RETURN
    CLRF WREG 
    ADDWF 0X00,W
    ADDWF 0X00,F    ;An = [000] = [000] + [000] = 2*An-1
    INCF 0X00		;An=2*An-1 + 1
    MOVLW Hanoitower
    MOVWF PCL
finish:
    NOP
end


