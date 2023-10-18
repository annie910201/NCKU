/*
 * File:   main.c
 * Author: Annie
 *
 * Created on 2022?10?16?, ?? 11:02
 */


#include "xc.h"

extern unsigned char isprime(unsigned int a);

void main(void) {
    volatile unsigned char res = isprime(57) ;
    while(1);
    return;
} 
