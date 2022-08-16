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

#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_types.h>
#include <esp_rmaker_standard_params.h>
#include <esp_rmaker_standard_devices.h>
#include <esp_rmaker_schedule.h>
#include <esp_rmaker_scenes.h>

#include "rmaker_wasm_api.h"

#define RMAKER_CALL_FUNC(id, argv) wasm_rmaker_call_native_func(id, \
                                                           sizeof(argv) / sizeof(argv[0]), \
                                                           argv)

/**
 * rmaker_core
 */
static esp_err_t esp_rmaker_device_scheme_cb(const esp_rmaker_device_t *device, const esp_rmaker_param_t *param, esp_rmaker_param_val_t *param_val,
                                             esp_rmaker_device_write_cb_t write_cb, void *priv_data, esp_rmaker_req_src_t src)
{    
    uint32_t argv[5];
    esp_rmaker_param_val_t val;
    char scheme_val[64] = { 0 };
    esp_rmaker_write_ctx_t ctx = {
        .src = src,
    };
    
    argv[0] = false;
    argv[1] = (uint32_t)param_val;
    argv[2] = (uint32_t)&val.type;
    argv[3] = (uint32_t)scheme_val;
    argv[4] = (uint32_t)sizeof(scheme_val);

    memset(scheme_val, 0, sizeof(scheme_val));
    RMAKER_CALL_FUNC(RMAKER_PARAM_GET_VAL, argv);
    switch (val.type) {
        case RMAKER_VAL_TYPE_BOOLEAN:
            val.val.b = (*(bool *)scheme_val);
            break;
        case RMAKER_VAL_TYPE_INTEGER:
            val.val.i = (*(int *)scheme_val);
            break;
        case RMAKER_VAL_TYPE_FLOAT:
            val.val.f = (*(float *)scheme_val);
            break;
        case RMAKER_VAL_TYPE_STRING:
        case RMAKER_VAL_TYPE_OBJECT:
        case RMAKER_VAL_TYPE_ARRAY:
            val.val.s = scheme_val;
            break;
        default:
            break;
    }

    return write_cb(device, param, val, priv_data, (src == ESP_RMAKER_REQ_SRC_MAX) ? NULL : &ctx);
}

const char *esp_rmaker_device_cb_src_to_str(esp_rmaker_req_src_t src)
{
    static char src_to_str[64] = { 0 };
    uint32_t argv[3];
    
    argv[0] = (uint32_t)src;
    argv[1] = (uint32_t)src_to_str;
    argv[2] = sizeof(src_to_str);

    memset(src_to_str, 0, sizeof(src_to_str));
    RMAKER_CALL_FUNC(RMAKER_DEVICE_CB_SRC_TO_STR, argv);

    return (const char *)src_to_str;
}

esp_rmaker_param_val_t esp_rmaker_bool(bool bval)
{
    esp_rmaker_param_val_t param_val = {
        .type = RMAKER_VAL_TYPE_BOOLEAN,
        .val.b = bval
    };

    return param_val;
}

esp_rmaker_param_val_t esp_rmaker_int(int ival)
{
    esp_rmaker_param_val_t param_val = {
        .type = RMAKER_VAL_TYPE_INTEGER,
        .val.i = ival
    };

    return param_val;
}

esp_rmaker_param_val_t esp_rmaker_float(float fval)
{
    esp_rmaker_param_val_t param_val = {
        .type = RMAKER_VAL_TYPE_FLOAT,
        .val.f = fval
    };

    return param_val;
}

esp_rmaker_param_val_t esp_rmaker_str(const char *sval)
{
    esp_rmaker_param_val_t param_val = {
        .type = RMAKER_VAL_TYPE_STRING,
        .val.s = (char *)sval
    };

    return param_val;
}

esp_rmaker_param_val_t esp_rmaker_obj(const char *val)
{
    esp_rmaker_param_val_t param_val = {
        .type = RMAKER_VAL_TYPE_OBJECT,
        .val.s = (char *)val
    };

    return param_val;
}

esp_rmaker_param_val_t esp_rmaker_array(const char *val)
{
    esp_rmaker_param_val_t param_val = {
        .type = RMAKER_VAL_TYPE_ARRAY,
        .val.s = (char *)val
    };

    return param_val;
}

esp_rmaker_node_t *esp_rmaker_node_init(const esp_rmaker_config_t *config, const char *name, const char *type)
{
    if (!config) {
        return NULL;
    }

    uint32_t argv[3];
    
    argv[0] = (uint32_t)config;
    argv[1] = (uint32_t)name;
    argv[2] = (uint32_t)type;

    return (esp_rmaker_node_t *)RMAKER_CALL_FUNC(RMAKER_NODE_INIT, argv);
}

esp_err_t esp_rmaker_start(void)
{
    return wasm_rmaker_run(RMAKER_COMMON_START);
}

esp_err_t esp_rmaker_stop(void)
{
    return wasm_rmaker_run(RMAKER_COMMON_STOP);
}

esp_err_t esp_rmaker_node_deinit(const esp_rmaker_node_t *node)
{
    uint32_t argv[1];
    
    argv[0] = (uint32_t)node;

    return RMAKER_CALL_FUNC(RMAKER_NODE_DEINIT, argv);
}

const esp_rmaker_node_t *esp_rmaker_get_node(void)
{
    uint32_t argv[1] = { 0 };

    return (const esp_rmaker_node_t *)RMAKER_CALL_FUNC(RMAKER_NODE_GET_NODE, argv);
}

char *esp_rmaker_get_node_id(void)
{
    static char node_id[64] = { 0 };
    uint32_t argv[3];
    
    argv[0] = (uint32_t)RMAKER_NODE_GET_NODE_ID;
    argv[1] = (uint32_t)node_id;
    argv[2] = sizeof(node_id);

    memset(node_id, 0, sizeof(node_id));
    RMAKER_CALL_FUNC(RMAKER_NODE_GET_STR, argv);

    return (char *)node_id;
}

esp_rmaker_node_info_t *esp_rmaker_node_get_info(const esp_rmaker_node_t *node)
{
    static char name[64] = { 0 };
    static char type[64] = { 0 };
    static char fw_version[64] = { 0 };
    static char model[64] = { 0 };
    static char subtype[64] = { 0 };
    static esp_rmaker_node_info_t node_info = {
        .name = name,
        .type = type,
        .fw_version = fw_version,
        .model = model,
        .subtype = subtype
    };

    uint32_t argv[6];
    
    argv[0] = (uint32_t)node;
    argv[1] = (uint32_t)node_info.name;
    argv[2] = (uint32_t)node_info.type;
    argv[3] = (uint32_t)node_info.fw_version;
    argv[4] = (uint32_t)node_info.model;
    argv[5] = (uint32_t)node_info.subtype;

    memset(type, 0, sizeof(type));
    RMAKER_CALL_FUNC(RMAKER_NODE_GET_INFO, argv);

    return (esp_rmaker_node_info_t *)&node_info;
}

esp_err_t esp_rmaker_node_add_attribute(const esp_rmaker_node_t *node, const char *attr_name, const char *val)
{
    uint32_t argv[4];
    
    argv[0] = (uint32_t)RMAKER_NODE_ADD_ATTRIBUTE;
    argv[1] = (uint32_t)node;
    argv[2] = (uint32_t)attr_name;
    argv[3] = (uint32_t)val;

    return RMAKER_CALL_FUNC(RMAKER_NODE_SET_STR, argv);
}

esp_err_t esp_rmaker_node_add_fw_version(const esp_rmaker_node_t *node, const char *fw_version)
{
    uint32_t argv[4];
    
    argv[0] = (uint32_t)RMAKER_NODE_ADD_FW_VERSION;
    argv[1] = (uint32_t)node;
    argv[2] = (uint32_t)fw_version;

    return RMAKER_CALL_FUNC(RMAKER_NODE_SET_STR, argv);
}

esp_err_t esp_rmaker_node_add_model(const esp_rmaker_node_t *node, const char *model)
{
    uint32_t argv[4];
    
    argv[0] = (uint32_t)RMAKER_NODE_ADD_MODEL;
    argv[1] = (uint32_t)node;
    argv[2] = (uint32_t)model;

    return RMAKER_CALL_FUNC(RMAKER_NODE_SET_STR, argv);
}

esp_err_t esp_rmaker_node_add_subtype(const esp_rmaker_node_t *node, const char *subtype)
{
    uint32_t argv[3];
    
    argv[0] = (uint32_t)RMAKER_NODE_ADD_SUBTYPE;
    argv[1] = (uint32_t)node;
    argv[2] = (uint32_t)subtype;

    return RMAKER_CALL_FUNC(RMAKER_NODE_SET_STR, argv);
}

esp_rmaker_device_t *esp_rmaker_device_create(const char *dev_name, const char *type, void *priv_data)
{
    uint32_t argv[3];
    
    argv[0] = (uint32_t)dev_name;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)priv_data;

    return (esp_rmaker_device_t *)RMAKER_CALL_FUNC(RMAKER_DEVICE_CREATE, argv);
}

esp_rmaker_device_t *esp_rmaker_service_create(const char *serv_name, const char *type, void *priv_data)
{
    uint32_t argv[3];
    
    argv[0] = (uint32_t)serv_name;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)priv_data;

    return (esp_rmaker_device_t *)RMAKER_CALL_FUNC(RMAKER_SERVICE_CREATE, argv);
}

esp_err_t esp_rmaker_device_delete(const esp_rmaker_device_t *device)
{
    uint32_t argv[1];
    
    argv[0] = (uint32_t)device;

    return RMAKER_CALL_FUNC(RMAKER_DEVICE_DELETE, argv);
}

esp_err_t esp_rmaker_device_add_cb(const esp_rmaker_device_t *device, esp_rmaker_device_write_cb_t write_cb, esp_rmaker_device_read_cb_t read_cb)
{
    uint32_t argv[4];
    
    argv[0] = (uint32_t)device;
    argv[1] = (uint32_t)esp_rmaker_device_scheme_cb;
    argv[2] = (uint32_t)write_cb;
    argv[3] = (uint32_t)read_cb;

    return RMAKER_CALL_FUNC(RMAKER_DEVICE_ADD_CALLBACK, argv);
}

esp_err_t esp_rmaker_node_add_device(const esp_rmaker_node_t *node, const esp_rmaker_device_t *device)
{
    uint32_t argv[3];
    
    argv[0] = true;
    argv[1] = (uint32_t)node;
    argv[2] = (uint32_t)device;

    return RMAKER_CALL_FUNC(RMAKER_NODE_SET_DEVICE, argv);
}

esp_err_t esp_rmaker_node_remove_device(const esp_rmaker_node_t *node, const esp_rmaker_device_t *device)
{
    uint32_t argv[3];
    
    argv[0] = false;
    argv[1] = (uint32_t)node;
    argv[2] = (uint32_t)device;

    return RMAKER_CALL_FUNC(RMAKER_NODE_SET_DEVICE, argv);
}

esp_rmaker_device_t *esp_rmaker_node_get_device_by_name(const esp_rmaker_node_t *node, const char *device_name)
{
    uint32_t argv[3];
    
    argv[0] = (uint32_t)RMAKER_NODE_GET_DEVICE_BY_NAME;
    argv[1] = (uint32_t)node;
    argv[2] = (uint32_t)device_name;

    return (esp_rmaker_device_t *)RMAKER_CALL_FUNC(RMAKER_NODE_GET_DEVICE, argv);
}

esp_err_t esp_rmaker_device_add_attribute(const esp_rmaker_device_t *device, const char *attr_name, const char *val)
{
    uint32_t argv[4];
    
    argv[0] = (uint32_t)RMAKER_DEVICE_ADD_ATTRIBUTE;
    argv[1] = (uint32_t)device;
    argv[2] = (uint32_t)attr_name;
    argv[3] = (uint32_t)val;

    return RMAKER_CALL_FUNC(RMAKER_DEVICE_SET_STR, argv);
}

esp_err_t esp_rmaker_device_add_subtype(const esp_rmaker_device_t *device, const char *subtype)
{
    uint32_t argv[4];
    
    argv[0] = (uint32_t)RMAKER_DEVICE_ADD_SUBTYPE;
    argv[1] = (uint32_t)device;
    argv[2] = (uint32_t)subtype;

    return RMAKER_CALL_FUNC(RMAKER_DEVICE_SET_STR, argv);
}

esp_err_t esp_rmaker_device_add_model(const esp_rmaker_device_t *device, const char *model)
{
    uint32_t argv[4];
    
    argv[0] = (uint32_t)RMAKER_DEVICE_ADD_MODEL;
    argv[1] = (uint32_t)device;
    argv[2] = (uint32_t)model;

    return RMAKER_CALL_FUNC(RMAKER_DEVICE_SET_STR, argv);
}

char *esp_rmaker_device_get_name(const esp_rmaker_device_t *device)
{
    static char name[64] = { 0 };
    uint32_t argv[4];
    
    argv[0] = (uint32_t)RMAKER_DEVICE_GET_NAME;
    argv[1] = (uint32_t)device;
    argv[2] = (uint32_t)name;
    argv[3] = (uint32_t)sizeof(name);

    memset(name, 0, sizeof(name));

    return (RMAKER_CALL_FUNC(RMAKER_DEVICE_GET_STR, argv) == ESP_OK) ? name : NULL;
}

char *esp_rmaker_device_get_type(const esp_rmaker_device_t *device)
{
    static char type[64] = { 0 };
    uint32_t argv[4];
    
    argv[0] = (uint32_t)RMAKER_DEVICE_GET_TYPE;
    argv[1] = (uint32_t)device;
    argv[2] = (uint32_t)type;
    argv[3] = (uint32_t)sizeof(type);

    memset(type, 0, sizeof(type));

    return (RMAKER_CALL_FUNC(RMAKER_DEVICE_GET_STR, argv) == ESP_OK) ? type : NULL;
}

esp_err_t esp_rmaker_device_add_param(const esp_rmaker_device_t *device, const esp_rmaker_param_t *param)
{
    uint32_t argv[3];
    
    argv[0] = (uint32_t)RMAKER_DEVICE_ADD_PARAM;
    argv[1] = (uint32_t)device;
    argv[2] = (uint32_t)param;

    return RMAKER_CALL_FUNC(RMAKER_DEVICE_SET_PARAM, argv);
}

esp_rmaker_param_t *esp_rmaker_device_get_param_by_type(const esp_rmaker_device_t *device, const char *param_type)
{
    uint32_t argv[3];
    
    argv[0] = (uint32_t)RMAKER_DEVICE_GET_PARAM_BY_TYPE;
    argv[1] = (uint32_t)device;
    argv[2] = (uint32_t)param_type;

    return (esp_rmaker_param_t *)RMAKER_CALL_FUNC(RMAKER_DEVICE_GET_PARAM, argv);
}

esp_rmaker_param_t *esp_rmaker_device_get_param_by_name(const esp_rmaker_device_t *device, const char *param_name)
{
    uint32_t argv[3];
    
    argv[0] = (uint32_t)RMAKER_DEVICE_GET_PARAM_BY_NAME;
    argv[1] = (uint32_t)device;
    argv[2] = (uint32_t)param_name;

    return (esp_rmaker_param_t *)RMAKER_CALL_FUNC(RMAKER_DEVICE_GET_PARAM, argv);
}

esp_err_t esp_rmaker_device_assign_primary_param(const esp_rmaker_device_t *device, const esp_rmaker_param_t *param)
{
    uint32_t argv[3];
    
    argv[0] = (uint32_t)RMAKER_DEVICE_ASSIGN_PRIMARY_PARAM;
    argv[1] = (uint32_t)device;
    argv[2] = (uint32_t)param;

    return RMAKER_CALL_FUNC(RMAKER_DEVICE_SET_PARAM, argv);
}

esp_rmaker_param_t *esp_rmaker_param_create(const char *param_name, const char *type,
        esp_rmaker_param_val_t val, uint8_t properties)
{
    uint32_t argv[5] = { 0 };
    
    argv[0] = (uint32_t)param_name;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)val.type;
    switch (val.type) {
        case RMAKER_VAL_TYPE_BOOLEAN:
            argv[3] = (uint32_t)val.val.b;
            break;
        case RMAKER_VAL_TYPE_INTEGER:
            argv[3] = (uint32_t)val.val.i;
            break;
        case RMAKER_VAL_TYPE_FLOAT:
            argv[3] = (uint32_t)val.val.f;
            break;
        case RMAKER_VAL_TYPE_STRING:
        case RMAKER_VAL_TYPE_OBJECT:
        case RMAKER_VAL_TYPE_ARRAY:
            argv[3] = (uint32_t)val.val.s;
            break;
        default:
            break;
    }

    argv[4] = (uint32_t)properties;

    return (esp_rmaker_param_t *)RMAKER_CALL_FUNC(RMAKER_PARAM_CREATE, argv);
}

esp_err_t esp_rmaker_param_add_ui_type(const esp_rmaker_param_t *param, const char *ui_type)
{
    uint32_t argv[3];
    
    argv[0] = (uint32_t)RMAKER_PARAM_ADD_UI_TYPE;
    argv[1] = (uint32_t)param;
    argv[2] = (uint32_t)ui_type;

    return RMAKER_CALL_FUNC(RMAKER_PARAM_SET_STR, argv);
}

esp_err_t esp_rmaker_param_add_bounds(const esp_rmaker_param_t *param,
    esp_rmaker_param_val_t min, esp_rmaker_param_val_t max, esp_rmaker_param_val_t step)
{
    uint32_t argv[7];
    
    argv[0] = (uint32_t)param;
    argv[1] = (uint32_t)min.type;
    switch (min.type) {
        case RMAKER_VAL_TYPE_BOOLEAN:
            argv[2] = (uint32_t)min.val.b;
            break;
        case RMAKER_VAL_TYPE_INTEGER:
            argv[2] = (uint32_t)min.val.i;
            break;
        case RMAKER_VAL_TYPE_FLOAT:
            argv[2] = (uint32_t)min.val.f;
            break;
        case RMAKER_VAL_TYPE_STRING:
        case RMAKER_VAL_TYPE_OBJECT:
        case RMAKER_VAL_TYPE_ARRAY:
            argv[2] = (uint32_t)min.val.s;
            break;
        default:
            break;
    }
    argv[3] = (uint32_t)max.type;
    switch (max.type) {
        case RMAKER_VAL_TYPE_BOOLEAN:
            argv[4] = (uint32_t)max.val.b;
            break;
        case RMAKER_VAL_TYPE_INTEGER:
            argv[4] = (uint32_t)max.val.i;
            break;
        case RMAKER_VAL_TYPE_FLOAT:
            argv[4] = (uint32_t)max.val.f;
            break;
        case RMAKER_VAL_TYPE_STRING:
        case RMAKER_VAL_TYPE_OBJECT:
        case RMAKER_VAL_TYPE_ARRAY:
            argv[4] = (uint32_t)max.val.s;
            break;
        default:
            break;
    }
    argv[5] = (uint32_t)step.type;
    switch (step.type) {
        case RMAKER_VAL_TYPE_BOOLEAN:
            argv[6] = (uint32_t)step.val.b;
            break;
        case RMAKER_VAL_TYPE_INTEGER:
            argv[6] = (uint32_t)step.val.i;
            break;
        case RMAKER_VAL_TYPE_FLOAT:
            argv[6] = (uint32_t)step.val.f;
            break;
        case RMAKER_VAL_TYPE_STRING:
        case RMAKER_VAL_TYPE_OBJECT:
        case RMAKER_VAL_TYPE_ARRAY:
            argv[6] = (uint32_t)step.val.s;
            break;
        default:
            break;
    }

    return RMAKER_CALL_FUNC(RMAKER_PARAM_ADD_BOUNDS, argv);
}

esp_err_t esp_rmaker_param_add_valid_str_list(const esp_rmaker_param_t *param, const char *strs[], uint8_t count)
{
    return wasm_rmaker_param_add_valid_str_list((uint32_t)param, strs, count);
}

esp_err_t esp_rmaker_param_add_array_max_count(const esp_rmaker_param_t *param, int count)
{
    uint32_t argv[3];
    
    argv[0] = (uint32_t)RMAKER_PARAM_ADD_ARRAY_MAX_COUNT;
    argv[1] = (uint32_t)param;
    argv[2] = (uint32_t)count;

    return RMAKER_CALL_FUNC(RMAKER_PARAM_SET_STR, argv);
}

esp_err_t esp_rmaker_param_update(const esp_rmaker_param_t *param, esp_rmaker_param_val_t val)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)RMAKER_PARAM_UPDATE;
    argv[1] = (uint32_t)param;
    argv[2] = (uint32_t)val.type;
    switch (val.type) {
        case RMAKER_VAL_TYPE_BOOLEAN:
            argv[3] = (uint32_t)val.val.b;
            break;
        case RMAKER_VAL_TYPE_INTEGER:
            argv[3] = (uint32_t)val.val.i;
            break;
        case RMAKER_VAL_TYPE_FLOAT:
            argv[3] = (uint32_t)val.val.f;
            break;
        case RMAKER_VAL_TYPE_STRING:
        case RMAKER_VAL_TYPE_OBJECT:
        case RMAKER_VAL_TYPE_ARRAY:
            argv[3] = (uint32_t)val.val.s;
            break;
        default:
            break;
    }

    return RMAKER_CALL_FUNC(RMAKER_PARAM_SET_VAL, argv);
}

esp_err_t esp_rmaker_param_update_and_report(const esp_rmaker_param_t *param, esp_rmaker_param_val_t val)
{
    uint32_t argv[4];
    
    argv[0] = (uint32_t)RMAKER_PARAM_UPDATE_AND_REPORT;
    argv[1] = (uint32_t)param;
    argv[2] = (uint32_t)val.type;
    switch (val.type) {
        case RMAKER_VAL_TYPE_BOOLEAN:
            argv[3] = (uint32_t)val.val.b;
            break;
        case RMAKER_VAL_TYPE_INTEGER:
            argv[3] = (uint32_t)val.val.i;
            break;
        case RMAKER_VAL_TYPE_FLOAT:
            argv[3] = (uint32_t)val.val.f;
            break;
        case RMAKER_VAL_TYPE_STRING:
        case RMAKER_VAL_TYPE_OBJECT:
        case RMAKER_VAL_TYPE_ARRAY:
            argv[3] = (uint32_t)val.val.s;
            break;
        default:
            break;
    }

    return RMAKER_CALL_FUNC(RMAKER_PARAM_SET_VAL, argv);
}

esp_err_t esp_rmaker_param_update_and_notify(const esp_rmaker_param_t *param, esp_rmaker_param_val_t val)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)RMAKER_PARAM_UPDATE_AND_NOTIFY;
    argv[1] = (uint32_t)param;
    argv[2] = (uint32_t)val.type;
    switch (val.type) {
        case RMAKER_VAL_TYPE_BOOLEAN:
            argv[3] = (uint32_t)val.val.b;
            break;
        case RMAKER_VAL_TYPE_INTEGER:
            argv[3] = (uint32_t)val.val.i;
            break;
        case RMAKER_VAL_TYPE_FLOAT:
            argv[3] = (uint32_t)val.val.f;
            break;
        case RMAKER_VAL_TYPE_STRING:
        case RMAKER_VAL_TYPE_OBJECT:
        case RMAKER_VAL_TYPE_ARRAY:
            argv[3] = (uint32_t)val.val.s;
            break;
        default:
            break;
    }

    return RMAKER_CALL_FUNC(RMAKER_PARAM_SET_VAL, argv);
}

esp_err_t esp_rmaker_raise_alert(const char *alert_str)
{
    uint32_t argv[1];
    
    argv[0] = (uint32_t)alert_str;

    return RMAKER_CALL_FUNC(RMAKER_COMMON_RAISE_ALERT, argv);
}

char *esp_rmaker_param_get_name(const esp_rmaker_param_t *param)
{
    static char name[64] = { 0 };
    uint32_t argv[4];

    argv[0] = (uint32_t)RMAKER_PARAM_GET_NAME;
    argv[1] = (uint32_t)param;
    argv[2] = (uint32_t)name;
    argv[3] = (uint32_t)sizeof(name);

    memset(name, 0, sizeof(name));
    RMAKER_CALL_FUNC(RMAKER_PARAM_GET_STR, argv);

    return name;
}

char *esp_rmaker_param_get_type(const esp_rmaker_param_t *param)
{
    static char type[64] = { 0 };
    uint32_t argv[4];
    
    argv[0] = (uint32_t)RMAKER_PARAM_GET_TYPE;
    argv[1] = (uint32_t)param;
    argv[2] = (uint32_t)type;
    argv[3] = (uint32_t)sizeof(type);

    memset(type, 0, sizeof(type));
    RMAKER_CALL_FUNC(RMAKER_PARAM_GET_STR, argv);

    return type;
}

esp_rmaker_param_val_t *esp_rmaker_param_get_val(esp_rmaker_param_t *param)
{
    static esp_rmaker_param_val_t val;
    static char scheme_val[64] = { 0 };
    uint32_t argv[5];
    
    argv[0] = true;
    argv[1] = (uint32_t)param;
    argv[2] = (uint32_t)&val.type;
    argv[3] = (uint32_t)scheme_val;
    argv[4] = (uint32_t)sizeof(scheme_val);

    RMAKER_CALL_FUNC(RMAKER_PARAM_GET_VAL, argv);
    switch (val.type) {
        case RMAKER_VAL_TYPE_BOOLEAN:
            val.val.b = (*(bool *)scheme_val);
            break;
        case RMAKER_VAL_TYPE_INTEGER:
            val.val.i = (*(int *)scheme_val);
            break;
        case RMAKER_VAL_TYPE_FLOAT:
            val.val.f = (*(float *)scheme_val);
            break;
        case RMAKER_VAL_TYPE_STRING:
        case RMAKER_VAL_TYPE_OBJECT:
        case RMAKER_VAL_TYPE_ARRAY:
            val.val.s = scheme_val;
            break;
        default:
            break;
    }

    return (esp_rmaker_param_val_t *)&val;
}

esp_err_t esp_rmaker_report_node_details(void)
{
    return wasm_rmaker_run(RMAKER_COMMON_NODE_DETAILS);
}

esp_err_t esp_rmaker_timezone_service_enable(void)
{
    return wasm_rmaker_run(RMAKER_COMMON_TIMEZONE_ENABLE);
}

esp_err_t esp_rmaker_system_service_enable(esp_rmaker_system_serv_config_t *config)
{
    uint32_t argv[1];
    
    argv[0] = (uint32_t)config;

    return RMAKER_CALL_FUNC(RMAKER_SERVICE_SYSTEM_ENABLE, argv);
}

bool esp_rmaker_local_ctrl_service_started(void)
{
    return wasm_rmaker_run(RMAKER_COMMON_LOCAL_CTRL_START);
}

esp_err_t esp_rmaker_ota_enable_default(void)
{
    return wasm_rmaker_run(RMAKER_COMMON_OTA_ENABLE);
}

/**
 * rmaker_scenes
 */
esp_err_t esp_rmaker_scenes_enable(void)
{
    return wasm_rmaker_run(RMAKER_COMMON_SCENES_ENABLE);
}

/**
 * rmaker_schedule
 */
esp_err_t esp_rmaker_schedule_enable(void)
{
    return wasm_rmaker_run(RMAKER_COMMON_SCHEDULE_ENABLE);
}
