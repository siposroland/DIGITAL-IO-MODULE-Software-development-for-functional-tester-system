/**
  ******************************************************************************
  * @file    usbd_digital_io.c
  * @author  MCD Application Team
  * @version V2.4.2
  * @date    11-December-2015
  * @brief   This file provides the HID core functions.
  *
  * @verbatim
  *      
  *          ===================================================================      
  *                                HID Class  Description
  *          =================================================================== 
  *           This module manages the HID class V1.11 following the "Device Class Definition
  *           for Human Interface Devices (HID) Version 1.11 Jun 27, 2001".
  *           This driver implements the following aspects of the specification:
  *             - The Boot Interface Subclass
  *             - The Mouse protocol
  *             - Usage Page : Generic Desktop
  *             - Usage : Digital IO
  *             - Collection : Application 
  *      
  * @note     In HS mode and when the DMA is used, all variables and data structures
  *           dealing with the DMA during the transaction process should be 32-bit aligned.
  *           
  *      
  *  @endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbd_digital_io.h"
#include "gpio.h"

/* Global ariables */
HID_DIGITAL_IO_TypeDef digital_io;

/* Functions */

/**
  * @brief  USBH_HID_Digital_IO_Init
  *         The function init the HID digital IO.
  * @param  phost: Host handle
  * @retval USBH Status
  */
void USBD_HID_Digital_IO_Init(HID_DIGITAL_IO_TypeDef digital_io_instance)
{
  uint8_t port_idx = 0, pin_idx = 0;

  // Initialize default values
  digital_io_instance.port_enabled_size = DIGITAL_MAX_PORT_NUM;

  // Step over all ports
  for(port_idx = 0; port_idx < DIGITAL_MAX_PORT_NUM; port_idx++)
  {
	  // Add default gpio settings
	  digital_io_instance.ports[port_idx].gpio_settings.Mode = GPIO_MODE_OUTPUT_PP;
	  digital_io_instance.ports[port_idx].gpio_settings.Pull = GPIO_PULLDOWN;
	  digital_io_instance.ports[port_idx].gpio_settings.Pin = 0;

	  // Add default number and change state
	  digital_io_instance.ports[port_idx].pin_enabled_size = DIGITAL_MAX_PIN_NUM;
	  digital_io_instance.ports[port_idx]._changeIO = UNCHANGED;
	  digital_io_instance.ports[port_idx]._changePIN = UNCHANGED;

	  // Set pin specific default values
	  for (pin_idx = 0; pin_idx < DIGITAL_MAX_PIN_NUM; pin_idx++){
		  digital_io_instance.ports[port_idx].pins[pin_idx] = DIGITAL_PIN_LOW;
		  digital_io_instance.ports[port_idx].gpio_settings.Pin |= gpio_digital_pin[port_idx][pin_idx];
	  }
  }
}

/**
  * @brief  USBH_HID_Digital_IO_Init
  *         The function init the HID digital IO.
  * @param  phost: Host handle
  * @retval USBH Status
  */
void USBD_HID_Digital_IO_Reset_SwitchTrig(void)
{
  uint8_t port_idx = 0;

  // Reset switch buffer
  digital_io_switch_buffer.head_idx = 0;
  digital_io_switch_buffer.tail_idx = (DIGITAL_MAX_PORT_NUM - 1);

  // Unset trigger
  digital_io_trigger = DONTCARE;

  for(port_idx = 0; port_idx < DIGITAL_MAX_PORT_NUM; port_idx++)
  {
	  // Fill switch buffer
	  digital_io_switch_buffer.array[port_idx] = PORT_UNUSED;
  }
}

/**
  * @brief  USBH_HID_Digital_IO_Init
  *         The function init the HID digital IO.
  * @retval USBH Status
  */
void USBD_HID_Digital_IO_CreateReport(uint8_t* report)
{
  uint8_t port_idx = 0, pin_idx = 0, offset = 0, report_num = 0;

  // Clean old report
  report[0] = 0;
  report[1] = 0;
  report[2] = 0;
  report[3] = 0;

  // Step over all ports
  for(port_idx = 0; port_idx < DIGITAL_MAX_PORT_NUM; port_idx++)
  {
	  // Add IO directions to the report
	  // FORMAT: 1 byte (2 last bit reserved)
	  // XX543210, when 0...5 indicate the direction of the numbered ports
	  report[0] += (digital_io.ports[port_idx].gpio_settings.Mode << port_idx);

	  // Select actual report and add offset
	  if ((port_idx % 2) == 0)
	  {
		  report_num += 1;
		  offset = 0;
	  }
	  else
	  {
		  offset = 4;
	  }

	  // Add pin values to the report
	  // FORMAT: 3 byte -> 0000|1111, 2222|3333, 4444|5555 (4 pin / port)
	  // Numbers sign the actual port
	  // Step over all pins
	  for (pin_idx = 0; pin_idx < DIGITAL_MAX_PIN_NUM; pin_idx++){
		  report[report_num] += (digital_io.ports[port_idx].pins[pin_idx] << (pin_idx + offset));
	  }
  }

}

/**
  * @brief  USBH_HID_Digital_IO_Init
  *         The function init the HID digital IO.
  * @retval USBH Status
  */
void USBD_HID_Digital_IO_Read(void)
{
  uint8_t port_idx = 0, pin_idx = 0;

  // Step over all ports
  for(port_idx = 0; port_idx < DIGITAL_MAX_PORT_NUM; port_idx++)
  {
	  for (pin_idx = 0; pin_idx < DIGITAL_MAX_PIN_NUM; pin_idx++){
		  digital_io.ports[port_idx].pins[pin_idx] = GPIO_Read_DIGITAL_IO(port_idx, pin_idx);
	  }
  }

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
