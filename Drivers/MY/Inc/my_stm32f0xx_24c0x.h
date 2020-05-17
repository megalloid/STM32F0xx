/**
 * @author  Андрей Заостровных
 * @email   megalloid@mail.ru
 * @website http://smarthouseautomatics.ru
 * @link    http://smarthouseautomatics.ru/stm32/stm32f0xx/24C0X/
 * @version v0.1
 * @ide     STM32CubeIDE
 * @brief   Библиотека для работы с EEPROM серии 24C01/24C02 в STM32F0xx
 */

#ifndef MY_24C0X_H
	#define MY_24C0X_H

	/* C++ detection */
	#ifdef __cplusplus
		extern "C" {
	#endif

	/**
	 * @addtogroup MY_STM32Fxxx_HAL_Libraries
	 * @{
	 */

		/**
		 * @defgroup MY_24С0X_H
		 * @brief    Библиотека для работы с EEPROM серии 24C01/24C02 в STM32F0xx
		 * @{
		 */

			#include "main.h"
			#include "my_stm32f0xx.h"
			#include "my_stm32f0xx_delay.h"
			#include "my_stm32f0xx_i2c.h"

			/**
			 * @defgroup MY_24С0X_Settings
			 * @brief    Библиотечные настройки
			 * @{
			 */
				/* Настройки I2C */
				#define EEPROM_24C0X_ADDRESSINGMODE  	I2C_ADDRESSINGMODE_7BIT
				#define EEPROM_24C0X_ANALOGFILTER  		I2C_ANALOGFILTER_ENABLE
				#define EEPROM_24C0X_CLOCKSPEED  		100000
				#define EEPROM_24C0X_DIGITALFILTER  	0U
				#define EEPROM_24C0X_DUALADDRESSMODE  	I2C_DUALADDRESS_DISABLE
				#define EEPROM_24C0X_GENERALCALLMODE  	I2C_GENERALCALL_DISABLE
				#define EEPROM_24C0X_NOSTRETCHMODE  	I2C_NOSTRETCH_ENABLE
				#define EEPROM_24C0X_OWNADDRESS1  		0U
				#define EEPROM_24C0X_OWNADDRESS2  		0U
				#define EEPROM_24C0X_TYPEACKNOLEGE  	I2C_NACK
				#define EEPROM_24C0X_DEFAULTSTATE  		MY_I2C_State_Reset

			/**
			 * @} MY_24С0X_Settings
			 */


			/**
			 * @defgroup MY_24С0X_Defines
			 * @brief    Библиотечные константы
			 * @{
			 */

				#define EEPROM_24C0X_ADDR				0x50<<1							/*!< Адрес EEPROM на шине I2C (при условии E0-E2 пины в 0)
																						 Смещение задано т.к. первый бит задаёт чтение или запись */
				#define EEPROM_24C0X_TRIALS				0x3U
				#define EEPROM_24C0X_TIMEOUT			0x100U
				#define EEPROM_24C0X_PAGE_SIZE         	8U								/*!< Размер страницы в памяти EEPROM */
				#define EEPROM_24C0X_BUFFER_LENGTH		32U								/*!< Размер буфера */
				#define EEPROM_24C0X_RD_BUFFER_SIZE    	EEPROM_BUFFER_LENGTH			/*!< Размер буфера I2C на чтение */
				#define EEPROM_24C0X_WR_BUFFER_SIZE    	(EEPROM_BUFFER_LENGTH - 1)		/*!< Размер буфера I2C на запись */

			/**
			 * @}
			 */


			/**
			 * @defgroup MY_24С0X_Typedefs
			 * @brief    Typedefs используемые в библиотеке
			 * @{
			 */

			/**
			 * @} MY_24С0X_Typedefs
			 */


			/**
			 * @defgroup MY_24С0X_Functions
			 * @brief    Библиотечные функции
			 * @{
			 */

				/**
				 * @brief  Инициализация периферии I2C и проверка, подключен ли EEPROM к шине
				 * @param  I2Cx - указатель на структуру I2C
				 * @param  pinspack - набор пинов к которым подключен EEPROM к шине
				 * @retval MY_Result_t
				 */
				MY_Result_t MY_24C0X_Init(I2C_TypeDef* I2Cx, MY_I2C_PinsPack_t pinspack);


				/**
				 * @brief  Записывает один байт по указанному адресу ячейки памяти
				 * @param  I2Cx - указатель на структуру I2C
				 * @param  address_byte - адрес ячейки
				 * @param  data - байт для записи
				 * @retval MY_Result_t
				 */
				MY_Result_t MY_24C0X_WriteByte(I2C_TypeDef* I2Cx, uint8_t address_byte, uint8_t data);


				/**
				 * @brief  Читает один байт по указанному адресу ячейки памяти
				 * @param  I2Cx - указатель на структуру I2C
				 * @param  address_byte - адрес ячейки
				 * @retval Значение ячейки памяти
				 */
				uint8_t MY_24C0X_ReadByte(I2C_TypeDef* I2Cx, uint8_t address_byte);


			/**
			 * @} MY_24С0X_Functions
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
