/**
	* @author  Andrey Zaostrovnykh
	* @email   megalloid@mail.ru
	* @website http://smarthouseautomatics.ru/stm32/stm32f0xx/disco
	* @version v0.1
  * @ide     Keil uVision
  * @brief   Полезные макросы и функции для работы с LED и BUTTON
	*/

#include "my_stm32f0xx_disco.h"
#include "my_stm32f0xx_gpio.h"

/* Статус текущего состояния кнопки в событиях нажата/отпущена */
static volatile uint8_t MY_INT_DISCO_ButtonPressed = 0;


void MY_DISCO_LedInit(void)
{
	/* Устанавливает пины как выход */
	MY_GPIO_Init(DISCO_LED_PORT, DISCO_LED_ALL, MY_GPIO_Mode_Out, MY_GPIO_OType_PP, MY_GPIO_PuPd_NoPull, MY_GPIO_Speed_High);

	/* Выключаем все светодиоды*/
	MY_DISCO_LedOff(DISCO_LED_ALL);
}


void MY_DISCO_ButtonInit(void)
{
	/* Устанавливает пины как вход */
	MY_GPIO_Init(DISCO_BUTTON_PORT, DISCO_BUTTON_PIN, MY_GPIO_Mode_In, MY_GPIO_OType_PP, DISCO_BUTTON_PULL, MY_GPIO_Speed_High);
}


uint8_t MY_DISCO_ButtonOnPressed(void)
{
	/* If button is now pressed, but was not already pressed */
	if (MY_DISCO_ButtonPressed())
	{
		if (!MY_INT_DISCO_ButtonPressed)
		{
			/* Set flag */
			MY_INT_DISCO_ButtonPressed = 1;

			/* Return button onpressed */
			return 1;
		}
	}
	else
	{
		/* Clear flag */
		MY_INT_DISCO_ButtonPressed = 0;
	}

	/* Button is not pressed or it was already pressed before */
	return 0;
}


uint8_t MY_DISCO_ButtonOnReleased(void)
{
	/* If button is now released, but was not already released */
	if (!MY_DISCO_ButtonPressed())
	{
		if (MY_INT_DISCO_ButtonPressed)
		{
			/* Set flag */
			MY_INT_DISCO_ButtonPressed = 0;

			/* Return button onreleased */
			return 1;
		}
	}
	else
	{
		/* Set flag */
		MY_INT_DISCO_ButtonPressed = 1;
	}

	/* Button is not released or it was already released before */
	return 0;
}

