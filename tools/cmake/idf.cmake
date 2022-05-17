get_property(__wdf_env_set GLOBAL PROPERTY __WDF_ENV_SET)
if(NOT __wdf_env_set)
    # Infer an WDF_PATH relative to the tools/cmake directory
    get_filename_component(_wdf_path "${CMAKE_CURRENT_LIST_DIR}/../.." REALPATH)
    file(TO_CMAKE_PATH "${_wdf_path}" _wdf_path)

    # Get the path set in environment
    set(wdf_path $ENV{WDF_PATH})

    # Environment WDF_PATH should match the inferred WDF_PATH. If not, warn the user.
    # (Note: REALPATH is needed in both above steps to account for case on case
    # insensitive filesystems, or relative paths)
    if(wdf_path)
        get_filename_component(wdf_path "${wdf_path}" REALPATH)
        file(TO_CMAKE_PATH "${wdf_path}" wdf_path)

        if(NOT wdf_path STREQUAL _wdf_path)
            message(WARNING "WDF_PATH environment variable is different from inferred WDF_PATH.
                            Check if your project's top-level CMakeLists.txt includes the right
                            CMake files. Environment WDF_PATH will be used for the build:
                            ${wdf_path}")
        endif()
    else()
        message(WARNING "WDF_PATH environment variable not found. Setting WDF_PATH to '${_wdf_path}'.")
        set(wdf_path ${_wdf_path})
        set(ENV{WDF_PATH} ${_wdf_path})
    endif()

    # Include other CMake modules required
    set(CMAKE_MODULE_PATH
        "${wdf_path}/tools/cmake"
        "${wdf_path}/tools/cmake/third_party"
        ${CMAKE_MODULE_PATH})

    set(WDF_PATH ${wdf_path})

    include(build)
    include(component)
    include(GetGitRevisionDescription)
    include(git_submodules)
    include(kconfig)
    include(utilities)

    __build_init("${wdf_path}")

    set_property(GLOBAL PROPERTY __WDF_ENV_SET 1)
endif()
