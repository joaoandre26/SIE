/* 
 * File  :  encoder.h
 * Author:  João Cruz       - 76517
 *          Henrique Martins- 76674    
 */

#ifndef ENCODER_H
#define	ENCODER_H

#ifdef	__cplusplus
extern "C" {
#endif
/*******************************************************************************
 * Função   : SetEncoderPorts
 * Input    : Não tem
 * Output   : Não tem
 * OverView : Funçao responsável pela definição dos pinos do microcontrolador 
 *          : como entrada.
 ******************************************************************************/
void SetEncoderPorts(void);
/*******************************************************************************
 * Função   : SetExternalInt0
 * Input    : Não tem
 * Output   : Não tem
 * OverView : Configuração de uma interrupção externa (INT0) para verificar 
 *          : quando há uma alteração de estado no canal A, não é necessario  
 *          : definir os outros como entrada, assim que existe uma interrupção 
 *          : verifica todos os canais.
 ******************************************************************************/
void SetExternalInt0(void);
/*******************************************************************************
 * Função   : SetExternalInt1
 * Input    : Não tem
 * Output   : Não tem
 * OverView : Configuração de uma interrupção externa (INT1) para verificar 
 *          : quando há uma alteração de estado no canal B, não é necessario  
 *          : definir os outros como entrada, assim que existe uma interrupção 
 *          : verifica todos os canais.
 ******************************************************************************/
void SetExternalInt1(void);
/*******************************************************************************
 * Função   : SetExternalInt2
 * Input    : Não tem
 * Output   : Não tem
 * OverView : Configuração de uma interrupção externa (INT2) para verificar 
 *          : quando há uma alteração de estado no canal Z, não é necessario  
 *          : definir os outros como entrada, assim que existe uma interrupção 
 *          : verifica todos os canais.
 ******************************************************************************/
void SetExternalInt2(void);
/*******************************************************************************
 * Função   : GetChannelA
 * Input    : Não tem
 * Output   : saída do canal
 * OverView : Devolve o estado do canal A (0/1)
 ******************************************************************************/
uint8_t GetChannelA(void);
/*******************************************************************************
 * Função   : GetChannelB
 * Input    : Não tem
 * Output   : saída do canal
 * OverView : Devolve o estado do canal B (0/1)
 ******************************************************************************/
uint8_t GetChannelB(void);
/*******************************************************************************
 * Função   : GetChannelZ
 * Input    : Não tem
 * Output   : saída do canal
 * OverView : Devolve o estado do canal Z (0/1)
 ******************************************************************************/
uint8_t GetChannelZ(void);
/*******************************************************************************
 * Função   : GetPos
 * Input    : Não tem
 * Output   : A posição do encoder
 * OverView : Devolve a posição do encoder
 ******************************************************************************/
uint32_t GetPos(void);
/*******************************************************************************
 * Função   : ResetPos
 * Input    : Não tem
 * Output   : Não tem
 * OverView : Faz o Reset da Posição.
 ******************************************************************************/
void UpdatePos(void);
/*******************************************************************************
 * Função   : ResetPos
 * Input    : Não tem
 * Output   : Não tem
 * OverView : Faz o Reset da Posição.
 ******************************************************************************/
void ResetPos(void);
/*******************************************************************************
 * Função   : Init_Timer4_Interrupt
 * Input    : Não tem
 * Output   : Não tem
 * OverView : Inicia um timer por interrupções responsável por fazer o Update 
 *          : da velocidade, tendo por base a posição actual quando comparada
 *          : com uma anteriormente medida e o periodo do timer. Freq = 400Hz
 ******************************************************************************/
//void Init_Timer4_Interrupt(void);



#ifdef	__cplusplus
}
#endif

#endif	/* ENCODER_H */

