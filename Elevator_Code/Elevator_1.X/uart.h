/* 
 * File  :  uart.h
 * Author:  João Cruz       - 76517
 *          Henrique Martins- 76674    
 */
#ifndef UART_H
#define	UART_H

/********************************************************************
* Function: 	Init_UART()
* Precondition: 
* Input: 		None.
* Returns:      None.
*               
* Side Effects:	Takes control of U1A TX and RX pins
* Overview:     Initializes UART.
*		
* 
********************************************************************/	
void Init_UART(void);

/********************************************************************
* Function: 	PutChar(char *str)
* Precondition: UART initialized
* Input: 		None.
* Output:		None.
* Side Effects:	None.
* Overview:     Put the data on UART TX FIFO.
* Note:		 	None.
********************************************************************/
void PutChar(char r);

/*******************************************************************
* Function: 	PutString(char *str)
* Precondition: UART initialized
* Input: 		None.
* Output:		None.
* Side Effects:	None.
* Overview:     Put string on UART TX FIFO.
* Note:		 	None.
********************************************************************/
void PutString(char *str);

/********************************************************************
* Function: 	GetChar()
* Precondition: UART initialized
* Input: 		None
* Output:		True: If there is some data.
* Side Effects:	None.
* Overview:     Gets the data from UART RX FIFO.
* Note:		 	None.
********************************************************************/
char GetChar();

#endif	/* UART_H */

