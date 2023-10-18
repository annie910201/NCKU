#include "xc.inc"
GLOBAL _isprime
    
PSECT mytext, local, class=CODE, reloc=2
;is prime   ->0x01
;not prime  ->0xff
_isprime:
    
    MOVFF 0X01,0X10 ;record the input
    
    MOVLW 0X01
    MOVWF 0X22	;record the result
    
    MOVLW 0X01
    MOVWF 0X11	;record current divisor
    rcall check
    GOTO finish
check:
    INCF 0X11		;add the divisor
    MOVFF 0X10,0X20
    MOVF 0X11,W	
    CPFSGT 0X10	;if cerrent divisor is greater than input, end
	RETURN
    rcall devide
    MOVLW 0XFF
    CPFSEQ 0X22
	GOTO check
    RETURN		;if find one divisor, it's not prime, end
    
devide:
    MOVF 0X11,W
    SUBWF 0X20
    CPFSLT 0X20	;if remainder is greater than divisor, continue
	GOTO devide
    CLRF WREG
    CPFSEQ 0X20	;if remainder is less than divisor, end
	RETURN
    MOVLW 0XFF	;if remainder is equal to divisor, is NOT prime, end
    MOVWF 0X22
    RETURN
finish:
    MOVF 0X22,W
    NOP
    
RETURN
 
    

