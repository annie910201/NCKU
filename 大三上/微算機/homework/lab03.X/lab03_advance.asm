List p=18f4520
    #include<p18f4520.inc>
	CONFIG OSC = INTIO67
	CONFIG WDT = OFF
	org 0x00 ; pc = 0x00
MOVLW 0X04
MOVWF 0X12 ;n = 4(quotient and remain bits)
MOVLW 0X17 
MOVWF 0X10 ;A = 0x17
	
MOVLW 0X06 
MOVWF 0X11 ;D = 0x06 
	
RLNCF 0X11,F,0
RLNCF 0X11,F,0
RLNCF 0X11,F,0
RLNCF 0X11,F,0 ;D = 0x60

A_shift_left:
    RLNCF 0X10,F,0 ;A<<1
    MOVF 0X11,W ;WREG =  D
    SUBWF 0X10 ;A = A - D

    BTFSS 0X10,7
	BSF STATUS,0 ;if positive, carry = 1 
    BTFSC 0X10,7
	BCF STATUS,0 ;if negative, carry = 0 
    BC part1
    BNC part2
part1:;A>=0
    BSF 0X10,0 ;A[0] = 1
    BC sub_n
part2:;A<0
    BCF 0X10,0 ;A[0] = 0
    MOVF 0X11,W
    ADDWF 0X10,F ;A = A + D
    BNC sub_n
sub_n:
    BCF STATUS,0
    DECFSZ 0X12 ;if n != 0, back to line 19(A_shift_left:)
	BSF STATUS,0
    BC A_shift_left ; if n = 0, continue
    MOVFF 0X10,0X00 ;Q
    MOVFF 0X10,0X01 ;R
    
    ;R = A[2*n-1:n]
    BCF 0X01,3
    BCF 0X01,2
    BCF 0X01,1
    BCF 0X01,0 ;clear right 4 bits
    RRNCF 0X01
    RRNCF 0X01
    RRNCF 0X01
    RRNCF 0X01 ;R>>4
     
    ;Q = A[n-1:0]
    BCF 0X00,7
    BCF 0X00,6
    BCF 0X00,5
    BCF 0X00,4 ;clear left 4 bits
end
