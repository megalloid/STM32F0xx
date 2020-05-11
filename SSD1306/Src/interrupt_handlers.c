/**
 * @author  Андрей Заостровных
 * @email   megalloid@mail.ru
 * @website http://smarthouseautomatics.ru/stm32/stm32f0xx/
 * @version v0.1
 * @ide     STM32CubeIDE
 * @brief   Этот файл содержит заголовки функций для обработчиков прерываний
 */

#include "interrupt_handlers.h"



/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/


void NMI_Handler(void)
{
	/* Check RCC CSS flag */
	if(MY_RCC_GET_IT(RCC_IT_CSS))
	{
		/* RCC Clock Security System interrupt user callback */
		/*<! User code here > */

		/* Clear RCC CSS pending bit */
		MY_RCC_CLEAR_IT(RCC_IT_CSS);
	}
}


void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{

	}
}


void SVC_Handler(void)
{

}


void PendSV_Handler(void)
{

}


void SysTick_Handler(void)
{
	MY_SysTick_IncTick();
}

