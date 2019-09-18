

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif
/*******************************************************************************
 * Funçao   : readADC0/1/2/3
 * Input    : Não tem
 * Output   : Returna valor do buffer para o AN0/1/2/3
 * OverView : Retorna o valor presente no buffer entre 0 e 1023
 ******************************************************************************/
uint32_t readADC0(void);   
uint32_t readADC1(void);
uint32_t readADC2(void);
uint32_t readADC3(void);
/*******************************************************************************
 * Função   : initADCTimer
 * Input    : Não tem
 * Output   : Não tem
 * OverView : Inicia o Timer 3 para ler com regularidade o buffer da ADC com
 *            uma frequencia de 400Hz
 ******************************************************************************/
void initADCTimer(void);
/*******************************************************************************
 * Função   : initADC
 * Input    : Não tem
 * Output   : Não tem
 * OverView : Configura a ADC
 ******************************************************************************/
void initADC(void);
/*******************************************************************************
 * Função   : buffer
 * Input    : Não tem
 * Output   : Buffer
 * OverView : Lê o valor no buffer da adc
 ******************************************************************************/
uint32_t buffer(void);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

