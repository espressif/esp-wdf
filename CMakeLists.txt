cmake_minimum_required(VERSION 3.5)
project(esp-wdf C CXX ASM)

if(CMAKE_CURRENT_LIST_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Current directory '${CMAKE_CURRENT_LIST_DIR}' is not buildable. "
    "Change directories to one of the example projects in '${CMAKE_CURRENT_LIST_DIR}/examples' and try "
    "again.")
endif()

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
