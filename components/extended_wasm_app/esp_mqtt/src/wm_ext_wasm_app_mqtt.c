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

#include "mqtt_client.h"
#include "mqtt_wasm_api.h"

/* Raw MQTT client structure */
typedef struct esp_mqtt_client {
    /* Next MQTT client */
    struct esp_mqtt_client *next;

    /* Handle of the MQTT client */
    uint32_t                handle;

    /* User data */
    void                    *user_data;

    /* Event loop is available */
    esp_event_handler_t     loop_event;

    /* MQTT event type */
    esp_mqtt_event_id_t     loop_event_id;

    /* User data for event loop */
    void                    *loop_event_arg;
} esp_mqtt_client_t;

/* Raw MQTT clients list */
static esp_mqtt_client_t *g_clients = NULL;

#define ATTR_CONTAINER_SET_STRING(key, value) if (value && !attr_container_set_string(&args, key, value)) { goto fail; }
#define ATTR_CONTAINER_SET_UINT16(key, value) if (value && !attr_container_set_uint16(&args, key, value)) { goto fail; }
#define ATTR_CONTAINER_SET_INT(key, value) if (value && !attr_container_set_int(&args, key, value)) { goto fail; }
#define ATTR_CONTAINER_SET_BOOL(key, value) if (value && !attr_container_set_bool(&args, key, value)) { goto fail; }

#define ATTR_CONTAINER_GET_STRING(key, value) if (attr_container_contain_key(args, key)) { value = attr_container_get_as_string(args, key); if (!value) goto fail; }
#define ATTR_CONTAINER_GET_UINT16(key, value) if (attr_container_contain_key(args, key)) { value = attr_container_get_as_uint16(args, key); if (!value) goto fail; }
#define ATTR_CONTAINER_GET_INT(key, value) if (attr_container_contain_key(args, key)) { value = attr_container_get_as_int(args, key); if (!value) goto fail; }
#define ATTR_CONTAINER_GET_BOOL(key, value) if (attr_container_contain_key(args, key)) { value = attr_container_get_as_bool(args, key); if (!value) goto fail; }

ESP_EVENT_DEFINE_BASE(MQTT_EVENTS);

static attr_container_t *esp_mqtt_client_config_pack(const esp_mqtt_client_config_t *config)
{
    bool container_set_flag = false;
    attr_container_t *args = attr_container_create("");
    if (!args) {
        return args;
    }

    ATTR_CONTAINER_SET_STRING(MQTT_HOST, config->broker.address.hostname)
    ATTR_CONTAINER_SET_STRING(MQTT_URI, config->broker.address.uri)
    ATTR_CONTAINER_SET_UINT16(MQTT_PORT, config->broker.address.port)
    ATTR_CONTAINER_SET_STRING(MQTT_CLIENT_ID, config->credentials.client_id)
    ATTR_CONTAINER_SET_STRING(MQTT_USERNAME, config->credentials.username)
    ATTR_CONTAINER_SET_STRING(MQTT_PASSWORD, config->credentials.authentication.password)
    ATTR_CONTAINER_SET_STRING(MQTT_LWT_TOPIC, config->session.last_will.topic)
    ATTR_CONTAINER_SET_STRING(MQTT_LWT_MSG, config->session.last_will.msg)
    ATTR_CONTAINER_SET_INT(MQTT_LWT_QOS, config->session.last_will.qos)
    ATTR_CONTAINER_SET_INT(MQTT_LWT_RETAIN, config->session.last_will.retain)
    ATTR_CONTAINER_SET_INT(MQTT_LWT_MSG_LEN, config->session.last_will.msg_len)
    ATTR_CONTAINER_SET_INT(MQTT_DISABLE_CLEAN_SESSION, config->session.disable_clean_session)
    ATTR_CONTAINER_SET_INT(MQTT_KEEPALIVE, config->session.keepalive)
    ATTR_CONTAINER_SET_BOOL(MQTT_DISABLE_AUTO_RECONNECT, config->network.disable_auto_reconnect)
    ATTR_CONTAINER_SET_STRING(MQTT_CERT_PEM, config->broker.verification.certificate)
    ATTR_CONTAINER_SET_UINT16(MQTT_CERT_LEN, config->broker.verification.certificate_len)
    ATTR_CONTAINER_SET_STRING(MQTT_CLIENT_CERT_PEM, config->credentials.authentication.certificate)
    ATTR_CONTAINER_SET_UINT16(MQTT_CLIENT_CERT_LEN, config->credentials.authentication.certificate_len)
    ATTR_CONTAINER_SET_STRING(MQTT_CLIENT_KEY_PEM, config->credentials.authentication.key)
    ATTR_CONTAINER_SET_UINT16(MQTT_CLIENT_KEY_LEN, config->credentials.authentication.key_len)
    ATTR_CONTAINER_SET_STRING(MQTT_CLIENTKEY_PASSWORD, config->credentials.authentication.key_password)
    ATTR_CONTAINER_SET_UINT16(MQTT_CLIENTKEY_PASSWORD_LEN, config->credentials.authentication.key_password_len)
    ATTR_CONTAINER_SET_STRING(MQTT_URI_PATH, config->broker.address.path)
    container_set_flag = true;

fail:
    if (!container_set_flag) {
        attr_container_destroy(args);
        args = NULL;
    }

    return args;
}

esp_mqtt_client_handle_t esp_mqtt_client_init(const esp_mqtt_client_config_t *config)
{
    if (!config) {
        return NULL;
    }

    attr_container_t *args = esp_mqtt_client_config_pack(config);
    if (!args) {
        return NULL;
    }

    uint32_t handle, args_len = attr_container_get_serialize_length(args);
    
    int ret = wasm_mqtt_init(&handle, args);
    attr_container_destroy(args);
    if (ret == -1) {
        return NULL;
    }

    esp_mqtt_client_t *client = (esp_mqtt_client_t *)malloc(sizeof(esp_mqtt_client_t));
    if (client == NULL) {
        wasm_mqtt_destory(handle);
        return NULL;
    }

    memset(client, 0, sizeof(esp_mqtt_client_t));
    client->handle = handle;

    if (g_clients != NULL) {
        client->next = g_clients;
        g_clients = client;
    } else {
        g_clients = client;
    }

    return client;
}

esp_err_t esp_mqtt_client_set_uri(esp_mqtt_client_handle_t client, const char *uri)
{
    if (!client) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_mqtt_set_uri(client->handle, uri);
}

esp_err_t esp_mqtt_client_start(esp_mqtt_client_handle_t client)
{
    if (!client) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_mqtt_start(client->handle);
}

esp_err_t esp_mqtt_client_reconnect(esp_mqtt_client_handle_t client)
{
    if (!client) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_mqtt_reconnect(client->handle);
}

esp_err_t esp_mqtt_client_disconnect(esp_mqtt_client_handle_t client)
{
    if (!client) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_mqtt_disconnect(client->handle);
}

esp_err_t esp_mqtt_client_stop(esp_mqtt_client_handle_t client)
{
    if (!client) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_mqtt_stop(client->handle);
}

int esp_mqtt_client_subscribe_multiple(esp_mqtt_client_handle_t client,
                                       const esp_mqtt_topic_t *topic_list, int size)
{
    if (!client) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_mqtt_subscribe(client->handle, topic_list->filter, topic_list->qos);
}

int esp_mqtt_client_subscribe_single(esp_mqtt_client_handle_t client, const char *topic, int qos)
{
    esp_mqtt_topic_t user_topic = {.filter = topic, .qos = qos};
    return esp_mqtt_client_subscribe_multiple(client, &user_topic, 1);
}

esp_err_t esp_mqtt_client_unsubscribe(esp_mqtt_client_handle_t client, const char *topic)
{
    if (!client) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_mqtt_unsubscribe(client->handle, topic);
}

esp_err_t esp_mqtt_client_publish(esp_mqtt_client_handle_t client, const char *topic, const char *data, int len, int qos, int retain)
{
    if (!client) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_mqtt_publish(client->handle, topic, (void *)data, len, qos);
}

int esp_mqtt_client_enqueue(esp_mqtt_client_handle_t client, const char *topic, const char *data, int len, int qos, int retain, bool store)
{
    if (!client) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_mqtt_enqueue(client->handle, topic, data, len, qos, retain, store);
}

esp_err_t esp_mqtt_client_destroy(esp_mqtt_client_handle_t client)
{
    if (!client) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_mqtt_destory(client->handle);
}

esp_err_t esp_mqtt_set_config(esp_mqtt_client_handle_t client, const esp_mqtt_client_config_t *config)
{
    if (!client) {
        return ESP_ERR_INVALID_ARG;
    }

    attr_container_t *args = esp_mqtt_client_config_pack(config);
    if (!args) {
        return ESP_ERR_NO_MEM;
    }

    wasm_mqtt_config(client->handle, args);

    attr_container_destroy(args);

    return ESP_OK;
}

esp_err_t esp_mqtt_client_register_event(esp_mqtt_client_handle_t client, esp_mqtt_event_id_t event, esp_event_handler_t event_handler, void *event_handler_arg)
{
    if (!client) {
        return ESP_ERR_INVALID_ARG;
    }

    client->loop_event = event_handler;
    client->loop_event_id = event;
    client->user_data = event_handler_arg;

    return ESP_OK;
}

int esp_mqtt_client_get_outbox_size(esp_mqtt_client_handle_t client)
{
    if (!client) {
        return ESP_ERR_INVALID_ARG;
    }

    return wasm_mqtt_get_outbox_size(client->handle);
}

void on_mqtt_dispatch_event(uint32 handle, char *buffer, uint32 len)
{
    esp_mqtt_client_t *client = g_clients;
    esp_mqtt_event_t mqtt_event[1];
    
    while (client != NULL) {
        if (client->handle == handle) {
            attr_container_t *args = (attr_container_t *)buffer;
            mqtt_event->client = client;

            /* On error event, the event id is zero */
            if (attr_container_contain_key(args, MQTT_EVENT_ATTR_ID)){
                mqtt_event->event_id = attr_container_get_as_uint16(args, MQTT_EVENT_ATTR_ID);
            }

            /* Length of the data must not be zero */
            ATTR_CONTAINER_GET_INT(MQTT_EVENT_ATTR_DATA_LEN, mqtt_event->data_len)
            if (attr_container_contain_key(args, MQTT_EVENT_ATTR_DATA)){
                ATTR_CONTAINER_GET_INT(MQTT_EVENT_ATTR_RETAIN, mqtt_event->retain)
                ATTR_CONTAINER_GET_INT(MQTT_EVENT_ATTR_TOTAL_LEN, mqtt_event->total_data_len)
                ATTR_CONTAINER_GET_INT(MQTT_EVENT_ATTR_DATA_OFFSET, mqtt_event->current_data_offset)
                ATTR_CONTAINER_GET_INT(MQTT_EVENT_ATTR_QOS, mqtt_event->qos)
                ATTR_CONTAINER_GET_INT(MQTT_EVENT_ATTR_DUP, mqtt_event->dup)
                char *data = attr_container_get_as_string(args, MQTT_EVENT_ATTR_DATA);
                if (data) {
                    mqtt_event->data = malloc(mqtt_event->data_len + 1);
                    if (!mqtt_event->data) {
                        break;
                    }
                    memset(mqtt_event->data, 0, mqtt_event->data_len + 1);
                    memcpy(mqtt_event->data, data, mqtt_event->data_len);
                } else {
                    break;
                }
            }

            /* Length of the topic must not be zero */
            ATTR_CONTAINER_GET_INT(MQTT_EVENT_ATTR_TOPIC_LEN, mqtt_event->topic_len)
            if (attr_container_contain_key(args, MQTT_EVENT_ATTR_TOPIC)){
                char *topic = attr_container_get_as_string(args, MQTT_EVENT_ATTR_TOPIC);
                if (topic) {
                    mqtt_event->topic = malloc(mqtt_event->topic_len + 1);
                    if (!mqtt_event->topic) {
                        break;
                    }
                    memset(mqtt_event->topic, 0, mqtt_event->topic_len + 1);
                    memcpy(mqtt_event->topic, topic, mqtt_event->topic_len);
                } else {
                    break;
                }
            }

            /* MQTT messaged id and session present flag of message must not be zero */
            ATTR_CONTAINER_GET_INT(MQTT_EVENT_ATTR_MSG_ID, mqtt_event->msg_id)
            ATTR_CONTAINER_GET_INT(MQTT_EVENT_ATTR_SESSION, mqtt_event->session_present)
            if (attr_container_contain_key(args, MQTT_EVENT_ATTR_ERROR_CODE)){
                uint32_t length = sizeof(esp_mqtt_error_codes_t);
                const int8_t *error_handle = attr_container_get_as_bytearray(args, MQTT_EVENT_ATTR_ERROR_CODE, &length);
                if (error_handle) {
                    mqtt_event->error_handle = malloc(sizeof(esp_mqtt_error_codes_t));
                    if (!mqtt_event->error_handle) {
                        break;
                    }
                    memset(mqtt_event->error_handle, 0, sizeof(esp_mqtt_error_codes_t));
                    memcpy(mqtt_event->error_handle, error_handle, sizeof(esp_mqtt_error_codes_t));
                }
            }

            if (client->loop_event) {
                client->loop_event(client->loop_event_arg, MQTT_EVENTS, mqtt_event->event_id, mqtt_event);
            }

            break;
        }
        client = client->next;
    }

fail:
    if (mqtt_event->topic) {
        free(mqtt_event->topic);
    }

    if (mqtt_event->data) {
        free(mqtt_event->data);
    }

    if (mqtt_event->error_handle) {
        free(mqtt_event->error_handle);
    }

    return;
}
