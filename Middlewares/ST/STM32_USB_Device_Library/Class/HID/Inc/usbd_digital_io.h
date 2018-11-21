/**
  ******************************************************************************
  * @file    usbd_digital_io.h
  * @author  MCD Application Team
  * @version V2.4.2
  * @date    11-December-2015
  * @brief   Header file for the usbd_hid_core.c file.
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
/* Includes -------------------------------------*/
#include "usbd_customhid.h"


/* Defines -------------------------------------*/
#ifndef __USBD_DIGITAL_IO_H
#define __USBD_DIGITAL_IO_H


#define DIGITAL_PIN_LOW			(0x00U)
#define DIGITAL_PIN_HIGH		(0x01U)
#define DIGITAL_MAX_PIN_NUM		(0x04U)
#define DIGITAL_MAX_PORT_NUM	(0x06U)
#define DIGITAL_PIN_INPUT		(0x00U)
#define DIGITAL_PIN_OUTPUT		(0x01U)

#ifdef __cplusplus
 extern "C" {
#endif

 typedef enum {
   UNCHANGED,
   CHANGED
 } Digital_IO_Change_Info;

 typedef enum {
   NOPULL = 0, // all two bits are 0
   PULLDOWN = 2, // only the second bit is 1
   PULLUP = 4 // only the third bit is 1
 } Digital_IO_Pull_Info;

 typedef enum {
   INPUT = 0,
   OUTPUT = 1
 } Digital_IO_Mode_Info;

 typedef enum {
	 DONTCARE,
	 TRIGGERED
 } HID_Digital_IO_Trigger;

 typedef enum {
	 LENGTH_NOTHING = 0,
	 LENGTH_TRIGGER = 1,
	 LENGTH_SYNC = 2,
	 LENGTH_DIGITAL_IO = 6,
	 LENGTH_DATETIME = 7
 } HID_Digital_IO_Output;

 typedef enum {
	 PORT_UNUSED = 0xff,
	 PORT_0 = 0x00,
	 PORT_1 = 0x01,
	 PORT_2 = 0x02,
	 PORT_3 = 0x03,
	 PORT_4 = 0x04,
	 PORT_5 = 0x05
 } HID_Digital_IO_Port_Names;

 typedef struct _ORDERED_ARRAY
   {
	 HID_Digital_IO_Port_Names 	array[DIGITAL_MAX_PORT_NUM];
     uint8_t              		head_idx;
     uint8_t              		tail_idx;
   } ORDERED_ARRAY;

 typedef struct _HID_DIGITAL_Port
   {
	 Digital_IO_Change_Info	_changeIO;
	 Digital_IO_Change_Info	_changePIN;
     uint8_t              	pin_enabled_size;
     uint8_t              	pins[DIGITAL_MAX_PIN_NUM];
     GPIO_InitTypeDef		gpio_settings;
   } HID_DIGITAL_Port_TypeDef;

 typedef struct _HID_DIGITAL_IO_Info
 {
   uint8_t              		port_enabled_size;
   HID_DIGITAL_Port_TypeDef		ports[DIGITAL_MAX_PORT_NUM];
 } HID_DIGITAL_IO_TypeDef;



 extern HID_DIGITAL_IO_TypeDef digital_io;
 extern HID_DIGITAL_IO_TypeDef digital_io_new_state;
 extern HID_Digital_IO_Trigger digital_io_trigger;

 /**
   * @brief  USBH_HID_Digital_IO_Init
   *         The function init the HID digital IO.
   * @param  phost: Host handle
   * @retval USBH Status
   */
 void USBD_HID_Digital_IO_Init();

 /**
   * @brief  USBH_HID_Digital_IO_Init
   *         The function init the HID digital IO.
   * @retval USBH Status
   */
 void USBD_HID_Digital_IO_CreateReport(uint8_t* report);

 /**
   * @brief  USBH_HID_Digital_IO_Init
   *         The function init the HID digital IO.
   * @retval USBH Status
   */
 void USBD_HID_Digital_IO_Read(void);


 /**
   * @brief  USBH_HID_Digital_IO_Init
   *         The function init the HID digital IO.
   * @retval USBH Status
   */
 void USBD_HID_Digital_IO_Set_Changes(uint8_t* output_buff);

 /**
   * @brief  USBH_HID_Digital_IO_Init
   *         The function init the HID digital IO.
   * @retval USBH Status
   */
 void USBD_HID_Digital_IO_Trigger (uint8_t* output_buff);

 /**
   * @brief  USBH_HID_Digital_IO_Init
   *         The function init the HID digital IO.
   * @param  phost: Host handle
   * @retval USBH Status
   */
 void USBD_HID_Digital_IO_Reset_SwitchTrig(void);


#ifdef __cplusplus
}
#endif

#endif  /* __USBD_DIGITAL_IO_H */
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
