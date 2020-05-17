/**
 * @author  Andrey Zaostrovnykh
 * @email   megalloid@mail.ru
 * @website http://smarthouseautomatics.ru/stm32/stm32f0xx/disco
 * @version v0.1
 * @ide     STM32CubeIDE
 * @brief   Полезные макросы и функции для работы с LED и BUTTON
 */

#ifndef MY_DISCO_H
	#define MY_DISCO_H

	/* C++ detection */
	#ifdef __cplusplus
		extern "C" {
	#endif

	/**
	 * @addtogroup MY_STM32F0xx_Libraries
	 * @{
	 */
		/**
		 * @defgroup MY_HAL_DISCO
		 * @brief    Библиотека LED и BUTTONS для STM32F0xx
		 *
		 * 		- STM32F0_DISCO: (STM32F051R8T6)
		 *   	- Leds:
		 *     	- LED_GREEN   on PC9
		 *     	- LED_BLUE    on PC8
		 *   	- Button: (HIGH when pressed)
		 *     	- Blue button on PA0
		 * @{
		 */

			#include "main.h"
			#include "my_stm32f0xx.h"

			/* STM32F0 Discovery */
			#if defined(STM32F0_DISCOVERY)
				#define DISCO_LED_PORT						GPIOC
				#define DISCO_LED_PINS						DISCO_LED_GREEN | DISCO_LED_BLUE
				#define DISCO_LED_GREEN						GPIO_PIN_9
				#define DISCO_LED_BLUE						GPIO_PIN_8
				#define DISCO_LED_ALL							DISCO_LED_GREEN | DISCO_LED_BLUE

				#define DISCO_BUTTON_PORT					GPIOA
				#define DISCO_BUTTON_PIN					GPIO_PIN_0
				#define DISCO_BUTTON_PRESSED			1
				#define DISCO_BUTTON_PULL					MY_GPIO_PuPd_NoPull

			/* Не выбрана плата */
			#else
				#warning "my_stm32f0xx_disco.h: Please select your board. Open my_stm32f0xx_disco.h and follow instructions! Support is currently disabled"

				#define DISCO_LED_GREEN									0
				#define DISCO_LED_RED										0
				#define DISCO_LED_ORANGE								0
				#define DISCO_LED_BLUE									0
				#define DISCO_LED_ALL										0

				#define DISCO_DISCO_LED_PORT						GPIOA
				#define DISCO_DISCO_LED_PINS						LED_ALL

				#define DISCO_BUTTON_PORT					GPIOA
				#define DISCO_BUTTON_PIN					0
				#define DISCO_BUTTON_PRESSED			0
				#define DISCO_BUTTON_PULL					MY_GPIO_PuPd_NoPull
			#endif

			/**
			 * @defgroup MY_DISCO_Functions
			 * @brief    Библиотечные функции
			 * @{
			 */
				/**
				 * @brief  Конфигурирует LED пины как outputs
				 * @param  Нет
				 * @retval Нет
				 */
				void MY_DISCO_LedInit(void);


				/**
				 * @brief  Конфигурирует пины кнопки как input
				 * @param  Нет
				 * @retval Нет
				 */
				void MY_DISCO_ButtonInit(void);


				/**
				 * @brief  Устанавливает значение в LED
				 * @param  led: LED который вы хотите инвертировать
				 * @param  state:
				 *            - = 0: выключает
				 *            - > 0: включает
				 * @retval Нет
				 */
				#define MY_DISCO_LedSet(led, state)    ((state) ? MY_DISCO_LedOn(led): MY_DISCO_LedOff(led))


				/**
				 * @brief  Включает LED на плате
				 * @param  led: LED который вы хотите включить
				 * @retval Нет
				 */
				#define MY_DISCO_LedOn(led)        			MY_GPIO_SetPinHigh(DISCO_LED_PORT, (uint16_t)(led))


				/**
				 * @brief  Выключает LED на плате
				 * @param  led: LED который вы хотите выключить
				 * @retval Нет
				 */
				#define MY_DISCO_LedOff(led)       			MY_GPIO_SetPinLow(DISCO_LED_PORT, (uint16_t)(led))


				/**
				 * @brief  Инвертирует LED на плате
				 * @param  led: LED который вы хотите инвертировать
				 * @retval Нет
				 */
				#define MY_DISCO_LedToggle(led)        MY_GPIO_TogglePinValue(DISCO_LED_PORT, (uint16_t)(led))


				/**
				 * @brief  Проверяет включен ли LED
				 * @param  led: LED который вы хотите инвертировать
				 * @retval Текущий статус LED:
				 *           - = 0: выключен
				 *           - > 0: включен
				 */
				#define MY_DISCO_LedIsOn(led)          MY_GPIO_GetOutputPinValue(DISCO_LED_PORT, (uint16_t)(led))


				/**
				 * @brief  Проверяет нажата ли кнопка
				 * @param  Нет
				 * @retval Текущий статус нажатия кнопки
				 *            - 0: кнопка не нажата
				 *            - > 0: кнопка нажата
				 */
				#define MY_DISCO_ButtonPressed()       ((MY_GPIO_GetInputPinValue(DISCO_BUTTON_PORT, DISCO_BUTTON_PIN) == 0) != DISCO_BUTTON_PRESSED)


				/**
				 * @brief  Проверяет произошло ли нажатие кнопки
				 * @param  Нет
				 * @retval Значение срабатывающее при нажатии
				 *           - 0: Если эта кнопка уже нажата при последнем вызове или еще не нажата
				 *           - 1: Произошло событие: кнопка была нажата
				 */
				uint8_t MY_DISCO_ButtonOnPressed(void);


				/**
				 * @brief  Проверяет была ли отпущена кнопка
				 * @param  Нет
				 * @retval Значение срабатывающее при отпускании кнопки
				 *           - 0: Кнопка была нажата но еще не была отпущена
				 *           - 1: Произошло событие: нажатая кнопка была отпущена
				 */
				uint8_t MY_DISCO_ButtonOnReleased(void);

			/**
			 * @}
			 */

		/**
		 * @}
		 */

	/**
	 * @}
	 */

	/* C++ detection */
	#ifdef __cplusplus
		}
	#endif

#endif
