#include "setting_hardaware/setting.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include <pic18f4520.h>
#include <xc.h>
#define _XTAL_FREQ 8000000
// using namespace std;

char str[20];
void Mode1()
{
    UART_Write_Text("[INFO] go to mode1\n\r"); // TODO
    ClearBuffer();
    while (1)
    {
        // UART_Write_Text("[INFO] enter");

        strcpy(str, GetString());
        if (str[0] == 'e')
        {
            UART_Write_Text("\n\r[INFO] exit mode1\n\r");
            LATD = 0;
            break;
        }
        ClearBuffer();
        LATD = 5;
        __delay_ms(500);

        strcpy(str, GetString());
        if (str[0] == 'e')
        {
            UART_Write_Text("\n\r[INFO] exit mode1\n\r");
            LATD = 0;
            break;
        }
        ClearBuffer();
        LATD = 10;
        __delay_ms(500);
    }
    return;
}
void Mode2()
{
    UART_Write_Text("[INFO] go to mode2\n\r"); // TODO
    ClearBuffer();
    while (1)
    {

        strcpy(str, GetString());
        if (str[0] == 'e')
        {
            UART_Write_Text("\n\r[INFO] exit mode2\n\r");
            LATD = 0;
            break;
        }
        ClearBuffer();
        LATD = 8;
        __delay_ms(500);

        strcpy(str, GetString());
        if (str[0] == 'e')
        {
            UART_Write_Text("\n\r[INFO] exit mode2\n\r");
            LATD = 0;
            break;
        }
        ClearBuffer();
        LATD = 4;
        __delay_ms(500);

        strcpy(str, GetString());
        if (str[0] == 'e')
        {
            UART_Write_Text("\n\r[INFO] exit mode2\n\r");
            LATD = 0;
            break;
        }
        ClearBuffer();
        LATD = 2;
        __delay_ms(500);

        strcpy(str, GetString());
        if (str[0] == 'e')
        {
            UART_Write_Text("\n\r[INFO] exit mode2\n\r");
            LATD = 0;
            break;
        }
        ClearBuffer();
        LATD = 1;
        __delay_ms(500);
    }
    return;
}
void main(void)
{
    SYSTEM_Initialize();
    ClearBuffer();

    while (1)
    {
        strcpy(str, GetString()); // TODO : GetString() in uart.c
        if (str[0] == 'm' && str[1] == '1')
        { // Mode1
            UART_Write('\n');
            UART_Write('\r');
            Mode1();
            ClearBuffer();
        }
        else if (str[0] == 'm' && str[1] == '2')
        { // Mode2
            UART_Write('\n');
            UART_Write('\r');
            Mode2(); // TODO
            ClearBuffer();
        }
        // else
        //     ClearBuffer();
    }
    return;
}

void __interrupt(high_priority) Hi_ISR(void)
{
}