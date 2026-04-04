/*
 * SPI_Connection.c
 *
 *  Created on: Mar 6, 2026
 *      Author: AVA
 */

#include "SPI_Connection.h"
#include "protocol_common.h"
#include "protocol_parser.h"

bool spi_rx_complete, response_ready = false;
bool spi_state;

uint8_t response_frame[264] = {};		// буфер для хранения команды от мастера
uint8_t safe_command_frame[264] = {};
uint8_t dummy_frame[264] = {};			// буфер-заглушка для ответа мастеру
uint8_t trash_frame[264] = {};			// буфер для приема заглушки от мастера
uint8_t *spi_tx_ptr, *spi_rx_ptr;		// указатели на буфера для передачи по SPI
bool cs_selected = false;
uint8_t *new_response_frame;
uint8_t wait_response_frame[264] = {0};

void switchBuffer(bool spi_state);
void initResponseBuffer();

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    // Мастер опустил CS
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET) {
		// проверка на наличие готового ответа для отправки
		if(response_ready && spi_state == SPI_MODE_TX) { 	// если ответ готов и датчик в режиме передатчика
			spi_tx_ptr = new_response_frame;				// использовать для передачи сформированный ответ
			response_ready = false;
		} else if (spi_state == SPI_MODE_TX){				// ответ не готов и датчик в режиме передатчика
			spi_tx_ptr = wait_response_frame;				// использовать для передачи кадр с состоянием STATE_WAIT
		}
		// Запускаем прием/передачу
		HAL_SPI_TransmitReceive_IT(&hspi2, spi_tx_ptr, spi_rx_ptr, FRAME_LEN);
    }
}

void fillBuffer(uint8_t* buf, uint8_t fill_symbol) {
	for(int i = 0; i < FRAME_LEN; i++) {
		buf[i] = fill_symbol;
	}
}
void initSPIConnection() {
	spi_state = SPI_MODE_RX;
	switchBuffer(spi_state);
	fillBuffer(dummy_frame, 0xAA);
	initResponseBuffer();
};

void resetSPIConnection() {
	initSPIConnection();
	response_ready = 0;
}

void initResponseBuffer() {
	wait_response_frame[0] = 0xFA;
	wait_response_frame[1] = 0xAF;
	wait_response_frame[1] = STATE_WAIT;
	wait_response_frame[258] = 0xFF;
	wait_response_frame[259] = 0x0D;
	// TODO: добавить расчет CRC
	uint32_t crc = calculateCRC32(wait_response_frame, FRAME_LEN);
	wait_response_frame[260] = (crc >> 24) & 0xFF;
	wait_response_frame[261] = (crc >> 16) & 0xFF;
	wait_response_frame[262] = (crc >> 8) & 0xFF;
	wait_response_frame[263] = crc & 0xFF;
};

void switchBuffer(bool spi_state) {
	if(spi_state == SPI_MODE_TX) {
		//spi_tx_ptr = &response_frame[0];
		spi_rx_ptr = &trash_frame[0];
	} else {
		spi_tx_ptr = &dummy_frame[0];
		spi_rx_ptr = &response_frame[0];
	}
};
/* Обработчик прерывания по окончанию передачи/приема всего кадра */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if (hspi->Instance == SPI2)
    {
        if (spi_state == SPI_MODE_TX) {
        	// сделать датчик приемником в следующем сеансе
        	spi_state = SPI_MODE_RX;
        } else {
        	// сделать датчик передатчиком в следующем сеансе
        	spi_state = SPI_MODE_TX;
        	// сохранить полученную команду от мастера в безопасный буфер
        	memcpy(safe_command_frame,response_frame,FRAME_LEN);
        	spi_rx_complete = true;
        }
        switchBuffer(spi_state);
    }
}

