/**
 * @author  Andrey Zaostrovnykh
 * @email   megalloid@mail.ru
 * @website http://smarthouseautomatics.ru/stm32/stm32f0xx/i2c
 * @version v0.1
 * @ide     STM32CubeIDE
 * @brief   Основной файл программы
 */
#include "my_stm32f0xx.h"
#include "my_stm32f0xx_disco.h"
#include "my_stm32f0xx_24c0x.h"


int main(void)
{
	MY_DISCO_LedInit();

	if(MY_24C0X_Init(I2C1, MY_I2C_PinsPack_1) == MY_Result_Ok)
	{

	}

	if(MY_24C0X_WriteByte(I2C1, 0xAA, 0xBB) == MY_Result_Ok)
	{
		MY_DISCO_LedOn(DISCO_LED_BLUE);
	}

	if(MY_24C0X_ReadByte(I2C1, 0xAA) == 0xBB)
	{
		MY_DISCO_LedOn(DISCO_LED_GREEN);
	}

	while(1)
	{

	}
}


