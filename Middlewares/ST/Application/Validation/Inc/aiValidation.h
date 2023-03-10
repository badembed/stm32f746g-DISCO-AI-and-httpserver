/**
  ******************************************************************************
  * @file    aiValidation.h
  * @author  MCD Vertical Application Team
  * @brief   AI Validation application
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) YYYY STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

#ifndef __AI_VALIDATION_H__
#define __AI_VALIDATION_H__

#include <stdint.h>
#include "aiPbMgr.h"
#include "app_x-cube-ai.h"
#if defined(AI_MNETWORK_IN_1_SIZE_BYTES)
AI_ALIGNED(4)
static ai_u8 in_data[AI_MNETWORK_IN_1_SIZE_BYTES];

AI_ALIGNED(4)
static ai_u8 out_data[AI_MNETWORK_OUT_1_SIZE_BYTES];
#else
static ai_float in_data[AI_MNETWORK_IN_1_SIZE];
static ai_float out_data[AI_MNETWORK_OUT_1_SIZE];
#endif
#ifdef __cplusplus
extern "C" {
#endif

int aiValidationInit(void);
int aiValidationProcess(void);
void aiValidationDeInit(void);

#ifdef __cplusplus
}
#endif

#endif /* __AI_VALIDATION_H__ */
