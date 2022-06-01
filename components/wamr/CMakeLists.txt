set(srcs
    "app-framework/app-native-shared/attr_container.c"
    "app-framework/app-native-shared/restful_utils.c"
    "app-framework/base/app/bh_platform.c"
    "app-framework/base/app/request.c"
    "app-framework/base/app/timer.c"
    )

if(CONFIG_WAMR_EXTENDED_LIBC_ERRNO)
    list(APPEND srcs "libc-builtin-extended/src/libc_errno.c")
endif()

set(include_dirs
    "app-framework/include"
    )

idf_component_register(SRCS         ${srcs}
                       INCLUDE_DIRS ${include_dirs}
                       )

if(CONFIG_WAMR_EXTENDED_LIBC_ERRNO)
    target_link_libraries(${COMPONENT_LIB} INTERFACE "-Wl,--export=libc_builtin_set_errno")
endif()
