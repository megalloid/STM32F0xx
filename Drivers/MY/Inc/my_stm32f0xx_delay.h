/**
 * @author  Andrey Zaostrovnykh
 * @email   megalloid@mail.ru
 * @website http://smarthouseautomatics.ru/stm32/stm32f0xx/delays
 * @version v0.1
 * @ide     STM32CubeIDE
 * @brief   Утилиты для работы с временными задержками
 */

#ifndef MY_STM32F0xx_DELAY_H
	#define MY_STM32F0xx_DELAY_H 100

	/* C++ detection */
	#ifdef __cplusplus
		extern "C"
		{
	#endif

	/**
	 * @addtogroup MY_STM32F0xx_Libraries
	 * @{
	 */

		/**
		 * @defgroup MY_DELAY
		 * @brief
		 *	@{
		 */

			/* Подключаем основные файлы библиотек и настройки проекта */
			#include "main.h"
			#include "my_stm32f0xx.h"

			/**
			 * @defgroup MY_DELAY_Settings
			 * @brief    Библиотечные настройки
			 * @{
			 */

			/**
			 * @} MY_DELAY_Settings
			 */


			/**
			 * @defgroup MY_DELAY_Defines
			 * @brief    Библиотечные константы
			 * @{
			 */


			/**
			 * @} MY_DELAY_Defines
			 */


			/**
			 * @defgroup MY_DELAY_Macros
			 * @brief    Библиотечные макросы
			 * @{
			 */

			/**
			 * @}  MY_DELAY_Macros
			 */


			/**
			 * @defgroup MY_DELAY_Typedefs
			 * @brief    Typedefs для библиотеки
			 * @{
			 */

			/**
			 * @} MY_DELAY_Typedefs
			 */


			/**
			 * @defgroup MY_DELAY_Functions
			 * @brief    Функции используемые в библиотеке
			 * @{
			 */
				/**
				 * @brief 	This function provides accurate delay (in milliseconds) based on variable incremented.
				 * @note 	In the default implementation , SysTick timer is the source of time base.
				 *       	It is used to generate interrupts at regular time intervals where uwTick is incremented.
				 * @note 	This function is declared as __weak to be overwritten in case of other implementations in user file.
				 * @param 	Delay specifies the delay time length, in milliseconds.
				 * @retval None
				 */
				void MY_Delay_ms(__IO uint32_t delay_ms);


			/**
			 * @} MY_DELAY_Functions
			 */

		/**
		 * @} MY_DELAY
		 */

	/**
	 * @} MY_STM32F0xx_Libraries
	 */

	/* C++ detection */
	#ifdef __cplusplus
		}
	#endif

#endif
