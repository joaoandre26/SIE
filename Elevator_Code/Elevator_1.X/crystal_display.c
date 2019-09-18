/* 
 * File  :  crystal_display.c
 * Author:  João Cruz       - 76517
 *          Henrique Martins- 76674    
 */
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include "crystal_display.h"
#include <math.h>
/**
 * Assumptions about Pin-out for selected port:
 * RF0-RF3: Data Lines 4-7 (RF0 = DB4, RF1 = DB5, etc.) 45, 46, 0, 25
 * RG8: R/S (Register Select)   - PIN 23
 * RG9: E (Enable)              - PIN 22
 */

//Control Pins of LCD 
#define PIN_ENABLE_LCD     PORTCbits.RC2    
#define PIN_RS_LCD         PORTCbits.RC3  
 
//Data Pins of LCD
#define PIN_DB4_LCD PORTFbits.RF0  
#define PIN_DB5_LCD PORTFbits.RF1  
#define PIN_DB6_LCD PORTFbits.RF2  
#define PIN_DB7_LCD PORTFbits.RF3      
 
#define DATA_LCD PORTF
/*
 * 
 */
void InitPorts(void)
{
    //Set Enable as output
    TRISCbits.TRISC2 = 0;
    //Set RS as output
    TRISCbits.TRISC3 = 0;
    //Set data pins as outputs
    TRISFbits.TRISF0 = 0;   //DB4 - pin 45
    TRISFbits.TRISF1 = 0;   //DB5 - pin 46
    TRISFbits.TRISF2 = 0;   //DB6 - pin 0
    TRISFbits.TRISF3 = 0;   //DB7 - pin 25
}
void InitialiseDisplay(void)
{
    InitPorts();
    ResetDisplay();
    SendCommandToLCD(0x28);         //4 bit interface 2 line First Initialise
    delay(20);                      //20ms delay
    SendCommandToLCD(0x0C);        //Display cursor off
    delay(1);
    SendCommandToLCD(0x06);        //Entry Mode
    delay(1);
    SendCommandToLCD(0x0F);
    delay(1);
}
 
void ResetDisplay(void)
{
    delay(10);
    //TRISG = 0x00;    //Set RG1 - RG3 as o/p 
    //TRISF = 0x000;    //Set port F as o/p 
    delay(10);
    PIN_ENABLE_LCD = 0;    
    //PIN_RW_LCD     = 0;
    PIN_RS_LCD     = 0;
    //SendCommandToLCD(0x02);        
    SendCommandToLCD(0x03);        //First Initialise
    delay(10);
    SendCommandToLCD(0x03);        //Second Initialise
    delay(1);
    SendCommandToLCD(0x03);        //Third Initialise
    delay(1);
    SendCommandToLCD(0x02);        
    delay(1);
} 
void SendCommandToLCD(uint8_t uiCommand)
{
    //PIN_RS_LCD = 0;
    DATA_LCD = (DATA_LCD & 0xF0) | (uiCommand >> 4);    //Send MSB nibble
    //DATA_LCD = uiCommand >> 4;  //Send MSB nibble
    PIN_ENABLE_LCD = 1;    
    PIN_ENABLE_LCD = 0;    
    delay(1);
    DATA_LCD = (DATA_LCD & 0xF0) | (uiCommand & 0x0F);//Send LSB nibble
    //DATA_LCD = uiCommand & 0x0F; //Send LSB nibble
    PIN_ENABLE_LCD = 1;    
    PIN_ENABLE_LCD = 0;    
    delay(1);
}
void LCDSendString(char * str)
{
    //PIN_RS_LCD = 1;
    while(*str)
    {
        LCDSendChar(*str++);
    }
}
void LCDSendChar(char character)
{
    PIN_RS_LCD = 1;
    DATA_LCD = (DATA_LCD & 0xF0) | (character >> 4);  //Send MSB nibble
    //DATA_LCD = character >> 4;  //Send MSB nibble
    PIN_ENABLE_LCD = 1;    
    PIN_ENABLE_LCD = 0;    
    delay(1);
    DATA_LCD = (DATA_LCD & 0xF0) | (character & 0x0F); //Send LSB nibble
    //DATA_LCD = character & 0x0F; //Send LSB nibble
    PIN_ENABLE_LCD = 1;    
    PIN_ENABLE_LCD = 0;    
    delay(1);
}
void delay(uint32_t period)
{
    //1s = 400000 conts 
    //1ms = 400
    const uint32_t ms = 4000;
    uint32_t MaxCount;
    uint32_t counter;
    
    MaxCount = period*ms;
    /* Delay... */
    for (counter = 0; counter < MaxCount; counter++) {
        asm("nop");
    }
}
uint8_t DecToASCII(uint8_t number)
{
    uint8_t val_ascii;
    if(number == 0)
    {
        val_ascii = 0x30;
    }
    else if(number == 1)
    {
        val_ascii = 0x31;
    }
    else if(number == 2)
    {
        val_ascii = 0x32;
    }
    else if(number == 3)
    {
        val_ascii = 0x33;
    }
    else if(number == 4)
    {
        val_ascii = 0x34;
    }
    else if(number == 5)
    {
        val_ascii = 0x35;
    }
    else if(number == 6)
    {
        val_ascii = 0x36;
    }
    else if(number == 7)
    {
        val_ascii = 0x37;
    }
    else if(number == 8)
    {
        val_ascii = 0x38;
    }
    else if(number == 9)
    {
        val_ascii = 0x39;
    }
    else
    {
        val_ascii = 0x30;
    }
    return val_ascii;
}
void UpdateL1(void)
{
    mLCDClear();
    ResetDisplay();
    mLCDSetCursor(0,0);
    LCDSendString("Bem-Vindo       ");
}
void UpdateL2(uint8_t nr2)
{
    mLCDClear();
    delay(2);
    ResetDisplay();
    uint8_t c, d, u;
    mLCDSetCursor(1,0);
    LCDSendString("Andar: ");
    //mLCDSetCursor(1,13);
    mLCDSetCursor(1,200);    
    LCDSendChar(DecToASCII(nr2));
    mLCDSetCursor(1,200);
    LCDSendString("      ");
}
void UpdateL3(void)
{
    mLCDClear();
    ResetDisplay();
    mLCDSetCursor(1,0);
    LCDSendString("Calibration     ");
}