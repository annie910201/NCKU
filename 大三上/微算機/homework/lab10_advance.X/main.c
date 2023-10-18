#include "setting_hardaware/setting.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
// #include<pic18f4520.h>
// using namespace std;

char str[20];

void main(void)
{
    SYSTEM_Initialize();
    ClearBuffer();

    while (1)
    {
        strcpy(str, GetString()); // TODO : GetString() in uart.c
    }
    return;
}

void __interrupt(high_priority) Hi_ISR(void)
{
    char* str = GetString();
    int number = atoi(str);
    if (number == 0)
    {
        PR2 = 122;
    }
    else if (number == 1)
    {
        PR2 = 61;
    }
    else if (number == 2)
    {
        PR2 = 30;
    }
    
    if (LATD == 0)
    {
        LATD = 1;
    }
    else
    {
        LATD = 0;
    }
    PIR1bits.TMR2IF = 0;
    return;
}