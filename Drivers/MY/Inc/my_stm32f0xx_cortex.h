/**
 * @author  Andrey Zaostrovnykh
 * @email   megalloid@mail.ru
 * @website http://smarthouseautomatics.ru/stm32/stm32f0xx/cortex
 * @version v0.1
 * @ide     STM32CubeIDE
 * @brief   Утилиты для работы с ядром Cortex-M0
 */

#ifndef MY_STM32F0xx_CORTEX_H
	#define MY_STM32F0xx_CORTEX_H 100

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
		 * @defgroup MY_CORTEX
		 * @brief
		 *	@{
		 */

			/* Подключаем основные файлы библиотек и настройки проекта */
			#include "main.h"
			#include "my_stm32f0xx.h"

			/**
			 * @defgroup MY_CORTEX_Settings
			 * @brief    Библиотечные настройки
			 * @{
			 */
				/*!< Приоритет прерывания от SysTick (по умолчанию наименьший) */
				/*  Внимание: Должен быть установлен в высокий приоритет для использования функций MY_Delay() и MY_SysTick_GetTick() */
				#ifndef		TICK_INT_PRIORITY
					#define	TICK_INT_PRIORITY           ((uint32_t)(1U<<__NVIC_PRIO_BITS) - 1U)
				#endif

			/**
			 * @} MY_CORTEX_Settings
			 */


			/**
			 * @defgroup MY_CORTEX_Defines
			 * @brief    Библиотечные константы
			 * @{
			 */
				/**
				 * @defgroup Источник тактирования SysTick
				 * @{
				 */
					#define SYSTICK_CLKSOURCE_HCLK_DIV8    (0x00000000U)
					#define SYSTICK_CLKSOURCE_HCLK         (0x00000004U)

				/**
				 * @}
				 */

				/* Маска ID */
				#define IDCODE_DEVID_MASK    (0x00000FFFU)

			/**
			 * @} MY_CORTEX_Defines
			 */


			/**
			 * @defgroup MY_CORTEX_Macros
			 * @brief    Библиотечные макросы
			 * @{
			 */

			/**
			 * @}  MY_CORTEX_Macros
			 */


			/**
			 * @defgroup MY_CORTEX_Typedefs
			 * @brief    Typedefs для библиотеки
			 * @{
			 */

			/**
			 * @} MY_CORTEX_Typedefs
			 */


			/**
			 * @defgroup MY_CORTEX_Functions
			 * @brief    Функции используемые в библиотеке
			 * @{
			 */

				/* ###################################################### Функции работы с SysTick ###################################################### */

				/**
				 * @brief 	Эта функция настраивает источник тактирования для временного отсчёта
				 *        	Источник тактирования настраивается чтобы иметь 1мс. точку отсчёта и выделенный приоритет прерываниям от SysTick
				 * @note 	Эта функция вызывается автоматически после начала выполнения основной программы либо после изменения настроек тактирования
				 * @note 	По умолчанию, таймер SysTick используется в качестве основы точки отсчёта времени.
				 *       	Используется для генерации прерываний в равные промежутки времени.
				 *       	Необходимо соблюдать осторожность, если MY_SYSTICK_Delay() используется в процессе ISR.
				 *					Прерывание SysTick должно иметь более высокий приоритет (численно ниже), чем прерывание периферии.
				 *					В противном случае процесс вызывающего прерывания ISR будет заблокирован.
				 * @param 	ticks: 				количество тиков (для получения значения в 1мс. нужно поделить системную частоту на 1000)
				 * @param 	TickPriority: приоритет прерывания
				 * @retval Нет
				 */
				void MY_SysTick_Init(uint32_t ticks, uint32_t TickPriority);


				/**
				 * @brief  Настройка источника тактирования для таймера SysTick
				 * @param  ClockSource может иметь следующие варианты тактирования:
				 *             @arg SYSTICK_CLKSOURCE_HCLK_DIV8: тактирование AHB clock делены на 8
				 *             @arg SYSTICK_CLKSOURCE_HCLK: тактирование AHB
				 * @retval Нет
				 */
				void MY_SysTick_ClockSourceConfig(uint32_t ClockSource);


				/**
				 * @brief 	Эта функция вызывается в прерывании от SysTick для инкремента глобальной переменной "uwTick"
				 * @note 	Каждый раз когда срабатывает прерывания в Systick - функция прибавляет значение на единицу
				 * @retval Нет
				 */
				void MY_SysTick_IncTick(void);


				/**
				 * @brief  Возвращает значение тиков из глобальной переменной
				 * @retval Значение "uwTick"
				 */
				uint32_t MY_SysTick_GetTick(void);


				/**
				 * @brief 	Остановка отсчёта "тиков"
				 * @note 	После вызова MY_SysTick_SuspendTick() отключается прерывание и отсчёт останавливается
				 * @retval Нет
				 */
				void MY_SysTick_SuspendTick(void);


				/**
				 * @brief 	Возобновление отсчёта "тиков"
				 * @note 	После вызова MY_SysTick_SuspendTick() включается прерывание и отсчёт начинается
				 * @retval Нет
				 */
				void MY_SysTick_ResumeTick(void);


				/* ###################################################### Функции работы с прерываниями ###################################################### */

				/**
				 * @brief  Включает прерывание в NVIC interrupt controller.
				 * @note   Чтобы правильно настроить приоритет прерываний, необходимо предварительно вызвать функцию NVIC_PriorityGroupConfig().
				 * @param  IRQn - номер прерывания
				 *         Может быть взят из списка IRQn_Type (Полный список указан в файле stm32f0xx.h)
				 * @retval Нет
				 */
				void MY_NVIC_EnableIRQ(IRQn_Type IRQn);


				/**
				 * @brief  Отключает прерывание в NVIC interrupt controller.
				 * @param  IRQn - номер прерывания
				 *         Может быть взят из списка IRQn_Type (Полный список указан в файле stm32f0xx.h)
				 * @retval Нет
				 */
				void MY_NVIC_DisableIRQ(IRQn_Type IRQn);


				/**
				 * @brief  Устанавливает приоритет прерывания
				 * @param  IRQn - номер прерывания
				 *         Может быть взят из списка IRQn_Type (Полный список указан в файле stm32f0xx.h)
				 * @param  PreemptPriority Опережающий приоритет для канала IRQn
				 *         Может устанавливаться в значении от 0 до 3.
				 *         Наименьшее значение имеет наибольший приоритет
				 * @retval Нет
				 */
				void MY_NVIC_Priority_Set(IRQn_Type IRQn, uint32_t PreemptPriority);


				/**
				 * @brief  Функция возвращает значение приоритета прерывание
				 * @param  IRQn - номер прерывания
				 *         Может быть взят из списка IRQn_Type (Полный список указан в файле stm32f0xx.h)
				 * @retval Возвращает IRQ-Number, если IRQn в ожидании
				 */
				uint32_t MY_NVIC_Priority_Get(IRQn_Type IRQn);


				/**
				 * @brief  Устанавливает прерывание в ожидание обработки
				 * @param  IRQn - номер прерывания
				 *         Может быть взят из списка IRQn_Type (Полный список указан в файле stm32f0xx.h)
				 * @retval Нет
				 */
				void MY_NVIC_PendingIRQ_Set(IRQn_Type IRQn);


				/**
				 * @brief  Проверяет ждёт ли прерывание обработки или нет
				 * @param  IRQn - номер прерывания
				 *         Может быть взят из списка IRQn_Type (Полный список указан в файле stm32f0xx.h)
				 * @retval status: - 0  не ожидает
				 *                 - 1  ожидает обработки
				 */
				uint32_t MY_NVIC_PendingIRQ_Get(IRQn_Type IRQn);


				/**
				 * @brief  Сбрасывает бит ожидания обработки прерывания
				 * @param  IRQn - номер прерывания
				 *         Может быть взят из списка IRQn_Type (Полный список указан в файле stm32f0xx.h)
				 * @retval Нет
				 */
				void MY_NVIC_PendingIRQ_Clear(IRQn_Type IRQn);


				/**
				 * @brief  Вызывает запрос на сброс MCU
				 * @retval Нет
				 */
				void MY_NVIC_SystemReset(void);


				/* ###################################################### Функции работы с ID микроконтроллера ###################################################### */

				/**
				 * @brief  Возвращает идентификатор ревизии MCU
				 */
				uint32_t MY_REVID_Get(void);


				/**
				 * @brief  Возвращает идентификатор MCUReturns the device identifier
				 */
				uint32_t MY_DEVID_Get(void);


				/**
				 * @brief  Возвращает первое слово уникального идентификатора MCU (UID состоит из 96 бит)
				 */
				uint32_t MY_UID_Word0_Get(void);


				/**
				 * @brief  Возвращает второе слово уникального идентификатора MCU (UID состоит из 96 бит)
				 */
				uint32_t MY_UID_Word1_Get(void);


				/**
				 * @brief  Возвращает третье слово уникального идентификатора MCU (UID состоит из 96 бит)
				 */
				uint32_t MY_UID_Word2_Get(void);


				/**
				 * @brief  Включает Debug Module в режиме STOP
				 * @retval Нет
				 */
				void MY_DBGMCU_DBGStopMode_Enable(void);


				/**
				 * @brief  Выключает Debug Module в режиме STOP
				 * @retval Нет
				 */
				void MY_DBGMCU_DBGStopMode_Disable(void);


				/**
				 * @brief  Включает Debug Module в режиме STANDBY
				 * @retval Нет
				 */
				void MY_DBGMCU_DBGStandbyMode_Enable(void);


				/**
				 * @brief  Выключает Debug Module в режиме STANDBY
				 * @retval Нет
				 */
				void MY_DBGMCU_DBGStandbyMode_Disable(void);

			/**
			 * @} MY_CORTEX_Functions
			 */

		/**
		 * @} MY_CORTEX
		 */

	/**
	 * @} MY_STM32F0xx_Libraries
	 */

	/* C++ detection */
	#ifdef __cplusplus
		}
	#endif

#endif
