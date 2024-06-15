/*
 * Copyright (C) 2017 Obermaier Johannes
 * Copyright (C) 2022 Lucas Teske
 *
 * This Source Code Form is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed with this file,
 * you can obtain one at https://opensource.org/licenses/MIT
 */

#pragma once

#include <stdint.h>

#include "Arduino.h"

#define BUTTON1_Pin 4
#define LED1_Pin 25
#define TARGET_RESET_Pin 27
#define TARGET_PWR_Pin 26
#define SWDIO_Pin 14
#define SWCLK_Pin 15

#define MAX_READ_ATTEMPTS (100u)

// Sometimes dummy value is received instead of valid data,
// set DUMMY_READ_ATTEMPTS to > 0 value to enable readout retrying
// until other value is received, or attempts limit is reached,
// when limit is reached assume that DUMMY_VALUE is valid data
#define DUMMY_READ_ATTEMPTS (0u)
#define DUMMY_VALUE (0x40021000)

#define POWER_ON_WAIT 5
#define POWER_OFF_WAIT 1

/* all times in milliseconds */
/* minimum wait time between reset deassert and attack */
/* With my test devices this works as 0. Obermaier's default is 20 */
// #define DELAY_JITTER_MS_MIN (20u)
#define DELAY_JITTER_MS_MIN (0)
/* increment per failed attack */
#define DELAY_JITTER_MS_INCREMENT (1u)
/* maximum wait time between reset deassert and attack */
#define DELAY_JITTER_MS_MAX (50u)

void targetInit(void);

void targetReset(void);

void targetRestore(void);

void targetPowerOff(void);

void targetPowerOn(void);