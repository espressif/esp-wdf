idf_component_register(SRC_DIRS "assets" "."
                       INCLUDE_DIRS .)

target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLV_USE_DEMO_WIDGETS")
