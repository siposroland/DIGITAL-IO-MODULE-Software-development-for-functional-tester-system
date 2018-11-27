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
#define LOGICAL_MAX_ELEMENT_NUM (0x04U)

#define DIGITAL_IO_MAX_TRIG_NUM (0x02U)

#define MASK_SHIFT(mask, nth) ((mask) << (nth))

#ifdef __cplusplus
 extern "C" {
#endif

 typedef enum {
	 SIZE_1 = 1,
	 SIZE_2 = 2,
	 SIZE_3 = 3,
	 SIZE_4 = 4,
	 SIZE_5 = 5,
	 SIZE_6 = 6,
	 SIZE_7 = 7,
	 SIZE_8 = 8
 } INTERVAL_Size;

 typedef enum {
	 SHIFT_0 = 0,
	 SHIFT_1 = 1,
	 SHIFT_2 = 2,
	 SHIFT_3 = 3,
	 SHIFT_4 = 4,
	 SHIFT_5 = 5,
	 SHIFT_6 = 6,
	 SHIFT_7 = 7
 } SHIFT_Num;


 typedef enum {
	 CONSTANT = 0,
	 VARIABLE = 1
 } LOGICAL_ELEMENT_Type;

 typedef enum {
   UNCHANGED,
   CHANGED
 } Digital_IO_Change_Flag;

 typedef enum {
	NO_REPORT,
	SEND_REPORT
 } Digital_IO_Report_Flag;

 typedef enum {
   NOPULL = 0, // all two bits are 0
   PULLDOWN = 4, // only the second bit is 1
   PULLUP = 8 // only the third bit is 1
 } Digital_IO_Pull_Info;

 typedef enum {
   INPUT = 0,
   OUTPUT = 2
 } Digital_IO_Mode_Info;

 typedef enum {
	 DONTCARE,
	 TRIGGERED,
	 DO_TRIGGER
 } HID_Digital_IO_Trigger;

 typedef enum {
	 LENGTH_NOTHING = 0,
	 LENGTH_TRIGGER = 1,
	 LENGTH_SYNC = 2,
	 LENGTH_TRIGGER_EVENT = 5,
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
	 Digital_IO_Change_Flag	_changeIO;
	 Digital_IO_Change_Flag	_changePIN;
     uint8_t              	pin_enabled_size;
     uint8_t              	pins[DIGITAL_MAX_PIN_NUM];
     GPIO_InitTypeDef		gpio_settings;
   } HID_DIGITAL_Port_TypeDef;

 typedef struct _HID_DIGITAL_IO_Info
 {
   uint8_t              		port_enabled_size;
   HID_DIGITAL_Port_TypeDef		ports[DIGITAL_MAX_PORT_NUM];
 } HID_DIGITAL_IO_TypeDef;

 typedef struct _DIGITAL_LOGICAL_Element_TypeDef
 {
	 uint8_t				port_num;
	 uint8_t				pin_num;
	 uint8_t  				var_val;
 } DIGITAL_LOGICAL_Element_TypeDef;

 typedef struct _HID_DIGITAL_IO_TRIGGER_Event
 {
	uint8_t 							enable;
	uint8_t								num_of_ANDs;
	DIGITAL_LOGICAL_Element_TypeDef		element[LOGICAL_MAX_ELEMENT_NUM];
 } HID_DIGITAL_IO_TRIGGER_Event;


 extern HID_DIGITAL_IO_TypeDef digital_io;
 extern HID_DIGITAL_IO_TypeDef digital_io_new_state;
 extern HID_Digital_IO_Trigger digital_io_trigger;
 extern Digital_IO_Change_Flag digital_io_change_flag;
 extern Digital_IO_Report_Flag digital_io_report_flag;
 extern Digital_IO_Change_Flag digital_io_change_enable;
 extern HID_DIGITAL_IO_TRIGGER_Event digital_io_trig_events[DIGITAL_IO_MAX_TRIG_NUM];
 extern HID_Digital_IO_Trigger digital_io_do_trigger;

 /**
   * @brief  USBH_HID_Digital_IO_Init
   *         The function init the HID digital IO.
   * @param  phost: Host handle
   * @retval USBH Status
   */
 void USBD_HID_Digital_IO_Init(HID_DIGITAL_IO_TypeDef* digital_io_instance);

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

 /**
   * @brief  USBH_HID_Digital_IO_Init
   *         The function init the HID digital IO.
   * @retval USBH Status
   */
 void USBD_HID_Digital_IO_SwitchPorts(void);

 /**
   * @brief  USBH_HID_Digital_IO_Init
   *         The function init the HID digital IO.
   * @retval USBH Status
   */
 void USBD_HID_Digital_IO_GPIO_Setup (uint8_t idx);

 /**
   * @brief  USBH_HID_Digital_IO_Init
   *         The function init the HID digital IO.
   * @retval USBH Status
   */
 void USBD_HID_Digital_IO_Reset_Trigger_Event(HID_DIGITAL_IO_TRIGGER_Event* trig_event);

 /**
   * @brief  USBH_HID_Digital_IO_Init
   *         The function init the HID digital IO.
   * @retval USBH Status
   */
 void USBD_HID_Digital_IO_Process_Trigger_Event(uint8_t* output_buff, HID_DIGITAL_IO_TRIGGER_Event* t);

 /**
   * @brief  USBH_HID_Digital_IO_Init
   *         The function init the HID digital IO.
   * @retval USBH Status
   */
 HID_Digital_IO_Trigger USBD_HID_Digital_IO_Check_Trigger_Event(HID_DIGITAL_IO_TRIGGER_Event* t, uint8_t id);

 uint8_t create_mask(uint8_t num);
 uint8_t read_from_byte(uint8_t buffer, INTERVAL_Size size, SHIFT_Num shift);

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
