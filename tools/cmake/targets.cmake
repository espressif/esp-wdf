#
# Set the target used for the standard project build.
#
macro(__target_init)
endmacro()

#
# Used by the project CMake file to set the toolchain before project() call.
#
macro(__target_set_toolchain)
    idf_build_get_property(wdf_path WDF_PATH)

    # First try to load the toolchain file from the tools/cmake/directory of IDF
    set(toolchain_file_global ${wdf_path}/tools/cmake/toolchain-wasi.cmake)
    if(EXISTS ${toolchain_file_global})
        set(CMAKE_TOOLCHAIN_FILE ${toolchain_file_global})
    else()
        message(FATAL_ERROR "Toolchain file ${toolchain_file_global} not found")
    endif()
endmacro()
