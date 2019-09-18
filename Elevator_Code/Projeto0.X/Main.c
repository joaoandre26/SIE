/* 
 * File:   main.c
 * Author: João André, Henrique Martins
 *
 * Created on 5 de Março de 2019, 17:08
 */
#include "../../ExemploCodigo/CKCommon/ConfigBits/config_bits.h" // NOTE!! Must precede project file includes
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
/*
 *
 */
#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz
/*
 * 
 */
#define fpwm 2000 //sampling frequency
#define NUMBER_OF_PRESCALERS (sizeof(prescalers)/sizeof(prescalers[0]))
#define max_pr2 65535
#define nbits 256   //2^8=256

#define flagTimer (IFS0bits.T3IF)
#define flagADC (IFS1bits.AD1IF)
/*
 *
 */
uint8_t set_timer(uint32_t freq);
void init(void);
void initADC(void);
void init_pwm(uint8_t duty_cycle);
/*Main code*/
int main(int argc, char** argv) {
    int fa;
    int fa2 = 400;
    fa=nbits*fpwm;
    set_timer(fa2);
    init();
    int res=0;
    int max=0;
    int min=100;
    int mean;
    initADC();
    while(1)
    {
        
        // Read ADC 

        AD1CON1bits.ASAM = 1; // Start conversion

        if (flagTimer == 1){
            flagTimer = 0;
            AD1CON1bits.ASAM = 1; // Start conversion
        }
        if (flagADC == 1){
            res = (ADC1BUF0*100)/1024;  // Convertion of ADC buffer from 0-100 
            flagADC = 0;
            
        }
        
            init_pwm(res);             //Start PWN signal
        
#if 0
        while(IFS0bits.T2IF==0);
        IFS0bits.T2IF=0;
        if(flag==1)
        {
            PORTDbits.RD1= 0;
            flag=0;
        }
        else
        {
            PORTDbits.RD1=1;
            flag=1;
        }
#endif
    }
    return (EXIT_SUCCESS);
}
/*Set ports and Timers */
void init(void)
{
    TRISDbits.TRISD0 = 0;
    PORTDbits.RD0= 1;  
    
    // Set timer of PWN 2k Hz
    T2CONbits.ON = 0; // Stop timer
    IFS0bits.T2IF=0; // Reset interrupt flag    
    T2CONbits.TCKPS = 0; //Select pre-scaler
    T2CONbits.T32 = 0; // 16 bit timer operation
    PR2=20000; // Compute PR value
    TMR2=0;
    
    // Set timer of ADC 400 Hz
    T3CONbits.ON = 0; // Stop timer
    IFS0bits.T3IF=0; // Reset interrupt flag    
    T3CONbits.TCKPS = 1; //Select pre-scaler
    
    //PR3=50000; // Compute PR value
    //TMR3=0;
    
    T3CONbits.TON=1; // Start the timer
    T3CONbits.ON=1; // Start the timer
}

#if 1
uint8_t set_timer(uint32_t freq) 
{
    /*Value for counter prescaler*/
    uint16_t prescalers[] ={1, 2, 4, 8, 16, 32, 64, 256};
    /*defining variables*/
    uint32_t div;
    uint8_t i=NUMBER_OF_PRESCALERS-1;
    /*Check if sampling frequency is equal to zero, if its the case, stops the timer*/
    if(freq==0)
    {
       return 0;
    }
    div=PBCLOCK/freq;
    /*Try to find the best prescaler value*/
    while(((div%prescalers[i])!=0) && (div/prescalers[i]>max_pr2))
    {
        i--;
        /*If none of the prescaler fits, it will return no valid value*/
        if(i<0)
            return -1;   
    }

    PR3=div/prescalers[1];
    TMR3=0;
    return 0;
}
#endif 
#if 1
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
    AD1PCFGbits.PCFG0 = 0; // Set AN0 to analog mode
    // Enable ADC
    AD1CON1bits.ON = 1; // Enable A/D module (This must be the ***last instruction of configuration phase***)
    
    T3CONbits.TON=1; // Start the timer
}
#endif
void init_pwm(uint8_t duty_cycle)
{
    if(duty_cycle<0)
        duty_cycle=0;
    if(duty_cycle>100)
        duty_cycle=100;
    //duty_cycle = 100-duty_cycle;
    
    // Set OC1
    OC1CONbits.OCM = 6; // OCM = 0b110 : OC1 in PWM mode,
    OC1CONbits.OCTSEL=0; // Timer 2 is clock source of OCM
    OC1RS=((PR2+1)*duty_cycle)/100; // Compute OC1xRS value
    OC1CONbits.ON=1;     // Enable OC1

    // Start PWM generation
    T2CONbits.TON=1; // Start the timer
}