
/* 
 * File:   adc.c
 * Author:  João Cruz       - 76517
 *          Henrique Martins- 76674    
 */
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>

#include "adc.h"
/*
 * 
 */
#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz

#define flagTimer (IFS0bits.T3IF)
#define flagADC (IFS1bits.AD1IF)

void initADC(void){
    
    AD1CON1bits.SSRC = 7; // Internal counter ends sampling and starts conversion
    AD1CON1bits.CLRASAM = 1; //Stop conversion when 1st A/D converter interrupt is generated and clears ASAM bit automatically
    AD1CON1bits.FORM = 0; // Integer 16 bit output format
    AD1CON2bits.VCFG = 0; // VR+=AVdd; VR-=AVss
    AD1CON2bits.SMPI = 0; // Number (+1) of consecutive conversions, stored in ADC1BUF0...ADCBUF{SMPI}
    AD1CON3bits.ADRC = 1; // ADC uses internal RC clock
    AD1CON3bits.SAMC = 16; // Sample time is 16TAD ( TAD = 100ns)
    // Set AN0 as input
    AD1CHSbits.CH0SA = 0; // Select AN0 as input for A/D converter
    
    
    TRISBbits.TRISB0 = 1; // Set AN0 to input mode
    TRISBbits.TRISB1 = 1; // Set AN1 to input mode
    TRISBbits.TRISB2 = 1; // Set AN2 to input mode
    
    AD1PCFGbits.PCFG0 = 0; // Set AN0 to analog mode
    AD1PCFGbits.PCFG1 = 0; // Set AN1 to analog mode
    AD1PCFGbits.PCFG2 = 0; // Set AN2 to analog mode
    
    // Enable ADC
    AD1CON1bits.ON = 1; // Enable A/D module (This must be the ***last instruction of configuration phase***)
    
    T3CONbits.TON=1; // Start the timer
    
}

void initADCTimer(void){
        
    // Sampling frequency of ADC of 400 Hz 
    // Set timer of ADC 400 Hz
    T3CONbits.ON = 0; // Stop timer
    IFS0bits.T3IF=0; // Reset interrupt flag    
    T3CONbits.TCKPS = 1; //Select pre-scaler
    
    PR3=50000; // Compute PR value
    TMR3=0;
    
    T3CONbits.TON=1; // Start the timer
    T3CONbits.ON=1; // Start the timer
}


uint32_t readADC0(void)
{
        
        AD1CHSbits.CH0SA = 0; // Select AN0 as input for A/D converter
        AD1CON1bits.SAMP = 1;           // Start conversion
    
       // Read ADC 
        AD1CON1bits.ASAM = 1; // Start conversion

                
        while(AD1CON1bits.DONE==0);     // Wait until Conversion is done
        AD1CON1bits.DONE=0;             // Reset DONE Flag by software

        return buffer();
}
uint32_t readADC1(void)
{
        AD1CHSbits.CH0SA = 1; // Select AN1 as input for A/D converter
        AD1CON1bits.SAMP = 1;           // Start conversion
    
       // Read ADC 
        AD1CON1bits.ASAM = 1; // Start conversion
        
        while(AD1CON1bits.DONE==0);     // Wait until Conversion is done
        AD1CON1bits.DONE=0;             // Reset DONE Flag by software
        
        return buffer();
}
uint32_t readADC2(void)
{
        AD1CHSbits.CH0SA = 2; // Select AN2 as input for A/D converter
        AD1CON1bits.SAMP = 1;           // Start conversion
    
       // Read ADC 
        AD1CON1bits.ASAM = 1; // Start conversion

        while(AD1CON1bits.DONE==0);     // Wait until Conversion is done
        AD1CON1bits.DONE=0;             // Reset DONE Flag by software
        return buffer();
}

uint32_t readADC3(void)
{
        AD1CHSbits.CH0SA = 3; // Select AN3 as input for A/D converter
        AD1CON1bits.SAMP = 1;           // Start conversion
    
       // Read ADC 
        AD1CON1bits.ASAM = 1; // Start conversion

        while(AD1CON1bits.DONE==0);     // Wait until Conversion is done
        AD1CON1bits.DONE=0;             // Reset DONE Flag by software

        return buffer();
}
uint32_t buffer(void){
    return ADC1BUF0;
}
