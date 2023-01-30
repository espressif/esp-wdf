// Copyright 2023 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _LEDCCBASE              (0x8400) /*!< LEDC ioctl command basic value */
#define _LEDCC(nr)              (_LEDCCBASE | (nr)) /*!< LEDC ioctl command macro */

#define LEDCIOCSCFG             _LEDCC(1) /*!< Set LEDC configuration */
#define LEDCIOCSSETFREQ         _LEDCC(2) /*!< Set LEDC frequency */
#define LEDCIOCSSETDUTY         _LEDCC(3) /*!< Set LEDC duty of target channel */
#define LEDCIOCSSETPHASE        _LEDCC(4) /*!< Set LEDC phase of target channel */
#define LEDCIOCSPAUSE           _LEDCC(5) /*!< Set LEDC to pause */
#define LEDCIOCSRESUME          _LEDCC(6) /*!< Set LEDC yo resume from pausing */

/**
 * @brief LEDC channel configuration.
 */
typedef struct ledc_channel_cfg {
    uint8_t output_pin;     /*!< LEDC channel signal output pin */
    uint32_t duty;          /*!< LEDC channel signal duty */
    uint32_t phase;         /*!< LEDC channel signal phase */
} ledc_channel_cfg_t;

/**
 * @brief LEDC configuration.
 */
typedef struct ledc_cfg {
    uint32_t frequency;     /*!< LEDC Frequency */
    uint8_t channel_num;    /*!< LEDC channel number */
    const ledc_channel_cfg_t *channel_cfg; /*!< LEDC channels configuration */
} ledc_cfg_t;

typedef struct ledc_duty_cfg {
    uint8_t channel;
    uint32_t duty;
} ledc_duty_cfg_t;

typedef struct ledc_phase_cfg {
    uint8_t channel;
    uint32_t phase;
} ledc_phase_cfg_t;

#ifdef __cplusplus
}
#endif
