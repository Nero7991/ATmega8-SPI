/*
 * ATmega8A.h
 *
 * Created: 7/23/2017 5:18:15 PM
 *  Author: orencollaco
 */ 

#define F_CPU 8000000UL
#ifndef ATMEGA8A_H_
#define ATMEGA8A_H_
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define admux_c 0x63
#define adcsra_c 0xAB
void Setup();
void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);
void USART_Init( unsigned int ubrr);
unsigned int USART_Receive( void );
void USART_Transmit9( unsigned int data );
void USART_Transmit(uint8_t data);
void USART1_Transmit(uint8_t data);
void ADC_Init(unsigned char admux, unsigned char adcsra);
void ADC_ChangeChannelTo(unsigned char admux);
unsigned char ADC_Read(unsigned char );
void ADC_Start();
void init_T1_FASTPWM();
void init_T1_CTC();
void init_T2_CTC();
uint64_t millis();


#endif /* ATMEGA8A_H_ */