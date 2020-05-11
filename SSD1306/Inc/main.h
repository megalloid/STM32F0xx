/**
 * @author  Андрей Заостровных
 * @email   megalloid@mail.ru
 * @link    http://smarthouseautomatics.ru/stm32/stm32f0xx/
 * @version v0.1
 * @ide     STM32CubeIDE
 * @brief   Настройки проекта
 */


#ifndef __MAIN_H
	#define __MAIN_H 100

	/* ###################################################### Общие настройки #################################################### */

	/* Семейство микроконтроллеров используемых в проекте */
	#ifndef 	STM32F0xx
		#define STM32F0xx
	#endif

	/* В верхнем регистре для исключения возможности ошибки */
	#ifndef 	STM32F0XX
		#define STM32F0XX
	#endif

	/* Модель микроконтроллера используемого в проекте */
	#ifndef 	STM32F051x8
		#define STM32F051x8
	#endif

	/* В верхнем регистре для исключения возможности ошибки */
	#ifndef 	STM32F051X8
		#define STM32F051X8
	#endif

	/* Тип использованнного устройства для отладки */
	#ifndef 	STM32F0_DISCOVERY
		#define STM32F0_DISCOVERY
	#endif


	/* ###################################################### Настройки тактирования ###################################################### */

	/* Устанавливаем значение HSE */
	#ifndef 	HSE_VALUE
		#define HSE_VALUE    								((uint32_t)8000000)
	#endif

	/* Устанавливаем HSI Calibration Value */
	#ifndef 	RCC_HSICALIBRATION_VALUE
		#define RCC_HSICALIBRATION_VALUE 					16U
	#endif

	/* Тип осцилятора: внешний (HSE) или внутренний (HSI) */
	#ifndef 	RCC_OSCILLATORTYPE
		#define RCC_OSCILLATORTYPE							RCC_OSCILLATORTYPE_HSE
	#endif

	/* Основной источник тактирования для микроконтроллера */
	#ifndef 	RCC_SYSCLK_SOURCE
		#define RCC_SYSCLK_SOURCE							RCC_SYSCLK_SOURCE_PLL
	#endif

	/* Источник тактового сигнала для PLL */
	#ifndef 	RCC_PLLSOURCE
		#define RCC_PLLSOURCE								RCC_PLLSOURCE_HSE
	#endif

	/* Устанавливаем основной предделитель */
	#ifndef 	RCC_PLL_PREDIV
		#define RCC_PLL_PREDIV								RCC_PLL_PREDIV_DIV1
	#endif

	/* Устанавливаем PLL умножитель */
	#ifndef 	RCC_PLL_MUL
		#define RCC_PLL_MUL 								RCC_PLL_MUL6
	#endif

	/* Устанавливаем делитель шины AHB */
	#ifndef 	RCC_AHB_DIV
		#define RCC_AHB_DIV 								RCC_AHB_DIV1
	#endif

	/* Устанавливаем делитель шины APB1 */
	#ifndef 	RCC_APB1_DIV
		#define RCC_APB1_DIV								RCC_APB1_DIV1
	#endif


	/* ###################################################### Настройки Flash (кэш, предвыборка и т.д.) ###################################################### */

	/* Устанавливаем значение предвыборки при чтении внутренней Flash в 1 если частота больше 24МГц, в 0 если 48МГц */
	#ifndef 	PREFETCH_ENABLE
		#define PREFETCH_ENABLE            					1U
	#endif

	/* Устанавливаем значение задержки при чтении внутренней Flash */
	#ifndef 	FLASH_LATENCY
		#define FLASH_LATENCY            					FLASH_ACR_LATENCY
	#endif


	/* ###################################################### Разные настройки ###################################################### */


#endif
