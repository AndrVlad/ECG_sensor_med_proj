#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "ADS1293.h"

void ADS1293_WriteReg(uint8_t address, uint8_t data)
{
  uint8_t dataToSend[1];
  uint8_t addrToSend[1];
  dataToSend[0]=(address & 0x7F);
  addrToSend[0]=data;
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi1, dataToSend, 1, HAL_MAX_DELAY);
  HAL_SPI_Transmit(&hspi1, addrToSend, 1, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
}

uint8_t ads1293readdata(uint8_t rdAddress)
{
  uint8_t rdData;
  uint8_t dataToSend[1];

  dataToSend[0]= (rdAddress | 0x80);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi1, dataToSend, 1, HAL_MAX_DELAY);
  HAL_SPI_Receive(&hspi1, &rdData, 1, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);


  return rdData;
}

void ADS1293_Init()
{
  // Write initial configuration
  ADS1293_WriteReg(0x00, 0x00); // Stopt data conversion
  HAL_Delay(500);
  ADS1293_WriteReg(0x01, 0x11); // Set input multiplexer 11
  HAL_Delay(1);
  ADS1293_WriteReg(0x02, 0x19); // Set input multiplexer for channel 2
  HAL_Delay(1);
  ADS1293_WriteReg(0x03, 0x2E); // From Selikhov
  HAL_Delay(1);
  ADS1293_WriteReg(0x0A, 0x07); // Enable CMDET for IN1, IN2, IN3
  HAL_Delay(1);
  ADS1293_WriteReg(0x0C, 0x04); // Connect RLD amplifier to IN4
  HAL_Delay(1);
  ADS1293_WriteReg(0x0D, 0x01); // From Selikhov
  HAL_Delay(1);
  ADS1293_WriteReg(0x0E, 0x02); // From Selikhov
  HAL_Delay(1);
  ADS1293_WriteReg(0x0F, 0x03); // From Selikhov
  HAL_Delay(1);
  ADS1293_WriteReg(0x10, 0x01); // From Selikhov
  HAL_Delay(1);
  ADS1293_WriteReg(0x12, 0x04); // Use external crystal
  HAL_Delay(1);
  ADS1293_WriteReg(0x21, 0x02); // Set R2 decimation rate to 6 (was 0x02)
  HAL_Delay(1);
  ADS1293_WriteReg(0x22, 0x02); // Set R3 decimation rate to 16 for channel 1 (was 0x02)
  HAL_Delay(1);
  ADS1293_WriteReg(0x23, 0x02); // Set R3 decimation rate to 16 for channel 2 (was 0x02)
  HAL_Delay(1);
  ADS1293_WriteReg(0x24, 0x02); // Set R3 decimation rate to 16 for channel 3 (Selikhov) (was 0x02)
  HAL_Delay(1);
  ADS1293_WriteReg(0x27, 0x08); // Set DRDYB source to channel 1 ECG
  HAL_Delay(1);
  ADS1293_WriteReg(0x2F, 0x70); // Selikhov
  HAL_Delay(1);
  ADS1293_WriteReg(0x00, 0x01); // Start data conversion
  HAL_Delay(1);
}
