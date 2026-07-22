#include "exp_measurement.h"

#include <stdbool.h>
#include <stdint.h>

#define MEASUREMENT_TIME_MAX_MS 60000

bool measurement_works = false;
uint32_t measurement_time = 0;

uint32_t get_measurement_time() {
	return measurement_time;
}

void reset_meas_time() {

	measurement_time = 0;
	__HAL_TIM_SET_COUNTER(&htim1,0);

	return;
}

void start_measurement() {

	if (measurement_works) {
		reset_meas_time();
		measurement_works = true;
		return;
	}

	HAL_TIM_Base_Start_IT(&htim3);

	// Запуск таймера времени измерения
	HAL_TIM_Base_Start_IT(&htim1);

	HAL_TIM_Base_Start_IT(&htim4);

	measurement_works = true;

	return;
}

void stop_measurement() {

	measurement_works = false;
	HAL_TIM_Base_Stop(&htim1);
	HAL_TIM_Base_Stop(&htim3);
	HAL_TIM_Base_Stop(&htim4);
	__HAL_TIM_SET_COUNTER(&htim3,0);
	reset_meas_time();

	return;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1) {
        __HAL_TIM_SET_COUNTER(&htim1, 0);
        measurement_time++;

        if (measurement_time >= MEASUREMENT_TIME_MAX_MS) {
        	measurement_time = 0;
        }
    }
    if (htim->Instance == TIM4) {
    	led_switch();
    	__HAL_TIM_SET_COUNTER(&htim4, 0);
    }
}
