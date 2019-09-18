/* 
 * File:   encoder.c
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
#include "encoder.h"
#include <math.h>

/*
 * 
 */
volatile uint32_t cnt=0;
volatile uint32_t PrevStateA = 0;
volatile uint32_t CurrStateA = 0;
volatile uint32_t CurrStateB = 0;
volatile uint32_t CurrStateZ = 0;

volatile uint32_t old_cnt = 0;
volatile uint32_t velocidade = 0;
volatile uint32_t i = 0;
/*
 * 
 */

 void __ISR (_EXTERNAL_0_VECTOR, IPL5SRS) ExtInt0ISR(void)
{
    CurrStateA = GetChannelA();
    CurrStateB = GetChannelB();
    UpdatePos();
           
    INTCONbits.INT0EP =!INTCONbits.INT0EP;    
    IFS0bits.INT0IF = 0; // Reset interrupt flag
        
}
void __ISR (_EXTERNAL_1_VECTOR, IPL5SRS) ExtInt1ISR(void) 
{    
    CurrStateB = GetChannelB();
        
    INTCONbits.INT1EP =!INTCONbits.INT1EP;    
    IFS0bits.INT1IF = 0; // Reset interrupt flag
        
}

void __ISR (_EXTERNAL_2_VECTOR, IPL5SRS) ExtInt2ISR(void)
{
    CurrStateZ = GetChannelZ();
    
    INTCONbits.INT2EP =!INTCONbits.INT2EP;
    IFS0bits.INT2IF = 0; // Reset interrupt flag
          
}

 
void SetEncoderPorts(void)
{
    TRISDbits.TRISD0 = 1; // Set pin as input Channel A - pin 3 INT0
    TRISEbits.TRISE8 = 1; // Set pin as input Channel B - pin 2 INT1
    TRISEbits.TRISE9 = 1; // Set pin as input Channel Z - pin 7 INT2
    
    
}
void SetExternalInt0(void)  //pin3
{    
    IEC0bits.INT0IE = 0; // Disable Int0 interrupts
    IFS0bits.INT0IF = 0; // Reset int flag
    INTCONbits.INT0EP = 1; // Generate interrupts on {rising edge-1 falling edge - 0}
    IPC0bits.INT0IP = 2; // Set interrupt priority (1..7) *** Set equal to ilpx above
    IEC0bits.INT0IE = 1; // Enable Int0 interrupts 
    IFS0bits.INT0IF = 0; // Reset int flag
}
void SetExternalInt1(void)  //pin 2
{
    IEC0bits.INT1IE = 0; // Disable Int0 interrupts
    IFS0bits.INT1IF = 0; // Reset int flag
    INTCONbits.INT1EP = 1; // Generate interrupts on {rising edge-1 falling edge - 0}
    IPC1bits.INT1IP = 2; // Set interrupt priority (1..7) *** Set equal to ilpx above
    IEC0bits.INT1IE = 1; // Enable Int0 interrupts 
        IFS0bits.INT1IF = 0; // Reset int flag
}

void SetExternalInt2(void)  //pin 7
{
    IEC0bits.INT2IE = 0; // Disable Int0 interrupts
    IFS0bits.INT2IF = 0; // Reset int flag
    INTCONbits.INT2EP = 1; // Generate interrupts on {rising edge-1 falling edge - 0}
    IPC2bits.INT2IP = 2; // Set interrupt priority (1..7) *** Set equal to ilpx above
    IEC0bits.INT2IE = 1; // Enable Int2 interrupts 
        IFS0bits.INT2IF = 0; // Reset int flag
}

uint32_t GetChannelA(void)
{    
    return PORTDbits.RD0;
}
uint32_t GetChannelB(void)
{
    return PORTEbits.RE8;
    //return PORTEbits.RE9;
}
uint32_t GetChannelZ(void)
{
    return PORTEbits.RE9;
}

uint32_t GetPos(void)
{
    return cnt;
}
/*
uint32_t GetSpeed(void)
{
    return velocidade;
}
*/
void UpdatePos(void)
{
    if(CurrStateA!=PrevStateA)
    {
        if(CurrStateA != CurrStateB)
        {
            cnt++;   
        }
        else
        {            
            cnt--;
        }
    }
    PrevStateA=CurrStateA;
}

void ResetPos(void)
{
    cnt = 0;
}

 /*
void Init_Timer4_Interrupt()
{
    //Sampling frequency of speed and position function 400Hz
    
    //for velocity and pos
    T4CONbits.ON = 0; //stop timer
    IFS0bits.T4IF=0; //reset flag
    IPC4bits.T4IP=2; //priority
    IEC0bits.T4IE =1; //enable interrupts
    //T4CONbits.TCKPS =1; //prescaler 256
    T4CONbits.TCKPS =3; //prescaler 256
    //PR4=50000; 
    //PR4=15625;   //10Hz 
    PR4=15625;
    TMR4=0;
    T4CONbits.ON=1; //start
    T4CONbits.TON = 1;
    //printf("Timer4 \n\r");
}

void __ISR( _TIMER_4_VECTOR, IPL5SRS) timer4_int()
{
    if(i >= 50){
        velocidade = 0;
       if(cnt>old_cnt)
       {
           //velocidade=(fabs(cnt-old_cnt)*100)/0.0025;
           //velocidade=(fabs(cnt-old_cnt)*100)/0.1;
           //velocidade=(fabs(cnt-old_cnt)*1000)/0.1;
           velocidade=(fabs(cnt-old_cnt))/10;
       }
       else
       {
           //velocidade=(fabs(old_cnt-cnt)*100)/0.0025;
           //velocidade=(fabs(old_cnt-cnt)*100)/0.1;
           //velocidade=(fabs(old_cnt-cnt)*1000)/0.1;
           velocidade=(fabs(old_cnt-cnt))/10;
       }
       //printf("posicao= %d \n\r",pos);
       //printf("SPEED = %d \n\r", velocidade);

       old_cnt=cnt;
       i=0;
    }
    else{
        i++;
    }
    IFS0bits.T4IF = 0;
    //printf("%d \n\r",GetChannelA());
    //printf("SPEED= %d \n\r",velocidade );
    
}
*/