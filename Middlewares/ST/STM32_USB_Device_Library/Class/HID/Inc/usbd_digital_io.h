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
#include "usbd_hid.h"


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

 typedef struct _HID_DIGITAL_Port
  {
    uint8_t              pin_enabled_size;
    uint8_t              direction;
    uint8_t              pins[DIGITAL_MAX_PIN_NUM];
  }
  HID_DIGITAL_Port_TypeDef;

 typedef struct _HID_DIGITAL_IO_Info
 {
   uint8_t              		port_enabled_size;
   HID_DIGITAL_Port_TypeDef		ports[DIGITAL_MAX_PORT_NUM];
 }
 HID_DIGITAL_IO_TypeDef;

 extern HID_DIGITAL_IO_TypeDef digital_io;

//USBH_StatusTypeDef USBH_HID_Digital_IO_Init(USBH_HandleTypeDef *phost);
//HID_DIGITAL_IO_Info_TypeDef *USBH_HID_Get_Digital_IO_Info(USBH_HandleTypeDef *phost);
//USBH_StatusTypeDef USBH_HID_Mouse_DecodeData(USBH_HandleTypeDef *phost, HID_Report_ItemTypedef *parser_data, uint8_t *pData, uint16_t length);


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
