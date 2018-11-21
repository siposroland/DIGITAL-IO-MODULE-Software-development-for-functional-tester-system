/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
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
#include "gpio.h"
/* USER CODE BEGIN 0 */
#include "usbd_digital_io.h"

uint16_t gpio_digital_pin [DIGITAL_MAX_PORT_NUM]  [DIGITAL_MAX_PIN_NUM] =
{
	{PORT_0_PIN_0_Pin, PORT_0_PIN_1_Pin, PORT_0_PIN_2_Pin, PORT_0_PIN_3_Pin},
	{PORT_1_PIN_0_Pin, PORT_1_PIN_1_Pin, PORT_1_PIN_2_Pin, PORT_1_PIN_3_Pin},
	{PORT_2_PIN_0_Pin, PORT_2_PIN_1_Pin, PORT_2_PIN_2_Pin, PORT_2_PIN_3_Pin},
	{PORT_3_PIN_0_Pin, PORT_3_PIN_1_Pin, PORT_3_PIN_2_Pin, PORT_3_PIN_3_Pin},
	{PORT_4_PIN_0_Pin, PORT_4_PIN_1_Pin, PORT_4_PIN_2_Pin, PORT_4_PIN_3_Pin},
	{PORT_5_PIN_0_Pin, PORT_5_PIN_1_Pin, PORT_5_PIN_2_Pin, PORT_5_PIN_3_Pin}
};

GPIO_TypeDef* gpio_digital_port [DIGITAL_MAX_PORT_NUM]  [DIGITAL_MAX_PIN_NUM] =
{
	{PORT_0_PIN_0_GPIO_Port, PORT_0_PIN_1_GPIO_Port, PORT_0_PIN_2_GPIO_Port, PORT_0_PIN_3_GPIO_Port},
	{PORT_1_PIN_0_GPIO_Port, PORT_1_PIN_1_GPIO_Port, PORT_1_PIN_2_GPIO_Port, PORT_1_PIN_3_GPIO_Port},
	{PORT_2_PIN_0_GPIO_Port, PORT_2_PIN_1_GPIO_Port, PORT_2_PIN_2_GPIO_Port, PORT_2_PIN_3_GPIO_Port},
	{PORT_3_PIN_0_GPIO_Port, PORT_3_PIN_1_GPIO_Port, PORT_3_PIN_2_GPIO_Port, PORT_3_PIN_3_GPIO_Port},
	{PORT_4_PIN_0_GPIO_Port, PORT_4_PIN_1_GPIO_Port, PORT_4_PIN_2_GPIO_Port, PORT_4_PIN_3_GPIO_Port},
	{PORT_5_PIN_0_GPIO_Port, PORT_5_PIN_1_GPIO_Port, PORT_5_PIN_2_GPIO_Port, PORT_5_PIN_3_GPIO_Port}
};
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PCPin PCPin PCPin PCPin 
                           PCPin PCPin PCPin PCPin 
                           PCPin */
  GPIO_InitStruct.Pin = PORT_4_PIN_0_Pin|PORT_4_PIN_1_Pin|PORT_4_PIN_2_Pin|PORT_4_PIN_3_Pin 
                          |PORT_5_PIN_0_Pin|PORT_5_PIN_1_Pin|PORT_5_PIN_2_Pin|PORT_5_PIN_3_Pin 
                          |PORT_3_PIN_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin 
                           PBPin PBPin PBPin PBPin 
                           PBPin PBPin PBPin PBPin 
                           PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = PORT_0_PIN_0_Pin|PORT_0_PIN_1_Pin|PORT_0_PIN_2_Pin|PORT_2_PIN_2_Pin 
                          |PORT_2_PIN_3_Pin|PORT_3_PIN_0_Pin|PORT_3_PIN_1_Pin|PORT_3_PIN_2_Pin 
                          |PORT_0_PIN_3_Pin|PORT_1_PIN_0_Pin|PORT_1_PIN_1_Pin|PORT_1_PIN_2_Pin 
                          |PORT_1_PIN_3_Pin|PORT_2_PIN_0_Pin|PORT_2_PIN_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = TRIGGER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TRIGGER_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 2 */
uint8_t GPIO_Read_DIGITAL_IO(uint8_t port, uint8_t pin)
{
	//volatile uint8_t szam = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13);
	//volatile uint8_t szam2 = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_8);
	return HAL_GPIO_ReadPin(gpio_digital_port[port][pin],gpio_digital_pin[port][pin]);
	//return szam2 + szam;
}

void GPIO_Write_DIGITAL_IO(uint8_t port, uint8_t pin, GPIO_PinState value)
{
	HAL_GPIO_WritePin(gpio_digital_port[port][pin],gpio_digital_pin[port][pin], value);
}


/* USER CODE END 2 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
