/**
 * @author  Andrey Zaostrovnykh
 * @email   megalloid@mail.ru
 * @website http://smarthouseautomatics.ru/stm32/stm32f0xx/cortex
 * @version v0.1
 * @ide     STM32CubeIDE
 * @brief   Утилиты для работы с ядром Cortex-M0
 */

#include "my_stm32f0xx_cortex.h"

/* Глобальная переменная, в которой содержится текущее значение счетчика таймера SysTick */
volatile uint32_t uwTick;

void MY_SysTick_Init(uint32_t ticks, uint32_t TickPriority)
{
	/* Настраиваем источник тактирования для SysTick */
	MY_SysTick_ClockSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* Останавливаем таймер */
	MY_SysTick_SuspendTick();

	/* Настраиваем SysTick чтобы он давал прерывание раз в 1 мс. */
	SysTick_Config(ticks);

	/* Настраиваем приоритет прерывания SysTick IRQ */
	MY_NVIC_Priority_Set(SysTick_IRQn, TickPriority);

	/* Включаем таймер */
	MY_SysTick_ResumeTick();
}


void MY_SysTick_ClockSourceConfig(uint32_t ClockSource)
{
	if (ClockSource == SYSTICK_CLKSOURCE_HCLK)
	{
		SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;
	}
	else
	{
		SysTick->CTRL &= ~SYSTICK_CLKSOURCE_HCLK;
	}
}


void MY_SysTick_IncTick(void)
{
	uwTick++;
}


uint32_t MY_SysTick_GetTick(void)
{
	return uwTick;
}


void MY_SysTick_SuspendTick(void)
{
	/* Выключаем прерывания от SysTick */
	CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}


void MY_SysTick_ResumeTick(void)
{
	/* Включаем прерывания от SysTick */
	SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}


void MY_NVIC_EnableIRQ(IRQn_Type IRQn)
{
	/* Включаем прерывание */
	NVIC_EnableIRQ(IRQn);
}


void MY_NVIC_DisableIRQ(IRQn_Type IRQn)
{
	/* Отключаем прерывание */
	NVIC_DisableIRQ(IRQn);
}


void MY_NVIC_Priority_Set(IRQn_Type IRQn, uint32_t PreemptPriority)
{
	/* Устанавливаем приоритет пререывания */
	NVIC_SetPriority(IRQn, PreemptPriority);
}


uint32_t MY_NVIC_Priority_Get(IRQn_Type IRQn)
{
	/* Получаем приоритет прерывания для прерывания */
	return NVIC_GetPriority(IRQn);
}


void MY_NVIC_PendingIRQ_Set(IRQn_Type IRQn)
{
	/* Устанавливаем ожидание прерывания */
	NVIC_SetPendingIRQ(IRQn);
}


uint32_t MY_NVIC_PendingIRQ_Get(IRQn_Type IRQn)
{
	/* Возвращает 1 если ожидание установлено, если нет - 0 */
	return NVIC_GetPendingIRQ(IRQn);
}


void MY_NVIC_PendingIRQ_Clear(IRQn_Type IRQn)
{
	/* Сброс ожидания прерывания */
	NVIC_ClearPendingIRQ(IRQn);
}


void MY_NVIC_SystemReset(void)
{
	/* Системный сброс */
	NVIC_SystemReset();
}


uint32_t MY_REVID_Get(void)
{
	return((DBGMCU->IDCODE) >> 16U);
}


uint32_t MY_DEVID_Get(void)
{
	return((DBGMCU->IDCODE) & IDCODE_DEVID_MASK);
}


uint32_t MY_UID_Word0_Get(void)
{
	return(READ_REG(*((uint32_t *)UID_BASE)));
}


uint32_t MY_UID_Word1_Get(void)
{
	return(READ_REG(*((uint32_t *)(UID_BASE + 4U))));
}


uint32_t MY_UID_Word2_Get(void)
{
	return(READ_REG(*((uint32_t *)(UID_BASE + 8U))));
}


void MY_DBGMCU_DBGStopMode_Enable(void)
{
	SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}


void MY_DBGMCU_DBGStopMode_Disable(void)
{
	CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}


void MY_DBGMCU_DBGStandbyMode_Enable(void)
{
	SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}


void MY_DBGMCU_DBGStandbyMode_Disable(void)
{
	CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}
