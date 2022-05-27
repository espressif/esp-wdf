set(srcs
    "app-framework/app-native-shared/attr_container.c"
    "app-framework/app-native-shared/restful_utils.c"
    "app-framework/base/app/bh_platform.c"
    "app-framework/base/app/request.c"
    "app-framework/base/app/timer.c"
    )

set(include_dirs
    "app-framework/include"
    )

idf_component_register(SRCS         ${srcs}
                       INCLUDE_DIRS ${include_dirs}
                       )