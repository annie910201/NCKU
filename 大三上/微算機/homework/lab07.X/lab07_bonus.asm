#include "p18f4520.inc"

; CONFIG1H
  CONFIG  OSC = INTIO67         ; Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)
  CONFIG  FCMEN = OFF           ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
  CONFIG  IESO = OFF            ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

; CONFIG2L
  CONFIG  PWRT = OFF            ; Power-up Timer Enable bit (PWRT disabled)
  CONFIG  BOREN = SBORDIS       ; Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
  CONFIG  BORV = 3              ; Brown Out Reset Voltage bits (Minimum setting)

; CONFIG2H
  CONFIG  WDT = OFF             ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
  CONFIG  WDTPS = 32768         ; Watchdog Timer Postscale Select bits (1:32768)

; CONFIG3H
  CONFIG  CCP2MX = PORTC        ; CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
  CONFIG  PBADEN = ON           ; PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
  CONFIG  LPT1OSC = OFF         ; Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
  CONFIG  MCLRE = ON            ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

; CONFIG4L
  CONFIG  STVREN = ON           ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
  CONFIG  LVP = OFF             ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
  CONFIG  XINST = OFF           ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

; CONFIG5L
  CONFIG  CP0 = OFF             ; Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
  CONFIG  CP1 = OFF             ; Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
  CONFIG  CP2 = OFF             ; Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
  CONFIG  CP3 = OFF             ; Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

; CONFIG5H
  CONFIG  CPB = OFF             ; Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
  CONFIG  CPD = OFF             ; Data EEPROM Code Protection bit (Data EEPROM not code-protected)

; CONFIG6L
  CONFIG  WRT0 = OFF            ; Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
  CONFIG  WRT1 = OFF            ; Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
  CONFIG  WRT2 = OFF            ; Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
  CONFIG  WRT3 = OFF            ; Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

; CONFIG6H
  CONFIG  WRTC = OFF            ; Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
  CONFIG  WRTB = OFF            ; Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
  CONFIG  WRTD = OFF            ; Data EEPROM Write Protection bit (Data EEPROM not write-protected)

; CONFIG7L
  CONFIG  EBTR0 = OFF           ; Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR1 = OFF           ; Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR2 = OFF           ; Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
  CONFIG  EBTR3 = OFF           ; Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

; CONFIG7H
  CONFIG  EBTRB = OFF           ; Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

    L1 EQU 0x14
    L2 EQU 0x15
    org 0x00
    
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

goto Initial			; 避免程式一開始就會執行到ISR這一段，要跳過。
ISR:				; Interrupt發生時，會跳到這裡執行。
    org 0x08	
    BTG 0X01, 0
    BTFSS 0X00, 2
      BRA SHIFT_LEFT
    CLRF 0X00
    BSF 0X00, 0
SET_INT:
    BCF INTCON, INT0IF      ; set INT flag to off
RETFIE                 

SHIFT_LEFT:
    RLNCF 0X00
BRA SET_INT

Initial:				; 初始化的相關設定
    BSF 0X00, 0     ; record the time interval
    BCF 0X01, 0     ; record direction
    MOVLW 0x0F
    MOVWF ADCON1		; 設定成要用數位的方式，Digitial I/O 
    
    CLRF TRISA
    CLRF LATA
    BSF TRISB,  0
    BSF LATA, 0
    BCF STATUS, C
    BCF RCON, IPEN
    BCF INTCON, INT0IF		; 先將Interrupt flag bit清空
    BSF INTCON, GIE		; 將Global interrupt enable bit打開
    BSF INTCON, INT0IE		; 將interrupt0 enable bit 打開 (INT0與RB0 pin腳位置相同)
    DELAY  d'350' , d'250'
main:
    BTFSC 0X01, 0
       BRA TURN_RIGHT
    BRA TURN_LEFT
TIME_INTERVAL:
    BTFSC 0X00, 0
      GOTO STATE_1
    BTFSC 0X00, 1
      GOTO STATE_2
    BTFSC 0X00, 2
      GOTO STATE_3


TURN_RIGHT:; 3->2->1->0
    BTFSC LATA, 0
      BRA SET_ZERO_TO_THREE
    RRNCF LATA
BRA TIME_INTERVAL

SET_ZERO_TO_THREE:
    CLRF LATA
    BSF LATA, 3
BRA TIME_INTERVAL

TURN_LEFT:; 0->1->2->3
    BTFSC LATA, 3
      BRA SET_ZERO_TO_ZERO
    RLNCF LATA
BRA TIME_INTERVAL

SET_ZERO_TO_ZERO:
    CLRF LATA
    BSF LATA, 0
BRA TIME_INTERVAL

STATE_1:; 1 SEC
    DELAY  d'350' , d'250'
GOTO main
STATE_2:; 0.5 SEC
    DELAY  d'350' , d'175'
GOTO main
STATE_3:; 0.25 SEC
    DELAY  d'350' , d'100'
GOTO main


end
