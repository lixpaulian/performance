//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// This is a workbench used to compare the gcc and IAR compilers. Various pieces
// of code are added to the workbench. As a reference the de facto standard
// "coremark" Ver 1.0 benchmark is also included.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

#include "coremark.h"
#include "xxtea.h"

#define COREMARK 1
#define XXTEA 2


#define BENCHMARK COREMARK

volatile uint32_t seconds = 0;

void SysTick_Handler(void);
static void initialize_hardware(void);
static void SystemClock_Config(void);

// ----- main() ---------------------------------------------------------------

int main(int argc, char* argv[])
{
	(void) argc;
	(void) argv;

	initialize_hardware();

	// At this stage the system clock should have already been configured
	// at high speed.
	printf("System clock: %lu Hz\n", SystemCoreClock);

	MX_TIM5_Init();

#if BENCHMARK == COREMARK
	printf("Run the coremark 1.0 benchmark\n");
	core_main(12000);		/* iterations */

#elif BENCHMARK == XXTEA
	printf("Run the XXTEA encryption/decryption benchmark\n");
	encryption_test(1000);	/* iterations */

#elif
	printf("No benchmark selected\n");
#endif

	printf("\nBenchmark done.\n");

	/* done, wait here indefinitely */
	for (;;)
		;
}

// This is the application hardware initialisation routine,
// redefined to add more inits.
//
// Called from _start(), right after data & bss init, before
// constructors.
//
// After reset the Cortex-M processor is in Thread mode,
// priority is Privileged, and the Stack is set to Main.
//
// Warning: The HAL requires the system timer, running at 1000 Hz
// and calling HAL_IncTick().

static void initialize_hardware(void)
{
	// Enable instruction & data cache.
	SCB_EnableICache();
	SCB_EnableDCache();

	// Initialise the HAL Library; it must be the first function
	// to be executed before the call of any HAL function.
	// More HAL initialisations can be defined in stm32f7xx_hal_msp.c
	HAL_Init();

	// Enable HSE Oscillator and activate PLL with HSE as source
	SystemClock_Config();

	// Call the CSMSIS system clock routine to store the clock frequency
	// in the SystemCoreClock global RAM location.
	SystemCoreClockUpdate();
}

// ----------------------------------------------------------------------------

/**
 * @brief  System Clock Configuration
 * @param  None
 * @retval None
 */
static void SystemClock_Config(void)
{
	// Enable Power Control clock
	__PWR_CLK_ENABLE()
	;

	// The voltage scaling allows optimizing the power consumption when the
	// device is clocked below the maximum system frequency, to update the
	// voltage scaling value regarding system frequency refer to product
	// datasheet.
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	RCC_OscInitTypeDef RCC_OscInitStruct;

	// Enable HSE Oscillator and activate PLL with HSE as source.
	// This is tuned for STM32F7-DISCOVERY; update it for your board.
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	// This assumes the HSE_VALUE is a multiple of 1 MHz. If this is not
	// your case, you have to recompute these PLL constants.
	RCC_OscInitStruct.PLL.PLLM = (HSE_VALUE / 1000000u);

	RCC_OscInitStruct.PLL.PLLN = 432; /* 216 MHz */
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 9; /* To make USB work. */
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	// Activate the OverDrive to reach the 200 MHz Frequency
	HAL_PWREx_EnableOverDrive();

	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	// Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	// clocks dividers
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	// This is expected to work for most large cores.
	// Check and update it for your own configuration.
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
	static int prescaler = 1000;

	HAL_IncTick();

	if (!prescaler--)
	{
		prescaler = 1000;
		seconds++;
	}
}

// ----------------------------------------------------------------------------
