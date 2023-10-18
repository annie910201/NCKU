#include "xc.inc"
GLOBAL _divide_signed
    
PSECT mytext, local, class=CODE, reloc=2
_divide_signed:
    MOVWF 0X10		;[010] = dividend
    MOVFF 0X01,0X11		;[011] = divisor
    BTFSC 0X10,7		;check if dividend is positive
	RCALL turn_positive_A	
    BTFSC 0X11,7		;check if divisor is positive
	RCALL turn_positive_D	
    MOVF 0X20,W
    XORWF 0X21,W		;check quotient signed bit, ex:--=>+
    MOVWF 0X22		;[022] is to record quotient's sign
    
    MOVF 0X11,W
    CPFSLT 0X10
	RCALL do_devisor
    BTFSC 0X22,0		;check if quotient is positive
	RCALL turn_negative_Q	
    BTFSC 0X20,0		;check if remainder is positive
	RCALL turn_negative_R	
    GOTO finish
do_devisor:
    SUBWF 0X10
    INCF 0X12		    ;[012] is to record quotient value
    CPFSLT 0X10	    ;if remainder is greater than divisor, continue
	GOTO do_devisor	
    RETURN		    ;else, end
turn_positive_A:    
    MOVLW 0X01
    MOVWF 0X20	    ;[020] is to record dividend's sign
    
    MOVLW 0XFF
    XORWF 0X10,F	    ;do 1's complement
    INCF 0X10		    ;add 1 to become 2's complement
    RETURN
turn_positive_D:    
    MOVLW 0X01
    MOVWF 0X21	;[021] is to record divisor's sign
    
    MOVLW 0XFF
    XORWF 0X11,F
    INCF 0X11
    RETURN
turn_negative_Q:
    DECF 0X12
    MOVLW 0XFF
    XORWF 0X12,F
    RETURN
turn_negative_R:
    DECF 0X10
    MOVLW 0XFF
    XORWF 0X10,F
    RETURN
finish:
    MOVFF 0X12,0X02	    ;quotient
    MOVFF 0X10,0X01	    ;remainder
    NOP
    
RETURN