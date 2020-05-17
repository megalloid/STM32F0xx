/**
 * @author  Andrey Zaostrovnykh
 * @email   megalloid@mail.ru
 * @website http://smarthouseautomatics.ru/stm32/stm32f0xx/delays
 * @version v0.1
 * @ide     STM32CubeIDE
 * @brief   Утилиты для работы с временными задержками
 */
#include "my_stm32f0xx_cortex.h"
#include "my_stm32f0xx_delay.h"

void MY_Delay_ms(__IO uint32_t delay_ms)
{
	uint32_t tickstart = MY_SysTick_GetTick();
	uint32_t wait = delay_ms;

	/* Добавим период для гарантии отсчёта одного периода
	if (wait < MAX_DELAY)
	{
		 wait++;
	}*/

	while((MY_SysTick_GetTick() - tickstart) < wait) { }
}
