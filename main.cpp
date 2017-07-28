/*
 * ATmega8-SPI.cpp
 *
 * Created: 7/21/2017 3:40:38 PM
 * Author : orencollaco
 */ 

#include "NRF24L01.h"
volatile uint8_t buf1;
volatile bool buf1full = 0,NewPayload = 0;
int main(void)
{
	uint8_t PRIM_RX = 0;
	//uint8_t t;
	DDRD = (1 << 6); 
	Setup();
	Notify(PSTR("Hello, Mega8 alive."));
	Notify(PSTR("Initializing..."));
	if(!init_NRF_TX(!PRIM_RX)){
		Notify("Initialization failed for nRF24L01. Check connections");
		while(1);
	}
	//writeSPIRegister(0x10,0x12345678AB,5);
	Notify(PSTR("Initializing done."));
	while (1) 
    { 
		if(!PRIM_RX){
			if(NewPayload && 0){
				transmitPayload(buf1);
				NewPayload = 0;
				//printStringCRNL(hexToString(buf1));
				
				//printInfo();
			}
		}
		if(PRIM_RX){
			if(!isRXEmpty()){
				buf1 = readFIFObyte();
				PORTD ^= (1 << 6);
				//printStringCRNL(hexToString(buf1));
			}
			else{
				//printStringCRNL("Nothing to read, Waiting...");
			}
		}
    }
}

ISR(ADC_vect){
		writeFIFObyte(ADCH);
		buf1 = ADCH;
		NewPayload = 1;
		//PORTD ^= (1 << 6); 
		//writeFIFObyte(ADCH);
}

ISR(TIMER1_OVF_vect){
	OCR1AL = buf1;
}
 
 /* static uint8_t count = 0;
 if(count < 32){
 if(buf1full)
 buf2[count] = ADCH;
 else
 buf1[count] = ADCH;
 count += 1;
 }
 else{
 //printStringCRNL(hexToString(ADCH));
 NewPayload = 1;
 buf1full ^= 1;
 count = 0;
 } */
 
 /*
 static uint8_t count = 0;
 if(count < 32){
	 if(buf1full)
	 OCR1AL = buf1[count];
	 else
	 OCR1AL = buf2[count];
 }
 else{
	 count = 0;
 }*/