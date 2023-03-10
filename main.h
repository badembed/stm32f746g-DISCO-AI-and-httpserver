/**
  ******************************************************************************
  * @file    Templates/main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "app_x-cube-ai.h"
//#include "C:\Users\sasha\Downloads\AI-handwriting-recognition-based-on-STM32f746g-DISCOVERY-master\AI-handwriting-recognition-based-on-STM32f746g-DISCOVERY-master\Drivers\BSP\STM32746G-Discovery\stm32746g_discovery_ts.h"

#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif
#ifdef RTE_CMSIS_RTOS2                  // when RTE component CMSIS RTOS2 is used
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern uint64_t app_main_stk[];
extern const osThreadAttr_t app_main_attr;

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
extern void app_main (void *arg);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
