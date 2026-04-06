/*
 * protocol_common.h
 *
 *  Created on: Mar 12, 2026
 *      Author: AVA
 */

#ifndef INC_PROTOCOL_COMMON_H_
#define INC_PROTOCOL_COMMON_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* Идентификатор датчика */
#define SENSOR_ID 			0x1A

/* Версия для обработки нескольких каналов данных измерения с датчика
 * (закомментировать, если используется обработка одного канала данных измерения) */
#define MULTICHANNEL_VERSION 1

/* Длина кадра ответа */
#define CONTROL_FRAME_LEN 	10

/* Состояние датчика */
#define STATE_READY 		0x01 		// устройство готово
#define STATE_NOT_READY 	0x02		// устройство занято
#define STATE_WAIT 			0x03		// устройство не готово предоставить ответ
#define STATE_RESET 		0x05		// устройство сброшено
#define STATE_START_MEASURE 0x06		// измерение начато
#define STATE_STOP_MEASURE 	0x07		// устройство сброшено
#define STATE_ERROR 		0x08		// ошибка устройства
#define STATE_CRC_ERR		0xFF		// контрольная сумма полученной команды неверна


/* Ответы датчика (введенные для удобства) */
#define CRC_ERROR			0xFF

/* Команды от ведущего устройства */
#define CMD_GET_MEASURE 	0xA1 		// запрос результата измерения
#define CMD_STATUS 			0xA2		// запрос статуса
#define CMD_RESET 			0xA3		// сброс датчика
#define CMD_START_MEASURE 	0xA4		// запрос начать измерение
#define CMD_STOP_MEASURE 	0xA7		// остановка измерения
#define CMD_CRC_ANS_ERR 	0xFF		// ошибка CRC полученного кадра

#endif /* INC_PROTOCOL_COMMON_H_ */
