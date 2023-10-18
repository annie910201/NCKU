/*
 * File:   main.c
 * Author: Annie
 *
 * Created on 2022?10?18?, ?? 12:56
 */
#include <xc.h>
extern unsigned int mypow(unsigned int a, unsigned int b);
void main(void) {
    volatile unsigned int res = mypow(2,7);
    while(1);
    return;
}
