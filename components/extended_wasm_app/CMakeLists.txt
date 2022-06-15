set(srcs  "")
set(include_dir "")
set(priv_include_dir "")

if(CONFIG_WDF_EXT_WASM_APP_MQTT)
    list(APPEND include_dir "esp_mqtt/include")
    list(APPEND priv_include_dir "esp_mqtt/private_include")
    list(APPEND srcs "esp_mqtt/src/wm_ext_wasm_app_mqtt.c")
endif()

idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${include_dir}
                       PRIV_INCLUDE_DIRS ${priv_include_dir}
                       REQUIRES "wamr" "esp_common" "esp_event")

if(CONFIG_WDF_EXT_WASM_APP_MQTT)
    target_link_libraries(${COMPONENT_LIB} INTERFACE "-Wl,--export=on_mqtt_dispatch_event")
endif()