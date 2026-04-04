#ifndef ADS1293_H_
#define ADS1293_H_

#include "main.h"
void ADS1293_WriteReg(uint8_t address, uint8_t data);
uint8_t ads1293readdata(uint8_t rdAddress);
void ADS1293_Init();

#endif /* ADS1293_ADS1293_H_ */
