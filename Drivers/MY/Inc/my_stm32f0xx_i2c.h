/**
 * @author  Andrey Zaostrovnykh
 * @email   megalloid@mail.ru
 * @website http://smarthouseautomatics.ru/stm32/stm32f0xx/i2c
 * @version v0.1
 * @ide     STM32CubeIDE
 * @brief   Утилиты для работы с I2C
 */

#ifndef MY_STM32F0xx_I2C_H
	#define MY_STM32F0xx_I2C_H 100

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
		 * @defgroup MY_I2C
		 * @pinout
		 *
			   @STM32F051x  |  PINSPACK 1 |   PINSPACK 2 |
			----------------------------------------------
			I2CX   			|  SCL   SDA  |   SCL   SDA  |
			----------------------------------------------
			I2C1   			|  PB6   PB7  |   PB8   PB9  |
			I2C2   			|  PB10  PB11 |   -     -    |

		 ==============================================================================
                        ##### Как использовать этот драйвер #####
  	  	 ==============================================================================

    	 Данный драйвер может использоваться следующими способами:

    	(#) Объявить структуру MY_I2C_Init_t, например:
        	MY_I2C_Init_t I2C_Struct;

    	(#) Инициализировать низкоуровневые ресурсы I2C используя MY_I2C_Init() или MY_I2C_StructInit():

        (##) Включите тактирование необходимого I2Cx
        (##) Конфигурируем I2C пины
            (+++) Включаем тактирование на пины GPIO которые использоваться для I2C
            (+++) Настраиваем пины I2C в качестве альтернативной функции в режиме open-drain

        (##) Настраиваем контроллер прерывания NVIC если передача будет по прерываниям
            (+++) Настройка приоритета прерывания для I2Cx
            (+++) Включаем NVIC I2C IRQ Channel

        (##) Настраиваем DMA если при обмене он будет использоваться:
            (+++) Объявляем новую структуру MY_DMA_Init_t для канала передачи или получения
            (+++) Включаем тактирование на интерфейс DMAx
            (+++) Настраиваем параметры DMA
            (+++) Настраиваем канал DMA на Tx или Rx
            (+++) Присваиваем инициализированный DMA handle к I2C_Struct DMA Tx или Rx
            (+++) Включаем прерывания и настраиваем приоритет в NVIC для получения статуса отправки
                  на канале DMA Tx или Rx

    	(#) Configure the Communication Clock Timing, Own Address1, Master Addressing mode, Dual Addressing mode,
        	Own Address2, Own Address2 Mask, General call and Nostretch mode in the hi2c Init structure.

    	(#) Initialize the I2C registers by calling the MY_I2C_Init(), configures also the low level Hardware
        	(GPIO, CLOCK, NVIC...etc) by calling the customized MY_I2C_MspInit(&hi2c) API.

    	(#) To check if target device is ready for communication, use the function MY_I2C_IsDeviceReady()

    	(#) For I2C IO and IO MEM operations, three operation modes are available within this driver :

		==============================================================================
		 	 	 	 	 	 	 *** Polling mode IO operation ***
   	   	==============================================================================

      	(+) Transmit in master mode an amount of data in blocking mode using MY_I2C_Master_Transmit()

      	(+) Receive in master mode an amount of data in blocking mode using MY_I2C_Master_Receive()

      	(+) Transmit in slave mode an amount of data in blocking mode using MY_I2C_Slave_Transmit()

      	(+) Receive in slave mode an amount of data in blocking mode using MY_I2C_Slave_Receive()

		==============================================================================
		 	 	 	 	 	 	 Polling mode IO MEM operation ***
		==============================================================================

        (+) Write an amount of data in blocking mode to a specific memory address using MY_I2C_Mem_Write()

      	(+) Read an amount of data in blocking mode from a specific memory address using MY_I2C_Mem_Read()

		==============================================================================
		 	 	 	 	 	 	 Interrupt mode IO operation ***
		==============================================================================

      	(+) Transmit in master mode an amount of data in non-blocking mode using MY_I2C_Master_Transmit_IT()

        (+) At transmission end of transfer, MY_I2C_MasterTxCpltCallback() is executed and user can
            add his own code by customization of function pointer MY_I2C_MasterTxCpltCallback()

        (+) Receive in master mode an amount of data in non-blocking mode using MY_I2C_Master_Receive_IT()

      	(+) At reception end of transfer, MY_I2C_MasterRxCpltCallback() is executed and user can
            add his own code by customization of function pointer MY_I2C_MasterRxCpltCallback()

      	(+) Transmit in slave mode an amount of data in non-blocking mode using MY_I2C_Slave_Transmit_IT()

      	(+) At transmission end of transfer, MY_I2C_SlaveTxCpltCallback() is executed and user can
            add his own code by customization of function pointer MY_I2C_SlaveTxCpltCallback()

      	(+) Receive in slave mode an amount of data in non-blocking mode using MY_I2C_Slave_Receive_IT()

      	(+) At reception end of transfer, MY_I2C_SlaveRxCpltCallback() is executed and user can
            add his own code by customization of function pointer MY_I2C_SlaveRxCpltCallback()

      	(+) In case of transfer Error, MY_I2C_ErrorCallback() function is executed and user can
            add his own code by customization of function pointer MY_I2C_ErrorCallback()

      	(+) Abort a master I2C process communication with Interrupt using MY_I2C_Master_Abort_IT()

      	(+) End of abort process, MY_I2C_AbortCpltCallback() is executed and user can
            add his own code by customization of function pointer MY_I2C_AbortCpltCallback()

      	(+) Discard a slave I2C process communication using __MY_I2C_GENERATE_NACK() macro.
            This action will inform Master to generate a Stop condition to discard the communication.

		==============================================================================
		 	 	 	 	 *** Interrupt mode IO sequential operation ***
		==============================================================================

      	(@) These interfaces allow to manage a sequential transfer with a repeated start condition
          	when a direction change during transfer

      	(+) A specific option field manage the different steps of a sequential transfer

      	(+) Option field values are defined through @ref I2C_XFEROPTIONS and are listed below:
      	 	 I2C_FIRST_AND_LAST_FRAME: No sequential usage, functionnal is same as associated interfaces in no sequential mode

      		 I2C_FIRST_FRAME: Sequential usage, this option allow to manage a sequence with start condition, address
                            and data to transfer without a final stop condition

      		 I2C_FIRST_AND_NEXT_FRAME: Sequential usage (Master only), this option allow to manage a sequence with start condition, address
                            and data to transfer without a final stop condition, an then permit a call the same master sequential interface
                            several times (like MY_I2C_Master_Sequential_Transmit_IT() then MY_I2C_Master_Sequential_Transmit_IT())

      	     I2C_NEXT_FRAME: Sequential usage, this option allow to manage a sequence with a restart condition, address
                            and with new data to transfer if the direction change or manage only the new data to transfer
                            if no direction change and without a final stop condition in both cases

      		 I2C_LAST_FRAME: Sequential usage, this option allow to manage a sequance with a restart condition, address
                            and with new data to transfer if the direction change or manage only the new data to transfer
                            if no direction change and with a final stop condition in both cases

      	(+) Differents sequential I2C interfaces are listed below:

      	(++) Sequential transmit in master I2C mode an amount of data in non-blocking mode using MY_I2C_Master_Sequential_Transmit_IT()
      	(+++) At transmission end of current frame transfer, MY_I2C_MasterTxCpltCallback() is executed and user can
           	  add his own code by customization of function pointer MY_I2C_MasterTxCpltCallback()

      	(++) Sequential receive in master I2C mode an amount of data in non-blocking mode using MY_I2C_Master_Sequential_Receive_IT()
      	(+++) At reception end of current frame transfer, MY_I2C_MasterRxCpltCallback() is executed and user can
           add his own code by customization of function pointer MY_I2C_MasterRxCpltCallback()

      	(++) Abort a master I2C process communication with Interrupt using MY_I2C_Master_Abort_IT()
      	(+++) End of abort process, MY_I2C_AbortCpltCallback() is executed and user can
              add his own code by customization of function pointer MY_I2C_AbortCpltCallback()

      	(++) Enable/disable the Address listen mode in slave I2C mode using MY_I2C_EnableListen_IT() MY_I2C_DisableListen_IT()
      	(+++) When address slave I2C match, MY_I2C_AddrCallback() is executed and user can
              add his own code to check the Address Match Code and the transmission direction request by master (Write/Read).
      	(+++) At Listen mode end MY_I2C_ListenCpltCallback() is executed and user can
              add his own code by customization of function pointer MY_I2C_ListenCpltCallback()

      	(++) Sequential transmit in slave I2C mode an amount of data in non-blocking mode using MY_I2C_Slave_Sequential_Transmit_IT()
      	(+++) At transmission end of current frame transfer, MY_I2C_SlaveTxCpltCallback() is executed and user can
              add his own code by customization of function pointer MY_I2C_SlaveTxCpltCallback()

      	(++) Sequential receive in slave I2C mode an amount of data in non-blocking mode using MY_I2C_Slave_Sequential_Receive_IT()
      	(+++) At reception end of current frame transfer, MY_I2C_SlaveRxCpltCallback() is executed and user can
              add his own code by customization of function pointer MY_I2C_SlaveRxCpltCallback()

      	(++) In case of transfer Error, MY_I2C_ErrorCallback() function is executed and user can
             add his own code by customization of function pointer MY_I2C_ErrorCallback()

      	(++) Abort a master I2C process communication with Interrupt using MY_I2C_Master_Abort_IT()

      	(++) End of abort process, MY_I2C_AbortCpltCallback() is executed and user can
             add his own code by customization of function pointer MY_I2C_AbortCpltCallback()

      	(++) Discard a slave I2C process communication using __MY_I2C_GENERATE_NACK() macro.
             This action will inform Master to generate a Stop condition to discard the communication.

		==============================================================================
		 	 	 	 	 	 *** Interrupt mode IO MEM operation ***
		==============================================================================

      	(+) Write an amount of data in non-blocking mode with Interrupt to a specific memory address using
          MY_I2C_Mem_Write_IT()

      	(+) At Memory end of write transfer, MY_I2C_MemTxCpltCallback() is executed and user can
           add his own code by customization of function pointer MY_I2C_MemTxCpltCallback()

      	(+) Read an amount of data in non-blocking mode with Interrupt from a specific memory address using
          MY_I2C_Mem_Read_IT()

      	(+) At Memory end of read transfer, MY_I2C_MemRxCpltCallback() is executed and user can
           add his own code by customization of function pointer MY_I2C_MemRxCpltCallback()

      	(+) In case of transfer Error, MY_I2C_ErrorCallback() function is executed and user can
           add his own code by customization of function pointer MY_I2C_ErrorCallback()

		==============================================================================
		 	 	 	 	 	 *** DMA mode IO operation ***
		==============================================================================

      	(+) Transmit in master mode an amount of data in non-blocking mode (DMA) using
          MY_I2C_Master_Transmit_DMA()

      	(+) At transmission end of transfer, MY_I2C_MasterTxCpltCallback() is executed and user can
            add his own code by customization of function pointer MY_I2C_MasterTxCpltCallback()

      	(+) Receive in master mode an amount of data in non-blocking mode (DMA) using
            MY_I2C_Master_Receive_DMA()

      	(+) At reception end of transfer, MY_I2C_MasterRxCpltCallback() is executed and user can
            add his own code by customization of function pointer MY_I2C_MasterRxCpltCallback()

      	(+) Transmit in slave mode an amount of data in non-blocking mode (DMA) using
            MY_I2C_Slave_Transmit_DMA()

      	(+) At transmission end of transfer, MY_I2C_SlaveTxCpltCallback() is executed and user can
            add his own code by customization of function pointer MY_I2C_SlaveTxCpltCallback()

      	(+) Receive in slave mode an amount of data in non-blocking mode (DMA) using
            MY_I2C_Slave_Receive_DMA()

      	(+) At reception end of transfer, MY_I2C_SlaveRxCpltCallback() is executed and user can
            add his own code by customization of function pointer MY_I2C_SlaveRxCpltCallback()

      	(+) In case of transfer Error, MY_I2C_ErrorCallback() function is executed and user can
            add his own code by customization of function pointer MY_I2C_ErrorCallback()

      	(+) Abort a master I2C process communication with Interrupt using MY_I2C_Master_Abort_IT()

      	(+) End of abort process, MY_I2C_AbortCpltCallback() is executed and user can
            add his own code by customization of function pointer MY_I2C_AbortCpltCallback()

      	(+) Discard a slave I2C process communication using __MY_I2C_GENERATE_NACK() macro.
            This action will inform Master to generate a Stop condition to discard the communication.

		==============================================================================
		 	 	 	 	 	 *** DMA mode IO MEM operation ***
		==============================================================================

      	(+) Write an amount of data in non-blocking mode with DMA to a specific memory address using MY_I2C_Mem_Write_DMA()

      	(+) At Memory end of write transfer, MY_I2C_MemTxCpltCallback() is executed and user can
            add his own code by customization of function pointer MY_I2C_MemTxCpltCallback()

      	(+) Read an amount of data in non-blocking mode with DMA from a specific memory address using MY_I2C_Mem_Read_DMA()

      	(+) At Memory end of read transfer, MY_I2C_MemRxCpltCallback() is executed and user can
             add his own code by customization of function pointer MY_I2C_MemRxCpltCallback()

      	(+) In case of transfer Error, MY_I2C_ErrorCallback() function is executed and user can
            add his own code by customization of function pointer MY_I2C_ErrorCallback()

		==============================================================================
		 	 	 	 	 	 *** I2C HAL driver macros list ***
		==============================================================================

		Below the list of most used macros in I2C HAL driver.

		(+) __MY_I2C_ENABLE: Enable the I2C peripheral
		(+) __MY_I2C_DISABLE: Disable the I2C peripheral
		(+) __MY_I2C_GENERATE_NACK: Generate a Non-Acknowledge I2C peripheral in Slave mode
		(+) __MY_I2C_GET_FLAG: Check whether the specified I2C flag is set or not
		(+) __MY_I2C_CLEAR_FLAG: Clear the specified I2C pending flag
		(+) __MY_I2C_ENABLE_IT: Enable the specified I2C interrupt
		(+) __MY_I2C_DISABLE_IT: Disable the specified I2C interrupt


		(@) You can refer to the I2C HAL driver header file for more useful macros

		 *	@{
		 */

			/* Подключаем основные файлы библиотек и настройки проекта */
			#include "main.h"
			#include "my_stm32f0xx.h"
			#include "my_stm32f0xx_gpio.h"

			/**
			 * @defgroup MY_I2C_Settings
			 * @brief    Библиотечные настройки
			 * @{
			 */

			/**
			 * @} MY_I2C_Settings
			 */


			/**
			 * @defgroup MY_I2C_Defines
			 * @brief    Библиотечные константы
			 * @{
			 */

				/**
				 * @brief  Битность адресации на I2C
				 */
				#define I2C_ADDRESSINGMODE_7BIT         (0x00000001U)
				#define I2C_ADDRESSINGMODE_10BIT        (0x00000002U)


				/**
				 * @brief  Двухадресный режим работы I2C (в режиме Slave)
				 */
				#define I2C_DUALADDRESS_DISABLE         (0x00000000U)
				#define I2C_DUALADDRESS_ENABLE          I2C_OAR2_OA2EN


				/**
				 * @brief  Маска для ACK используемая при двухадресном режиме работы I2C (в режиме Slave)
				 */
				#define I2C_OA2_NOMASK                  ((uint8_t)0x00U)
				#define I2C_OA2_MASK01                  ((uint8_t)0x01U)
				#define I2C_OA2_MASK02                  ((uint8_t)0x02U)
				#define I2C_OA2_MASK03                  ((uint8_t)0x03U)
				#define I2C_OA2_MASK04                  ((uint8_t)0x04U)
				#define I2C_OA2_MASK05                  ((uint8_t)0x05U)
				#define I2C_OA2_MASK06                  ((uint8_t)0x06U)
				#define I2C_OA2_MASK07                  ((uint8_t)0x07U)


				/**
				 * @brief  Отклик на широковещательный адрес (в режиме Slave)
				 */
				#define I2C_GENERALCALL_DISABLE         (0x00000000U)
				#define I2C_GENERALCALL_ENABLE          I2C_CR1_GCEN


				/**
				 * @brief  Режим отложенной передачи (в режиме Slave)
				 */
				#define I2C_NOSTRETCH_DISABLE           (0x00000000U)
				#define I2C_NOSTRETCH_ENABLE            I2C_CR1_NOSTRETCH


				/**
				 * @brief  Аналоговый фильтр
				 */
				#define I2C_ANALOGFILTER_ENABLE          (0x00000000U)
				#define I2C_ANALOGFILTER_DISABLE         I2C_CR1_ANFOFF


				/**
				 * @brief  Использование бита подтверждения ACK (для режима Slave)
				 */
				#define I2C_ACK                          0x00000000U
				#define I2C_NACK                         I2C_CR2_NACK


				/**
				 * @brief  I2C Reload End Mode
				 */
				#define  I2C_RELOAD_MODE                I2C_CR2_RELOAD
				#define  I2C_AUTOEND_MODE               I2C_CR2_AUTOEND
				#define  I2C_SOFTEND_MODE               (0x00000000U)


				/**
				 * @brief  I2C Start или Stop Mode
				 */
				#define  I2C_NO_STARTSTOP               (0x00000000U)
				#define  I2C_GENERATE_STOP              I2C_CR2_STOP
				#define  I2C_GENERATE_START_READ        (uint32_t)(I2C_CR2_START | I2C_CR2_RD_WRN)
				#define  I2C_GENERATE_START_WRITE       I2C_CR2_START


				/**
				 * @brief  Флаги I2C
				 */
				#define I2C_FLAG_TXE                    I2C_ISR_TXE				/*!< Transmit data register empty */
				#define I2C_FLAG_TXIS                   I2C_ISR_TXIS			/*!< Transmit interrupt status */
				#define I2C_FLAG_RXNE                   I2C_ISR_RXNE			/*!< Receive data register not empty */
				#define I2C_FLAG_ADDR                   I2C_ISR_ADDR			/*!< Address matched (slave mode) */
				#define I2C_FLAG_AF                     I2C_ISR_NACKF			/*!< Acknowledge failure received flag */
				#define I2C_FLAG_STOPF                  I2C_ISR_STOPF			/*!< STOP detection flag */
				#define I2C_FLAG_TC                     I2C_ISR_TC				/*!< Transfer complete (master mode) */
				#define I2C_FLAG_TCR                    I2C_ISR_TCR				/*!< Transfer complete reload */
				#define I2C_FLAG_BERR                   I2C_ISR_BERR			/*!< Bus error */
				#define I2C_FLAG_ARLO                   I2C_ISR_ARLO			/*!< Arbitration lost */
				#define I2C_FLAG_OVR                    I2C_ISR_OVR				/*!< Overrun/Underrun */
				#define I2C_FLAG_PECERR                 I2C_ISR_PECERR			/*!< PEC error in reception */
				#define I2C_FLAG_TIMEOUT                I2C_ISR_TIMEOUT			/*!< Timeout or Tlow detection flag */
				#define I2C_FLAG_ALERT                  I2C_ISR_ALERT			/*!< SMBus alert */
				#define I2C_FLAG_BUSY                   I2C_ISR_BUSY			/*!< Bus busy */
				#define I2C_FLAG_DIR                    I2C_ISR_DIR				/*!< Transfer direction (slave mode) */


				/**
				 * @brief  Таймауты I2C
				 */
				#define I2C_TIMEOUT_ADDR    			(10000U)       			/*!< 10 s  */
				#define I2C_TIMEOUT_BUSY    			(25U)          			/*!< 25 ms */
				#define I2C_TIMEOUT_DIR     			(25U)          			/*!< 25 ms */
				#define I2C_TIMEOUT_RXNE    			(25U)          			/*!< 25 ms */
				#define I2C_TIMEOUT_STOPF   			(25U)          			/*!< 25 ms */
				#define I2C_TIMEOUT_TC      			(25U)          			/*!< 25 ms */
				#define I2C_TIMEOUT_TCR     			(25U)         			/*!< 25 ms */
				#define I2C_TIMEOUT_TXIS    			(25U)         			/*!< 25 ms */
				#define I2C_TIMEOUT_FLAG    			(25U)         			/*!< 25 ms */


				/**
				 * @brief  Коды ошибок I2C
				 */
				#define I2C_ERROR_NONE      			(0x00000000U)    		/*!< No error              */
				#define I2C_ERROR_BERR      			(0x00000001U)    		/*!< BERR error            */
				#define I2C_ERROR_ARLO      			(0x00000002U)    		/*!< ARLO error            */
				#define I2C_ERROR_AF        			(0x00000004U)    		/*!< ACKF error            */
				#define I2C_ERROR_OVR       			(0x00000008U)    		/*!< OVR error             */
				#define I2C_ERROR_DMA       			(0x00000010U)   		/*!< DMA transfer error    */
				#define I2C_ERROR_TIMEOUT   			(0x00000020U)    		/*!< Timeout error         */
				#define I2C_ERROR_SIZE      			(0x00000040U)    		/*!< Size Management error */

			/**
			 * @} MY_I2C_Defines
			 */


			/**
			 * @defgroup MY_I2C_Macros
			 * @brief    Библиотечные макросы
			 * @{
			 */

				/** @brief  Включает периферию I2C через регистр CR1
				 * @param  	I2CX - определяет над каким I2C провести действие
				 * @retval 	Нет
				 */
				#define MY_I2C_ENABLE(I2CX)                            (SET_BIT((I2CX)->CR1,  I2C_CR1_PE))


				/** @brief  Выключает периферию I2C через регистр CR1
				 * @param   I2CX - определяет над каким I2C провести действие
				 * @retval  Нет
				 */
				#define MY_I2C_DISABLE(I2CX)                           (CLEAR_BIT((I2CX)->CR1, I2C_CR1_PE))


				/** @brief  Проверяет, установлен ли указанный флаг I2C или нет
				  * @param  I2CX - определяет над каким I2C провести действие
				  * @param  I2C_IT_FLAG - определяет какой флаг нужно проверить
				  * @retval SET или RESET
				  */
				#define MY_I2C_GET_FLAG(I2CX, I2C_IT_FLAG) 				((((I2CX->ISR) & (I2C_IT_FLAG)) == (I2C_IT_FLAG)) ? SET : RESET)


				/** @brief  Сбрасывает указанный флаг I2C
				 * @param   I2CX - определяет над каким I2C провести действие
				 * @param   I2C_IT_FLAG - определяет какой флаг нужно проверить
				 * @retval  Нет
				 */
				#define MY_I2C_CLEAR_FLAG(I2CX, I2C_IT_FLAG) 			(((I2C_IT_FLAG) == I2C_FLAG_TXE) ? \
																		((I2CX)->ISR |= (I2C_FLAG_TXE)) : \
		                                                                ((I2CX)->ICR = (I2C_IT_FLAG)))


				/** @brief  Генерирует START-последовательность при работе I2C
				 * @param   ADDRESSMODE - определяет над каким I2C провести действие
				 * @param   ADDRESS - адрес Slave-устройства
				 * @retval  Нет
				 */
				#define MY_I2C_GENERATE_START(ADDRESSMODE, ADDRESS)  	(((ADDRESSMODE) == I2C_ADDRESSINGMODE_7BIT) ? \
																			(uint32_t)((((uint32_t)(ADDRESS) & (I2C_CR2_SADD)) | (I2C_CR2_START) | (I2C_CR2_AUTOEND)) & (~I2C_CR2_RD_WRN)) : \
																			(uint32_t)((((uint32_t)(ADDRESS) & (I2C_CR2_SADD)) | (I2C_CR2_ADD10) | (I2C_CR2_START))   & (~I2C_CR2_RD_WRN)))


				/** @brief  Сбрасывает регистр CR2 в указанном I2Cх
				 * @param   I2CX - определяет над каким I2C провести действие
				 * @retval  Нет
				 */
				#define MY_I2C_RESET_CR2(I2CX)                 			((I2CX)->CR2 &= (uint32_t)~((uint32_t)(I2C_CR2_SADD | I2C_CR2_HEAD10R | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_RD_WRN)))


			/**
			 * @}  MY_I2C_Macros
			 */


			/**
			 * @defgroup MY_I2C_Typedefs
			 * @brief    Typedefs для библиотеки
			 * @{
			 */
				/**
				 * @brief  Набор пинов, который используется для I2C
				 */
				typedef enum
				{
					MY_I2C_PinsPack_1 = 0x00,
					MY_I2C_PinsPack_2,
					MY_I2C_PinsPack_3,
					MY_I2C_PinsPack_4,
					MY_I2C_PinsPack_Custom
				}
				MY_I2C_PinsPack_t;


				/**
				  * @brief  Режим работы I2C
				  * @note   Режим работы закодировано в следующей битовой последовательности:
				  *          b7      Не используется:
				  *            	x  : Должен быть равен 0
				  *          b6
				  *             0  : Нет
				  *             1  : Memory Mode
				  *          b5
				  *             0  : Нет
				  *             1  : Slave Mode
				  *          b4
				  *             0  : Нет
				  *             1  : Master Mode
				  *          b3-b2-b1-b0 Не используется
				  *             xxxx : Должен быть равен 0000
				  * @{
				  */
				typedef enum
				{
					MY_I2C_Mode_None  	= 0x00U,
					MY_I2C_Mode_Master  = 0x10U,
					MY_I2C_Mode_Slave   = 0x20U,
					MY_I2C_Mode_Memory  = 0x40U
				}
				MY_I2C_Mode_t;


				/**
				  * @brief  Структура для определения состояния I2C
				  * @note   Состояние I2C закодировано в следующей битовой последовательности:
				  *         b7-b6 - Информация об ошибках:
				  *             00 : No Error
				  *             01 : Abort (Abort user request on going)
				  *             10 : Timeout
				  *             11 : Error
				  *
				  *         b5 - Статус инициализации:
				  *             0  : Reset (IP not initialized)
				  *             1  : Init done (IP initialized and ready to use. HAL I2C Init function called)
				  *
				  *         b4 - Не используется:
				  *             x  : Should be set to 0
				  *
				  *         b3 - Текущий статус:
				  *             0  : Ready or Busy (No Listen mode ongoing)
				  *             1  : Listen (IP in Address Listen Mode)
				  *
				  *         b2 - Intrinsic process state:
				  *             0  : Ready
				  *             1  : Busy (IP busy with some configuration or internal operations)
				  *
				  *         b1 - Rx state:
				  *             0  : Ready (no Rx operation ongoing)
				  *             1  : Busy (Rx operation ongoing)
				  *
				  *         b0 - Tx state:
				  *             0  : Ready (no Tx operation ongoing)
				  *             1  : Busy (Tx operation ongoing)
				  * @{
				  */
				typedef enum
				{
				  MY_I2C_State_Reset             = 0x00U,   /*!< Peripheral is not yet Initialized         */
				  MY_I2C_State_Ready             = 0x20U,   /*!< Peripheral Initialized and ready for use  */
				  MY_I2C_State_Busy              = 0x24U,   /*!< An internal process is ongoing            */
				  MY_I2C_State_Busy_Tx           = 0x21U,   /*!< Data Transmission process is ongoing      */
				  MY_I2C_State_Busy_Rx           = 0x22U,   /*!< Data Reception process is ongoing         */
				  MY_I2C_State_Listen            = 0x28U,   /*!< Address Listen Mode is ongoing            */
				  MY_I2C_State_Busy_Tx_Listen    = 0x29U,   /*!< Address Listen Mode and Data Transmission process is ongoing  */
				  MY_I2C_State_Busy_Rx_Listen    = 0x2AU,   /*!< Address Listen Mode and Data Reception process is ongoing     */
				  MY_I2C_State_Abort             = 0x60U,   /*!< Abort user request ongoing                */
				  MY_I2C_State_Timeout           = 0xA0U,   /*!< Timeout state                             */
				  MY_I2C_State_Error             = 0xE0U    /*!< Error                                     */

				}
				MY_I2C_State_t;



				/**
				 * @brief Структура для конфигурирования I2C
				 */
				typedef struct
				{
					I2C_TypeDef        *Instance;      		/*!< Базовый регистр I2C */

					MY_I2C_PinsPack_t 	Pinspack;			/*!< I2C пины используемые для работы */

			   	    uint32_t 			ClockSpeed;			/*!< Частота работы I2C */

			   __IO MY_I2C_Mode_t  		Mode;           	/*!< Режим работы I2C */

			   	    uint32_t 			AnalogFilter;       /*!< Enables or disables analog noise filter.
			   	                                      	  	  	 This parameter can be a value of @ref I2C_LL_EC_ANALOGFILTER_SELECTION
			   	                                      	  	  	 This feature can be modified afterwards using unitary functions @ref LL_I2C_EnableAnalogFilter() or LL_I2C_DisableAnalogFilter(). */

			   	   uint32_t 			DigitalFilter;      /*!< Configures the digital noise filter.
			   	                                      	  	  	 This parameter can be a number between Min_Data = 0x00 and Max_Data = 0x0F
			   	                                      	  	  	 This feature can be modified afterwards using unitary function @ref LL_I2C_SetDigitalFilter(). */

				  	uint32_t 			OwnAddress1;        /*!< Specifies the first device own address.
				                                  	  	  	  	 This parameter can be a 7-bit or 10-bit address. */

				  	uint32_t 			AddressingMode;     /*!< Specifies if 7-bit or 10-bit addressing mode is selected.
				                                  	  	  	  	 This parameter can be a value of @ref I2C_ADDRESSING_MODE */

				  	uint32_t 			DualAddressMode;    /*!< Specifies if dual addressing mode is selected.
				                                  	  	  	  	 This parameter can be a value of @ref I2C_DUAL_ADDRESSING_MODE */

				  	uint32_t 			OwnAddress2;        /*!< Specifies the second device own address if dual addressing mode is selected
				                                  	  	  	  	 This parameter can be a 7-bit address. */

				  	uint32_t 			OwnAddress2Masks;   /*!< Specifies the acknowledge mask address second device own address if dual addressing mode is selected
				                                  	  	  	  	 This parameter can be a value of @ref I2C_OWN_ADDRESS2_MASKS */

				  	uint32_t 			GeneralCallMode;    /*!< Параметр определяет включен ли режим работы с широковещательными запросами.
				                                  	  	  	  	 This parameter can be a value of @ref I2C_GENERAL_CALL_ADDRESSING_MODE */

				  	uint32_t 			NoStretchMode;      /*!< Specifies if nostretch mode is selected.
				                                  	  	  	  	 This parameter can be a value of @ref I2C_NOSTRETCH_MODE */

				  	uint32_t 			TypeAcknowledge;    /*!< Specifies the ACKnowledge or Non ACKnowledge condition after the address receive match code or next received byte.
				  	                                     	 	 This parameter can be a value of @ref I2C_LL_EC_I2C_ACKNOWLEDGE
																 This feature can be modified afterwards using unitary function @ref LL_I2C_AcknowledgeNextData(). */

				  	uint8_t             *BufferPointer;     /*!< Pointer to I2C transfer buffer */

			   __IO uint16_t            TransferCount;      /*!< I2C transfer counter */

			   	   uint16_t             TransferSize;       /*!< I2C transfer size */

			   	   uint32_t				TransferISR;

				  	MY_Lock_t           Lock;           	/*!< Статус блокировки I2C */

			   __IO MY_I2C_State_t 		State;          	/*!< Статус передачи данных по I2C */

			   __IO uint32_t       		ErrorCode;      	/*!< I2C Error code */

			   __IO uint32_t       		PreviousState;  	/*!< I2C communication Previous state */

				}
				MY_I2C_Init_t;

			/**
			 * @} MY_I2C_Typedefs
			 */


			/**
			 * @defgroup MY_I2C_Functions
			 * @brief    Функции используемые в библиотеке
			 * @{
			 */
				/**
				 * @brief  Функция позволяет получить указатель на структуру I2C
				 * @param  *I2Cx: указатель на I2C
				 * @retval Указатель на структуру I2C
				 */
				MY_I2C_Init_t* MY_I2C_GetHandler(I2C_TypeDef* I2Cx);


				/**
				 * @brief  Функция для инициализации I2C
				 * @param  Указатель на структуру I2C
				 * @retval MY_Result_t
				 */
				MY_Result_t MY_I2C_Init(I2C_TypeDef* I2Cx);


				/**
				 * @brief  Функция проверят наличие устройства на шине I2C
				 * @param  I2Cx - указатель на структуру I2Cx
				 * @param  device_address - адрес устройства
				 * @param  trials - количество проходов, в которые проходит проверка
				 * @param  timeout - таймаут проверки наличия устройства на шине I2C
				 * @retval MY_Result_t
				 */
				MY_Result_t MY_I2C_IsDeviceReady(I2C_TypeDef* I2Cx, uint16_t device_address, uint32_t trials, uint32_t timeout);


				MY_Result_t MY_I2C_ReadByte(I2C_TypeDef* I2Cx, uint16_t device_address, uint8_t register_address, uint8_t* data);


				MY_Result_t MY_I2C_WriteByte(I2C_TypeDef* I2Cx, uint16_t device_address, uint8_t register_address, uint8_t data);


				/**
				  * @brief  Transmits in master mode an amount of data in blocking mode.
				  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
				  *                the configuration information for the specified I2C.
				  * @param  DevAddress Target device address: The device 7 bits address value
				  *         in datasheet must be shift at right before call interface
				  * @param  pData Pointer to data buffer
				  * @param  Size Amount of data to be sent
				  * @param  Timeout Timeout duration
				  * @retval HAL status
				  */
				MY_Result_t MY_I2C_Master_Transmit(MY_I2C_Init_t *I2C_Handler, uint16_t device_address, uint8_t *pData, uint16_t size, uint32_t timeout);

				/**
				  * @brief  Handles I2Cx communication when starting transfer or during transfer (TC or TCR flag are set).
				  * @param  hi2c I2C handle.
				  * @param  DevAddress Specifies the slave address to be programmed.
				  * @param  Size Specifies the number of bytes to be programmed.
				  *   This parameter must be a value between 0 and 255.
				  * @param  Mode New state of the I2C START condition generation.
				  *   This parameter can be one of the following values:
				  *     @arg @ref I2C_RELOAD_MODE Enable Reload mode .
				  *     @arg @ref I2C_AUTOEND_MODE Enable Automatic end mode.
				  *     @arg @ref I2C_SOFTEND_MODE Enable Software end mode.
				  * @param  Request New state of the I2C START condition generation.
				  *   This parameter can be one of the following values:
				  *     @arg @ref I2C_NO_STARTSTOP Don't Generate stop and start condition.
				  *     @arg @ref I2C_GENERATE_STOP Generate stop condition (Size should be set to 0).
				  *     @arg @ref I2C_GENERATE_START_READ Generate Restart for read request.
				  *     @arg @ref I2C_GENERATE_START_WRITE Generate Restart for write request.
				  * @retval None
				  */
				void MY_I2C_TransferConfig(MY_I2C_Init_t *I2C_Handler,  uint16_t DevAddress, uint8_t Size, uint32_t Mode, uint32_t Request);


				/**
				  * @brief  Receives in master mode an amount of data in blocking mode.
				  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
				  *                the configuration information for the specified I2C.
				  * @param  DevAddress Target device address: The device 7 bits address value
				  *         in datasheet must be shift at right before call interface
				  * @param  pData Pointer to data buffer
				  * @param  Size Amount of data to be sent
				  * @param  Timeout Timeout duration
				  * @retval HAL status
				  */
				MY_Result_t MY_I2C_Master_Receive(MY_I2C_Init_t *I2C_Handler, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);


				MY_Result_t MY_I2C_WaitOnFlagUntilTimeout(MY_I2C_Init_t *I2C_Handler, uint32_t Flag, FlagStatus Status, uint32_t Timeout, uint32_t Tickstart);

				/**
				  * @brief  This function handles I2C Communication Timeout for specific usage of TXIS flag.
				  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
				  *                the configuration information for the specified I2C.
				  * @param  Timeout Timeout duration
				  * @param  Tickstart Tick start value
				  * @retval HAL status
				  */
				MY_Result_t MY_I2C_WaitOnTXISFlagUntilTimeout(MY_I2C_Init_t *I2C_Handler, uint32_t Timeout, uint32_t Tickstart);


				/**
				  * @brief  This function handles Acknowledge failed detection during an I2C Communication.
				  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
				  *                the configuration information for the specified I2C.
				  * @param  Timeout Timeout duration
				  * @param  Tickstart Tick start value
				  * @retval HAL status
				  */
				MY_Result_t MY_I2C_IsAcknowledgeFailed(MY_I2C_Init_t *I2C_Handler, uint32_t Timeout, uint32_t Tickstart);


				/**
				  * @brief  This function handles I2C Communication Timeout for specific usage of STOP flag.
				  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
				  *                the configuration information for the specified I2C.
				  * @param  Timeout Timeout duration
				  * @param  Tickstart Tick start value
				  * @retval HAL status
				  */
				MY_Result_t MY_I2C_WaitOnSTOPFlagUntilTimeout(MY_I2C_Init_t *I2C_Handler, uint32_t Timeout, uint32_t Tickstart);


				void MY_I2C_Flush_TXDR(MY_I2C_Init_t *I2C_Handler);

				/**
				  * @brief  This function handles I2C Communication Timeout for specific usage of RXNE flag.
				  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
				  *                the configuration information for the specified I2C.
				  * @param  Timeout Timeout duration
				  * @param  Tickstart Tick start value
				  * @retval HAL status
				  */
				MY_Result_t MY_I2C_WaitOnRXNEFlagUntilTimeout(MY_I2C_Init_t *I2C_Handler, uint32_t Timeout, uint32_t Tickstart);

				/**
				  * @brief  Configure Noise Filters (Analog and Digital).
				  * @note   If the analog filter is also enabled, the digital filter is added to analog filter.
				  *         The filters can only be programmed when the I2C is disabled (PE = 0).
				  * @rmtoll CR1          ANFOFF        LL_I2C_ConfigFilters\n
				  *         CR1          DNF           LL_I2C_ConfigFilters
				  * @param  I2Cx I2C Instance.
				  * @param  AnalogFilter This parameter can be one of the following values:
				  *         @arg @ref LL_I2C_ANALOGFILTER_ENABLE
				  *         @arg @ref LL_I2C_ANALOGFILTER_DISABLE
				  * @param  DigitalFilter This parameter must be a value between Min_Data=0x00 (Digital filter disabled) and Max_Data=0x0F (Digital filter enabled and filtering capability up to 15*ti2cclk).
				  *         This parameter is used to configure the digital noise filter on SDA and SCL input.
				  *         The digital filter will filter spikes with a length of up to DNF[3:0]*ti2cclk.
				  * @retval None
				  */
				void MY_I2C_ConfigFilters(I2C_TypeDef *I2Cx, uint32_t AnalogFilter, uint32_t DigitalFilter);

				void MY_I2C_AcknowledgeNextData(I2C_TypeDef *I2Cx, uint32_t TypeAcknowledge);

				/**
				* @brief  Return the I2C error code.
				  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
				  *              the configuration information for the specified I2C.
				* @retval I2C Error Code
				*/
				uint32_t MY_I2C_GetError(MY_I2C_Init_t *I2C_Handler);
			/**
			 * @} MY_I2C_Functions
			 */

		/**
		 * @} MY_I2C
		 */

	/**
	 * @} MY_STM32F0xx_Libraries
	 */

	/* C++ detection */
	#ifdef __cplusplus
		}
	#endif

#endif
