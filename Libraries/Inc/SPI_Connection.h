/*
 * SPI_connection.h
 *
 *  Created on: Mar 6, 2026
 *      Author: vlado
 */

#ifndef INC_SPI_CONNECTION_H_
#define INC_SPI_CONNECTION_H_

#include <stdio.h>
#include <stdbool.h>
#include "main.h"

#define SPI_MODE_RX 0
#define SPI_MODE_TX 1

#define FRAME_LEN 264

extern bool spi_rx_complete, response_ready;
extern uint8_t safe_command_frame[264];
extern uint8_t* new_response_frame;

void initSPIConnection();
void resetSPIConnection();

#endif /* INC_SPI_CONNECTION_H_ */
