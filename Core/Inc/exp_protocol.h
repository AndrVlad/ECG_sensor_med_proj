/*
 * exp_protocol.h
 *
 *  Created on: Jul 21, 2026
 *      Author: vlado
 */

#ifndef INC_EXP_PROTOCOL_H_
#define INC_EXP_PROTOCOL_H_

#include "stm32f1xx_hal.h"
#include "main.h"
#include <stdbool.h>
#include <stdint.h>

#define SENSOR_ID_ 1;

extern uint8_t uart1_rx_buf[2];
extern bool uart1_rx_complete;
extern UART_HandleTypeDef huart1;


void parser_exp();
void uart_init();
void send_data(uint8_t* meas_result);


#endif /* INC_EXP_PROTOCOL_H_ */
