
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "usbd_customhid.h"
#include "usbd_custom_hid_if.h"
#include "usbd_digital_io.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void USB_RX_Interrupt(void);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
uint8_t input_report[11] = {1};
uint8_t output_report[64] = {0};
MAIN_STATE main_state = MAIN_STATE_NORMAL;
uint8_t trig_event_to_delete = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t i = 0;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USB_DEVICE_Init();
  MX_TIM3_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
  USBD_HID_Digital_IO_Init(&digital_io);
  USBD_HID_Digital_IO_Init(&digital_io_new_state);
  USBD_HID_Digital_IO_Reset_SwitchTrig();
  for (i = 0; i < DIGITAL_IO_MAX_TRIG_NUM; i++)
  {
	  USBD_HID_Digital_IO_Reset_Trigger_Event(&digital_io_trig_events[i]);
  }
  HAL_TIM_Base_Start_IT(&htim3);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	if (main_state == MAIN_STATE_NORMAL)
	{
		// Read GPIO pins and test trigger events
		USBD_HID_Digital_IO_Read();

		for(i = 0; i < DIGITAL_IO_MAX_TRIG_NUM; i++)
		{
			if(digital_io_do_trigger != TRIGGERED)
			{
				digital_io_do_trigger = USBD_HID_Digital_IO_Check_Trigger_Event(digital_io_trig_events, i);
				if (digital_io_do_trigger == TRIGGERED)
				{
					trig_event_to_delete = i;
				}
			}
		}

		if(digital_io_do_trigger == TRIGGERED)
		{
			HAL_GPIO_WritePin(TRIGGER_OUT_GPIO_Port, TRIGGER_OUT_Pin, GPIO_PIN_SET);
			digital_io_do_trigger = DO_TRIGGER;
			USBD_HID_Digital_IO_Reset_Trigger_Event(&digital_io_trig_events[trig_event_to_delete]);
		}

		// Create and send digital IO report
		if (digital_io_report_flag == SEND_REPORT)
		{
		  USBD_HID_Digital_IO_CreateReport((uint8_t*)&input_report);
		  USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t*)&input_report, 11);
		  digital_io_report_flag = NO_REPORT;
		}

		// Store digital IO changes
		if (digital_io_change_flag == CHANGED)
		{
			USBD_HID_Digital_IO_Init(&digital_io_new_state);
			USBD_HID_Digital_IO_Set_Changes(output_report);
			digital_io_change_flag = UNCHANGED;
			digital_io_change_enable = 1;
		}

		// Enforce settings of the pins
		if (digital_io_trigger == TRIGGERED)
		{
			USBD_HID_Digital_IO_SwitchPorts();
			USBD_HID_Digital_IO_Init(&digital_io_new_state);
			USBD_HID_Digital_IO_Reset_SwitchTrig();
			digital_io_trigger = DONTCARE;
			digital_io_change_enable = 0;
		}
	}
	if (main_state == MAIN_STATE_SYNC)
	{
		// TODO
	}
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* TIM3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

/* USER CODE BEGIN 4 */

void USB_RX_Interrupt(void)
{
	uint8_t i;
	HID_Digital_IO_Output length = LENGTH_NOTHING;
	USBD_CUSTOM_HID_HandleTypeDef *myusb=(USBD_CUSTOM_HID_HandleTypeDef *)hUsbDeviceFS.pClassData;

	//Clear arr
	for(i=0;i<64;i++)
	{
		output_report[i]=0;
	}

	// First byte contains numbers of datas in byte length
	length = myusb->Report_buf[0];

	// Copy the output report
	for( i = 0; i < length; i++ )
	{
		output_report[i]=myusb->Report_buf[i+1];
	}

	// Handle report based on the length
	switch (length)
	{
		case LENGTH_NOTHING:
			break;
		case LENGTH_TRIGGER_EVENT:
			USBD_HID_Digital_IO_Process_Trigger_Event(output_report, digital_io_trig_events);
			break;
		case LENGTH_TRIGGER:
			// Defend to the multiple triggering
			if (digital_io_change_enable)
			{
				USBD_HID_Digital_IO_Trigger(output_report);
			}
			break;
		case LENGTH_SYNC:
			// Handle sync method, disable other tasks
			break;
		case LENGTH_DIGITAL_IO:
			digital_io_change_flag = CHANGED;
			break;
		case LENGTH_DATETIME:
			// Handle date- and timestamp
			break;
		default:
			break;
	}

	// Test answer
	/*HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	input_report[1] = 1;
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t*)&input_report, 11);*/
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
