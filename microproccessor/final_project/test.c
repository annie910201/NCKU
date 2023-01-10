#include <pic18f4520.h>
#include <xc.h>

#pragma config OSC = INTIO67    // Oscillator Selection bits
#pragma config WDT = OFF        // Watchdog Timer Enable bit 
#pragma config PWRT = OFF       // Power-up Enable bit
#pragma config BOREN = ON       // Brown-out Reset Enable bit
#pragma config PBADEN = OFF     // Watchdog Timer Enable bit 
#pragma config LVP = OFF        // Low Voltage (single -supply) In-Circute Serial Pragramming Enable bit
#pragma config CPD = OFF        // Data EEPROM?Memory Code Protection bit (Data EEPROM code protection off)
#define _XTAL_FREQ 8000000

/*
 * PORTA: seven segments
 *  0: a
 *  1: b
 *  2: c
 *  3: d
 *  4: e
 *  5: f
 *  6: g
 * 
 * PORTB: seven segments
 *  0: 1
 *  1: 2
 *  2: 3
 * 
 * PORTC: start signal
 *  0: start count score
 * 
 * PORTD: add score signal
 *  0: add score
 */

// 1 ~ 3
#define FIRST 0x06
#define SECOND 0x05
#define THIRD 0x03

// 0 ~ 9
#define ZERO 0x3F
#define ONE 0x06
#define TWO 0x5B
#define THREE 0x4F
#define FOUR 0x66
#define FIVE 0x6D
#define SIX 0x7D
#define SEVEN 0x27
#define EIGHT 0x7F
#define NINE 0x67
//1024 => 16
int add_score = 0;
void __interrupt(high_priority)H_ISR(){
    
    //step4
    int value = ADRESH;
    value = value << 8;
    value = value | ADRESL;
    while (value >= 64)
    {
        value -= 64 ;
        add_score ++ ;
    }
    
    //clear flag bit
    PIR1bits.ADIF = 0;
    //step5 & go back step3
    ADCON0bits.GO = 1;
    
    return;
}

void display(int number, int level) {
    switch (number) {
        case 0:
            LATA = ZERO;
            break;
        case 1:
            LATA = ONE;
            break;
        case 2:
            LATA = TWO;
            break;
        case 3:
            LATA = THREE;
            break;
        case 4:
            LATA = FOUR;
            break;
        case 5:
            LATA = FIVE;
            break;
        case 6:
            LATA = SIX;
            break;
        case 7:
            LATA = SEVEN;
            break;
        case 8:
            LATA = EIGHT;
            break;
        case 9:
            LATA = NINE;
            break;
    }
    if (level == 1) {
        LATB = FIRST;
    } else if (level == 2) {
        LATB = SECOND;
    } else {
        LATB = THIRD;
    }
}

void seven_segment(int score) { // 3 -> 2 -> 1
    if (score >= 100) {
        int hundred = score / 100;
        int ten = (score / 10) % 10;
        int digit = score % 10;
        display(hundred, 3);
        __delay_ms(1);
        display(ten, 2);
        __delay_ms(1);
        display(digit, 1);
    } else if (score >= 10) {
        int ten = (score / 10) % 10;
        int digit = score % 10;
        display(ten, 2);
        __delay_ms(1);
        display(digit, 1);
    } else {
        int digit = score % 10;
        display(digit, 1);
    }
}

void main(void) {
    ADCON1 = 0x0e;
    TRISA = 0x00; // seven segment 0 ~ 9
    TRISB = 0x00; // seven segment 1 ~ 3
    TRISC = 0x01; // start signal
    TRISD = 0x01; // add score

    //step1
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
    ADCON1bits.PCFG = 0b1110;   //AN0 為analog input,其他則是 digital
    ADCON0bits.CHS = 0b0000;    //AN0 當作 analog input
    ADCON2bits.ADCS = 0b100;    //查表後設000(1Mhz < 2.86Mhz)
    ADCON2bits.ACQT = 0b010;    //Tad = 2 us acquisition time設2Tad = 4 > 2.4
    ADCON0bits.ADON = 1;
    ADCON2bits.ADFM = 1;        //right justified 
    
    //step2
    PIE1bits.ADIE = 1;          //Enable A/D interrupt
    PIR1bits.ADIF = 0;          //Clear A/D interrupt flag bit
    INTCONbits.PEIE = 1;        //Enable peripheral interrupt
    INTCONbits.GIE = 1;         //Set GIE bit

    //step3
    ADCON0bits.GO = 1;          //Set GO/DONE bit

    int score = 0;
    int judge = 0;
    LATA = 0;
    LATB = 0;

    while (PORTCbits.RC0 == 0); // Wait for start signal

    LATA = ZERO; // Initial to zero
    LATB = FIRST;

    while (1) {
        if (PORTCbits.RC0 == 1) {
            while (PORTDbits.RD0 == 0) {
                seven_segment(score);
                if(PORTCbits.RC0 == 0){
                    judge = 1;
                    break;
                }
            }
            if(judge == 0)
                score += add_score;
            seven_segment(score);
            __delay_ms(20); // To be change the value
        } else {
            score = 0;
            judge = 0;
            seven_segment(score);
        }
    }
    return;
}