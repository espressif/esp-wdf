cmake_minimum_required(VERSION 3.5)
project(esp-wdf C CXX ASM)

if(CMAKE_CURRENT_LIST_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Current directory '${CMAKE_CURRENT_LIST_DIR}' is not buildable. "
    "Change directories to one of the example projects in '${CMAKE_CURRENT_LIST_DIR}/examples' and try "
    "again.")
endif()

unset(compile_options)
unset(link_options)

if(CONFIG_COMPILER_OPTIMIZATION_SIZE)
    list(APPEND compile_options "-Os")
elseif(CONFIG_COMPILER_OPTIMIZATION_DEFAULT)
    list(APPEND compile_options "-Og")
elseif(CONFIG_COMPILER_OPTIMIZATION_NONE)
    list(APPEND compile_options "-O0")
elseif(CONFIG_COMPILER_OPTIMIZATION_PERF)
    list(APPEND compile_options "-O3")
endif()

if(CONFIG_COMPILER_WASI_NO_USE_STDLIB)
    list(APPEND compile_options "-nostdlib")
    list(APPEND link_options "-nostdlib")
endif()

if(CONFIG_COMPILER_WASI_USE_WAMR_LIBC_BUILTIN_SYSROOT)
    idf_build_get_property(idf_path IDF_PATH)
    set(CMAKE_SYSROOT ${IDF_PATH}/components/wamr/libc-builtin-sysroot)
endif()

if(CONFIG_COMPILER_WASI_STACK_SIZE)
    list(APPEND link_options "-z stack-size=${CONFIG_COMPILER_WASI_STACK_SIZE}")
endif()

if(CONFIG_COMPILER_WASI_USE_SHARED_MEMORY)
    list(APPEND link_options "-Wl,--shared-memory")
endif()

if(CONFIG_COMPILER_WASI_INITIAL_MEMORY)
    list(APPEND link_options "-Wl,--initial-memory=${CONFIG_COMPILER_WASI_INITIAL_MEMORY}")
endif()

if(CONFIG_COMPILER_WASI_MAX_MEMORY)
    list(APPEND link_options "-Wl,--max-memory=${CONFIG_COMPILER_WASI_MAX_MEMORY}")
endif()

if(CONFIG_WAMR_APP_FRAMEWORK)
    list(APPEND link_options "-Wl,--export=on_init")
    list(APPEND link_options "-Wl,--export=on_destroy")
endif()

if(CONFIG_WAMR_APP_FRAMEWORK_EXPORT_REQUEST_RESPONSE)
    list(APPEND link_options "-Wl,--export=on_request")
    list(APPEND link_options "-Wl,--export=on_response")
endif()

if(CONFIG_WAMR_APP_FRAMEWORK_EXPORT_TIMER)
    list(APPEND link_options "-Wl,--export=on_timer_callback")
endif()

idf_build_set_property(COMPILE_OPTIONS "${compile_options}" APPEND)
idf_build_set_property(LINK_OPTIONS "${link_options}" APPEND)

idf_build_get_property(build_component_targets __BUILD_COMPONENT_TARGETS)

# Add each component as a subdirectory, processing each component's CMakeLists.txt
foreach(component_target ${build_component_targets})
    __component_get_property(dir ${component_target} COMPONENT_DIR)
    __component_get_property(_name ${component_target} COMPONENT_NAME)
    __component_get_property(prefix ${component_target} __PREFIX)
    __component_get_property(alias ${component_target} COMPONENT_ALIAS)
    set(COMPONENT_NAME ${_name})
    set(COMPONENT_DIR ${dir})
    set(COMPONENT_ALIAS ${alias})
    set(COMPONENT_PATH ${dir}) # for backward compatibility only, COMPONENT_DIR is preferred
    idf_build_get_property(build_prefix __PREFIX)
    set(__idf_component_context 1)
    if(NOT prefix STREQUAL build_prefix)
        add_subdirectory(${dir} ${prefix}_${_name})
    else()
        add_subdirectory(${dir} ${_name})
    endif()
    set(__idf_component_context 0)
endforeach()
