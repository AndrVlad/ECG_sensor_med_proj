
#ifndef __W25Q_SPI_H
#define __W25Q_SPI_H
//-------------------------------------------------------------
#include "stm32f1xx_hal.h"
#include "stdint.h"
#include <stdio.h>
#include <string.h>
typedef struct
{
  uint16_t  PageSize;
  uint32_t  PageCount;
  uint32_t  SectorSize;
  uint32_t  SectorCount;
  uint32_t  BlockSize;
  uint32_t  BlockCount;
  uint32_t  NumKB;
  uint8_t   SR1;
  uint8_t   SR2;
  uint8_t   SR3;
  uint8_t   high_cap;
  uint8_t   StatusRegister1;
  uint8_t   StatusRegister2;
  uint8_t   StatusRegister3;
}w25_info_t;
//-------------------------------------------------------------
void SPI1_Send (uint8_t *dt, uint16_t cnt);
void SPI1_Recv (uint8_t *dt, uint16_t cnt);
void W25_Reset (void);
void W25_Read_Info(char* str_info);
void W25_Erase_Sector(uint32_t addr);
void W25_Erase_Block(uint32_t addr);
void W25_Erase_Chip(void);
void W25_Read_Data(uint32_t addr, uint8_t* data, uint32_t sz);
uint32_t W25_Read_ID(void);
void W25_Ini(char need_report);
void W25_Read_Page(uint8_t* data, uint32_t page_addr, uint32_t offset, uint32_t sz);
void W25_Read_Data(uint32_t addr, uint8_t* data, uint32_t sz);
void W25_Read_Page(uint8_t* data, uint32_t page_addr, uint32_t offset, uint32_t sz);
void W25_Write_Data(uint32_t addr, uint8_t* data, uint32_t sz);
void W25_Write_Page(uint8_t* data, uint32_t page_addr, uint32_t offset, uint32_t sz);
//-------------------------------------------------------------
#endif /* __W25Q_SPI_H */
