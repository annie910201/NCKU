/*
 * File:   main.c
 * Author: Annie
 *
 * Created on 2022?10?17?, ?? 10:13
 */


#include <xc.h>
extern unsigned int divide_signed(unsigned char a, unsigned char b);
void main(void) {
    volatile unsigned int res = divide_signed(-7,12);
    volatile char quotient = res>>8;
    volatile char remainder = res%65280;
    while(1);
    return;
}
