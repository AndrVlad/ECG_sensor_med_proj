#include "w25q_spi.h"
//-------------------------------------------------------------
#define    W25_WRITE_DISABLE  0x04
#define    W25_WRITE_ENABLE 0x06
#define    W25_SECTOR_ERASE 0x20
#define    W25_BLOCK_ERASE  0xD8
#define    W25_CHIP_ERASE 0xC7
#define    W25_ENABLE_RESET  0x66
#define    W25_RESET  0x99
#define    W25_READ  0x03
#define    W25_PAGE_PROGRAMM  0x02
#define    W25_FAST_READ  0x0B
#define    W25_GET_JEDEC_ID  0x9f
#define    W25_READ_STATUS_1  0x05
#define    W25_READ_STATUS_2  0x35
#define    W25_READ_STATUS_3  0x15
#define    W25_WRITE_STATUS_1 0x01
#define    W25_WRITE_STATUS_2 0x31
#define    W25_WRITE_STATUS_3 0x11

//-------------------------------------------------------------
#define cs_set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET)
#define cs_reset() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET)
//-------------------------------------------------------------
extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;
//-------------------------------------------------------------
w25_info_t  w25_info;
//-------------------------------------------------------------
char str1[30];
static uint8_t buf[10];



//-------------------------------------------------------------
void myDelay(void)
{
  for (long unsigned int i = 0; i < 50; i++)
    asm("nop");
}

//-------------------------------------------------------------
void SPI1_Send (uint8_t *dt, uint16_t cnt)
{
  HAL_SPI_Transmit (&hspi1, dt, cnt, 5000);

}
//-------------------------------------------------------------
void SPI1_Recv (uint8_t *dt, uint16_t cnt)
{
  HAL_SPI_Receive (&hspi1, dt, cnt, 5000);
}
//-------------------------------------------------------------
void W25_Reset (void)
{
  cs_set();
  buf[0] = W25_ENABLE_RESET;
  buf[1] = W25_RESET;
  SPI1_Send(buf, 2);
  cs_reset();
}
//-------------------------------------------------------------//-------------------------------------------------------------
void W25_Read_Info(char* str_info)
{
	unsigned int id = W25_Read_ID();
  sprintf(str_info,"ID:0x%X\n",id);
	id &= 0x0000ffff;
  w25_info.high_cap = 0;
	switch(id)
  {
    case 0x401A:
      w25_info.high_cap=1;
      w25_info.BlockCount=1024;
      strcat(str_info,"w25qxx Chip: w25q512\n");
      break;
    case 0x4019:
      w25_info.high_cap=1;
      w25_info.BlockCount=512;
      strcat(str_info,"w25qxx Chip: w25q256\n");
      break;
    case 0x4018:
      w25_info.BlockCount=256;
      strcat(str_info,"w25qxx Chip: w25q128\n");
      break;
    case 0x4017:
      w25_info.BlockCount=128;
      strcat(str_info,"w25qxx Chip: w25q64\n");
      break;
    case 0x4016:
      w25_info.BlockCount=64;
      strcat(str_info,"w25qxx Chip: w25q32\n");
      break;
    case 0x4015:
      w25_info.BlockCount=32;
      strcat(str_info,"w25qxx Chip: w25q16\n");
      break;
    case 0x4014:
      w25_info.BlockCount=16;
      strcat(str_info,"w25qxx Chip: w25q80\n");
      break;
    case 0x4013:
      w25_info.BlockCount=8;
      strcat(str_info,"w25qxx Chip: w25q40\n");
      break;
    case 0x4012:
      w25_info.BlockCount=4;
      strcat(str_info,"w25qxx Chip: w25q20\n");
      break;
    case 0x4011:
      w25_info.BlockCount=2;
      strcat(str_info,"w25qxx Chip: w25q10\n");
      break;
    default:
      strcat(str_info,"w25qxx Unknown ID\n");
      return;
  }
  w25_info.PageSize=256;
  w25_info.SectorSize=0x1000;
  w25_info.SectorCount=w25_info.BlockCount*16;
  w25_info.PageCount=(w25_info.SectorCount*w25_info.SectorSize)/w25_info.PageSize;
  w25_info.BlockSize=w25_info.SectorSize*16;
  w25_info.NumKB=(w25_info.SectorCount*w25_info.SectorSize)/1024;
  sprintf(str1,"Page Size: %d Bytes\n",(unsigned int)w25_info.PageSize);
  strcat(str_info,str1);
  sprintf(str1,"Page Count: %u\n",(unsigned int)w25_info.PageCount);
  strcat(str_info,str1);
  sprintf(str1,"Sector Size: %u Bytes\n",(unsigned int)w25_info.SectorSize);
  strcat(str_info,str1);
  sprintf(str1,"Sector Count: %u\r\n",(unsigned int)w25_info.SectorCount);
  strcat(str_info,str1);
  sprintf(str1,"Block Size: %u Bytes\n",(unsigned int)w25_info.BlockSize);
  strcat(str_info,str1);
  sprintf(str1,"Block Count: %u\n",(unsigned int)w25_info.BlockCount);
  strcat(str_info,str1);
  sprintf(str1,"Capacity: %u KB\n",(unsigned int)w25_info.NumKB);
  strcat(str_info,str1);
}//-------------------------------------------------------------
void W25_Write_Enable(void)
{
	cs_set();
  buf[0] = W25_WRITE_ENABLE;
	SPI1_Send(buf, 1);
	cs_reset();
}
//-------------------------------------------------------------
void W25_Write_Disable(void)
{
  cs_set();
  buf[0] = W25_WRITE_DISABLE;
  SPI1_Send(buf, 1);
  cs_reset();
}
//-------------------------------------------------------------
void W25_Set_Block_Protect(uint8_t val)
{
  /*buf[0] = 0x50;
  cs_set();
  SPI1_Send(buf, 1);
  cs_reset();
  buf[0] = W25_WRITE_STATUS_1;
  buf[1] = ((val & 0x0F) << 2);
  cs_set();
  SPI1_Send(buf, 2);
  cs_reset();

  W25_Ini(0); */
}
//-------------------------------------------------------------
void W25_Wait_Write_End(void)
{
  //HAL_Delay(1);
  myDelay();
  cs_set();
  buf[0] = W25_READ_STATUS_1;
  SPI1_Send(buf, 1);
  do{
    SPI1_Recv(buf,1);
    w25_info.StatusRegister1 = buf[0];
    //HAL_Delay(1);
    myDelay();
  }
  while((w25_info.StatusRegister1 & 0x01) == 0x01);
  cs_reset();
}
//-------------------------------------------------------------
void W25_Erase_Sector(uint32_t addr)
{
  W25_Wait_Write_End();
  W25_Set_Block_Protect(0x00);
  addr = addr * w25_info.SectorSize;
  W25_Write_Enable();
  cs_set();
  buf[0] = W25_SECTOR_ERASE;
  if(w25_info.high_cap)
  {
    buf[1] = (addr >> 24) & 0xFF;
    buf[2] = (addr >> 16) & 0xFF;
    buf[3] = (addr >> 8) & 0xFF;
    buf[4] = addr & 0xFF;
    SPI1_Send(buf, 5);
  }
  else
  {
    buf[1] = (addr >> 16) & 0xFF;
    buf[2] = (addr >> 8) & 0xFF;
    buf[3] = addr & 0xFF;
    SPI1_Send(buf, 4);
  }
  cs_reset();
  W25_Wait_Write_End();
  W25_Write_Disable();
  W25_Set_Block_Protect(0x0F);
}
//-------------------------------------------------------------
void W25_Erase_Block(uint32_t addr)
{
  W25_Wait_Write_End();
  addr = addr * w25_info.BlockSize;
  W25_Write_Enable();
  cs_set();
  buf[0] = W25_BLOCK_ERASE;
  if(w25_info.high_cap)
  {
    buf[1] = (addr >> 24) & 0xFF;
    buf[2] = (addr >> 16) & 0xFF;
    buf[3] = (addr >> 8) & 0xFF;
    buf[4] = addr & 0xFF;
    SPI1_Send(buf, 5);
  }
  else
  {
    buf[1] = (addr >> 16) & 0xFF;
    buf[2] = (addr >> 8) & 0xFF;
    buf[3] = addr & 0xFF;
    SPI1_Send(buf, 4);
  }
  cs_reset();
  W25_Wait_Write_End();
  W25_Write_Disable();
  W25_Set_Block_Protect(0x0F);
}
//-------------------------------------------------------------
void W25_Erase_Chip(void)
{
  W25_Wait_Write_End();
  W25_Write_Enable();
  cs_set();
  buf[0] = W25_CHIP_ERASE;
  SPI1_Send(buf, 1);
  cs_reset();
  W25_Wait_Write_End();
  W25_Write_Disable();
  W25_Set_Block_Protect(0x0F);
}
//-------------------------------------------------------------
void W25_Write_Data(uint32_t addr, uint8_t* data, uint32_t sz)
{
  W25_Wait_Write_End();
  W25_Set_Block_Protect(0x00);
  W25_Write_Enable();
  cs_set();
  buf[0] = W25_PAGE_PROGRAMM;
  if(w25_info.high_cap)
  {
    buf[1] = (addr >> 24) & 0xFF;
    buf[2] = (addr >> 16) & 0xFF;
    buf[3] = (addr >> 8) & 0xFF;
    buf[4] = addr & 0xFF;
    SPI1_Send(buf, 5);
  }
  else
  {
    buf[1] = (addr >> 16) & 0xFF;
    buf[2] = (addr >> 8) & 0xFF;
    buf[3] = addr & 0xFF;
    SPI1_Send(buf, 4);
  }
  SPI1_Send(data, sz);
  cs_reset();
  W25_Wait_Write_End();
  W25_Write_Disable();
  W25_Ini(0);
}
//-------------------------------------------------------------
void W25_Write_Page(uint8_t* data, uint32_t page_addr, uint32_t offset, uint32_t sz)
{
  if(sz > w25_info.PageSize)
      sz=w25_info.PageSize;
  if((offset+sz) > w25_info.PageSize)
      sz = w25_info.PageSize - offset;
  page_addr = page_addr * w25_info.PageSize + offset;


  W25_Wait_Write_End();
  W25_Set_Block_Protect(0x00);
  //HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11);
  W25_Write_Enable();
  cs_set();
  buf[0] = W25_PAGE_PROGRAMM;
  if(w25_info.high_cap)
  {
    buf[1] = (page_addr >> 24) & 0xFF;
    buf[2] = (page_addr >> 16) & 0xFF;
    buf[3] = (page_addr >> 8) & 0xFF;
    buf[4] = page_addr & 0xFF;
    SPI1_Send(buf, 5);
  }
  else
  {
    buf[1] = (page_addr >> 16) & 0xFF;
    buf[2] = (page_addr >> 8) & 0xFF;
    buf[3] = page_addr & 0xFF;
    SPI1_Send(buf, 4);
  }
  SPI1_Send(data, sz);
  cs_reset();
  W25_Wait_Write_End();
  W25_Write_Disable();
  W25_Set_Block_Protect(0x0F);
}
//-------------------------------------------------------------
void W25_Read_Data(uint32_t addr, uint8_t* data, uint32_t sz)
{
  cs_set();
  buf[0] = W25_READ;
  buf[1] = (addr >> 16) & 0xFF;
  buf[2] = (addr >> 8) & 0xFF;
  buf[3] = addr & 0xFF;
  SPI1_Send(buf, 4);
  SPI1_Recv(data, sz);
  cs_reset();
}
//-------------------------------------------------------------
 uint32_t W25_Read_ID(void)
{
  uint8_t dt[4];
  buf[0] = W25_GET_JEDEC_ID;
  cs_set();
  SPI1_Send(buf, 1);
  SPI1_Recv(dt,3);
  cs_reset();
  return (dt[0] << 16) | (dt[1] << 8) | dt[2];
}
//-------------------------------------------------------------
void W25_Ini(char need_report)
{
  unsigned int id = W25_Read_ID();
  HAL_Delay(100);
  W25_Reset();
  HAL_Delay(100);
  if (need_report)
  {
    HAL_UART_Transmit(&huart1,(uint8_t*)"\r\n",2,0x1000);
    sprintf(str1,"ID:0x%X\r\n",id);
    HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
  }
  id &= 0x0000ffff;
  w25_info.high_cap = 0;
  switch(id)
  {
    case 0x401A:
      w25_info.high_cap=1;
      w25_info.BlockCount=1024;
      sprintf(str1,"w25qxx Chip: w25q512\r\n");
      break;
    case 0x4019:
      w25_info.high_cap=1;
      w25_info.BlockCount=512;
      sprintf(str1,"w25qxx Chip: w25q256\r\n");
      break;
    case 0x4018:
      w25_info.BlockCount=256;
      sprintf(str1,"w25qxx Chip: w25q128\r\n");
      break;
    case 0x4017:
      w25_info.BlockCount=128;
      sprintf(str1,"w25qxx Chip: w25q64\r\n");
      break;
    case 0x4016:
      w25_info.BlockCount=64;
      sprintf(str1,"w25qxx Chip: w25q32\r\n");
      break;
    case 0x4015:
      w25_info.BlockCount=32;
      sprintf(str1,"w25qxx Chip: w25q16\r\n");
      break;
    case 0x4014:
      w25_info.BlockCount=16;
      sprintf(str1,"w25qxx Chip: w25q80\r\n");
      break;
    case 0x4013:
      w25_info.BlockCount=8;
      sprintf(str1,"w25qxx Chip: w25q40\r\n");
      break;
    case 0x4012:
      w25_info.BlockCount=4;
      sprintf(str1,"w25qxx Chip: w25q20\r\n");
      break;
    case 0x4011:
      w25_info.BlockCount=2;
      sprintf(str1,"w25qxx Chip: w25q10\r\n");
      break;
    default:
      sprintf(str1,"w25qxx Unknown ID\r\n");
      HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
      return;
  }
  if (need_report)
  {
    HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
  }
  w25_info.PageSize=256;
  w25_info.SectorSize=0x1000;
  w25_info.SectorCount=w25_info.BlockCount*16;
  w25_info.PageCount=(w25_info.SectorCount*w25_info.SectorSize)/w25_info.PageSize;
  w25_info.BlockSize=w25_info.SectorSize*16;
  w25_info.NumKB=(w25_info.SectorCount*w25_info.SectorSize)/1024;
  if (need_report)
  {
    sprintf(str1,"Page Size: %d Bytes\r\n",(unsigned int)w25_info.PageSize);HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
    sprintf(str1,"Page Count: %u\r\n",(unsigned int)w25_info.PageCount);
    HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
    sprintf(str1,"Sector Size: %u Bytes\r\n",(unsigned int)w25_info.SectorSize);
    HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
    sprintf(str1,"Sector Count: %u\r\n",(unsigned int)w25_info.SectorCount);
    HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
    sprintf(str1,"Block Size: %u Bytes\r\n",(unsigned int)w25_info.BlockSize);
    HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
    sprintf(str1,"Block Count: %u\r\n",(unsigned int)w25_info.BlockCount);
    HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
    sprintf(str1,"Capacity: %u KB\r\n",(unsigned int)w25_info.NumKB);
    HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
  }
}
//-------------------------------------------------------------
void W25_Read_Page(uint8_t* data, uint32_t page_addr, uint32_t offset, uint32_t sz)
{
  if(sz > w25_info.PageSize)
      sz=w25_info.PageSize;
  if((offset+sz) > w25_info.PageSize)
      sz = w25_info.PageSize - offset;
  page_addr = page_addr * w25_info.PageSize + offset;
  buf[0] = W25_FAST_READ;
  if(w25_info.high_cap)
  {
    buf[1] = (page_addr >> 24) & 0xFF;
    buf[2] = (page_addr >> 16) & 0xFF;
    buf[3] = (page_addr >> 8) & 0xFF;
    buf[4] = page_addr & 0xFF;
    buf[5] = 0;
    cs_set();
    SPI1_Send(buf, 6);
  }
  else
  {
    buf[1] = (page_addr >> 16) & 0xFF;
    buf[2] = (page_addr >> 8) & 0xFF;
    buf[3] = page_addr & 0xFF;
    buf[4] = 0;
    cs_set();
    SPI1_Send(buf, 5);
  }
  SPI1_Recv(data, sz);
  cs_reset();
}
