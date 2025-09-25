idf_component_register(SRC_DIRS "assets" "."
                       INCLUDE_DIRS ".")

target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLV_USE_DEMO_MUSIC"
                                                   "-DLV_DEMO_MUSIC_SQUARE=0"
                                                   "-DLV_DEMO_MUSIC_LANDSCAPE=0"
                                                   "-DLV_DEMO_MUSIC_ROUND=0"
                                                   "-DLV_DEMO_MUSIC_LARGE=0"
                                                   "-DLV_DEMO_MUSIC_AUTO_PLAY=0"
                                                   "-DLV_EXTERNAL_DATA_AND_DESTRUCTOR"
                                                   "-DLV_EXT_DATA_MAX_NUM=3")
