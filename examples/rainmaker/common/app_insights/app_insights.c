/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <esp_err.h>
#include <esp_log.h>
#ifdef CONFIG_ESP_INSIGHTS_ENABLED
#include <esp_rmaker_mqtt.h>
#include <esp_insights.h>
#include <string.h>
#include <esp_rmaker_core.h>
#include <esp_rmaker_common_events.h>

#if CONFIG_APP_INSIGHTS_ENABLE_LOG_TYPE_ALL
#define APP_INSIGHTS_LOG_TYPE               ESP_DIAG_LOG_TYPE_ERROR \
                                            | ESP_DIAG_LOG_TYPE_WARNING \
                                            | ESP_DIAG_LOG_TYPE_EVENT
#else
#define APP_INSIGHTS_LOG_TYPE               ESP_DIAG_LOG_TYPE_ERROR
#endif /* CONFIG_APP_INSIGHTS_ENABLE_LOG_TYPE_ALL */

esp_err_t esp_insights_enable(esp_insights_config_t *config);

#define INSIGHTS_TOPIC_SUFFIX       "diagnostics/from-node"

static int app_insights_data_send(void *data, size_t len)
{
    char topic[128];
    int msg_id = -1;
    if (data == NULL) {
        return 0;
    }
    char *node_id = esp_rmaker_get_node_id();
    if (!node_id) {
        return -1;
    }
    snprintf(topic, sizeof(topic), "node/%s/%s", node_id, INSIGHTS_TOPIC_SUFFIX);
    esp_rmaker_mqtt_publish(topic, data, len, RMAKER_MQTT_QOS1, &msg_id);
    return msg_id;
}

static void rmaker_common_event_handler(void* arg, esp_event_base_t event_base,
                                        int32_t event_id, void* event_data)
{
    if (event_base != RMAKER_COMMON_EVENT) {
        return;
    }
    esp_insights_transport_event_data_t data;
    switch(event_id) {
        case RMAKER_MQTT_EVENT_PUBLISHED:
            memset(&data, 0, sizeof(data));
            data.msg_id = *(int *)event_data;
            esp_event_post(INSIGHTS_EVENT, INSIGHTS_EVENT_TRANSPORT_SEND_SUCCESS, &data, sizeof(data), portMAX_DELAY);
            break;
#ifdef CONFIG_MQTT_REPORT_DELETED_MESSAGES
        case RMAKER_MQTT_EVENT_MSG_DELETED:
            memset(&data, 0, sizeof(data));
            data.msg_id = *(int *)event_data;
            esp_event_post(INSIGHTS_EVENT, INSIGHTS_EVENT_TRANSPORT_SEND_FAILED, &data, sizeof(data), portMAX_DELAY);
            break;
#endif /* CONFIG_MQTT_REPORT_DELETED_MESSAGES */
        default:
            break;
    }
}
#endif /* CONFIG_ESP_INSIGHTS_ENABLED */

#define TAG "app_insights"

esp_err_t app_insights_enable(void)
{
#ifdef CONFIG_ESP_INSIGHTS_ENABLED
#ifdef CONFIG_ESP_RMAKER_SELF_CLAIM
    ESP_LOGW(TAG, "Nodes with Self Claiming may not be accessible for Insights.");
#endif
    char *node_id = esp_rmaker_get_node_id();

    esp_insights_transport_config_t transport = {
        .callbacks.data_send  = app_insights_data_send,
    };
    esp_insights_transport_register(&transport);

    esp_event_handler_register(RMAKER_COMMON_EVENT, ESP_EVENT_ANY_ID, rmaker_common_event_handler, NULL);

    esp_insights_config_t config = {
        .log_type = APP_INSIGHTS_LOG_TYPE,
        .node_id  = node_id,
    };
    esp_insights_enable(&config);
#else
    ESP_LOGI(TAG, "Enable CONFIG_ESP_INSIGHTS_ENABLED to get Insights.");
#endif /* ! CONFIG_ESP_INSIGHTS_ENABLED */
    return ESP_OK;
}
