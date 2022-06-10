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

if(CONFIG_WAMR_EXTENDED_LIBC_ERRNO)
    list(APPEND srcs "libc-builtin-extended/src/libc_errno.c")
endif()

if(CONFIG_WAMR_EXTENDED_LIBC_IOCTL)
    list(APPEND srcs "libc-builtin-extended/src/libc_ioctl.c")
    list(APPEND include_dirs "libc-builtin-extended/include")
    list(APPEND priv_include_dir "libc-builtin-extended/private_include")
endif()

idf_component_register(SRCS         ${srcs}
                       INCLUDE_DIRS ${include_dirs}
                       PRIV_INCLUDE_DIRS ${priv_include_dir}
                       REQUIRES "data_sequence")

if(CONFIG_WAMR_EXTENDED_LIBC_ERRNO)
    target_link_libraries(${COMPONENT_LIB} INTERFACE "-Wl,--export=libc_builtin_set_errno")
endif()

target_link_libraries(${COMPONENT_LIB} INTERFACE "-Wl,--wrap=ioctl")
