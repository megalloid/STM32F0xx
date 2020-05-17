/**
 * @author  Андрей Заостровных
 * @email   megalloid@mail.ru
 * @website http://smarthouseautomatics.ru
 * @link    http://smarthouseautomatics.ru/stm32/stm32f0xx/24C0X/
 * @version v0.1
 * @ide     STM32CubeIDE
 * @brief   Библиотека для работы с EEPROM серии 24C01/24C02 в STM32F0xx
 */

#include "my_stm32f0xx_delay.h"
#include "my_stm32f0xx_i2c.h"
#include "my_stm32f0xx_24c0x.h"



MY_Result_t MY_24C0X_Init(I2C_TypeDef* I2Cx, MY_I2C_PinsPack_t pinspack)
{
	/* Получаем указатель на структуру связанную с I2Cx*/
	MY_I2C_Init_t* EEPROM_I2C_Init = MY_I2C_GetHandler(I2Cx);

	/* Заполняем ее настройками*/
	EEPROM_I2C_Init->Instance = I2Cx;
	EEPROM_I2C_Init->AddressingMode = EEPROM_24C0X_ADDRESSINGMODE;
	EEPROM_I2C_Init->AnalogFilter = EEPROM_24C0X_ANALOGFILTER;
	EEPROM_I2C_Init->ClockSpeed = EEPROM_24C0X_CLOCKSPEED;
	EEPROM_I2C_Init->DigitalFilter = EEPROM_24C0X_DIGITALFILTER;
	EEPROM_I2C_Init->DualAddressMode = EEPROM_24C0X_DUALADDRESSMODE;
	EEPROM_I2C_Init->GeneralCallMode = EEPROM_24C0X_GENERALCALLMODE;
	EEPROM_I2C_Init->NoStretchMode = EEPROM_24C0X_NOSTRETCHMODE;
	EEPROM_I2C_Init->OwnAddress1 = EEPROM_24C0X_OWNADDRESS1;
	EEPROM_I2C_Init->OwnAddress2 = EEPROM_24C0X_OWNADDRESS2;
	EEPROM_I2C_Init->TypeAcknowledge = EEPROM_24C0X_TYPEACKNOLEGE;
	EEPROM_I2C_Init->Pinspack = pinspack;
	EEPROM_I2C_Init->State = MY_I2C_State_Reset;
	EEPROM_I2C_Init->Lock = MY_Lock_Off;

	/* Пробуем инициализировать */
	if(MY_I2C_Init(I2Cx) == MY_Result_Ok)
	{
		/* Проверяем, есть ли устройство на шине I2C */
		if(MY_I2C_IsDeviceReady(I2Cx, EEPROM_24C0X_ADDR, EEPROM_24C0X_TRIALS, EEPROM_24C0X_TIMEOUT) == MY_Result_Ok)
		{
			return MY_Result_Ok;
		}
		else
		{
			return MY_Result_Error;
		}
	}
	else
	{
		return MY_Result_Error;
	}
}


MY_Result_t MY_24C0X_WriteByte(I2C_TypeDef* I2Cx, uint8_t address_byte, uint8_t data)
{
	if(MY_I2C_WriteByte(I2Cx, EEPROM_24C0X_ADDR, address_byte, data) == MY_Result_Ok)
	{
		MY_Delay_ms(2);

		return MY_Result_Ok;
	}

	return MY_Result_Error;
}


uint8_t MY_24C0X_ReadByte(I2C_TypeDef* I2Cx, uint8_t address_byte)
{
	uint8_t tmp;

	MY_I2C_ReadByte(I2Cx, EEPROM_24C0X_ADDR, address_byte, &tmp);

	return tmp;
}
