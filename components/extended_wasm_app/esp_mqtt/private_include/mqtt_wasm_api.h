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

#ifndef _MQTT_WASM_API_H_
#define _MQTT_WASM_API_H_

#include "bh_platform.h"
#include "bi-inc/attr_container.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MQTT_HOST                   "host"                      /*!< MQTT server domain (ipv4 as string) */
#define MQTT_URI                    "uri"                       /*!< MQTT broker URI (string) */
#define MQTT_PORT                   "port"                      /*!< MQTT server port ()*/
#define MQTT_CLIENT_ID              "client_id"                 /*!< MQTT client id (string) */
#define MQTT_USERNAME               "username"                  /*!< MQTT username (string) */
#define MQTT_PASSWORD               "password"                  /*!< MQTT password (string) */
#define MQTT_LWT_TOPIC              "lwt_topic"                 /*!< MQTT LWT (Last Will and Testament) message topic (string) */
#define MQTT_LWT_MSG                "lwt_msg"                   /*!< MQTT LWT message (string, NULL by default) */
#define MQTT_LWT_QOS                "lwt_qos"                   /*!< MQTT LWT message qos () */
#define MQTT_LWT_RETAIN             "lwt_retain"                /*!< MQTT LWT retained message flag () */
#define MQTT_LWT_MSG_LEN            "lwt_msg_len"               /*!< MQTT LWT message length () */
#define MQTT_DISABLE_CLEAN_SESSION  "disable_clean_session"     /*!< MQTT clean session (default clean_session is true) */
#define MQTT_KEEPALIVE              "keepalive"                 /*!< MQTT keepalive (default is 120 seconds) */
#define MQTT_DISABLE_AUTO_RECONNECT "disable_auto_reconnect"    /*!< MQTT client will reconnect to server (when errors/disconnect). Set disable_auto_reconnect=true to disable */
#define MQTT_CERT_PEM               "cert_pem"                  /*!< MQTT certificate data in PEM or DER format for server verify (with SSL, default is NULL), not required to verify the server. PEM-format must have a terminating NULL-character. DER-format requires the length to be passed in cert_len. */
#define MQTT_CERT_LEN               "cert_len"                  /*!< Length of the cert_pem. May be 0 for null-terminated pem () */
#define MQTT_CLIENT_CERT_PEM        "client_cert_pem"           /*!< MQTT certificate data in PEM or DER format for SSL mutual authentication, default is NULL, not required if mutual authentication is not needed. If it is not NULL, also `client_key_pem` has to be provided. PEM-format must have a terminating NULL-character. DER-format requires the length to be passed in client_cert_len. */
#define MQTT_CLIENT_CERT_LEN        "client_cert_len"           /*!< Length of the client_cert_pem. May be 0 for null-terminated pem () */
#define MQTT_CLIENT_KEY_PEM         "client_key_pem"            /*!< MQTT private key data in PEM or DER format for SSL mutual authentication, default is NULL, not required if mutual authentication is not needed. If it is not NULL, also `client_cert_pem` has to be provided. PEM-format must have a terminating NULL-character. DER-format requires the length to be passed in client_key_len */
#define MQTT_CLIENT_KEY_LEN         "client_key_len"            /*!< Length of the client_key_pem. May be 0 for null-terminated pem () */
#define MQTT_CLIENTKEY_PASSWORD     "clientkey_password"       /*!< MQTT Client key decryption password string (string) */
#define MQTT_CLIENTKEY_PASSWORD_LEN "clientkey_password_len"   /*!< Length of the clientkey_password () */
#define MQTT_URI_PATH               "path"                      /*!< MQTT Path in the URI (string) */
#define MQTT_EVENT_ATTR_ID          "event_id"                  /*!< MQTT event type */
#define MQTT_EVENT_ATTR_DATA        "data"                      /*!< MQTT Data associated with this event */
#define MQTT_EVENT_ATTR_DATA_LEN    "data_len"                  /*!< Length of the data for this event */
#define MQTT_EVENT_ATTR_TOTAL_LEN   "total_len"                 /*!< Total Length of the data for this event */
#define MQTT_EVENT_ATTR_DATA_OFFSET "offset"                    /*!< Actual offset for the data associated with this event */
#define MQTT_EVENT_ATTR_TOPIC       "topic"                     /*!< MQTT Topic associated with this event */
#define MQTT_EVENT_ATTR_TOPIC_LEN   "topic_len"                 /*!< Length of the topic for this event associated with this event */
#define MQTT_EVENT_ATTR_MSG_ID      "msg_id"                    /*!< MQTT messaged id of message */
#define MQTT_EVENT_ATTR_SESSION     "session"                   /*!< MQTT session_present flag for connection event */
#define MQTT_EVENT_ATTR_ERROR_CODE  "error_code"                /*!< MQTT error handle including esp-tls errors as well as internal mqtt errors */
#define MQTT_EVENT_ATTR_RETAIN      "retain"                    /*!< Retained flag of the message associated with this event */

/**
 * @brief Creates mqtt client handle based on the configuration
 *
 * @param args          attribute container for mqtt configuration
 * @param mqtt_handle   mqtt client handle
 *
 * @return ESP_OK
 *         ESP_ERR_INVALID_ARG on wrong initialization
 *         ESP_FAIL on other error
 */
int wasm_mqtt_init(uint32_t *mqtt_handle, attr_container_t *args);

/**
 * @brief Destroys the mqtt client handle
 *
 * Notes:
 *  - Cannot be called from the mqtt event handler
 *
 * @param mqtt_handle    mqtt client handle
 *
 * @return ESP_OK
 *         ESP_ERR_INVALID_ARG on wrong initialization
 *         ESP_FAIL on other error
 */
int wasm_mqtt_destory(uint32_t mqtt_handle);

/**
 * @brief Starts mqtt client with already created client handle
 *
 * @param mqtt_handle    mqtt client handle
 *
 * @return ESP_OK on success
 *         ESP_ERR_INVALID_ARG on wrong initialization
 *         ESP_FAIL on other error
 */
int wasm_mqtt_start(uint32_t mqtt_handle);

/**
 * @brief Stops mqtt client tasks
 *
 *  * Notes:
 *  - Cannot be called from the mqtt event handler
 *
 * @param mqtt_handle    mqtt client handle
 *
 * @return ESP_OK on success
 *         ESP_ERR_INVALID_ARG on wrong initialization
 *         ESP_FAIL if client is in invalid state
 */
int wasm_mqtt_stop(uint32_t mqtt_handle);

/**
 * @brief This api is typically used to force reconnection upon a specific event
 *
 * @param mqtt_handle    mqtt client handle
 *
 * @return ESP_OK on success
 *         ESP_ERR_INVALID_ARG on wrong initialization
 *         ESP_FAIL if client is in invalid state
 */
int wasm_mqtt_reconnect(uint32_t mqtt_handle);

/**
 * @brief This api is typically used to force disconnection from the broker
 *
 * @param mqtt_handle    mqtt client handle
 *
 * @return ESP_OK on success
 *         ESP_ERR_INVALID_ARG on wrong initialization
 *         ESP_FAIL if client is in invalid state
 */
int wasm_mqtt_disconnect(uint32_t mqtt_handle);

/**
 * @brief Client send a publish message to the broker
 *
 * Notes:
 * - This API might block for several seconds, either due to network timeout (10s)
 *   or if publishing payloads longer than internal buffer (due to message
 *   fragmentation)
 * - Client doesn't have to be connected for this API to work, enqueueing the messages
 *   with qos>1 (returning -1 for all the qos=0 messages if disconnected).
 *   If MQTT_SKIP_PUBLISH_IF_DISCONNECTED is enabled, this API will not attempt to publish
 *   when the client is not connected and will always return -1.
 * - It is thread safe, please refer to `wasm_mqtt_subscribe` for details
 *
 * @param mqtt_handle    mqtt client handle
 * @param topic          topic string
 * @param data           payload string (set to NULL, sending empty payload message)
 * @param len            data length, if set to 0, length is calculated from payload string
 * @param qos            qos of publish message
 * @param retain         retain flag
 *
 * @return message_id of the publish message (for QoS 0 message_id will always be zero) on success.
 *         -1 on failure.
 */
int wasm_mqtt_publish(uint32_t mqtt_handle, const char *topic, void *data, size_t data_len, uint8_t qos);

/**
 * @brief Subscribe the client to defined topic with defined qos
 *
 * Notes:
 * - Client must be connected to send subscribe message
 * - This API is could be executed from a user task or
 * from a mqtt event callback i.e. internal mqtt task
 * (API is protected by internal mutex, so it might block
 * if a longer data receive operation is in progress.
 *
 * @param mqtt_handle    mqtt client handle
 * @param topic          topic string
 * @param qos            qos of subscribe message
 *
 * @return message_id of the subscribe message on success
 *         -1 on failure
 */
int wasm_mqtt_subscribe(uint32_t mqtt_handle, const char *topic, uint8_t qos);

/**
 * @brief Unsubscribe the client from defined topic
 *
 * Notes:
 * - Client must be connected to send unsubscribe message
 * - It is thread safe, please refer to `wasm_mqtt_subscribe` for details
 *
 * @param mqtt_handle    mqtt client handle
 * @param topic          topic string
 *
 * @return message_id of the subscribe message on success
 *         -1 on failure
 */
int wasm_mqtt_unsubscribe(uint32_t mqtt_handle, const char *topic);

/**
 * @brief Enqueue a message to the outbox, to be sent later. Typically used for messages with qos>0, but could
 * be also used for qos=0 messages if store=true.
 *
 * This API generates and stores the publish message into the internal outbox and the actual sending
 * to the network is performed in the mqtt-task context (in contrast to the wasm_mqtt_publish()
 * which sends the publish message immediately in the user task's context).
 * Thus, it could be used as a non blocking version of wasm_mqtt_publish().
 *
 * @param mqtt_handle    mqtt client handle
 * @param topic          topic string
 * @param data           payload string (set to NULL, sending empty payload message)
 * @param len            data length, if set to 0, length is calculated from payload string
 * @param qos            qos of publish message
 * @param retain         retain flag
 * @param store          if true, all messages are enqueued; otherwise only qos1 and qos 2 are enqueued
 *
 * @return message_id if queued successfully, -1 otherwise
 */
int wasm_mqtt_enqueue(uint32_t mqtt_handle, const char *topic, const char *data, int len, int qos, int retain, bool store);

/**
 * @brief Sets mqtt broker URI. This API is usually used to overrides the URI
 * configured in wasm_mqtt_init
 *
 * @param mqtt_handle    mqtt client handle
 * @param uri            mqtt broker URI
 *
 * @return ESP_FAIL if URI parse error, ESP_OK on success
 */
int wasm_mqtt_set_uri(uint32_t mqtt_handle, const char *uri);

/**
 * @brief Set mqtt configuration, typically used when updating the config
 *
 * @param mqtt_handle    mqtt client handle
 *
 * @param args           attribute container for mqtt configuration
 *
 * @return ESP_ERR_NO_MEM if failed to allocate
 *         ESP_ERR_INVALID_ARG if conflicts on transport configuration.
 *         ESP_OK on success
 */
int wasm_mqtt_config(uint32_t mqtt_handle, attr_container_t *args);

/**
 * @brief Get outbox size
 *
 * @param mqtt_handle    mqtt client handle
 * @return outbox size
 *         0 on wrong initialization
 */
int wasm_mqtt_get_outbox_size(uint32_t mqtt_handle);

#ifdef __cplusplus
}
#endif

#endif /* end of _MQTT_WASM_API_H_ */
