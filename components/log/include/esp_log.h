/*
 * SPDX-FileCopyrightText: 2015-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __ESP_LOG_H__
#define __ESP_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_LOGE(TAG, ...) printf(__VA_ARGS__); printf("\r\n");
#define ESP_LOGI(TAG, ...) printf(__VA_ARGS__); printf("\r\n");
#define ESP_LOGW(TAG, ...) printf(__VA_ARGS__); printf("\r\n");

#ifdef __cplusplus
}
#endif


#endif /* __ESP_LOG_H__ */