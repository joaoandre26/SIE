/* 
 * File:   buttons.c
 * Author:  João Cruz       - 76517
 *          Henrique Martins- 76674    
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
/*
 * 
 */
#include "buttons.h"
/*
 * 
 */
void InitButtons(void)
{
    //Butões para selecionar o nível 0..3
    TRISEbits.TRISE7 = 1; // Set pin 30 as input - Nível 0
    TRISEbits.TRISE6 = 1; // Set pin 31 as input - Nível 1
    TRISEbits.TRISE5 = 1; // Set pin 32 as input - Nível 2
    TRISEbits.TRISE4 = 1; // Set pin 33 as input - Nível 3
    // Switch fim de nível
    TRISEbits.TRISE3 = 1; //Set pin 34 as input
    
    TRISAbits.TRISA3 = 0;
    
}
uint32_t PushButton0(void)
{
    return !PORTEbits.RE7;
}
uint32_t PushButton1(void)
{
    return !PORTEbits.RE6;
}
uint32_t PushButton2(void)
{
    return !PORTEbits.RE5;
}
uint32_t PushButton3(void)
{
    return !PORTEbits.RE4;
}
uint32_t BottomSwitch(void)
{
    return !PORTEbits.RE3;
}
