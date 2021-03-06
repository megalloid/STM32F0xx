/**
 * @author  Andrey Zaostrovnykh
 * @email   megalloid@mail.ru
 * @website http://smarthouseautomatics.ru/stm32/stm32f0xx/i2c
 * @version v0.1
 * @ide     STM32CubeIDE
 * @brief   Основной файл программы
 */

#include "my_stm32f0xx.h"
#include "my_stm32f0xx_gpio.h"
#include "my_stm32f0xx_delay.h"

int main(void)
{
	MY_GPIO_Init_t GPIO_Leds;
	GPIO_Leds.Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Leds.Mode = MY_GPIO_Mode_Out;
	GPIO_Leds.Pull = MY_GPIO_PuPd_NoPull;
	GPIO_Leds.Speed = MY_GPIO_Speed_High;

	MY_GPIO_StructInit(GPIOC, &GPIO_Leds);

	while(1)
	{
		/* Зажигаем светодиод PC8, гасим PC9 */
		MY_GPIO_SetPinHigh(GPIOC, GPIO_Pin_9);
		MY_Delay_ms(100);

		/* Зажигаем светодиод PC9, гасим PC8 */
		MY_GPIO_SetPinLow(GPIOC, GPIO_Pin_9);
		MY_Delay_ms(100);
	}
}
