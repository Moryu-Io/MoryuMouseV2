/**
  ******************************************************************************
  * File Name          : OPAMP.c
  * Description        : This file provides code for the configuration
  *                      of the OPAMP instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "opamp.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* OPAMP1 init function */
void MX_OPAMP1_Init(void)
{
  LL_OPAMP_InitTypeDef OPAMP_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  /**OPAMP1 GPIO Configuration  
  PA1   ------> OPAMP1_VINP
  PA2   ------> OPAMP1_VOUT
  PA3   ------> OPAMP1_VINM 
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  OPAMP_InitStruct.PowerMode = LL_OPAMP_POWERMODE_NORMAL;
  OPAMP_InitStruct.FunctionalMode = LL_OPAMP_MODE_PGA;
  OPAMP_InitStruct.InputNonInverting = LL_OPAMP_INPUT_NONINVERT_IO0;
  OPAMP_InitStruct.InputInverting = LL_OPAMP_INPUT_INVERT_IO0;
  LL_OPAMP_Init(OPAMP1, &OPAMP_InitStruct);
  LL_OPAMP_SetInputsMuxMode(OPAMP1, LL_OPAMP_INPUT_MUX_DISABLE);
  LL_OPAMP_SetInternalOutput(OPAMP1, LL_OPAMP_INTERNAL_OUPUT_DISABLED);
  LL_OPAMP_SetPGAGain(OPAMP1, LL_OPAMP_PGA_GAIN_2_OR_MINUS_1);
  LL_OPAMP_SetTrimmingMode(OPAMP1, LL_OPAMP_TRIMMING_FACTORY);

}
/* OPAMP2 init function */
void MX_OPAMP2_Init(void)
{
  LL_OPAMP_InitTypeDef OPAMP_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  /**OPAMP2 GPIO Configuration  
  PA5   ------> OPAMP2_VINM
  PA6   ------> OPAMP2_VOUT
  PA7   ------> OPAMP2_VINP 
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  OPAMP_InitStruct.PowerMode = LL_OPAMP_POWERMODE_NORMAL;
  OPAMP_InitStruct.FunctionalMode = LL_OPAMP_MODE_PGA;
  OPAMP_InitStruct.InputNonInverting = LL_OPAMP_INPUT_NONINVERT_IO0;
  OPAMP_InitStruct.InputInverting = LL_OPAMP_INPUT_INVERT_IO0;
  LL_OPAMP_Init(OPAMP2, &OPAMP_InitStruct);
  LL_OPAMP_SetInputsMuxMode(OPAMP2, LL_OPAMP_INPUT_MUX_DISABLE);
  LL_OPAMP_SetInternalOutput(OPAMP2, LL_OPAMP_INTERNAL_OUPUT_DISABLED);
  LL_OPAMP_SetPGAGain(OPAMP2, LL_OPAMP_PGA_GAIN_2_OR_MINUS_1);
  LL_OPAMP_SetTrimmingMode(OPAMP2, LL_OPAMP_TRIMMING_FACTORY);

}
/* OPAMP3 init function */
void MX_OPAMP3_Init(void)
{
  LL_OPAMP_InitTypeDef OPAMP_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  /**OPAMP3 GPIO Configuration  
  PB0   ------> OPAMP3_VINP
  PB1   ------> OPAMP3_VOUT
  PB2   ------> OPAMP3_VINM 
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_0;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  OPAMP_InitStruct.PowerMode = LL_OPAMP_POWERMODE_NORMAL;
  OPAMP_InitStruct.FunctionalMode = LL_OPAMP_MODE_PGA;
  OPAMP_InitStruct.InputNonInverting = LL_OPAMP_INPUT_NONINVERT_IO0;
  OPAMP_InitStruct.InputInverting = LL_OPAMP_INPUT_INVERT_IO0;
  LL_OPAMP_Init(OPAMP3, &OPAMP_InitStruct);
  LL_OPAMP_SetInputsMuxMode(OPAMP3, LL_OPAMP_INPUT_MUX_DISABLE);
  LL_OPAMP_SetInternalOutput(OPAMP3, LL_OPAMP_INTERNAL_OUPUT_DISABLED);
  LL_OPAMP_SetPGAGain(OPAMP3, LL_OPAMP_PGA_GAIN_2_OR_MINUS_1);
  LL_OPAMP_SetTrimmingMode(OPAMP3, LL_OPAMP_TRIMMING_FACTORY);

}
/* OPAMP4 init function */
void MX_OPAMP4_Init(void)
{
  LL_OPAMP_InitTypeDef OPAMP_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  /**OPAMP4 GPIO Configuration  
  PB10   ------> OPAMP4_VINM
  PB11   ------> OPAMP4_VINP
  PB12   ------> OPAMP4_VOUT 
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_11;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_12;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  OPAMP_InitStruct.PowerMode = LL_OPAMP_POWERMODE_NORMAL;
  OPAMP_InitStruct.FunctionalMode = LL_OPAMP_MODE_PGA;
  OPAMP_InitStruct.InputNonInverting = LL_OPAMP_INPUT_NONINVERT_IO2;
  OPAMP_InitStruct.InputInverting = LL_OPAMP_INPUT_INVERT_IO0;
  LL_OPAMP_Init(OPAMP4, &OPAMP_InitStruct);
  LL_OPAMP_SetInputsMuxMode(OPAMP4, LL_OPAMP_INPUT_MUX_DISABLE);
  LL_OPAMP_SetInternalOutput(OPAMP4, LL_OPAMP_INTERNAL_OUPUT_DISABLED);
  LL_OPAMP_SetPGAGain(OPAMP4, LL_OPAMP_PGA_GAIN_2_OR_MINUS_1);
  LL_OPAMP_SetTrimmingMode(OPAMP4, LL_OPAMP_TRIMMING_FACTORY);

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
