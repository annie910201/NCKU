#include "xc.inc"
GLOBAL _mypow
    
PSECT mytext, local, class=CODE, reloc=2
;do a^b
_mypow:
    MOVFF 0X01,0X12 ;[012] = a
    MOVFF 0X03,0X10 ;[010] = b
    CLRF WREG
    CPFSGT 0X10
	CLRF 0x12   ;if b = 0
    CPFSGT 0X10
	INCF 0X12   ;if b = 0, (anynumber)^0 = 1
    CPFSEQ 0X10
	RCALL mul   ;if b != 0
    GOTO finish
mul:
    DCFSNZ 0X10	;if do b times, end
	RETURN
    MOVFF 0X11,0X21	;[011] = high byte
    MOVFF 0X12,0X22	;[012] = low byte
    MOVFF 0X01,0X13	;do a times
    RCALL n_times
    GOTO mul
n_times:
    DCFSNZ 0X13	;if do a times, end
	RETURN
    MOVF 0X22,W
    ADDWF 0X12,F	;do low byte first
    MOVF 0X21,W
    ADDWFC 0X11	;do high byte, and add carry  
    GOTO n_times
finish:
    MOVFF 0X11,0X02
    MOVFF 0X12,0X01
    NOP
    
RETURN
