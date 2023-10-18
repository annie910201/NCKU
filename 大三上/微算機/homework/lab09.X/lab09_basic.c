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
0~63        = 0
64~127      = 1
128~191     = 2
192~255     = 3  
256~319     = 4  
320~383     = 5  
384~447     = 6  
448~511     = 7  
512~575     = 8
576~639     = 9
640~703     = 10
704~767     = 11
768~831     = 12
832~895     = 13
896~959     = 14
960~1023    = 15
 */
/* 10bit -> set ADFM to right justified, take ADRESH rightest two bit : ADRESL   */

void __interrupt(high_priority)H_ISR(){
    
    //step4
    int value = ADRESH;
    //do things
    value = value << 8;
    value = value | ADRESL;
    int map_addr = 0;
    while (value >= 64)
    {
        value -= 64 ;
        map_addr ++ ;
    }
    
    LATD = map_addr;
    
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
    ADCON1bits.PCFG = 0b1110; //AN0 為analog input,其他則是 digital
    ADCON0bits.CHS = 0b0000;  //AN0 當作 analog input
    ADCON2bits.ADCS = 0b100;  //選擇conversion clock -> 查表後設000(1Mhz < 2.86Mhz)
    ADCON2bits.ACQT = 0b010;  //選擇acquisition time要幾個Tad -> Tad = 2 us acquisition time設2Tad = 4 > 2.4
    ADCON0bits.ADON = 1;
    ADCON2bits.ADFM = 1;    //設定justified -> right justified 
    
    
    //step2
    PIE1bits.ADIE = 1;
    PIR1bits.ADIF = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;


    //step3
    ADCON0bits.GO = 1;
    
    while(1){
        for(int i=0;i<20;i++);
    }
    
    return;
}