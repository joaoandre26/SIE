/* 
 * File  :  uart.c
 * Author:  João Cruz       - 76517
 *          Henrique Martins- 76674    
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
/*
 * 
 */	
void Init_UART(void)
{
    uint32_t F_PBCLK=40000000;
    uint32_t baudrate=9600;
   
    U1MODEbits.BRGH=0;
    U1BRG = ((F_PBCLK+8*baudrate)/(16*baudrate))-1;
    U1MODEbits.PDSEL=0; //sem bits de paridade
    U1MODEbits.STSEL=0;
    U1STAbits.UTXEN=1;  //ativação envio
    U1STAbits.URXEN=1;  //ativação receção
    U1MODEbits.ON=1;
}
void PutChar(char r)
{
       while(U1STAbits.UTXBF);
       U1TXREG=r;
}
void PutString(char *str)
{
    while(*str!= '\0')
    {
        PutChar(*str);
        str++;
    }
}
char GetChar(void)
{
    if(U1STAbits.OERR == 1)
    {
        U1STAbits.OERR=0;
    }
        while (U1STAbits.URXDA == 0);
        return U1RXREG;
}
