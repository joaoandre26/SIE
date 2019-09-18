/* 
 * File:   pwm.c
 * Author:  João Cruz       - 76517
 *          Henrique Martins- 76674    
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>

#include "pwm.h"
/*
 * 
 */
#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz
/*
 * 
 */
void __ISR ( _TIMER_2_VECTOR, IPL5SRS) T2Interrupt(void)
{
   IFS0bits.T2IF = 0;
}
int SetTimer(void)
{
    /*Set Timer*/
    StopTimer();
    IFS0bits.T2IF = 0; // Reset interrupt flag
    IPC2bits.T2IP = 5; //set interrupt priority (1..7) *** Make sure it matches iplx in isr declaration ***
    IEC0bits.T2IE = 1; // Enable T2 interrupts
    
    T2CONbits.TCKPS = 0; //Divide by 256 pre-scaler
    T2CONbits.T32 = 0; // 16 bit timer operation
   
    PR2 = 2000;
    TMR2 = 0;
    
    
}
void StartTimer(void)
{
    T2CONbits.TON = 1; // Start the timer
}
void StopTimer(void)
{
    T2CONbits.ON = 0; // Stop the timer
}
void setPWM1(uint32_t duty_cycle)
{
    ODCDbits.ODCD1 = 1;
    if(duty_cycle<0)
    {
        duty_cycle=0;
    }
    if(duty_cycle>100)
    {
        duty_cycle=100;
    }
    
    // Set OC2
    OC2CONbits.OCM = 6;     // OCM = 0b110 : OC1 in PWM mode,
    OC2CONbits.OCTSEL=0;    // Timer 2 is clock source of OCM
    OC2RS=0;                // Compute OC1xRS value
    OC2CONbits.ON=1;        // Enable OC1
    
    OC2RS = ((PR2+1)*duty_cycle)/100;
    
    //T2CONbits.TON=1; // Start the timer
}
void setPWM2(uint32_t duty_cycle)
{
    ODCDbits.ODCD2 = 1;
    if(duty_cycle<0)
    {
        duty_cycle=0;
    }
    if(duty_cycle>100)
    {
        duty_cycle=100;
    }
    
    // Set OC2
    OC3CONbits.OCM = 6; // OCM = 0b110 : OC1 in PWM mode,
    OC3CONbits.OCTSEL=0; // Timer 2 is clock source of OCM
    OC3RS=0; // Compute OC1xRS value
    OC3CONbits.ON=1;     // Enable OC1
    
    OC3RS = ((PR2+1)*duty_cycle)/100;
    
    T2CONbits.TON=1; // Start the timer
}