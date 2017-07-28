/*
 * ATmega8A.cpp
 *
 * Created: 7/23/2017 5:17:53 PM
 *  Author: orencollaco
 */ 

#include "ATmega8A.h"



volatile uint64_t time;

void Setup(){
	SPI_MasterInit();
	USART_Init(12);
	init_T2_CTC();
	
}

void SPI_MasterInit(void)
{
	/* Sets MOSI and SCK as output all others inputs */
	DDRB = (1 << 3) | (1 << 5) | (1 << 2) | (1 << 0);
	/* Set SS bar high */
	PORTB = (1 << 2) | (1 << 0);
	/* Enable SPI as Master and set clock to FCPU/16 */
	SPCR = (1 << SPE) | (1 << MSTR);// | (1 << SPR1);
	_delay_us(10);
}

void SPI_MasterTransmit(char cData){
	/* Start Transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1 << SPIF)));
}

void init_T1_FASTPWM(){
	TCCR1A = 0x81;
	TCCR1B = 0x09;
	TIMSK |= (1 << TOIE1);
	DDRB |= (1 << 1);
	//OCR1A = 1000;
	sei();
}

void init_T1_CTC(){
	
}

void init_T2_CTC(){
	TCCR2 = 0x0B;
	OCR2 = 233;
	TIMSK |= (1 << OCIE2);
	sei();
}

void init_T0_CTC(uint8_t prescale){
	TCCR0 = 0x03;
}

void USART_Init( unsigned int ubrr)
{
	/*Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSRB =(1<<RXEN) | (1<<UCSZ2) | (1<<TXEN);
	/* Set Frame Format : 9 data, 2 stop bits */
	UCSRC = (1<<URSEL)|(1<<UCSZ0) | (1<<UCSZ1);
}

void USART_Transmit9( unsigned int data )
{
	/* Wait for empty transmit Buffer */
	while(!(UCSRA & (1<<UDRE)));
	UCSRB &= ~(1<<TXB8);
	if (data & 0x100)
	UCSRB |= (1<<TXB8);
	UDR = data;
}

void USART_Transmit(uint8_t data){
	/* Wait for empty transmit Buffer */
	while(!(UCSRA & (1 << UDRE)));
	/* Put data in the buffer */
	UDR = data;
}

void USART1_Transmit(uint8_t data){
	
}

unsigned int USART_Receive( void )
{
	unsigned char status, resh, resl;
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get status and 9th bit, then data */
	/* from buffer */
	status = UCSRA;
	resh = UCSRB;
	resl = UDR;
	/* If error, return -1 */
	if (status & ((1<<FE)|(1<<DOR)|(1<<2)))
	return -1;
	/* Filter the 9th bit, then return */
	resh = (resh >> 1) & 0x01;
	return ((resh << 8) | resl);
}

void ADC_Init(unsigned char admux, unsigned char adcsra)
{
	ADMUX = admux;
	ADCSRA = adcsra;
}
void ADC_ChangeChannelTo(unsigned char admux)
{
	admux&=0x0F;
	admux|=admux_c;
	ADMUX = admux;
}

unsigned char ADC_Read(unsigned char admux)
{
	admux&=0x0F;
	admux|=admux_c;
	ADMUX = admux;
	while(!(ADCSRA & (1<<ADIF)))
	;
	return ADCH;
}
void ADC_Start()
{
	ADCSRA = adcsra_c | (1<<ADSC);
}

uint64_t millis(){
	return time;
}

ISR(TIMER1_COMPA_vect){
	//PORTD ^= (1 << 6);
}

ISR(TIMER2_COMP_vect){
	time += 1;
	//PORTD ^= (1 << 6);
}