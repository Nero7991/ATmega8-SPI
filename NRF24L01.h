/*
 * NRF24L01.h
 *
 * Created: 7/25/2017 4:53:57 PM
 *  Author: orencollaco
 */ 


#ifndef NRF24L01_H_
#define NRF24L01_H_
#include "Essential.h"

uint8_t init_NRF_TX(uint8_t data);
uint8_t isTXFull();
uint8_t isTXEmpty();
uint8_t isRXFull();
uint8_t isRXEmpty();
uint8_t isTX_DS_Set();
void readFIFO(volatile uint8_t *data);
void transmitPayload(volatile uint8_t data);
void writeToFIFO(volatile uint8_t *data);
uint8_t sendSPICommand(uint8_t cmd);
uint8_t writeSPIRegister(uint8_t addr, uint64_t data, uint8_t length);
uint64_t readSPIRegister(uint8_t addr, uint8_t length);
uint8_t readFIFObyte();
void writeFIFObyte(volatile uint8_t data);
void printInfo();
void fastTransferPayload(volatile uint8_t data);

#endif /* NRF24L01_H_ */