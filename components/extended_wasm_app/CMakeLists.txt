set(srcs  "")
set(include_dir "")
set(priv_include_dir "")

if(CONFIG_WDF_EXT_WASM_APP_MQTT)
    list(APPEND include_dir "esp_mqtt/include")
    list(APPEND priv_include_dir "esp_mqtt/private_include")
    list(APPEND srcs "esp_mqtt/src/wm_ext_wasm_app_mqtt.c")
endif()

if(CONFIG_WDF_EXT_WASM_APP_LVGL)
    list(APPEND include_dir "esp_lvgl/include" "esp_lvgl/include/lvgl/src" "esp_lvgl/include/lvgl/src/core")
    list(APPEND priv_include_dir "esp_lvgl/private_include")
    list(APPEND srcs "esp_lvgl/src/wm_ext_wasm_app_lvgl.c")

    if(NOT CONFIG_USING_CUSTOMER_LV_CONF_H)
        list(APPEND include_dir "esp_lvgl/include/config")
    endif()
endif()

if(CONFIG_WDF_EXT_WASM_APP_HTTP_CLIENT)
    list(APPEND include_dir "esp_http_client/include")
    list(APPEND priv_include_dir "esp_http_client/private_include")
    list(APPEND srcs "esp_http_client/src/wm_ext_wasm_app_http_client.c")
endif()

if(CONFIG_WDF_EXT_WASM_APP_WIFI_PROVISIONING)
    list(APPEND include_dir "esp_wifi/include")
    list(APPEND include_dir "wifi_provisioning/include")
    list(APPEND priv_include_dir "wifi_provisioning/private_include")
    list(APPEND srcs "wifi_provisioning/src/wm_ext_wasm_app_wifi_provisioning.c")
endif()

if(CONFIG_WDF_EXT_WASM_APP_RMAKER)
    list(APPEND include_dir "esp-rainmaker/include/esp_rainmaker")
    list(APPEND include_dir "esp-rainmaker/include/esp_schedule")
    list(APPEND include_dir "esp-rainmaker/include/rmaker_common")
    list(APPEND priv_include_dir "esp-rainmaker/private_include")
    list(APPEND srcs "esp-rainmaker/src/wm_ext_wasm_app_rmaker.c")
    list(APPEND srcs "esp-rainmaker/src/standard_types/esp_rmaker_standard_devices.c")
    list(APPEND srcs "esp-rainmaker/src/standard_types/esp_rmaker_standard_params.c")
    list(APPEND srcs "esp-rainmaker/src/standard_types/esp_rmaker_standard_services.c")
endif()

idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${include_dir}
                       PRIV_INCLUDE_DIRS ${priv_include_dir}
                       REQUIRES "wamr" "esp_common" "esp_event")

if(CONFIG_WDF_EXT_WASM_APP_MQTT)
    target_link_libraries(${COMPONENT_LIB} INTERFACE "-Wl,--export=on_mqtt_dispatch_event")
endif()