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

#include <string.h>
#include <stdlib.h>

#include <esp_http_client.h>
#include <http_client_wasm_api.h>

#define HTTP_CLIENT_CALL_FUNC(id, argv) wasm_http_client_call_native_func(id, \
                                                           sizeof(argv) / sizeof(argv[0]), \
                                                           argv)

struct esp_http_client {
    uint32_t                    handle;
    http_event_handle_cb        event_handler;
    void                        *user_data;

    char                        *post_data;
    char                        *head_value;
    char                        *username;
    char                        *password;
};

static esp_err_t http_dispatch_event(esp_http_client_event_id_t event_id, esp_http_client_handle_t client, uint32_t data, uint32_t dup)
{
    esp_http_client_event_t evt = {
        .event_id = event_id,
        .client = client,
        .user_data = client->user_data
    };

    switch (evt.event_id) {
        case HTTP_EVENT_ON_HEADER:
            evt.header_key = (char *)data;
            evt.header_value = (char *)dup;
            break;
        case HTTP_EVENT_ON_DATA:
        case HTTP_EVENT_DISCONNECTED:
            evt.data = (void *)data;
            evt.data_len = dup;
            break;
        default:
            break;
    }

    return client->event_handler ? client->event_handler(&evt) : ESP_OK;
}

esp_http_client_handle_t esp_http_client_init(const esp_http_client_config_t *config)
{
    if (!config) {
        return NULL;
    }

    esp_http_client_handle_t client = (esp_http_client_handle_t)calloc(1, sizeof(struct esp_http_client));
    if (!client) {
        return NULL;
    }

    client->event_handler = config->event_handler;
    client->user_data = config->user_data;

    uint32_t argv[36] = { 0 };

    argv[0]  = (uint32_t)config->url;
    argv[1]  = (uint32_t)config->host;
    argv[2]  = (uint32_t)config->port;
    argv[3]  = (uint32_t)config->username;
    argv[4]  = (uint32_t)config->password;
    argv[5]  = (uint32_t)config->auth_type;
    argv[6]  = (uint32_t)config->path;
    argv[7]  = (uint32_t)config->query;
    argv[8]  = (uint32_t)config->cert_pem;
    argv[9]  = (uint32_t)config->cert_len;
    argv[10] = (uint32_t)config->client_cert_pem;
    argv[11] = (uint32_t)config->client_cert_len;
    argv[12] = (uint32_t)config->client_key_pem;
    argv[13] = (uint32_t)config->client_key_len;
    argv[14] = (uint32_t)config->client_key_password;
    argv[15] = (uint32_t)config->client_key_password_len;
    argv[16] = (uint32_t)config->user_agent;
    argv[17] = (uint32_t)config->method;
    argv[18] = (uint32_t)config->timeout_ms;
    argv[19] = (uint32_t)config->disable_auto_redirect;
    argv[20] = (uint32_t)config->max_redirection_count;
    argv[21] = (uint32_t)config->max_authorization_retries;
    argv[22] = (uint32_t)http_dispatch_event;
    argv[23] = (uint32_t)config->transport_type;
    argv[24] = (uint32_t)config->buffer_size;
    argv[25] = (uint32_t)config->buffer_size_tx;
    argv[26] = (uint32_t)client;
    argv[27] = (uint32_t)config->is_async;
    argv[28] = (uint32_t)config->use_global_ca_store;
    argv[29] = (uint32_t)config->skip_cert_common_name_check;
    argv[30] = (uint32_t)config->crt_bundle_attach;
    argv[31] = (uint32_t)config->keep_alive_enable;
    argv[32] = (uint32_t)config->keep_alive_idle;
    argv[33] = (uint32_t)config->keep_alive_interval;
    argv[34] = (uint32_t)config->keep_alive_count;
    argv[35] = (uint32_t)config->if_name;

    if (HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_INIT, argv)) {
        free(client);
        client = NULL;
    } else {
        client->handle = argv[0];
    }

    return client;
}

esp_err_t esp_http_client_perform(esp_http_client_handle_t client)
{
    uint32_t argv[2] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_PERFORM;
    argv[1]  = (uint32_t)client->handle;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_COMMON, argv);
}

esp_err_t esp_http_client_set_url(esp_http_client_handle_t client, const char *url)
{
    uint32_t argv[4] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_SET_URL;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)url;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_SET_STR, argv);
}

esp_err_t esp_http_client_set_post_field(esp_http_client_handle_t client, const char *data, int len)
{
    uint32_t argv[4] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_SET_POST_FILED;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)data;
    argv[3]  = (uint32_t)len;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_SET_STR, argv);
}

int esp_http_client_get_post_field(esp_http_client_handle_t client, char **data)
{
    uint32_t argv[5] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_GET_POST_FILED;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)NULL;

    if (HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_STR, argv)) {
        return 0;
    } else {
        int len = argv[0];
        if (client->post_data) {
            free(client->post_data);
            client->post_data = NULL;
        }

        client->post_data = malloc(len + 1);
        if (client->post_data) {
            memset(client->post_data, 0, len + 1);
            memset(argv, 0, sizeof(argv));
            
            argv[0]  = (uint32_t)HTTP_CLIENT_GET_POST_FILED;
            argv[1]  = (uint32_t)client->handle;
            argv[2]  = (uint32_t)client->post_data;
            argv[3]  = (uint32_t)len;

            if (HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_STR, argv)) {
                return 0;
            } else {
                *data = client->post_data;
                return len;
            }
        } else {
            return 0;
        }
    }
}

esp_err_t esp_http_client_set_header(esp_http_client_handle_t client, const char *key, const char *value)
{
    uint32_t argv[4] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_SET_HEADER;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)key;
    argv[3]  = (uint32_t)value;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_SET_STR, argv);
}

esp_err_t esp_http_client_get_header(esp_http_client_handle_t client, const char *key, char **value)
{
    uint32_t argv[5] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_GET_HEADER;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)key;
    argv[3]  = (uint32_t)0;
    argv[4]  = (uint32_t)NULL;

    if (HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_STR, argv)) {
        return ESP_FAIL;
    } else {
        int len = argv[0];
        if (client->head_value) {
            free(client->head_value);
            client->head_value = NULL;
        }

        client->head_value = malloc(len + 1);
        if (client->head_value) {
            memset(client->head_value, 0, len + 1);
            memset(argv, 0, sizeof(argv));
            
            argv[0]  = (uint32_t)HTTP_CLIENT_GET_HEADER;
            argv[1]  = (uint32_t)client->handle;
            argv[2]  = (uint32_t)key;
            argv[3]  = (uint32_t)len;
            argv[4]  = (uint32_t)client->head_value;

            if (HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_STR, argv)) {
                return ESP_FAIL;
            } else {
                *value = client->head_value;
                return ESP_OK;
            }
        } else {
            return ESP_FAIL;
        }
    }
}

esp_err_t esp_http_client_get_username(esp_http_client_handle_t client, char **value)
{
    uint32_t argv[5] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_GET_USERNAME;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)NULL;

    if (HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_STR, argv)) {
        return ESP_FAIL;
    } else {
        int len = argv[0];
        if (client->username) {
            free(client->username);
            client->username = NULL;
        }

        client->username = malloc(len + 1);
        if (client->username) {
            memset(client->username, 0, len + 1);
            memset(argv, 0, sizeof(argv));
            
            argv[0]  = (uint32_t)HTTP_CLIENT_GET_USERNAME;
            argv[1]  = (uint32_t)client->handle;
            argv[2]  = (uint32_t)client->username;
            argv[3]  = (uint32_t)len;

            if (HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_STR, argv)) {
                return ESP_FAIL;
            } else {
                *value = client->username;
                return ESP_OK;
            }
        } else {
            return ESP_FAIL;
        }
    }
}

esp_err_t esp_http_client_set_username(esp_http_client_handle_t client, const char *username)
{
    uint32_t argv[4] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_SET_USERNAME;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)username;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_SET_STR, argv);
}

esp_err_t esp_http_client_get_password(esp_http_client_handle_t client, char **value)
{
    uint32_t argv[5] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_GET_PASSWORD;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)NULL;

    if (HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_STR, argv)) {
        return ESP_FAIL;
    } else {
        int len = argv[0];
        if (client->password) {
            free(client->password);
            client->password = NULL;
        }

        client->password = malloc(len + 1);
        if (client->password) {
            memset(client->password, 0, len + 1);
            memset(argv, 0, sizeof(argv));
            
            argv[0]  = (uint32_t)HTTP_CLIENT_GET_PASSWORD;
            argv[1]  = (uint32_t)client->handle;
            argv[2]  = (uint32_t)client->password;
            argv[3]  = (uint32_t)len;

            if (HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_STR, argv)) {
                return ESP_FAIL;
            } else {
                *value = client->password;
                return ESP_OK;
            }
        } else {
            return ESP_FAIL;
        }
    }
}

esp_err_t esp_http_client_set_password(esp_http_client_handle_t client, const char *password)
{
    uint32_t argv[4] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_SET_PASSWORD;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)password;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_SET_STR, argv);
}

esp_err_t esp_http_client_set_authtype(esp_http_client_handle_t client, esp_http_client_auth_type_t auth_type)
{
    uint32_t argv[3] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_SET_AUTHTYPE;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)auth_type;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_SET_INT, argv);
}

int esp_http_client_get_errno(esp_http_client_handle_t client)
{
    uint32_t argv[2] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_GET_ERRNO;
    argv[1]  = (uint32_t)client->handle;

    esp_err_t ret = HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_INT, argv);

    return (ret == ESP_OK) ? argv[0] : ret;
}

esp_err_t esp_http_client_set_method(esp_http_client_handle_t client, esp_http_client_method_t method)
{
    uint32_t argv[3] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_SET_METHOD;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)method;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_SET_INT, argv);
}

esp_err_t esp_http_client_set_timeout_ms(esp_http_client_handle_t client, int timeout_ms)
{
    uint32_t argv[3] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_SET_TIMEOUT;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)timeout_ms;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_SET_INT, argv);
}

esp_err_t esp_http_client_delete_header(esp_http_client_handle_t client, const char *key)
{
    uint32_t argv[4] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_DELETE_HEADER;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)key;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_SET_STR, argv);
}

esp_err_t esp_http_client_open(esp_http_client_handle_t client, int write_len)
{
    uint32_t argv[3] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_OPEN;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)write_len;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_SET_INT, argv);
}

int esp_http_client_write(esp_http_client_handle_t client, const char *buffer, int len)
{
    uint32_t argv[4] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_WRITE_DATA;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)buffer;
    argv[3]  = (uint32_t)len;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_SET_STR, argv);
}

int esp_http_client_fetch_headers(esp_http_client_handle_t client)
{
    uint32_t argv[2] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_FETCH_HEADER;
    argv[1]  = (uint32_t)client->handle;

    esp_err_t ret = HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_INT, argv);

    return (ret == ESP_OK) ? argv[0] : ret;
}

bool esp_http_client_is_chunked_response(esp_http_client_handle_t client)
{
    uint32_t argv[2] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_IS_CHUNKED;
    argv[1]  = (uint32_t)client->handle;

    esp_err_t ret = HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_INT, argv);

    return (ret == ESP_OK) ? argv[0] : false;
}

int esp_http_client_read(esp_http_client_handle_t client, char *buffer, int len)
{
    uint32_t argv[5] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_READ_DATA;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)buffer;
    argv[3]  = (uint32_t)len;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_STR, argv);
}

int esp_http_client_get_status_code(esp_http_client_handle_t client)
{
    uint32_t argv[2] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_GET_STATUS_CODE;
    argv[1]  = (uint32_t)client->handle;

    esp_err_t ret = HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_INT, argv);

    return (ret == ESP_OK) ? argv[0] : ret;
}

int esp_http_client_get_content_length(esp_http_client_handle_t client)
{
    uint32_t argv[2] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_GET_CONTENT_LENGTH;
    argv[1]  = (uint32_t)client->handle;

    esp_err_t ret = HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_INT, argv);

    return (ret == ESP_OK) ? argv[0] : ret;
}

esp_err_t esp_http_client_close(esp_http_client_handle_t client)
{
    uint32_t argv[2] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_CLOSE;
    argv[1]  = (uint32_t)client->handle;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_COMMON, argv);
}

esp_err_t esp_http_client_cleanup(esp_http_client_handle_t client)
{
    uint32_t argv[2] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_CLEANUP;
    argv[1]  = (uint32_t)client->handle;

    esp_err_t ret = HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_COMMON, argv);

    if (client->post_data) {
        free(client->post_data);
    }

    if (client->head_value) {
        free(client->head_value);
    }

    if (client->username) {
        free(client->username);
    }

    if (client->password) {
        free(client->password);
    }

    free(client);

    return ret;
}

esp_http_client_transport_t esp_http_client_get_transport_type(esp_http_client_handle_t client)
{
    uint32_t argv[2] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_GET_TRANSPORT_TYPE;
    argv[1]  = (uint32_t)client->handle;

    esp_err_t ret = HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_INT, argv);

    return (ret == ESP_OK) ? argv[0] : HTTP_TRANSPORT_UNKNOWN;
}

esp_err_t esp_http_client_set_redirection(esp_http_client_handle_t client)
{
    uint32_t argv[2] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_SET_REDIRECTION;
    argv[1]  = (uint32_t)client->handle;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_COMMON, argv);
}

void esp_http_client_add_auth(esp_http_client_handle_t client)
{
    uint32_t argv[2] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_ADD_AUTH;
    argv[1]  = (uint32_t)client->handle;

    HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_COMMON, argv);
}

bool esp_http_client_is_complete_data_received(esp_http_client_handle_t client)
{
    uint32_t argv[2] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_IS_COMPLETE;
    argv[1]  = (uint32_t)client->handle;

    esp_err_t ret = HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_INT, argv);

    return (ret == ESP_OK) ? argv[0] : false;
}

int esp_http_client_read_response(esp_http_client_handle_t client, char *buffer, int len)
{
    uint32_t argv[5] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_READ_RESP;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)buffer;
    argv[3]  = (uint32_t)len;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_STR, argv);
}

esp_err_t esp_http_client_flush_response(esp_http_client_handle_t client, int *len)
{
    uint32_t argv[2] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_FLUSH_RESPONSE;
    argv[1]  = (uint32_t)client->handle;

    esp_err_t ret = HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_INT, argv);

    *len = (ret == ESP_OK) ? argv[0] : 0;

    return ret;
}

esp_err_t esp_http_client_get_url(esp_http_client_handle_t client, char *url, const int len)
{
    uint32_t argv[5] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_GET_URL;
    argv[1]  = (uint32_t)client->handle;
    argv[2]  = (uint32_t)url;
    argv[3]  = (uint32_t)len;

    return HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_STR, argv);
}

esp_err_t esp_http_client_get_chunk_length(esp_http_client_handle_t client, int *len)
{
    uint32_t argv[2] = { 0 };

    argv[0]  = (uint32_t)HTTP_CLIENT_GET_CHUNK_LENGTH;
    argv[1]  = (uint32_t)client->handle;

    esp_err_t ret = HTTP_CLIENT_CALL_FUNC(HTTP_CLIENT_GET_INT, argv);

    *len = (ret == ESP_OK) ? argv[0] : 0;

    return ret;
}