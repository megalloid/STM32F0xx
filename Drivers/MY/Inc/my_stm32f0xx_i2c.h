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
		 *
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

    	(#) Initialize the I2C registers by calling the HAL_I2C_Init(), configures also the low level Hardware
        	(GPIO, CLOCK, NVIC...etc) by calling the customized HAL_I2C_MspInit(&hi2c) API.

    	(#) To check if target device is ready for communication, use the function HAL_I2C_IsDeviceReady()

    	(#) For I2C IO and IO MEM operations, three operation modes are available within this driver :

		==============================================================================
		 	 	 	 	 	 	 *** Polling mode IO operation ***
   	   	==============================================================================

      	(+) Transmit in master mode an amount of data in blocking mode using HAL_I2C_Master_Transmit()

      	(+) Receive in master mode an amount of data in blocking mode using HAL_I2C_Master_Receive()

      	(+) Transmit in slave mode an amount of data in blocking mode using HAL_I2C_Slave_Transmit()

      	(+) Receive in slave mode an amount of data in blocking mode using HAL_I2C_Slave_Receive()

		==============================================================================
		 	 	 	 	 	 	 Polling mode IO MEM operation ***
		==============================================================================

        (+) Write an amount of data in blocking mode to a specific memory address using HAL_I2C_Mem_Write()

      	(+) Read an amount of data in blocking mode from a specific memory address using HAL_I2C_Mem_Read()

		==============================================================================
		 	 	 	 	 	 	 Interrupt mode IO operation ***
		==============================================================================

      	(+) Transmit in master mode an amount of data in non-blocking mode using HAL_I2C_Master_Transmit_IT()

        (+) At transmission end of transfer, HAL_I2C_MasterTxCpltCallback() is executed and user can
            add his own code by customization of function pointer HAL_I2C_MasterTxCpltCallback()

        (+) Receive in master mode an amount of data in non-blocking mode using HAL_I2C_Master_Receive_IT()

      	(+) At reception end of transfer, HAL_I2C_MasterRxCpltCallback() is executed and user can
            add his own code by customization of function pointer HAL_I2C_MasterRxCpltCallback()

      	(+) Transmit in slave mode an amount of data in non-blocking mode using HAL_I2C_Slave_Transmit_IT()
      	(+) At transmission end of transfer, HAL_I2C_SlaveTxCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_SlaveTxCpltCallback()
      	(+) Receive in slave mode an amount of data in non-blocking mode using HAL_I2C_Slave_Receive_IT()
      	(+) At reception end of transfer, HAL_I2C_SlaveRxCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_SlaveRxCpltCallback()
      	(+) In case of transfer Error, HAL_I2C_ErrorCallback() function is executed and user can
           add his own code by customization of function pointer HAL_I2C_ErrorCallback()
      	(+) Abort a master I2C process communication with Interrupt using HAL_I2C_Master_Abort_IT()
      	(+) End of abort process, HAL_I2C_AbortCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_AbortCpltCallback()
      	(+) Discard a slave I2C process communication using __HAL_I2C_GENERATE_NACK() macro.
           This action will inform Master to generate a Stop condition to discard the communication.

		==============================================================================
		 	 	 	 	 *** Interrupt mode IO sequential operation ***
		==============================================================================

      	(@) These interfaces allow to manage a sequential transfer with a repeated start condition
          when a direction change during transfer

      	(+) A specific option field manage the different steps of a sequential transfer
      	(+) Option field values are defined through @ref I2C_XFEROPTIONS and are listed below:
      	(++) I2C_FIRST_AND_LAST_FRAME: No sequential usage, functionnal is same as associated interfaces in no sequential mode
      	(++) I2C_FIRST_FRAME: Sequential usage, this option allow to manage a sequence with start condition, address
                            and data to transfer without a final stop condition
      	(++) I2C_FIRST_AND_NEXT_FRAME: Sequential usage (Master only), this option allow to manage a sequence with start condition, address
                            and data to transfer without a final stop condition, an then permit a call the same master sequential interface
                            several times (like HAL_I2C_Master_Sequential_Transmit_IT() then HAL_I2C_Master_Sequential_Transmit_IT())
      	(++) I2C_NEXT_FRAME: Sequential usage, this option allow to manage a sequence with a restart condition, address
                            and with new data to transfer if the direction change or manage only the new data to transfer
                            if no direction change and without a final stop condition in both cases
      	(++) I2C_LAST_FRAME: Sequential usage, this option allow to manage a sequance with a restart condition, address
                            and with new data to transfer if the direction change or manage only the new data to transfer
                            if no direction change and with a final stop condition in both cases

      	(+) Differents sequential I2C interfaces are listed below:
      	(++) Sequential transmit in master I2C mode an amount of data in non-blocking mode using HAL_I2C_Master_Sequential_Transmit_IT()
      	(+++) At transmission end of current frame transfer, HAL_I2C_MasterTxCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_MasterTxCpltCallback()
      	(++) Sequential receive in master I2C mode an amount of data in non-blocking mode using HAL_I2C_Master_Sequential_Receive_IT()
      	(+++) At reception end of current frame transfer, HAL_I2C_MasterRxCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_MasterRxCpltCallback()
      	(++) Abort a master I2C process communication with Interrupt using HAL_I2C_Master_Abort_IT()
      	(+++) End of abort process, HAL_I2C_AbortCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_AbortCpltCallback()
      	(++) Enable/disable the Address listen mode in slave I2C mode using HAL_I2C_EnableListen_IT() HAL_I2C_DisableListen_IT()
      	(+++) When address slave I2C match, HAL_I2C_AddrCallback() is executed and user can
           add his own code to check the Address Match Code and the transmission direction request by master (Write/Read).
      	(+++) At Listen mode end HAL_I2C_ListenCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_ListenCpltCallback()
      	(++) Sequential transmit in slave I2C mode an amount of data in non-blocking mode using HAL_I2C_Slave_Sequential_Transmit_IT()
      	(+++) At transmission end of current frame transfer, HAL_I2C_SlaveTxCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_SlaveTxCpltCallback()
      	(++) Sequential receive in slave I2C mode an amount of data in non-blocking mode using HAL_I2C_Slave_Sequential_Receive_IT()
      	(+++) At reception end of current frame transfer, HAL_I2C_SlaveRxCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_SlaveRxCpltCallback()
      	(++) In case of transfer Error, HAL_I2C_ErrorCallback() function is executed and user can
           add his own code by customization of function pointer HAL_I2C_ErrorCallback()
      	(++) Abort a master I2C process communication with Interrupt using HAL_I2C_Master_Abort_IT()
      	(++) End of abort process, HAL_I2C_AbortCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_AbortCpltCallback()
      	(++) Discard a slave I2C process communication using __HAL_I2C_GENERATE_NACK() macro.
           This action will inform Master to generate a Stop condition to discard the communication.

		==============================================================================
		 	 	 	 	 	 *** Interrupt mode IO MEM operation ***
		==============================================================================

      	(+) Write an amount of data in non-blocking mode with Interrupt to a specific memory address using
          HAL_I2C_Mem_Write_IT()
      	(+) At Memory end of write transfer, HAL_I2C_MemTxCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_MemTxCpltCallback()
      	(+) Read an amount of data in non-blocking mode with Interrupt from a specific memory address using
          HAL_I2C_Mem_Read_IT()
      	(+) At Memory end of read transfer, HAL_I2C_MemRxCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_MemRxCpltCallback()
      	(+) In case of transfer Error, HAL_I2C_ErrorCallback() function is executed and user can
           add his own code by customization of function pointer HAL_I2C_ErrorCallback()

		==============================================================================
		 	 	 	 	 	 *** DMA mode IO operation ***
		==============================================================================

      	(+) Transmit in master mode an amount of data in non-blocking mode (DMA) using
          HAL_I2C_Master_Transmit_DMA()
      	(+) At transmission end of transfer, HAL_I2C_MasterTxCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_MasterTxCpltCallback()
      	(+) Receive in master mode an amount of data in non-blocking mode (DMA) using
          HAL_I2C_Master_Receive_DMA()
      	(+) At reception end of transfer, HAL_I2C_MasterRxCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_MasterRxCpltCallback()
      	(+) Transmit in slave mode an amount of data in non-blocking mode (DMA) using
          HAL_I2C_Slave_Transmit_DMA()
      	(+) At transmission end of transfer, HAL_I2C_SlaveTxCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_SlaveTxCpltCallback()
      	(+) Receive in slave mode an amount of data in non-blocking mode (DMA) using
          HAL_I2C_Slave_Receive_DMA()
      	(+) At reception end of transfer, HAL_I2C_SlaveRxCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_SlaveRxCpltCallback()
      	(+) In case of transfer Error, HAL_I2C_ErrorCallback() function is executed and user can
           add his own code by customization of function pointer HAL_I2C_ErrorCallback()
      	(+) Abort a master I2C process communication with Interrupt using HAL_I2C_Master_Abort_IT()
      	(+) End of abort process, HAL_I2C_AbortCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_AbortCpltCallback()
      	(+) Discard a slave I2C process communication using __HAL_I2C_GENERATE_NACK() macro.
           This action will inform Master to generate a Stop condition to discard the communication.

		==============================================================================
		 	 	 	 	 	 *** DMA mode IO MEM operation ***
		==============================================================================

      	(+) Write an amount of data in non-blocking mode with DMA to a specific memory address using
          HAL_I2C_Mem_Write_DMA()
      	(+) At Memory end of write transfer, HAL_I2C_MemTxCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_MemTxCpltCallback()
      	(+) Read an amount of data in non-blocking mode with DMA from a specific memory address using
          HAL_I2C_Mem_Read_DMA()
      	(+) At Memory end of read transfer, HAL_I2C_MemRxCpltCallback() is executed and user can
           add his own code by customization of function pointer HAL_I2C_MemRxCpltCallback()
      	(+) In case of transfer Error, HAL_I2C_ErrorCallback() function is executed and user can
           add his own code by customization of function pointer HAL_I2C_ErrorCallback()

		==============================================================================
		 	 	 	 	 	 *** I2C HAL driver macros list ***
		==============================================================================

		Below the list of most used macros in I2C HAL driver.

		(+) __HAL_I2C_ENABLE: Enable the I2C peripheral
		(+) __HAL_I2C_DISABLE: Disable the I2C peripheral
		(+) __HAL_I2C_GENERATE_NACK: Generate a Non-Acknowledge I2C peripheral in Slave mode
		(+) __HAL_I2C_GET_FLAG: Check whether the specified I2C flag is set or not
		(+) __HAL_I2C_CLEAR_FLAG: Clear the specified I2C pending flag
		(+) __HAL_I2C_ENABLE_IT: Enable the specified I2C interrupt
		(+) __HAL_I2C_DISABLE_IT: Disable the specified I2C interrupt


		(@) You can refer to the I2C HAL driver header file for more useful macros

		 *	@{
		 */

			/* Подключаем основные файлы библиотек и настройки проекта */
			#include "main.h"
			#include "my_stm32f0xx.h"

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
			 * @} MY_I2C_Defines
			 */


			/**
			 * @defgroup MY_I2C_Macros
			 * @brief    Библиотечные макросы
			 * @{
			 */

			/**
			 * @}  MY_I2C_Macros
			 */


			/**
			 * @defgroup MY_I2C_Typedefs
			 * @brief    Typedefs для библиотеки
			 * @{
			 */

			/**
			 * @} MY_I2C_Typedefs
			 */


			/**
			 * @defgroup MY_I2C_Functions
			 * @brief    Функции используемые в библиотеке
			 * @{
			 */



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
