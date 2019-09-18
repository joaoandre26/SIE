/* 
 * File  :  buttons.h
 * Author:  João Cruz       - 76517
 *          Henrique Martins- 76674    
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#ifdef	__cplusplus
extern "C" {
#endif
/*******************************************************************************
 * Função   : InitButtons
 * Input    : Não tem
 * Output   : Não tem
 * OverView : Configura os portos aos quais estão ligados os PushButton e Switch
 *          : como entrada
 ******************************************************************************/
void InitButtons(void);
/*******************************************************************************
 * Função   : PushButton0/1/2/3
 * Input    : Não tem
 * Output   : estado do pushbutton 0/1/2/3
 * OverView : Devolve o estado do pushbutton, se este for primido, o estado
 *          : será 1
 ******************************************************************************/
uint32_t PushButton0(void);
uint32_t PushButton1(void);
uint32_t PushButton2(void);
uint32_t PushButton3(void);
/*******************************************************************************
 * Função   : BottomSwitch
 * Input    : Não tem
 * Output   : Estado do Switch
 * OverView : devolve o estado do switch, '1' se estiver activo e '0' se o 
 *          : contrário
 ******************************************************************************/
uint32_t BottomSwitch(void);

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

