idf_component_register(SRCS "app_wifi.c"
                    INCLUDE_DIRS "."
                    REQUIRES extended_wasm_app esp_common esp_event log qrcode)
