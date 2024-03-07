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

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "sdkconfig.h"
#include "mqtt_client.h"

#if CONFIG_BROKER_CERTIFICATE_OVERRIDDEN == 1
static const uint8_t mqtt_eclipseprojects_io_pem_start[]  = "-----BEGIN CERTIFICATE-----\n" CONFIG_BROKER_CERTIFICATE_OVERRIDE "\n-----END CERTIFICATE-----";
#else
extern const uint8_t mqtt_eclipseprojects_io_pem_start[]   asm("_binary_mqtt_eclipseprojects_io_pem_start");
#endif
extern const uint8_t mqtt_eclipseprojects_io_pem_end[]   asm("_binary_mqtt_eclipseprojects_io_pem_end");

/*
 * @brief Event handler registered to receive MQTT events
 *
 *  This function is called by the MQTT client event loop.
 *
 * @param handler_args user data registered to the event.
 * @param base Event base for the handler(always MQTT Base in this example).
 * @param event_id The id for the received event.
 * @param event_data The data for the event, esp_mqtt_event_handle_t.
 */
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    printf("Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:
            printf("MQTT_EVENT_CONNECTED\r\n");
            msg_id = esp_mqtt_client_subscribe(event->client, "/topic/qos0", 0);
            printf("sent subscribe successful, msg_id=%d\r\n", msg_id);
            msg_id = esp_mqtt_client_subscribe(event->client, "/topic/qos1", 0);
            printf("sent subscribe successful, msg_id=%d\r\n", msg_id);
            msg_id = esp_mqtt_client_unsubscribe(event->client, "/topic/qos1");
            printf("sent unsubscribe successful, msg_id=%d\r\n", msg_id);
            break;
        case MQTT_EVENT_DISCONNECTED:
            printf("MQTT_EVENT_DISCONNECTED\r\n");
            break;
        case MQTT_EVENT_SUBSCRIBED:
            printf("MQTT_EVENT_SUBSCRIBED, msg_id=%d\r\n", event->msg_id);
            msg_id = esp_mqtt_client_publish(event->client, "/topic/qos0", "data", 0, 0, 0);
            printf("sent publish successful, msg_id=%d\r\n", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            printf("MQTT_EVENT_UNSUBSCRIBED, msg_id=%d\r\n", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            printf("MQTT_EVENT_PUBLISHED, msg_id=%d\r\n", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            printf("MQTT_EVENT_DATA\r\n");
            if (event->topic) {
                printf("TOPIC=%s\r\n", event->topic);
            }
            printf("DATA=%s\r\n", event->data);
            break;
        case MQTT_EVENT_ERROR:
            printf("MQTT_EVENT_ERROR\r\n");
            if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
                printf("Last error code reported from esp-tls: 0x%x\r\n", event->error_handle->esp_tls_last_esp_err);
                printf("Last tls stack error number: 0x%x\r\n", event->error_handle->esp_tls_stack_err);
                printf("Last captured errno : %d\r\n",  event->error_handle->esp_transport_sock_errno);
            } else if (event->error_handle->error_type == MQTT_ERROR_TYPE_CONNECTION_REFUSED) {
                printf("Connection refused error: 0x%x\r\n", event->error_handle->connect_return_code);
            } else {
                printf("Unknown error type: 0x%x\r\n", event->error_handle->error_type);
            }
            break;
        default:
            printf("Other event id:%d\r\n", event->event_id);
            break;
    }
}

static void mqtt_app_start(void)
{
    const esp_mqtt_client_config_t mqtt_cfg = {
        .broker = {
            .address.uri = CONFIG_BROKER_URI,
#if CONFIG_SSL_BROKER_URI || CONFIG_WSS_BROKER_URI
            .verification.certificate = (const char *)mqtt_eclipseprojects_io_pem_start
#endif
        },
    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}

void on_init()
{
    mqtt_app_start();
}

void on_destroy()
{
    /* real destroy work including destroying mqtt is accomplished
       in wasm app library version of on_destroy() */
}

int main(int argc, char *argv[])
{
    on_init();

    return 0;
}