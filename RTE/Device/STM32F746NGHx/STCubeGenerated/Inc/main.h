/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void MX_ETH_Init(void);
void MX_LTDC_Init(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SS_MCU_2_Pin GPIO_PIN_15
#define SS_MCU_2_GPIO_Port GPIOA
#define MCU_LED6_Pin GPIO_PIN_3
#define MCU_LED6_GPIO_Port GPIOI
#define SS_MCU_3_Pin GPIO_PIN_2
#define SS_MCU_3_GPIO_Port GPIOI
#define MCU_LED4_Pin GPIO_PIN_0
#define MCU_LED4_GPIO_Port GPIOI
#define SS_MCU_1_Pin GPIO_PIN_8
#define SS_MCU_1_GPIO_Port GPIOA
#define MCU_LED5_Pin GPIO_PIN_7
#define MCU_LED5_GPIO_Port GPIOG
#define Deurslot_Pin GPIO_PIN_6
#define Deurslot_GPIO_Port GPIOF
#define MCU_LED1_Pin GPIO_PIN_10
#define MCU_LED1_GPIO_Port GPIOF
#define MCU_LED2_Pin GPIO_PIN_9
#define MCU_LED2_GPIO_Port GPIOF
#define MCU_LED3_Pin GPIO_PIN_8
#define MCU_LED3_GPIO_Port GPIOF
#define IRQ_MCU_Pin GPIO_PIN_0
#define IRQ_MCU_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */
extern void app_main (void *arg);

extern uint64_t app_main_stk[];
extern const osThreadAttr_t app_main_attr;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
