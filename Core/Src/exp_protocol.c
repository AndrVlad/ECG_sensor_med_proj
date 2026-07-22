#include "exp_protocol.h"
#include "exp_measurement.h"
#include "stm32f1xx_hal.h"
#include <string.h>



uint8_t uart1_rx_buf[2];
uint8_t uart1_rx_safe_buf[2] = {0x0};
uint8_t uart1_tx_buf[9] = {0x0};
bool uart1_rx_complete;

void parser_exp() {

	uart1_rx_complete = false;

	switch(uart1_rx_buf[0]) {
	case 0xAA:
		start_measurement();
		break;
	case 0xFF:
		stop_measurement();
		led_off();
		break;
	default:
		break;
	}
	return;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uart1_rx_complete = true;
	memcpy(uart1_rx_safe_buf, uart1_rx_buf,1);
	led_switch();
	HAL_UART_Receive_IT(&huart1,uart1_rx_buf,1);

}

void uart_init() {
	HAL_UART_Receive_IT(&huart1,uart1_rx_buf,1);
	led_on();
}

void send_data(uint8_t* meas_result) {

	//led_switch();

	uint32_t meas_time;
	meas_time = get_measurement_time();

	uart1_tx_buf[0] = SENSOR_ID_;
	uart1_tx_buf[1] = meas_time;
	uart1_tx_buf[2] = meas_time >> 8;
	uart1_tx_buf[3] = meas_result[0];
	uart1_tx_buf[4] = meas_result[1];
	uart1_tx_buf[5] = meas_result[2];
	uart1_tx_buf[6] = meas_result[3];
	uart1_tx_buf[7] = meas_result[4];
	uart1_tx_buf[8] = meas_result[5];

	HAL_UART_Transmit(&huart1,uart1_tx_buf,9,4);

	return;
}


