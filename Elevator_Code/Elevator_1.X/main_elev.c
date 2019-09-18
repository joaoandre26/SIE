/* 
 * File:   main_elev.c
 * Author:  João Cruz       - 76517
 *          Henrique Martins- 76674    
 */
#include "config_bits.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include <math.h>

#include "pwm.h"              //- Funciona
#include "crystal_display.h"  //- Nao funciona
#include "encoder.h"          //- Nao testada
#include "buttons.h"          //- Testada
#include "adc.h"
#include "uart.h"
#define br 9600
#define pbclk 40000000L
/*
 * 
 */

volatile uint8_t level = 0;
volatile uint32_t setpoint = 0;

#define DP 100
const uint16_t Kp = 20, Ti = 2;
const uint32_t mid_point = 745;
int32_t e[2]={0 , 0} ;
int32_t u[2]={ 0 , 0};
uint16_t f = 10;
uint32_t s0, s1;
uint32_t pwm1, pwm2;
uint32_t err;
uint32_t buff;


void init(void);
void SetExternalInt3(void);
void PIInit(void);
void PI_Controller(void);
void Init_Timer1_Interrupt();
void Init_Timer5_Interrupt();

int main(int argc, char** argv){
    
    InitialiseDisplay();
    uint8_t p = 5;
    UpdateL1(p);
    //Init_UART();
    //__XC_UART =1;
    
    init();      
           
    while(1)
    {        
        
    }
    return (EXIT_SUCCESS);
}
void init(void)
{

    InitButtons();
    SetTimer();
    TRISDbits.TRISD1 = 0;   //define as output OC2 - pin 5
    TRISDbits.TRISD2 = 0;   //define as output OC3 - pin 6
    
    TRISEbits.TRISE2 = 0;
    
    PORTEbits.RE2 = 0;
    SetEncoderPorts();  
    
    initADCTimer();
    initADC();
    
           

    
    SetExternalInt3();      //Calibration
                          
    SetExternalInt0();   //pino 3
    SetExternalInt1();  // pino 2
    SetExternalInt2();  // pino 7
    //PI 
    PIInit();        
    
    Init_Timer1_Interrupt();        //Leitura dos botões e setpoint       
    Init_Timer5_Interrupt();        //Controlador PI
    
    INTCONSET = _INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
}

void __ISR(_EXTERNAL_3_VECTOR, IPL5SRS) da (void){     
        UpdateL3();
        setPWM1(100);
        setPWM2(0);        
        while(BottomSwitch()==0);                
        setPWM1(0);
        setPWM2(0);
        IFS0bits.INT3IF = 0; // Reset interrupt flag           
        delay(3000);
        
        ResetPos(); //reset do counter da posição
        setpoint = 0;
        e[1]=0;
        u[1]=0;
        e[0]=0;
        u[0]=0;
        
    
}

void SetExternalInt3(void)
{
    TRISAbits.TRISA14 = 1; // Set pin as input PushBotton3 - pin 21 INT3
    IEC0bits.INT3IE = 0; // Disable Int0 interrupts
    IFS0bits.INT3IF = 0; // Reset int flag
    INTCONbits.INT3EP = 0; // Generate interrupts on {rising edge-1 falling edge - 0}
    IPC3bits.INT3IP = 2; // Set interrupt priority (1..7) *** Set equal to ilpx above
    IEC0bits.INT3IE = 1; // Enable Int0 interrupts     
}



void Init_Timer1_Interrupt()
{
    //Fa para leitura dos botões
    
    //for position
    T1CONbits.ON = 0; //stop timer
    IFS0bits.T1IF=0; //reset flag
    IPC1bits.T1IP=2; //priority
    IEC0bits.T1IE =1; //enable interrupts
    T1CONbits.TCKPS =3; //prescaler 256
    PR1=15625; //fout=10hz                      DEVIA SER 100 HZ
    TMR1=0;
    T1CONbits.ON=1; //start
    T1CONbits.TON = 1;    
}

void __ISR( _TIMER_1_VECTOR, IPL5SRS) timer1_int(void)
{
   // Rotina da leitura dos botões 
    
    if(PushButton0() == 1){
        level = 0;
        setpoint = 0 ; 
        UpdateL2(level);        
    }
    if(PushButton1() == 1){
        level = 1;        
        setpoint = 3090 ;
        UpdateL2(level);        
    }
    if(PushButton2() == 1){
        level = 2;        
        setpoint = 5997 ;  
        UpdateL2(level);
    }
    if(PushButton3() == 1){
        level = 3;        
        setpoint = 9063;  
        UpdateL2(level);
    }           
    IFS0bits.T1IF = 0;
}

void Init_Timer5_Interrupt()
{
    //impoe frequencia de amostragem ao controlador PI
    
    T5CONbits.ON = 0; //stop timer
    IFS0bits.T5IF=0; //reset flag
    IPC5bits.T5IP=2; //priority
    IEC0bits.T5IE =1; //enable interrupts
    T5CONbits.TCKPS =7; //prescaler 256
    PR5=311; //fout=100Hz
    TMR5=0;
    T5CONbits.ON=1; //start
}

void __ISR( _TIMER_5_VECTOR, IPL5SRS) timer5_int(void){    
    PI_Controller();        
    IFS0bits.T5IF = 0;
}

void PIInit(void)
{
    s0=Kp*(DP+DP/(Ti*f))/DP;
    s1 = -Kp;
}

void PI_Controller(void)
{        
    if(setpoint == 0)
    {
        buff = readADC0();
    }
    if(setpoint == 3090)
    {
        buff = readADC1();
    }
    if(setpoint == 5997)
    {
        buff = readADC2();
    }
    if(setpoint == 9063)
    {
        buff = readADC3();
    }
    
    err = (buff-mid_point);        
    e[1]=e[0];
    u[1]=u[0];
    e[0]=setpoint-GetPos();
    u[0]=u[1]+(s0*e[0]+s1*e[1])/DP;
    if(e[0]>0)
    {
        pwm1 = u[0];
        pwm2 = 0;
    }if(e[0]<0)
    {
        pwm1 = 0;
        pwm2 = u[0];
    }
    setPWM1(pwm2);
    setPWM2(pwm1);
    
    
    
    e[0]=(setpoint-GetPos()); //error signal
    u[0]= fabs(e[0]);
}
 
    


