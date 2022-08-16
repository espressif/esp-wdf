// Copyright 2022 Espressif Systems (Shanghai) PTE LTD
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

/**
 * @brief Function ID for the ramker
 */
#define RMAKER_NODE_INIT                        0
#define RMAKER_NODE_DEINIT                      1
#define RMAKER_NODE_SET_STR                     2
#define RMAKER_NODE_GET_STR                     3
#define RMAKER_NODE_SET_DEVICE                  4
#define RMAKER_NODE_GET_DEVICE                  5
#define RMAKER_NODE_GET_NODE                    6
#define RMAKER_NODE_GET_INFO                    7
#define RMAKER_DEVICE_CREATE                    8
#define RMAKER_DEVICE_DELETE                    9
#define RMAKER_DEVICE_SET_STR                   10
#define RMAKER_DEVICE_GET_STR                   11
#define RMAKER_DEVICE_SET_PARAM                 12
#define RMAKER_DEVICE_GET_PARAM                 13
#define RMAKER_DEVICE_ADD_CALLBACK              14
#define RMAKER_DEVICE_CB_SRC_TO_STR             15
#define RMAKER_SERVICE_CREATE                   16
#define RMAKER_SERVICE_SYSTEM_ENABLE            17
#define RMAKER_PARAM_CREATE                     18
#define RMAKER_PARAM_DELETE                     19
#define RMAKER_PARAM_SET_STR                    20
#define RMAKER_PARAM_GET_STR                    21
#define RMAKER_PARAM_SET_VAL                    22
#define RMAKER_PARAM_GET_VAL                    23
#define RMAKER_PARAM_ADD_BOUNDS                 24
#define RMAKER_COMMON_RAISE_ALERT               25

/**
 * @brief Node option ID for the ramker
 */
#define RMAKER_NODE_ADD_ATTRIBUTE               0
#define RMAKER_NODE_ADD_FW_VERSION              1
#define RMAKER_NODE_ADD_MODEL                   2
#define RMAKER_NODE_ADD_SUBTYPE                 3
#define RMAKER_NODE_GET_NODE_ID                 4
#define RMAKER_NODE_ADD_DEVICE                  5
#define RMAKER_NODE_REMOVE_DEVICE               6
#define RMAKER_NODE_GET_DEVICE_BY_NAME          7

/**
 * @brief Device option ID for the ramker
 */
#define RMAKER_DEVICE_ADD_ATTRIBUTE             0
#define RMAKER_DEVICE_ADD_SUBTYPE               1
#define RMAKER_DEVICE_ADD_MODEL                 2
#define RMAKER_DEVICE_GET_NAME                  3
#define RMAKER_DEVICE_GET_TYPE                  4
#define RMAKER_DEVICE_ADD_PARAM                 5
#define RMAKER_DEVICE_ASSIGN_PRIMARY_PARAM      6
#define RMAKER_DEVICE_GET_PARAM_BY_TYPE         7
#define RMAKER_DEVICE_GET_PARAM_BY_NAME         8

/**
 * @brief Param option ID for the ramker
 */
#define RMAKER_PARAM_ADD_UI_TYPE                0
#define RMAKER_PARAM_ADD_ARRAY_MAX_COUNT        1
#define RMAKER_PARAM_GET_NAME                   2
#define RMAKER_PARAM_GET_TYPE                   3
#define RMAKER_PARAM_UPDATE                     4
#define RMAKER_PARAM_UPDATE_AND_REPORT          5
#define RMAKER_PARAM_UPDATE_AND_NOTIFY          6

/**
 * @brief Common option ID for the ramker
 */
#define RMAKER_COMMON_LOCAL_CTRL_START          0
#define RMAKER_COMMON_NODE_DETAILS              1
#define RMAKER_COMMON_OTA_ENABLE                2
#define RMAKER_COMMON_TIMEZONE_ENABLE           3
#define RMAKER_COMMON_SCHEDULE_ENABLE           4
#define RMAKER_COMMON_SCENES_ENABLE             5
#define RMAKER_COMMON_START                     6
#define RMAKER_COMMON_STOP                      7

int wasm_rmaker_run(int mode);
int wasm_rmaker_param_add_valid_str_list(uint32_t param, const char *strs[], uint8_t count);
int wasm_rmaker_call_native_func(int32_t func_id, uint32_t argc, uint32_t *argv);