set(LV_DEMO_DIR "")
set(LV_DEMOS_SOURCES "")

get_filename_component(LV_DEMO_DIR "${CMAKE_CURRENT_LIST_DIR}/../../lv_demo_widgets/main" ABSOLUTE)

idf_component_register(SRC_DIRS "assets" "." ${LV_DEMO_DIR}
                       INCLUDE_DIRS "." ${LV_DEMO_DIR})

target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLV_USE_DEMO_BENCHMARK"
                                                   "-DLV_EXTERNAL_DATA_AND_DESTRUCTOR"
                                                   "-DLV_EXT_DATA_MAX_NUM=3")
