/*
 * sensor_utils.c
 *
 *  Created on: 20 мар. 2026 г.
 *      Author: AVA
 */

#include "sensor_utils.h"
#include "main.h"
#include "Common.h"
#include "w25q_spi.h"
#include "protocol_parser.h"
#include "SPI_Connection.h"
#include "ADS1293.h"
#include <stdbool.h>
#include <stdint.h>

bool need_selfcheck = 0;

/* Выполняет проверку работоспособности датчика
 * Возврат: 1 - датчик работоспособен
 * 			0 - датчик не работоспособен */
bool sensorSelfCheck() {

#ifdef TEST_VERSION
	return true;
#endif
	if(ads1293readdata(0x40) == 0x1) {
		return true;
	} else {
		return false;
	}
}

void sensorChipInit() {
	ADS1293_Init();
	return;
}

void resetSensorChip() {
	ADS1293_Init();
	return;
}

void stopSensorChip() {
	return;
}

void enableSensorChip() {
	return;
}

/* Выполняет сброс датчика */
void resetSensor() {

	stopMeasurement();

    // сброс cостояния протокола
    resetFSMProtocol();

    // сброс переменных
#ifndef MULTICHANNEL_VERSION
    page_pos_ptr = 0;
    page_ptr = 0;

#endif

#ifdef MULTICHANNEL_VERSION
    page_ptr = 0;
    write_cycle_closed = 0;
#endif
    // сброс микросхемы датчика
    resetSensorChip();

	// очистка флеш-памяти
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
    W25_Erase_Chip();

    reset_ready = true;

	return;
}
/* Запуск измерения */
void startMeasurement() {

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	// установка флага начала записи данных во флеш-память (равносильно началу измерения)
	need_save = 1;
	//enableSensorChip();
	return;
}

/* Остановка измерения */
void stopMeasurement() {

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
	W25_Ini(0);
	// сброс флага записи данных во флеш-память (равносильно началу измерения)
	need_save = 0;
	//stopSensorChip();
	return;
}



