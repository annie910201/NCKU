#include <xc.h>
#include <stdio.h>
#include <pic18f4520.h>

#pragma config OSC = INTIO67 // Oscillator Selection bits
#pragma config WDT = OFF     // Watchdog Timer Enable bit
#pragma config PWRT = OFF    // Power-up Enable bit
#pragma config BOREN = ON    // Brown-out Reset Enable bit
#pragma config PBADEN = OFF  // Watchdog Timer Enable bit
#pragma config LVP = OFF     // Low Voltage (single -supply) In-Circute Serial Pragramming Enable bit
#pragma config CPD = OFF     // Data EEPROM?Memory Code Protection bit (Data EEPROM code protection off)

/* 0~1023:0~15 => 1024/16 = 64
0~102       = 0
103~205     = 1
206~308     = 2
309~411     = 3  
412~514     = 4  
515~617     = 5  
618~720     = 6  
721~823     = 7  
824~926     = 8
927~1029    = 9
 */
/* 10bit -> set ADFM to right justified, take ADRESH rightest two bit : ADRESL   */

void __interrupt(high_priority)H_ISR(){
    
    //step4
    int value = ADRESH;
    //do things
    int pi[10] = {3,1,4,1,5,9,2,6,5,3};
    value = value << 8;
    value = value | ADRESL;
    int map_addr = 0;
    while (value >= 103)
    {
        value -= 103 ;
        map_addr ++ ;
    }
    
    LATD = pi[map_addr];
    
    //clear flag bit
    PIR1bits.ADIF = 0;
    //step5 & go back step3
    ADCON0bits.GO = 1;
    
    return;
}

void main(void) 
{
    //configure OSC and port
    OSCCONbits.IRCF = 0b100; //1MHz
    TRISAbits.RA0 = 1;       //analog input port
    TRISD = 0;
    LATD = 0;
    
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
    
    while(1){
        for(int i=0;i<20;i++);  //set delay
    }
    
    return;
}