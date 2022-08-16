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

#include <sys/types.h>
#include "wifi_provisioning/manager.h"
#include "wifi_prov_wasm_api.h"

/**
 * scheme_ble
 */
esp_err_t wifi_prov_scheme_ble_set_service_uuid(uint8_t *uuid128)
{
    if (!uuid128) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_wifi_prov_scheme_ble_set_service_uuid(uuid128);
}

esp_err_t wifi_prov_scheme_ble_set_mfg_data(uint8_t *mfg_data, ssize_t mfg_data_len)
{
    if (!mfg_data || !mfg_data_len) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_wifi_prov_scheme_ble_set_mfg_data(mfg_data, mfg_data_len);
}

/**
 * scheme_softap
 */
void wifi_prov_scheme_softap_set_httpd_handle(void *handle)
{
    //Todo
}

/**
 * manager
 */
esp_err_t wifi_prov_mgr_init(wifi_prov_mgr_config_t config)
{
    uint32_t argv[2] = {
        (uint32_t)config.app_event_handler.event_cb,
        (uint32_t)config.app_event_handler.user_data
    };

    return wasm_wifi_prov_mgr_init((uint32_t)config.scheme, sizeof(argv) / sizeof(argv[0]), argv);
}

void wifi_prov_mgr_deinit(void)
{
    wasm_wifi_prov_mgr_deinit();
}

esp_err_t wifi_prov_mgr_is_provisioned(bool *provisioned)
{
    if (!provisioned) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_wifi_prov_mgr_is_provisioned(provisioned);
}

esp_err_t wifi_prov_mgr_start_provisioning(wifi_prov_security_t security, const char *pop,
                                           const char *service_name, const char *service_key)
{
    if (!service_name) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_wifi_prov_mgr_start_provisioning(security, (uint32_t)pop, service_name, (uint32_t)service_key);
}

void wifi_prov_mgr_stop_provisioning(void)
{
    wasm_wifi_prov_mgr_stop_provisioning();
}

void wifi_prov_mgr_wait(void)
{
    wasm_wifi_prov_mgr_wait();
}

esp_err_t wifi_prov_mgr_disable_auto_stop(uint32_t cleanup_delay)
{
    return wasm_wifi_prov_mgr_disable_auto_stop(cleanup_delay);
}

esp_err_t wifi_prov_mgr_set_app_info(const char *label, const char *version,
                                     const char **capabilities, size_t total_capabilities)
{
    if (!label || !version || !capabilities) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_wifi_prov_mgr_set_app_info(label, version, (uint32_t)capabilities, total_capabilities);
}

esp_err_t wifi_prov_mgr_endpoint_create(const char *ep_name)
{
    if (!ep_name) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_wifi_prov_mgr_endpoint_create(ep_name);
}

esp_err_t wifi_prov_mgr_endpoint_register(const char *ep_name,
                                          protocomm_req_handler_t handler,
                                          void *user_ctx)
{
    if (!ep_name) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_wifi_prov_mgr_endpoint_register(ep_name, (uint32_t)handler, (uint32_t)user_ctx);
}
                                    
void wifi_prov_mgr_endpoint_unregister(const char *ep_name)
{
    if (ep_name) {
        wasm_wifi_prov_mgr_endpoint_unregister(ep_name);
    }
}

esp_err_t wifi_prov_mgr_get_wifi_state(wifi_prov_sta_state_t *state)
{
    if (!state) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_wifi_prov_mgr_get_wifi_state((uint32_t)state);
}

esp_err_t wifi_prov_mgr_get_wifi_disconnect_reason(wifi_prov_sta_fail_reason_t *reason)
{
    if (!reason) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_wifi_prov_mgr_get_wifi_disconnect_reason((uint32_t)reason);
}

esp_err_t wifi_prov_mgr_configure_sta(wifi_config_t *wifi_cfg)
{
    if (!wifi_cfg) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_wifi_prov_mgr_configure_sta((uint32_t)wifi_cfg);
}

esp_err_t wifi_prov_mgr_reset_provisioning(void)
{
    return wasm_wifi_prov_mgr_reset_provisioning();
}

esp_err_t wifi_prov_mgr_reset_sm_state_on_failure(void)
{
    return wasm_wifi_prov_mgr_reset_sm_state_on_failure();
}