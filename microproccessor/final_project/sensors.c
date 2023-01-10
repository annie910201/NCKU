
#include <xc.h>
#include <pic18f4520.h>
#include<stdlib.h>
#define _XTAL_FREQ 8000000

#pragma config OSC = INTIO67    // Oscillator Selection bits
#pragma config WDT = OFF        // Watchdog Timer Enable bit 
#pragma config PWRT = OFF       // Power-up Enable bit
#pragma config BOREN = ON       // Brown-out Reset Enable bit
#pragma config PBADEN = OFF     // Watchdog Timer Enable bit 
#pragma config LVP = OFF        // Low Voltage (single -supply) In-Circute Serial Pragramming Enable bit
#pragma config CPD = OFF        // Data EEPROM?Memory Code Protection bit (Data EEPROM code protection off)

unsigned int duration;

void __interrupt(high_priority)H_ISR() {
    if (INTCONbits.RBIF == 1) {
        INTCONbits.RBIE = 0;
        if (PORTBbits.RB4 == 1) {
            duration = 0;
            TMR1L = 0;
            TMR1H = 0;
            T1CONbits.TMR1ON = 1;
        }
        if (PORTBbits.RB4 == 0) {
            duration = (TMR1H << 8) | TMR1L;
            T1CONbits.TMR1ON = 0;
        }
        INTCONbits.RBIF = 0;
    }
    INTCONbits.RBIE = 1;
}

void main(void) {
    OSCCONbits.IRCF = 0b110;

    INTCONbits.GIE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;

    T1CONbits.TMR1CS = 0;
    T1CONbits.TMR1ON = 0;
    T1CONbits.T1CKPS0 = 1;
    T1CONbits.T1CKPS1 = 0;

    TRISA = 0b00000000;
    LATA = 0b00010000;

    TMR1L = 0;
    TMR1H = 0;

    TRISB = 0b00010000;
    PORTBbits.RB0 = 0;
    PORTBbits.RB4 = 0;

    TRISD = 0b10000000;
    PORTDbits.RD7 = 0;

    float distance = 0;

    while (1) {
        LATAbits.LA3 = 0;
        LATAbits.LA4 = 0;
        while (PORTDbits.RD7 == 1);
        PORTDbits.RD7 = 0;

        LATAbits.LA3 = 1;

        for (int i = 0; i < 5; i++) {
            PORTBbits.RB0 = 1;
            __delay_us(10);
            PORTBbits.RB0 = 0;

            distance = 1000;

            while (PORTBbits.RB4 == 0);
            __delay_ms(10);
            distance = duration * (0.034 / 2);

            if (distance < 5) {
                LATAbits.LA0 = 1;
                LATAbits.LA1 = 1;
                LATAbits.LA2 = 1;
            } else if (distance < 15) {
                LATAbits.LA0 = 1;
                LATAbits.LA1 = 1;
                LATAbits.LA2 = 0;
            } else if (distance < 25) {
                LATAbits.LA0 = 1;
                LATAbits.LA1 = 0;
                LATAbits.LA2 = 0;
            } else {
                LATAbits.LA0 = 0;
                LATAbits.LA1 = 0;
                LATAbits.LA2 = 0;
            }

            __delay_ms(20);
        }
    }



    return;
}
