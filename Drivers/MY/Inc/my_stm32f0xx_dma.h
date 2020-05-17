/**
 * @author  Andrey Zaostrovnykh
 * @email   megalloid@mail.ru
 * @website http://smarthouseautomatics.ru/stm32/stm32f0xx/dma
 * @version v0.1
 * @ide     STM32CubeIDE
 * @brief   Утилиты для работы с DMA
 */

#ifndef MY_STM32F0xx_DMA_H
	#define MY_STM32F0xx_DMA_H 100

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
		 * @defgroup MY_DMA
		 * @brief
		 *
		 ==============================================================================
                        ##### Как использовать данный драйвер #####
  	  	 ==============================================================================

   	     (#) Включить и сконфигурировать периферию которая подключенна к одному из канала DMA
       	 	 (исключая внутренную память SRAM/FLASH: инициализация не требуется
       	 	 Для получения информации о соединении между периферией и каналами DMA необходимо обратиться в Reference Manual.

   	     (#) Для использования DMA требуется настройка соответствующих параметров:
       	   	 - Transfer Direction
       	   	 - Source and Destination data formats
       	   	 - Circular or Normal mode
       	   	 - Channel Priority level
       	   	 - Source and Destination Increment mode,
       	   	 используя функцию MY_DMA_Init()

   	     (#) Используя функцию MY_DMA_GetState() можно получить текущее состояние DMA

   	     (#) Используя функцию MY_DMA_GetError() можно получить текущую ошибку при работе

   	     (#) Используя функцию MY_DMA_Abort() можно прервать текущую передачу.

   	      	 Примечание. В случае передачи Memory-to-Memory, Circular mode не доступен

   	     ==============================================================================
                        		##### Polling mode IO #####
   	     ==============================================================================

   	     (+) Функция MY_DMA_Start() используется для запуска передачи через DMA после
   	     	 настройки Source address, Destination address и длину передаваемых данных.

   	     (+) Функция MY_DMA_PollForTransfer() для фиксации конца текущей передачи,
   	     	 в этом случае фиксированный тайм-аут может быть настроен в зависимости от его приложения.

   	     ==============================================================================
                        		##### Interrupt mode IO #####
   	     ==============================================================================

   	     (+) Настройка приоритета прерывания от DMA используя MY_NVIC_SetPriority()

   	     (+) Включаем DMA IRQ handler используя MY_NVIC_EnableIRQ()

   	     (+) Используя функцию MY_DMA_Start_IT() запускается передача DMA после настройки
          	 Source address и Destination address  и длину передаваемых данных.

   	     (+) Используем обработчик прерывания через вызов MY_DMA_Channel_IRQHandler() в DMA_IRQHandler()

   	     (+) At the end of data transfer MY_DMA_IRQHandler() function is executed and user can
          	 add his own function by customization of function pointer XferCpltCallback and
          	 XferErrorCallback (i.e a member of DMA handle structure).

		 * @{
		 */

			/* Подключаем основные файлы библиотек и настройки проекта */
			#include "main.h"
			#include "my_stm32f0xx.h"

			/**
			 * @defgroup MY_DMA_Settings
			 * @brief    Библиотечные настройки
			 * @{
			 */

			/**
			 * @} MY_DMA_Settings
			 */


			/**
			 * @defgroup MY_DMA_Defines
			 * @brief    Библиотечные константы
			 * @{
			 */
				/**
				 * @brief Направление передачи данных через DMA
				 */
				#define DMA_PERIPH_TO_MEMORY        (0x00000000U)        			/*!< Peripheral to memory direction */
				#define DMA_MEMORY_TO_PERIPH        ((uint32_t)(DMA_CCR_DIR))      	/*!< Memory to peripheral direction */
				#define DMA_MEMORY_TO_MEMORY        ((uint32_t)(DMA_CCR_MEM2MEM)) 	/*!< Memory to memory direction     */


				/**
				 * @brief Peripheral incremented mode DMA
				 */
				#define DMA_PERIPH_INC_ENABLE        ((uint32_t)(DMA_CCR_PINC))  	/*!< Peripheral increment mode Enable */
				#define DMA_PERIPH_INC_DISABLE       (0x00000000U)    				/*!< Peripheral increment mode Disable */


				/**
				 * @brief Memory incremented mode DMA
				 */
				#define DMA_MEMORY_INC_ENABLE         ((uint32_t)(DMA_CCR_MINC))  	/*!< Memory increment mode Enable  */
				#define DMA_MEMORY_INC_DISABLE        (0x00000000U)    				/*!< Memory increment mode Disable */


				/**
				 * @brief DMA Peripheral data size
				 */
				#define DMA_PERIPH_DATAALIGN_BYTE          (0x00000000U)       				/*!< Peripheral data alignment : Byte     */
				#define DMA_PERIPH_DATAALIGN_HALFWORD      ((uint32_t)(DMA_CCR_PSIZE_0))  	/*!< Peripheral data alignment : HalfWord */
				#define DMA_PERIPH_DATAALIGN_WORD          ((uint32_t)(DMA_CCR_PSIZE_1))  	/*!< Peripheral data alignment : Word     */


				/**
				 * @brief DMA Memory data size
				 */
				#define DMA_MEMORY_DATAALIGN_BYTE          (0x00000000U)       				/*!< Memory data alignment : Byte     */
				#define DMA_MEMORY_DATAALIGN_HALFWORD      ((uint32_t)(DMA_CCR_MSIZE_0))  	/*!< Memory data alignment : HalfWord */
				#define DMA_MEMORY_DATAALIGN_WORD          ((uint32_t)(DMA_CCR_MSIZE_1))  	/*!< Memory data alignment : Word     */


				/**
				 * @brief DMA Mode
				 */
				#define DMA_MODE_NORMAL         			(0x00000000U)      				/*!< Normal Mode */
				#define DMA_MODE_CIRCULAR       			((uint32_t)(DMA_CCR_CIRC))    	/*!< Circular Mode */


				/**
				 * @brief DMA Priority
				 */
				#define DMA_PRIORITY_LOW             (0x00000000U)    						/*!< Priority level : Low       */
				#define DMA_PRIORITY_MEDIUM          ((uint32_t)DMA_CCR_PL_0)  				/*!< Priority level : Medium    */
				#define DMA_PRIORITY_HIGH            ((uint32_t)DMA_CCR_PL_1)  				/*!< Priority level : High      */
				#define DMA_PRIORITY_VERY_HIGH       ((uint32_t)DMA_CCR_PL)    				/*!< Priority level : Very_High */
			/**
			 * @} MY_DMA_Defines
			 */


			/**
			 * @defgroup MY_DMA_Macros
			 * @brief    Библиотечные макросы
			 * @{
			 */

			/**
			 * @}  MY_DMA_Macros
			 */


			/**
			 * @defgroup MY_DMA_Typedefs
			 * @brief    Typedefs для библиотеки
			 * @{
			 */
				/**
				 * @brief  DMA State
				 */
				typedef enum
				{
					MY_DMA_State_Reset             = 0x00U,  	/*!< DMA не инициализирован или отключен */
					MY_DMA_State_Ready             = 0x01U,  	/*!< DMA инициализирован и готов к использованию */
					MY_DMA_State_Busy              = 0x02U,  	/*!< DMA занят каким-либо процессом */
					MY_DMA_State_Timeout           = 0x03U   	/*!< DMA попал в таймаут */
				}
				MY_DMA_State_t;


				/**
				  * @brief  DMA Error Code
				  */
				typedef enum
				{
					MY_DMA_Full_Transfer      = 0x00U,    		/*!< Full transfer */
					MY_DMA_Half_Transfer      = 0x01U     		/*!< Half Transfer */
				}
				MY_DMA_LevelComplete_t;


				/**
				  * @brief  DMA Configuration
				  */
				typedef struct
				{
				  uint32_t Direction;                 /*!< Указывает, будут ли данные передаваться из памяти в периферийное устройство,
				   	   	   	   	   	   	   	   	   	   	   из памяти в память или из периферийного устройства в память.
														   Этот параметр определяется в константах @ref Направление передачи данных через DMA */

				  uint32_t PeriphInc;                 /*!< Указывает, нужно ли увеличивать Peripheral address register.
														   Этот параметр определяется в константах @ref Peripheral incremented mode DMA */

				  uint32_t MemInc;                    /*!< Указывает, нужно ли увеличивать адрес памяти при передаче.
														   Этот параметр определяется в константах @ref Memory incremented mode DMA */

				  uint32_t PeriphDataAlignment;       /*!< Определяет размер данных периферии.
														   Этот параметр определяется в константах @ref DMA Peripheral data size */

				  uint32_t MemDataAlignment;          /*!< Определяет размер данных памяти.
														   Этот параметр определяется в константах @ref DMA Memory data size */

				  uint32_t Mode;                      /*!< Определяет режим работы на канале DMA.
														   Этот параметр определяется в константах @ref DMA mode
														   @note Циклический буферне может быть использован в режиме memory-to-memory */

				  uint32_t Priority;                   /*!< Определяет программный приоритет для канала DMA.
															Этот параметр определяется в константах @ref DMA Priority level */
				}
				MY_DMA_Init_t;
			/**
			 * @} MY_DMA_Typedefs
			 */


			/**
			 * @defgroup MY_DMA_Functions
			 * @brief    Функции используемые в библиотеке
			 * @{
			 */



			/**
			 * @} MY_DMA_Functions
			 */

		/**
		 * @} MY_DMA
		 */

	/**
	 * @} MY_STM32F0xx_Libraries
	 */

	/* C++ detection */
	#ifdef __cplusplus
		}
	#endif

#endif
