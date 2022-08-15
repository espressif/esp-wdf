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

#include "bh_platform.h"
#include "bi-inc/attr_container.h"

/**
 * @brief Function ID for the HTTP client
 */
#define HTTP_CLIENT_INIT                0
#define HTTP_CLIENT_SET_STR             1
#define HTTP_CLIENT_GET_STR             2
#define HTTP_CLIENT_SET_INT             3
#define HTTP_CLIENT_GET_INT             4
#define HTTP_CLIENT_COMMON              5

/**
 * @brief Set string ID for the HTTP client
 */
#define HTTP_CLIENT_SET_URL             0
#define HTTP_CLIENT_SET_POST_FILED      1
#define HTTP_CLIENT_SET_HEADER          2
#define HTTP_CLIENT_SET_USERNAME        3
#define HTTP_CLIENT_SET_PASSWORD        4
#define HTTP_CLIENT_DELETE_HEADER       5
#define HTTP_CLIENT_WRITE_DATA          6

/**
 * @brief Get string ID for the HTTP client
 */

#define HTTP_CLIENT_GET_POST_FILED      0
#define HTTP_CLIENT_GET_HEADER          1
#define HTTP_CLIENT_GET_USERNAME        2
#define HTTP_CLIENT_GET_PASSWORD        3
#define HTTP_CLIENT_READ_DATA           4
#define HTTP_CLIENT_READ_RESP           5
#define HTTP_CLIENT_GET_URL             6

/**
 * @brief Set value ID for the HTTP client
 */
#define HTTP_CLIENT_SET_AUTHTYPE        0
#define HTTP_CLIENT_SET_METHOD          1
#define HTTP_CLIENT_SET_TIMEOUT         2
#define HTTP_CLIENT_OPEN                3

/**
 * @brief Get value ID for the HTTP client
 */
#define HTTP_CLIENT_GET_ERRNO           0
#define HTTP_CLIENT_FETCH_HEADER        1
#define HTTP_CLIENT_IS_CHUNKED          2
#define HTTP_CLIENT_GET_STATUS_CODE     3
#define HTTP_CLIENT_GET_CONTENT_LENGTH  4
#define HTTP_CLIENT_GET_TRANSPORT_TYPE  5
#define HTTP_CLIENT_IS_COMPLETE         6
#define HTTP_CLIENT_FLUSH_RESPONSE      7
#define HTTP_CLIENT_GET_CHUNK_LENGTH    8

/**
 * @brief Common ID for the HTTP client
 */
#define HTTP_CLIENT_PERFORM             0
#define HTTP_CLIENT_CLOSE               1
#define HTTP_CLIENT_CLEANUP             2
#define HTTP_CLIENT_SET_REDIRECTION     3
#define HTTP_CLIENT_ADD_AUTH            4

int wasm_http_client_call_native_func(int32_t func_id, uint32_t argc, uint32_t *argv);
