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

#ifndef _WIFI_PROV_WASM_H_
#define _WIFI_PROV_WASM_H_

#include "bh_platform.h"
#include "bi-inc/attr_container.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Initialize provisioning manager instance
 *
 * Configures the manager and allocates internal resources
 *
 * Configuration specifies the provisioning scheme (transport)
 * and event handlers
 *
 * Event WIFI_PROV_INIT is emitted right after initialization
 * is complete
 *
 * @param[in] config Configuration structure
 *
 * @return
 *  - ESP_OK      : Success
 *  - ESP_FAIL    : Fail
 */
int wasm_wifi_prov_mgr_init(uint32_t func_id, uint32_t argc, uint32_t *argv);

/**
 * @brief   Stop provisioning (if running) and release
 *          resource used by the manager
 *
 * Event WIFI_PROV_DEINIT is emitted right after de-initialization
 * is finished
 *
 * If provisioning service is  still active when this API is called,
 * it first stops the service, hence emitting WIFI_PROV_END, and
 * then performs the de-initialization
 */
int wasm_wifi_prov_mgr_deinit(void);

/**
 * @brief   Checks if device is provisioned
 *
 * This checks if Wi-Fi credentials are present on the NVS
 *
 * The Wi-Fi credentials are assumed to be kept in the same
 * NVS namespace as used by esp_wifi component
 *
 * If one were to call esp_wifi_set_config() directly instead
 * of going through the provisioning process, this function will
 * still yield true (i.e. device will be found to be provisioned)
 *
 * @note    Calling wifi_prov_mgr_start_provisioning() automatically
 *          resets the provision state, irrespective of what the
 *          state was prior to making the call.
 *
 * @param[out] provisioned  True if provisioned, else false
 *
 * @return
 *  - ESP_OK      : Retrieved provision state successfully
 *  - ESP_FAIL    : Wi-Fi not initialized
 *  - ESP_ERR_INVALID_ARG   : Null argument supplied
 *  - ESP_ERR_INVALID_STATE : Manager not initialized
 */
int wasm_wifi_prov_mgr_is_provisioned(bool *provisioned);

/**
 * @brief   Start provisioning service
 *
 * This starts the provisioning service according to the scheme
 * configured at the time of initialization. For scheme :
 * - wifi_prov_scheme_ble : This starts protocomm_ble, which internally initializes
 *                          BLE transport and starts GATT server for handling
 *                          provisioning requests
 * - wifi_prov_scheme_softap : This activates SoftAP mode of Wi-Fi and starts
 *                          protocomm_httpd, which internally starts an HTTP
 *                          server for handling provisioning requests (If mDNS is
 *                          active it also starts advertising service with type
 *                          _esp_wifi_prov._tcp)
 *
 * Event WIFI_PROV_START is emitted right after provisioning starts without failure
 *
 * @note   This API will start provisioning service even if device is found to be
 *         already provisioned, i.e. wifi_prov_mgr_is_provisioned() yields true
 *
 * @param[in] security      Specify which protocomm security scheme to use :
 *                              - WIFI_PROV_SECURITY_0 : For no security
 *                              - WIFI_PROV_SECURITY_1 : x25519 secure handshake for session
 *                                establishment followed by AES-CTR encryption of provisioning messages
 * @param[in] pop           Pointer to proof of possession string (NULL if not needed). This
 *                          is relevant only for protocomm security 1, in which case it is used
 *                          for authenticating secure session
 * @param[in] service_name  Unique name of the service. This translates to:
 *                              - Wi-Fi SSID when provisioning mode is softAP
 *                              - Device name when provisioning mode is BLE
 * @param[in] service_key   Key required by client to access the service (NULL if not needed).
 *                          This translates to:
 *                              - Wi-Fi password when provisioning mode is softAP
 *                              - ignored when provisioning mode is BLE
 *
 * @return
 *  - ESP_OK      : Provisioning started successfully
 *  - ESP_FAIL    : Failed to start provisioning service
 *  - ESP_ERR_INVALID_STATE : Provisioning manager not initialized or already started
 */
int wasm_wifi_prov_mgr_start_provisioning(uint32_t security, uint32_t pop,
                                           const char *service_name, uint32_t service_key);

/**
 * @brief   Stop provisioning service
 *
 * If provisioning service is active, this API will initiate a process to stop
 * the service and return. Once the service actually stops, the event WIFI_PROV_END
 * will be emitted.
 *
 * If wifi_prov_mgr_deinit() is called without calling this API first, it will
 * automatically stop the provisioning service and emit the WIFI_PROV_END, followed
 * by WIFI_PROV_DEINIT, before returning.
 *
 * This API will generally be used along with wifi_prov_mgr_disable_auto_stop()
 * in the scenario when the main application has registered its own endpoints,
 * and wishes that the provisioning service is stopped only when some protocomm
 * command from the client side application is received.
 *
 * Calling this API inside an endpoint handler, with sufficient cleanup_delay,
 * will allow the response / acknowledgment to be sent successfully before the
 * underlying protocomm service is stopped.
 *
 * Cleaup_delay is set when calling wifi_prov_mgr_disable_auto_stop().
 * If not specified, it defaults to 1000ms.
 *
 * For straightforward cases, using this API is usually not necessary as
 * provisioning is stopped automatically once WIFI_PROV_CRED_SUCCESS is emitted.
 * Stopping is delayed (maximum 30 seconds) thus allowing the client side
 * application to query for Wi-Fi state, i.e. after receiving the first query
 * and sending `Wi-Fi state connected` response the service is stopped immediately.
 */
int wasm_wifi_prov_mgr_stop_provisioning(void);

/**
 * @brief   Wait for provisioning service to finish
 *
 * Calling this API will block until provisioning service is stopped
 * i.e. till event WIFI_PROV_END is emitted.
 *
 * This will not block if provisioning is not started or not initialized.
 */
int wasm_wifi_prov_mgr_wait(void);

/**
 * @brief   Disable auto stopping of provisioning service upon completion
 *
 * By default, once provisioning is complete, the provisioning service is automatically
 * stopped, and all endpoints (along with those registered by main application) are
 * deactivated.
 *
 * This API is useful in the case when main application wishes to close provisioning service
 * only after it receives some protocomm command from the client side app. For example, after
 * connecting to Wi-Fi, the device may want to connect to the cloud, and only once that is
 * successfully, the device is said to be fully configured. But, then it is upto the main
 * application to explicitly call wifi_prov_mgr_stop_provisioning() later when the device is
 * fully configured and the provisioning service is no longer required.
 *
 * @note    This must be called before executing wifi_prov_mgr_start_provisioning()
 *
 * @param[in] cleanup_delay Sets the delay after which the actual cleanup of transport related
 *                          resources is done after a call to wifi_prov_mgr_stop_provisioning()
 *                          returns. Minimum allowed value is 100ms. If not specified, this will
 *                          default to 1000ms.
 *
 * @return
 *  - ESP_OK : Success
 *  - ESP_ERR_INVALID_STATE : Manager not initialized or
 *                            provisioning service already started
 */
int wasm_wifi_prov_mgr_disable_auto_stop(uint32_t cleanup_delay);

/**
 * @brief   Set application version and capabilities in the JSON data returned by
 *          proto-ver endpoint
 *
 * This function can be called multiple times, to specify information about the various
 * application specific services running on the device, identified by unique labels.
 *
 * The provisioning service itself registers an entry in the JSON data, by the label "prov",
 * containing only provisioning service version and capabilities. Application services should
 * use a label other than "prov" so as not to overwrite this.
 *
 * @note    This must be called before executing wifi_prov_mgr_start_provisioning()
 *
 * @param[in] label   String indicating the application name.
 *
 * @param[in] version String indicating the application version.
 *                    There is no constraint on format.
 *
 * @param[in] capabilities  Array of strings with capabilities.
 *                          These could be used by the client side app to know
 *                          the application registered endpoint capabilities
 *
 * @param[in] total_capabilities  Size of capabilities array
 *
 * @return
 *  - ESP_OK : Success
 *  - ESP_ERR_INVALID_STATE : Manager not initialized or
 *                            provisioning service already started
 *  - ESP_ERR_NO_MEM : Failed to allocate memory for version string
 *  - ESP_ERR_INVALID_ARG : Null argument
 */
int wasm_wifi_prov_mgr_set_app_info(const char *label, const char *version, uint32_t capabilities, size_t total_capabilities);

/**
 * @brief   Create an additional endpoint and allocate internal resources for it
 *
 * This API is to be called by the application if it wants to create an additional
 * endpoint. All additional endpoints will be assigned UUIDs starting from 0xFF54
 * and so on in the order of execution.
 *
 * protocomm handler for the created endpoint is to be registered later using
 * wifi_prov_mgr_endpoint_register() after provisioning has started.
 *
 * @note    This API can only be called BEFORE provisioning is started
 *
 * @note    Additional endpoints can be used for configuring client provided
 *          parameters other than Wi-Fi credentials, that are necessary for the
 *          main application and hence must be set prior to starting the application
 *
 * @note    After session establishment, the additional endpoints must be targeted
 *          first by the client side application before sending Wi-Fi configuration,
 *          because once Wi-Fi configuration finishes the provisioning service is
 *          stopped and hence all endpoints are unregistered
 *
 * @param[in] ep_name  unique name of the endpoint
 *
 * @return
 *  - ESP_OK      : Success
 *  - ESP_FAIL    : Failure
 */
int wasm_wifi_prov_mgr_endpoint_create(const char *ep_name);

/**
 * @brief   Register a handler for the previously created endpoint
 *
 * This API can be called by the application to register a protocomm handler
 * to any endpoint that was created using wifi_prov_mgr_endpoint_create().
 *
 * @note    This API can only be called AFTER provisioning has started
 *
 * @note    Additional endpoints can be used for configuring client provided
 *          parameters other than Wi-Fi credentials, that are necessary for the
 *          main application and hence must be set prior to starting the application
 *
 * @note    After session establishment, the additional endpoints must be targeted
 *          first by the client side application before sending Wi-Fi configuration,
 *          because once Wi-Fi configuration finishes the provisioning service is
 *          stopped and hence all endpoints are unregistered
 *
 * @param[in] ep_name   Name of the endpoint
 * @param[in] handler   Endpoint handler function
 * @param[in] user_ctx  User data
 *
 * @return
 *  - ESP_OK      : Success
 *  - ESP_FAIL    : Failure
 */
int wasm_wifi_prov_mgr_endpoint_register(const char *ep_name, uint32_t handler, uint32_t user_ctx);

/**
 * @brief   Unregister the handler for an endpoint
 *
 * This API can be called if the application wants to selectively
 * unregister the handler of an endpoint while the provisioning
 * is still in progress.
 *
 * All the endpoint handlers are unregistered automatically when
 * the provisioning stops.
 *
 * @param[in] ep_name  Name of the endpoint
 */
int wasm_wifi_prov_mgr_endpoint_unregister(const char *ep_name);

/**
 * @brief   Get state of Wi-Fi Station during provisioning
 *
 * @param[out] state    Pointer to wifi_prov_sta_state_t
 *                      variable to be filled
 *
 * @return
 *  - ESP_OK    : Successfully retrieved Wi-Fi state
 *  - ESP_FAIL  : Provisioning app not running
 */
int wasm_wifi_prov_mgr_get_wifi_state(uint32_t state);

/**
 * @brief   Get reason code in case of Wi-Fi station
 *          disconnection during provisioning
 *
* @param[out] reason    Pointer to wifi_prov_sta_fail_reason_t
*                       variable to be filled
 *
 * @return
 *  - ESP_OK    : Successfully retrieved Wi-Fi disconnect reason
 *  - ESP_FAIL  : Provisioning app not running
 */
int wasm_wifi_prov_mgr_get_wifi_disconnect_reason(uint32_t reason);

/**
 * @brief   Runs Wi-Fi as Station with the supplied configuration
 *
 * Configures the Wi-Fi station mode to connect to the AP with
 * SSID and password specified in config structure and sets
 * Wi-Fi to run as station.
 *
 * This is automatically called by provisioning service upon
 * receiving new credentials.
 *
 * If credentials are to be supplied to the manager via a
 * different mode other than through protocomm, then this
 * API needs to be called.
 *
 * Event WIFI_PROV_CRED_RECV is emitted after credentials have
 * been applied and Wi-Fi station started
 *
 * @param[in] wifi_cfg  Pointer to Wi-Fi configuration structure
 *
 * @return
 *  - ESP_OK      : Wi-Fi configured and started successfully
 *  - ESP_FAIL    : Failed to set configuration
 */
int wasm_wifi_prov_mgr_configure_sta(uint32_t wifi_cfg);

/**
 * @brief   Reset Wi-Fi provisioning config
 *
 * Calling this API will restore WiFi stack persistent settings to default values.
 *
 * @return
 *  - ESP_OK      : Reset provisioning config successfully
 *  - ESP_FAIL    : Failed to reset provisioning config
 */
int wasm_wifi_prov_mgr_reset_provisioning(void);

/**
 * @brief   Reset internal state machine and clear provisioned credentials.
 *
 * This API can be used to restart provisioning in case invalid credentials are entered.
 *
 * @return
 *  - ESP_OK      : Reset provisioning state machine successfully
 *  - ESP_FAIL    : Failed to reset provisioning state machine
 *  - ESP_ERR_INVALID_STATE : Manager not initialized
 */
int wasm_wifi_prov_mgr_reset_sm_state_on_failure(void);

/**
 * @brief   Set the 128 bit GATT service UUID used for provisioning
 *
 * This API is used to override the default 128 bit provisioning
 * service UUID, which is 0000ffff-0000-1000-8000-00805f9b34fb.
 *
 * This must be called before starting provisioning, i.e. before
 * making a call to wifi_prov_mgr_start_provisioning(), otherwise
 * the default UUID will be used.
 *
 * @note    The data being pointed to by the argument must be valid
 *          atleast till provisioning is started. Upon start, the
 *          manager will store an internal copy of this UUID, and
 *          this data can be freed or invalidated afterwords.
 *
 * @param[in] uuid128  A custom 128 bit UUID
 *
 * @return
 *  - ESP_OK              : Success
 *  - ESP_ERR_INVALID_ARG : Null argument
 */
int wasm_wifi_prov_scheme_ble_set_service_uuid(uint8_t *uuid128);

/**
 * @brief   Set manufacturer specific data in scan response
 *
 * This must be called before starting provisioning, i.e. before
 * making a call to wifi_prov_mgr_start_provisioning().
 *
 * @note    It is important to understand that length of custom manufacturer
 *          data should be within limits. The manufacturer data goes into scan
 *          response along with BLE device name. By default, BLE device name
 *          length is of 11 Bytes, however it can vary as per application use
 *          case. So, one has to honour the scan response data size limits i.e.
 *          (mfg_data_len + 2) < 31 - (device_name_length + 2 ). If the
 *          mfg_data length exceeds this limit, the length will be truncated.
 *
 * @param[in] mfg_data      Custom manufacturer data
 * @param[in] mfg_data_len  Manufacturer data length
 *
 * @return
 *  - ESP_OK              : Success
 *  - ESP_ERR_INVALID_ARG : Null argument
 */
int wasm_wifi_prov_scheme_ble_set_mfg_data(uint8_t *mfg_data, ssize_t mfg_data_len);

#ifdef __cplusplus
}
#endif

#endif /* end of _WIFI_PROV_WASM_H_ */
