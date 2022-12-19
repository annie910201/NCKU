#include "setting_hardaware/setting.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
// #include<pic18f4520.h>
// using namespace std;

char str[20];

void main(void) 
{
    SYSTEM_Initialize() ;
    ClearBuffer();
    
    while(1) {
        strcpy(str, GetString()); // TODO : GetString() in uart.c
        
    }
    return;
}

void __interrupt(high_priority) Hi_ISR(void)
{

}