/**
 * @author  Andrey Zaostrovnykh
 * @email   megalloid@mail.ru
 * @website http://smarthouseautomatics.ru/stm32/stm32f0xx/i2c
 * @version v0.1
 * @ide     STM32CubeIDE
 * @brief   Утилиты для работы с I2C
 */
#include "my_stm32f0xx.h"
#include "my_stm32f0xx_i2c.h"


#define MAX_NBYTE_SIZE      255U

/* Приватные функции */
#ifdef I2C1
	/* Функция для инициализации GPIO-пинов для I2C1*/
	static void MY_I2C1_INT_InitPins(MY_I2C_PinsPack_t pinspack);
#endif

#ifdef I2C2
	/* Функция для инициализации GPIO-пинов для I2C1*/
	static void MY_I2C2_INT_InitPins(MY_I2C_PinsPack_t pinspack);
#endif


/* Струкутура для I2C */
#ifdef I2C1
	static MY_I2C_Init_t I2C1Handler = {I2C1};
#endif

#ifdef I2C2
	static MY_I2C_Init_t I2C2Handler = {I2C2};
#endif


MY_I2C_Init_t* MY_I2C_GetHandler(I2C_TypeDef* I2Cx)
{
	#ifdef I2C1

		if (I2Cx == I2C1)
		{
			return &I2C1Handler;
		}

	#endif

	#ifdef I2C2

		if (I2Cx == I2C2)
		{
			return &I2C2Handler;
		}

	#endif

	/* Return invalid */
	return 0;

}


MY_Result_t MY_I2C_Init(I2C_TypeDef* I2Cx)
{
	MY_I2C_Init_t* I2C_Handler = MY_I2C_GetHandler(I2Cx);

	uint32_t I2C_Timing;

	/* Проверяем валидность переданного параметра */
	if (I2C_Handler->Instance == NULL)
	{
		return MY_Result_Error;
	}

	/* Если периферия еще не была инициализирована - включаем тактирование и инициализируем GPIO пины*/
	if(I2C_Handler->State == MY_I2C_State_Reset)
	{
		/* Блокируем структуру */
		MY_LOCK(I2C_Handler);

		#ifdef I2C1
			if (I2C_Handler->Instance == I2C1)
			{
				MY_RCC_I2C1_CLK_ENABLE();
				MY_I2C1_INT_InitPins(I2C_Handler->Pinspack);
			}
		#endif

		#ifdef I2C2
			if (I2C_Handler->Instance == I2C2)
			{
				MY_RCC_I2C2_CLK_ENABLE();
				MY_I2C2_INT_InitPins(I2C_Handler->Pinspack);
			}
		#endif
	}

	/* Переводим в режим Busy */
	I2C_Handler->State = MY_I2C_State_Busy;

	/* Убеждаемся, что I2C выключен*/
	MY_I2C_DISABLE(I2C_Handler->Instance);

	/*---------------------------- Конфигурация I2Cx TIMINGR ------------------*/
	/* Вычисляем значение скорости тактирования I2C*/
	if(I2C_Handler->ClockSpeed == 100000)
	{
		/* 100kHz @ 48MHz SYSCLK clock */
		I2C_Timing = 0x20303E5D;
	}
	else if(I2C_Handler->ClockSpeed == 400000)
	{
		/* 400kHz @ 48MHz SYSCLK clock */
		I2C_Timing = 0x2010091A;
	}
	else if(I2C_Handler->ClockSpeed == 1000000)
	{
		/* 1000kHz @ 48MHz SYSCLK*/
		I2C_Timing = 0x20000209;
	}

	/* Настройка частоты I2Cx */
	I2C_Handler->Instance->TIMINGR = I2C_Timing;


	/*---------------------------- Конфигурация I2Cx OAR1 ---------------------*/
	/* Отключаем Own Address1 прежде чем настроить конфигурацию данного регистра */
	I2C_Handler->Instance->OAR1 &= ~I2C_OAR1_OA1EN;

	/* Настройка 7-битного режима адресации, Own Address1 и ACK на Own Address1  */
	if (I2C_Handler->AddressingMode == I2C_ADDRESSINGMODE_7BIT)
	{
		I2C_Handler->Instance->OAR1 = (I2C_OAR1_OA1EN | I2C_Handler->OwnAddress1);
	}
	/* Настройка 10-битного режима адресации, Own Address1 и ACK на Own Address1 */
	else
	{
		I2C_Handler->Instance->OAR1 = (I2C_OAR1_OA1EN | I2C_OAR1_OA1MODE | I2C_Handler->OwnAddress1);
	}


	/*---------------------------- Конфигурация I2Cx CR2 ----------------------*/
	/* Настраиваем режим адресации для режима Master */
	if (I2C_Handler->AddressingMode == I2C_ADDRESSINGMODE_10BIT)
	{
		I2C_Handler->Instance->CR2 = (I2C_CR2_ADD10);
	}
	/* Включаем AUTOEND по умолчанию, и включаем NACK (ACK используется только когда активирован режим Slave */
	I2C_Handler->Instance->CR2 |= (I2C_CR2_AUTOEND | I2C_CR2_NACK);


	/*---------------------------- Конфигурация I2Cx OAR2 ---------------------*/
	/* Отключаем Own Address2 прежде чем настроить конфигурацию данного регистра */
	I2C_Handler->Instance->OAR2 &= ~I2C_DUALADDRESS_ENABLE;

	/* Настраиваем режим работы Single or Dual mode и устанавливаем Own Address2 (если установлена опция) */
	I2C_Handler->Instance->OAR2 = (I2C_Handler->DualAddressMode | I2C_Handler->OwnAddress2 | (I2C_Handler->OwnAddress2Masks << 8));


	/*---------------------------- Конфигурация I2Cx CR1 ----------------------*/
	/* Настройка Generalcall и NoStretch mode */
	I2C_Handler->Instance->CR1 = (I2C_Handler->GeneralCallMode | I2C_Handler->NoStretchMode);

	/* Конфигурируем аналоговый и цифровой фильтр I2C */
	MY_I2C_ConfigFilters(I2C_Handler->Instance, I2C_Handler->AnalogFilter, I2C_Handler->DigitalFilter);

	/* Устанавливаем режим ACK/NACK (если используется Slave-режим) */
	MY_I2C_AcknowledgeNextData(I2C_Handler->Instance, I2C_Handler->TypeAcknowledge);

	/* Включаем I2C */
	MY_I2C_ENABLE(I2C_Handler->Instance);

	/* Разблокируем I2C */
	MY_UNLOCK(I2C_Handler);

	I2C_Handler->ErrorCode = I2C_ERROR_NONE;
	I2C_Handler->State = MY_I2C_State_Ready;
	I2C_Handler->Mode = MY_I2C_Mode_None;

	return MY_Result_Ok;
}


MY_Result_t MY_I2C_IsDeviceReady(I2C_TypeDef* I2Cx, uint16_t device_address, uint32_t trials, uint32_t timeout)
{
	/* Получаем указатель на структуру */
	MY_I2C_Init_t* I2C_Handler = MY_I2C_GetHandler(I2Cx);

	uint32_t tickstart = 0U;
	__IO uint32_t I2C_Trials = 0U;

	/* Если периферия инициализирована */
	if (I2C_Handler->State == MY_I2C_State_Ready)
	{
		/* Если взведен флаг "I2C занят" */
	    if (MY_I2C_GET_FLAG(I2C_Handler->Instance, I2C_FLAG_BUSY) == SET)
	    {
	    	return MY_Result_Busy;
	    }

	    /* Блокируем периферию */
	    MY_LOCK(I2C_Handler);

	    /* Меняем состояние на "Занят" */
	    I2C_Handler->State = MY_I2C_State_Busy;

	    /* Очищаем последнюю ошибку */
	    I2C_Handler->ErrorCode = I2C_ERROR_NONE;

	    do
	    {
	    	/* Генерируем Start и записываем его в CR2 */
	    	I2C_Handler->Instance->CR2 = MY_I2C_GENERATE_START(I2C_Handler->AddressingMode, device_address);

	    	/* Нет необходимости проверять флаг TC (Transfer complete), в режиме AUTOEND - STOP генерируется автоматически */
	    	/* Ждём пока не установлен флаг STOPF или NACK */
	    	tickstart = MY_SysTick_GetTick();

	    	while ((MY_I2C_GET_FLAG(I2C_Handler->Instance, I2C_FLAG_STOPF) == RESET) && \
	    		   (MY_I2C_GET_FLAG(I2C_Handler->Instance, I2C_FLAG_AF   ) == RESET) && \
				   (I2C_Handler->State != MY_I2C_State_Timeout))
	    	{
	    		if (timeout != MAX_DELAY)
	    		{
	    			if ((timeout == 0U) || ((MY_SysTick_GetTick() - tickstart) > timeout))
	    			{
	    				/* Возвращаем устройство в режим готовности */
	    				I2C_Handler->State = MY_I2C_State_Ready;

	    				/* Разблокируем структуру */
	    				MY_UNLOCK(I2C_Handler);

	    				return MY_Result_Timeout;
	    			}
	    		}
	    	}

	    	/* Проверяем не установлен ли флаг NACK (Acknowledge faliure) */
	    	if (MY_I2C_GET_FLAG(I2C_Handler->Instance, I2C_FLAG_AF) == RESET)
	    	{
	    		/* Ждём пока флаг STOPF сброшен */
	    		if (MY_I2C_WaitOnFlagUntilTimeout(I2C_Handler, I2C_FLAG_STOPF, RESET, timeout, tickstart) != MY_Result_Ok)
	    		{
	    			return MY_Result_Timeout;
	    		}

	    		/* Сброс флага STOP */
	    		MY_I2C_CLEAR_FLAG(I2C_Handler->Instance, I2C_FLAG_STOPF);

	    		/* Возвращаем устройство в режим готовности */
	    		I2C_Handler->State = MY_I2C_State_Ready;

	    		/* Разблокируем процесс */
	    		MY_UNLOCK(I2C_Handler);

	    		return MY_Result_Ok;
	    	}
	    	else
	    	{
	    		/* Ждём пока флаг STOPF сброшен */
	    		if (MY_I2C_WaitOnFlagUntilTimeout(I2C_Handler, I2C_FLAG_STOPF, RESET, timeout, tickstart) != MY_Result_Ok)
	    		{
	    			return MY_Result_Timeout;
	    		}

	    		/* Сбрасываем флаг NACK */
	    		MY_I2C_CLEAR_FLAG(I2C_Handler->Instance, I2C_FLAG_AF);

	    		/* Сбрасываем флаг STOP, auto generated с autoend*/
	    		MY_I2C_CLEAR_FLAG(I2C_Handler->Instance, I2C_FLAG_STOPF);
	    	}

	    	/* Проверяем, достигнуто ли максимальное количество проходов */
	    	if (I2C_Trials++ == trials)
	    	{
	    		/* Генерируем Stop */
	    		I2C_Handler->Instance->CR2 |= I2C_CR2_STOP;

	    		/* Ждём пока флаг не будет сброшен STOPF */
	    		if (MY_I2C_WaitOnFlagUntilTimeout(I2C_Handler, I2C_FLAG_STOPF, RESET, timeout, tickstart) != MY_Result_Ok)
	    		{
	    			return MY_Result_Timeout;
	    		}

	    		/* Сброс флага STOP */
	    		MY_I2C_CLEAR_FLAG(I2C_Handler->Instance, I2C_FLAG_STOPF);
	    	}
	    }
	    while (I2C_Trials < trials);

	    /* Возвращаем состояние структуры */
	    I2C_Handler->State = MY_I2C_State_Ready;

	    /* Разблокируем процесс */
	    MY_UNLOCK(I2C_Handler);

	    return MY_Result_Timeout;
	 }
	 else
	 {
		 return MY_Result_Busy;
	 }
}


MY_Result_t MY_I2C_ReadByte(I2C_TypeDef* I2Cx, uint16_t device_address, uint8_t register_address, uint8_t* data)
{
	/* Получаем указатель на структуру */
	MY_I2C_Init_t* I2C_Handler = MY_I2C_GetHandler(I2Cx);

	/* Отправляем адрес */
	if (MY_I2C_Master_Transmit(I2C_Handler, device_address, &register_address, 1, 1000) != MY_Result_Ok)
	{
		/* Проверяем ошибки */
		if (MY_I2C_GetError(I2C_Handler) != I2C_ERROR_AF)
		{

		}
		/* Возвращаем ошибку */
		return MY_Result_Error;
	}

	/* Receive multiple byte */
	if (MY_I2C_Master_Receive(I2C_Handler, device_address, data, 1, 1000) != MY_Result_Ok)
	{
		/* Проверяем ошибки */
		if (MY_I2C_GetError(I2C_Handler) != I2C_ERROR_AF)
		{

		}

		/* Возвращаем ошибку */
		return MY_Result_Error;
	}

	return MY_Result_Ok;
}


MY_Result_t MY_I2C_Master_Transmit(MY_I2C_Init_t *I2C_Handler, uint16_t device_address, uint8_t *pData, uint16_t size, uint32_t timeout)
{
	uint32_t tickstart = 0U;

	/* Если периферия инициализирована */
	if (I2C_Handler->State == MY_I2C_State_Ready)
	{
		/* Блокируем структуру */
		MY_LOCK(I2C_Handler);

		/* Получаем текущее значение счетчика SysTick для управления таймаутом */
		tickstart = MY_SysTick_GetTick();

		/* Ждём пока не будет снят флаг I2C BUSY */
		if (MY_I2C_WaitOnFlagUntilTimeout(I2C_Handler, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY, tickstart) != MY_Result_Ok)
		{
			/* Выходим по таймауту не дождавшись снятия флага BUSY */
			return MY_Result_Timeout;
		}

		/* Заносим параметры текущего состояния I2C */
		I2C_Handler->State     = MY_I2C_State_Busy_Tx;
		I2C_Handler->Mode      = MY_I2C_Mode_Master;
		I2C_Handler->ErrorCode = I2C_ERROR_NONE;


		/* Подготавливаем параметы передачи */
		I2C_Handler->BufferPointer  = pData;
		I2C_Handler->TransferCount = size;
		I2C_Handler->TransferISR   = 0U;


		/* ----------------------------------- Отправляем адрес Slave -----------------------------------*/

		/* Устанавливаем NBYTES для записи и перезагрузки если I2C_Handler->TransferCount > MAX_NBYTE_SIZE и генерируем RESTART */
		if (I2C_Handler->TransferCount > MAX_NBYTE_SIZE)
		{
			/* Ограничиваем максимальное количество передаваемых байт */
			I2C_Handler->TransferSize = MAX_NBYTE_SIZE;

			/* Отправляем данные в режиме Reload */
		    MY_I2C_TransferConfig(I2C_Handler, device_address, I2C_Handler->TransferSize, I2C_RELOAD_MODE, I2C_GENERATE_START_WRITE);
		}
		else
		{
			/* Устанавливаем количество передаваемых данных */
			I2C_Handler->TransferSize = I2C_Handler->TransferCount;
			/* Отправляем данные в режиме Autoend */
		    MY_I2C_TransferConfig(I2C_Handler, device_address, I2C_Handler->TransferSize, I2C_AUTOEND_MODE, I2C_GENERATE_START_WRITE);
		}

		/* Пока не переданы все байты, то... */
		while(I2C_Handler->TransferCount > 0U)
		{
			/* Ждём пока не будет установлен флаг TXIS (устанавливается когда TXDR становится пуст) */
			if (MY_I2C_WaitOnTXISFlagUntilTimeout(I2C_Handler, timeout, tickstart) != MY_Result_Ok)
		    {
		    	if (I2C_Handler->ErrorCode == I2C_ERROR_AF)
		        {
		        	return MY_Result_Error;
		        }
		        else
		        {
		        	return MY_Result_Timeout;
		        }
		    }

			/* Записываем данные в TXDR для отправки и делаем отсчёт в буфере */
			I2C_Handler->Instance->TXDR = (*I2C_Handler->BufferPointer++);
			I2C_Handler->TransferCount--;
			I2C_Handler->TransferSize--;

			/* Если все данные переданы */
		    if ((I2C_Handler->TransferSize == 0U) && (I2C_Handler->TransferCount != 0U))
		    {
		    	/* Ждём пока установлен флаг TCR */
		        if (MY_I2C_WaitOnFlagUntilTimeout(I2C_Handler, I2C_FLAG_TCR, RESET, timeout, tickstart) != MY_Result_Ok)
		        {
		        	return MY_Result_Timeout;
		        }

		        /* Если количество передаваемых данных больше максимального */
		        if (I2C_Handler->TransferCount > MAX_NBYTE_SIZE)
		        {
		        	/* Устанавливаем ограничение */
		        	I2C_Handler->TransferSize = MAX_NBYTE_SIZE;

		        	/* Устанавливаем режим передачи Reload */
		        	MY_I2C_TransferConfig(I2C_Handler, device_address, I2C_Handler->TransferSize, I2C_RELOAD_MODE, I2C_NO_STARTSTOP);
		        }
		        else
		        {
					/* Устанавливаем количество передаваемых данных */
		        	I2C_Handler->TransferSize = I2C_Handler->TransferCount;

					/* Устанавливаем количество передаваемых данных */
		        	MY_I2C_TransferConfig(I2C_Handler, device_address, I2C_Handler->TransferSize, I2C_AUTOEND_MODE, I2C_NO_STARTSTOP);
		        }
		    }
		}

		/* Нет необходимости дожидаться флага TC, в режиме AUTOEND - STOP генерируется автоматически */
		/* Ждём пока не будет установлен флаг STOPF */
		if (MY_I2C_WaitOnSTOPFlagUntilTimeout(I2C_Handler, timeout, tickstart) != MY_Result_Ok)
		{
			if (I2C_Handler->ErrorCode == I2C_ERROR_AF)
		    {
				return MY_Result_Error;
		    }
		    else
		    {
		    	return MY_Result_Timeout;
		    }
		 }

		 /* Сбрасываем флаг STOP */
		 MY_I2C_CLEAR_FLAG(I2C_Handler->Instance, I2C_FLAG_STOPF);

		 /* Сбрасываем конфигурационный регистр CR2 */
		 MY_I2C_RESET_CR2(I2C_Handler->Instance);

		 /* Обновляем статус структуры */
		 I2C_Handler->State = MY_I2C_State_Ready;
		 I2C_Handler->Mode  = MY_I2C_Mode_None;

		 /* Разблокируем процесс */
		 MY_UNLOCK(I2C_Handler);

		 return MY_Result_Ok;
	}
	else
	{
		 return MY_Result_Busy;
	}
}


void MY_I2C_TransferConfig(MY_I2C_Init_t *I2C_Handler,  uint16_t device_address, uint8_t size, uint32_t transfer_mode, uint32_t request)
{
	uint32_t tmpreg = 0U;

	/* Сохраняем текущее значение регистра CR2 */
	tmpreg = I2C_Handler->Instance->CR2;

	/* Сбрасываем биты CR2 */
	tmpreg &= (uint32_t)~((uint32_t)(I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP));

	/* Обновляем переменную tmpreg */
	tmpreg |= (uint32_t)(((uint32_t)device_address & I2C_CR2_SADD) | \
						(((uint32_t)size << 16) & I2C_CR2_NBYTES)  | \
	                      (uint32_t)transfer_mode | \
						  (uint32_t)request);

	 /* Записываем значение в CR2 */
	I2C_Handler->Instance->CR2 = tmpreg;
}


MY_Result_t MY_I2C_Master_Receive(MY_I2C_Init_t *I2C_Handler, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	uint32_t tickstart = 0U;

	if (I2C_Handler->State == MY_I2C_State_Ready)
	{
		/* Process Locked */
		MY_LOCK(I2C_Handler);

		/* Init tickstart for timeout management*/
	    tickstart = MY_SysTick_GetTick();

	    if (MY_I2C_WaitOnFlagUntilTimeout(I2C_Handler, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY, tickstart) != MY_Result_Ok)
	    {
	    	return MY_Result_Timeout;
	    }

	    I2C_Handler->State     = MY_I2C_State_Busy_Rx;
	    I2C_Handler->Mode      = MY_I2C_Mode_Master;
	    I2C_Handler->ErrorCode = I2C_ERROR_NONE;

	    /* Prepare transfer parameters */
	    I2C_Handler->BufferPointer  = pData;
	    I2C_Handler->TransferCount = Size;
	    I2C_Handler->TransferISR   = 0U;

	    /* Send Slave Address */
	    /* Set NBYTES to write and reload if hi2c->XferCount > MAX_NBYTE_SIZE and generate RESTART */
	    if (I2C_Handler->TransferCount > MAX_NBYTE_SIZE)
	    {
	    	I2C_Handler->TransferSize = MAX_NBYTE_SIZE;
	    	MY_I2C_TransferConfig(I2C_Handler, DevAddress, I2C_Handler->TransferSize, I2C_RELOAD_MODE, I2C_GENERATE_START_READ);
	    }
	    else
	    {
	    	I2C_Handler->TransferSize = I2C_Handler->TransferCount;
	    	MY_I2C_TransferConfig(I2C_Handler, DevAddress, I2C_Handler->TransferSize, I2C_AUTOEND_MODE, I2C_GENERATE_START_READ);
	    }

	    while (I2C_Handler->TransferCount > 0U)
	    {
	    	/* Wait until RXNE flag is set */
	    	if (MY_I2C_WaitOnRXNEFlagUntilTimeout(I2C_Handler, Timeout, tickstart) != MY_Result_Ok)
	    	{
	    		if (I2C_Handler->ErrorCode == I2C_ERROR_AF)
	    		{
	    			return MY_Result_Error;
	    		}
	    		else
	    		{
	    			return MY_Result_Timeout;
	    		}
	    	}

	    	/* Read data from RXDR */
	    	(*I2C_Handler->BufferPointer++) = I2C_Handler->Instance->RXDR;
	    	I2C_Handler->TransferSize--;
	    	I2C_Handler->TransferCount--;

	    	if ((I2C_Handler->TransferSize == 0U) && (I2C_Handler->TransferCount != 0U))
	    	{
	    		/* Wait until TCR flag is set */
	    		if (MY_I2C_WaitOnFlagUntilTimeout(I2C_Handler, I2C_FLAG_TCR, RESET, Timeout, tickstart) != MY_Result_Ok)
	    		{
	    			return MY_Result_Timeout;
	    		}

	    		if (I2C_Handler->TransferCount > MAX_NBYTE_SIZE)
	    		{
	    			I2C_Handler->TransferSize = MAX_NBYTE_SIZE;
	    			MY_I2C_TransferConfig(I2C_Handler, DevAddress, I2C_Handler->TransferSize, I2C_RELOAD_MODE, I2C_NO_STARTSTOP);
	    		}
	    		else
	    		{
	    			I2C_Handler->TransferSize = I2C_Handler->TransferCount;
	    			MY_I2C_TransferConfig(I2C_Handler, DevAddress, I2C_Handler->TransferSize, I2C_AUTOEND_MODE, I2C_NO_STARTSTOP);
	    		}
	    	}
	    }

	    /* No need to Check TC flag, with AUTOEND mode the stop is automatically generated */
	    /* Wait until STOPF flag is set */
	    if (MY_I2C_WaitOnSTOPFlagUntilTimeout(I2C_Handler, Timeout, tickstart) != MY_Result_Ok)
	    {
	    	if (I2C_Handler->ErrorCode == I2C_ERROR_AF)
	    	{
	    		return MY_Result_Error;
	    	}
	    	else
	    	{
	    		return MY_Result_Timeout;
	    	}
	    }

	    /* Clear STOP Flag */
	    MY_I2C_CLEAR_FLAG(I2C_Handler->Instance, I2C_FLAG_STOPF);

	    /* Clear Configuration Register 2 */
	    MY_I2C_RESET_CR2(I2C_Handler->Instance);

	    I2C_Handler->State = MY_I2C_State_Ready;
	    I2C_Handler->Mode  = MY_I2C_Mode_None;

	    /* Process Unlocked */
	    MY_UNLOCK(I2C_Handler);

	    return MY_Result_Ok;
	}
	else
	{
		return MY_Result_Busy;
	}
}


MY_Result_t MY_I2C_WaitOnFlagUntilTimeout(MY_I2C_Init_t *I2C_Handler, uint32_t flag, FlagStatus status, uint32_t timeout, uint32_t tickstart)
{
	while (MY_I2C_GET_FLAG(I2C_Handler->Instance, flag) == status)
	{
	    /* Проверяем таймаут */
	    if (timeout != MAX_DELAY)
	    {
	    	if ((timeout == 0U) || ((MY_SysTick_GetTick() - tickstart) > timeout))
	    	{
	    		/* Возвращаем структуру к исходному состоянию */
	    		I2C_Handler->State = MY_I2C_State_Ready;
	    		I2C_Handler->Mode = MY_I2C_Mode_None;

	    		/* Разблокируем процесс */
	    		MY_UNLOCK(I2C_Handler);

	    		return MY_Result_Timeout;
	    	}
	    }
	}
	return MY_Result_Ok;

}


MY_Result_t MY_I2C_WaitOnTXISFlagUntilTimeout(MY_I2C_Init_t *I2C_Handler, uint32_t Timeout, uint32_t Tickstart)
{
	while (MY_I2C_GET_FLAG(I2C_Handler->Instance, I2C_FLAG_TXIS) == RESET)
	{
	    /* Check if a NACK is detected */
	    if (MY_I2C_IsAcknowledgeFailed(I2C_Handler, Timeout, Tickstart) != MY_Result_Ok)
	    {
	    	return MY_Result_Error;
	    }

	    /* Check for the Timeout */
	    if (Timeout != MAX_DELAY)
	    {
	    	if ((Timeout == 0U) || ((MY_SysTick_GetTick() - Tickstart) > Timeout))
	    	{
	    		I2C_Handler->ErrorCode |= I2C_ERROR_TIMEOUT;
	    		I2C_Handler->State = MY_I2C_State_Ready;
	    		I2C_Handler->Mode = MY_I2C_Mode_None;

	    		/* Process Unlocked */
	    		MY_UNLOCK(I2C_Handler);

	    		return MY_Result_Timeout;
	    	}
	    }
	}

	return MY_Result_Ok;

}

MY_Result_t MY_I2C_WaitOnRXNEFlagUntilTimeout(MY_I2C_Init_t *I2C_Handler, uint32_t Timeout, uint32_t Tickstart)
{
	while (MY_I2C_GET_FLAG(I2C_Handler->Instance, I2C_FLAG_RXNE) == RESET)
	{
	    /* Check if a NACK is detected */
	    if (MY_I2C_IsAcknowledgeFailed(I2C_Handler, Timeout, Tickstart) != MY_Result_Ok)
	    {
	    	return MY_Result_Error;
	    }

	    /* Check if a STOPF is detected */
	    if (MY_I2C_GET_FLAG(I2C_Handler->Instance, I2C_FLAG_STOPF) == SET)
	    {
	    	/* Clear STOP Flag */
	    	MY_I2C_CLEAR_FLAG(I2C_Handler->Instance, I2C_FLAG_STOPF);

	    	/* Clear Configuration Register 2 */
	    	MY_I2C_RESET_CR2(I2C_Handler->Instance);

	    	I2C_Handler->ErrorCode = I2C_ERROR_NONE;
	    	I2C_Handler->State = MY_I2C_State_Ready;
	    	I2C_Handler->Mode = MY_I2C_Mode_None;

	    	/* Process Unlocked */
	    	MY_UNLOCK(I2C_Handler);

	    	return MY_Result_Error;
	    }

	    /* Check for the Timeout */
	    if ((Timeout == 0U) || ((MY_SysTick_GetTick() - Tickstart) > Timeout))
	    {
	    	I2C_Handler->ErrorCode |= I2C_ERROR_TIMEOUT;
	    	I2C_Handler->State = MY_I2C_State_Ready;

	    	/* Process Unlocked */
	    	MY_UNLOCK(I2C_Handler);

	      return MY_Result_Timeout;
	    }
	}

	return MY_Result_Ok;
}


MY_Result_t MY_I2C_IsAcknowledgeFailed(MY_I2C_Init_t *I2C_Handler, uint32_t Timeout, uint32_t Tickstart)
{
	if (MY_I2C_GET_FLAG(I2C_Handler->Instance, I2C_FLAG_AF) == SET)
	{
		/* Wait until STOP Flag is reset */
		/* AutoEnd should be initiate after AF */
	    while (MY_I2C_GET_FLAG(I2C_Handler->Instance, I2C_FLAG_STOPF) == RESET)
	    {
	    	/* Check for the Timeout */
	    	if (Timeout != MAX_DELAY)
	    	{
	    		if ((Timeout == 0U) || ((MY_SysTick_GetTick() - Tickstart) > Timeout))
	    		{
	    			I2C_Handler->State = MY_I2C_State_Ready;
	    			I2C_Handler->Mode = MY_I2C_Mode_None;

	    			/* Process Unlocked */
	    			MY_UNLOCK(I2C_Handler);
	    			return MY_Result_Timeout;
	    		}
	    	}
	    }

	    /* Clear NACKF Flag */
	    MY_I2C_CLEAR_FLAG(I2C_Handler->Instance, I2C_FLAG_AF);

	    /* Clear STOP Flag */
	    MY_I2C_CLEAR_FLAG(I2C_Handler->Instance, I2C_FLAG_STOPF);

	    /* Flush TX register */
	    MY_I2C_Flush_TXDR(I2C_Handler);

	    /* Clear Configuration Register 2 */
	    MY_I2C_RESET_CR2(I2C_Handler->Instance);

	    I2C_Handler->ErrorCode = I2C_ERROR_AF;
	    I2C_Handler->State = MY_I2C_State_Ready;
	    I2C_Handler->Mode = MY_I2C_Mode_None;

	    /* Process Unlocked */
	    MY_UNLOCK(I2C_Handler);

		return MY_Result_Error;

	}

	return MY_Result_Ok;

}


MY_Result_t MY_I2C_WaitOnSTOPFlagUntilTimeout(MY_I2C_Init_t *I2C_Handler, uint32_t Timeout, uint32_t Tickstart)
{
	while (MY_I2C_GET_FLAG(I2C_Handler->Instance, I2C_FLAG_STOPF) == RESET)
	{
	    /* Check if a NACK is detected */
	    if (MY_I2C_IsAcknowledgeFailed(I2C_Handler, Timeout, Tickstart) != MY_Result_Ok)
	    {
	    	return MY_Result_Error;
	    }

	    /* Check for the Timeout */
	    if ((Timeout == 0U) || ((MY_SysTick_GetTick() - Tickstart) > Timeout))
	    {
	    	I2C_Handler->ErrorCode |= I2C_ERROR_TIMEOUT;
	    	I2C_Handler->State = MY_I2C_State_Ready;
	    	I2C_Handler->Mode = MY_I2C_Mode_None;

	    	/* Process Unlocked */
	    	MY_UNLOCK(I2C_Handler);

	    	return MY_Result_Timeout;
	    }
	}

	return MY_Result_Ok;

}

void MY_I2C_Flush_TXDR(MY_I2C_Init_t *I2C_Handler)
{
	/* If a pending TXIS flag is set */
	/* Write a dummy data in TXDR to clear it */
	if (MY_I2C_GET_FLAG(I2C_Handler->Instance, I2C_FLAG_TXIS) != RESET)
	{
		I2C_Handler->Instance->TXDR = 0x00U;
	}

	/* Flush TX register if not empty */
	if (MY_I2C_GET_FLAG(I2C_Handler->Instance, I2C_FLAG_TXE) == RESET)
	{
	    MY_I2C_CLEAR_FLAG(I2C_Handler->Instance, I2C_FLAG_TXE);
	}
}


void MY_I2C_ConfigFilters(I2C_TypeDef *I2Cx, uint32_t AnalogFilter, uint32_t DigitalFilter)
{
	MODIFY_REG(I2Cx->CR1, I2C_CR1_ANFOFF | I2C_CR1_DNF, AnalogFilter | (DigitalFilter << I2C_CR1_DNF_Pos));
}


void MY_I2C_AcknowledgeNextData(I2C_TypeDef *I2Cx, uint32_t TypeAcknowledge)
{
	MODIFY_REG(I2Cx->CR2, I2C_CR2_NACK, TypeAcknowledge);
}

uint32_t MY_I2C_GetError(MY_I2C_Init_t *I2C_Handler)
{
	return I2C_Handler->ErrorCode;
}


MY_Result_t MY_I2C_Write(I2C_TypeDef* I2Cx, uint8_t device_address, uint8_t register_address, uint8_t data)
{
	MY_I2C_Init_t* I2C_Handler = MY_I2C_GetHandler(I2Cx);

	uint8_t d[2];

	/* Format array to send */
	d[0] = register_address;
	d[1] = data;

	/* Try to transmit via I2C */
	if (MY_I2C_Master_Transmit(I2C_Handler, (uint16_t)device_address, (uint8_t *)d, 2, 1000) != MY_Result_Ok)
	{
		/* Check error */
		if (MY_I2C_GetError(I2C_Handler) != I2C_ERROR_AF)
		{

		}

		/* Return error */
		return MY_Result_Error;
	}

	/* Return OK */
	return MY_Result_Ok;
}

/* Приватные функции */
static void MY_I2C1_INT_InitPins(MY_I2C_PinsPack_t pinspack)
{
	uint8_t GPIO_AlternateFunction;

	#if defined (STM32F051x8)
		GPIO_AlternateFunction = GPIO_AF1_I2C1;
	#endif

	/* Инициализируем пины в режиме альтернативной функции */
	if (pinspack == MY_I2C_PinsPack_1)
	{
		MY_GPIO_InitAlternate(GPIOB, GPIO_Pin_6 | GPIO_Pin_7, MY_GPIO_OType_OD, MY_GPIO_PuPd_Up, MY_GPIO_Speed_High, GPIO_AlternateFunction);
	}

	if (pinspack == MY_I2C_PinsPack_2)
	{
		MY_GPIO_InitAlternate(GPIOB, GPIO_Pin_8 | GPIO_Pin_9, MY_GPIO_OType_OD, MY_GPIO_PuPd_Up, MY_GPIO_Speed_High, GPIO_AlternateFunction);
	}
}


static void MY_I2C2_INT_InitPins(MY_I2C_PinsPack_t pinspack)
{
	uint8_t GPIO_AlternateFunction;

	#if defined (STM32F051x8)
		GPIO_AlternateFunction = GPIO_AF1_I2C2;
	#endif

	/* Инициализируем пины в режиме альтернативной функции */
	if (pinspack == MY_I2C_PinsPack_1)
	{
		MY_GPIO_InitAlternate(GPIOB, GPIO_Pin_10 | GPIO_Pin_11, MY_GPIO_OType_OD, MY_GPIO_PuPd_Up, MY_GPIO_Speed_High, GPIO_AlternateFunction);
	}

	if (pinspack == MY_I2C_PinsPack_2)
	{
		MY_GPIO_InitAlternate(GPIOF, GPIO_Pin_6 | GPIO_Pin_7, MY_GPIO_OType_OD, MY_GPIO_PuPd_Up, MY_GPIO_Speed_High, GPIO_AlternateFunction);
	}
}
