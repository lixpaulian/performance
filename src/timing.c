/*
 * timming.c
 *
 * (c) 2016 Lixco Microsystems <lix@paulian.net>
 *
 * Created on: Aug 7, 2016 (LNP)
 */

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include "timing.h"


TIM_HandleTypeDef htim5;

/**
 * @brief  TIM_Config: Configure TIM5 timer (32 bit). The timer increments in
 * @brief  1 us steps and is used for profiling.
 */
void MX_TIM5_Init(void)
{
	/* TIMx Peripheral clock enable */
	__TIM5_CLK_ENABLE();

	/* Set TIM5 instance */
	htim5.Instance = TIM5;

	htim5.Init.Period = 0xFFFFFFFF;
	htim5.Init.Prescaler = (uint16_t) ((SystemCoreClock / 2) / 1000000) - 1;
	htim5.Init.ClockDivision = 0;
	htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim5.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&htim5);
	__HAL_TIM_SetCounter(&htim5, 0);
	HAL_TIM_Base_Start(&htim5);
}

/**
 * @brief       Returns the current 32 bit value of the us counter.
 * @retval      The current value of the Timer5 register
 */
uint32_t getCounterValue(void)
{
	return TIM5->CNT;
}
