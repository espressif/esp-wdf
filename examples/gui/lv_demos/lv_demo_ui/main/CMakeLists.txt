idf_component_register(SRC_DIRS "assets" "."
                       INCLUDE_DIRS .)

target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLV_USE_DEMO_WIDGETS"
                                                   "-DLV_EXTERNAL_DATA_AND_DESTRUCTOR"
                                                   "-DLV_EXT_DATA_MAX_NUM=3")
