/*
 * protocol_parser.h
 *
 *  Created on: Mar 12, 2026
 *      Author: vlado
 */

#ifndef INC_PROTOCOL_PARSER_H_
#define INC_PROTOCOL_PARSER_H_

extern bool reset_ready;

enum FSM_States {
	CONNECTED_STATE,
	READY_STATE,
	MEASUREMENT_STATE,
	EXCHANGE_STATE,
	MEASUREMENT_EXCHANGE_STATE,
	RESET_STATE
};

void parserFSM();
void sensorInit();
void resetFSMProtocol();
// открыто здесь для тестов
bool checkCRC32(uint8_t* command_frame, uint16_t length);
// открыто здесь для тестов
uint32_t calculateCRC32(uint8_t* arg,uint16_t length);

void setFSMProtocolState(uint8_t state);

#endif /* INC_PROTOCOL_PARSER_H_ */
