idf_component_register(SRCS "src/esp_qrcode_main.c" "src/esp_qrcode_wrapper.c" "src/qrcodegen.c"
                    INCLUDE_DIRS "include"
                    PRIV_INCLUDE_DIRS "private_include"
                    REQUIRES "esp_common" "log"
                    )
