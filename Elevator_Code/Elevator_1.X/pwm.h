/* 
 * File  :  pwm.h
 * Author:  João Cruz       - 76517
 *          Henrique Martins- 76674    
 */
#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif
/*******************************************************************************
 * Função   : SetTimer
 * Input    : freq       - em Hz
 * Output   : Não está definida, não é necessário
 * OverView : Configuração e inicialização do timer
 ******************************************************************************/
int SetTimer(void);
/*******************************************************************************
 * Função   : StartTimer
 * Input    : Não tem
 * Output   : Não tem
 * Overview : Inicia o timer
 ******************************************************************************/
void StartTimer(void);
/*******************************************************************************
 * Função   : StopTimer
 * Input    : Não tem
 * Output   : Não tem
 * Overview : Para o timer
 ******************************************************************************/
void StopTimer(void);
/*******************************************************************************
 * Função   : setPWM1
 * Input    : duty cycle
 * Output   : Não tem
 * Overview : Configura uma saída pwm OC2
 ******************************************************************************/
void setPWM1(uint8_t duty_cycle);
/*******************************************************************************
 * Função   : setPWM2
 * Input    : duty cycle
 * Output   : Não tem
 * Overview : Configura uma saída pwm OC3
 ******************************************************************************/
void setPWM2(uint8_t duty_cycle);

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

