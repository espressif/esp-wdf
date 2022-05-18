cmake_minimum_required(VERSION 3.10)

include(${CMAKE_CURRENT_LIST_DIR}/toolchain-wasi.cmake)

# When functions are overriden in CMake, the originals can still be accessed
# using an underscore prefixed function of the same name.
# See https://cmake.org/pipermail/cmake/2015-October/061751.html.

# Trick to temporarily redefine add_library. The following lines make sure that __add_library calls
# the original add_library(). 
function(add_library)
    
endfunction()

function(_add_library)
    
endfunction()

macro(add_library)
    __add_library(${ARGV})
    get_property(link_libraries GLOBAL PROPERTY link_library_list)
    list(APPEND link_libraries "${ARGV0}")
    set_property(GLOBAL PROPERTY link_library_list "${link_libraries}")
endmacro()

# Trick to temporarily redefine project(). The following lines make sure that __project calls
# the original project(). 
function(project)
endfunction()

function(_project)
endfunction()

macro(project project_name)
    __project(${project_name} C CXX ASM)

    #set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

    set(project_wasm ${CMAKE_PROJECT_NAME}.wasm)

    # Create a dummy file to work around CMake requirement of having a source file while adding an
    # executable.
    set(project_wasm_src ${CMAKE_BINARY_DIR}/project_wasm_src.c)
    add_custom_command(OUTPUT ${project_wasm_src}
        COMMAND ${CMAKE_COMMAND} -E touch ${project_wasm_src}
        VERBATIM)
    add_executable(${project_wasm} "${project_wasm_src}")

    function(__project_component_dir component_dir)
        get_filename_component(component_dir "${component_dir}" ABSOLUTE)
        # The directory itself is a valid idf component
        if(EXISTS ${component_dir}/CMakeLists.txt)
            add_subdirectory(${component_dir})
        else()
            # otherwise, check whether the subfolders are potential idf components
            file(GLOB component_dirs ${component_dir}/*)
            foreach(component_dir ${component_dirs})
                add_subdirectory(${component_dir})
            endforeach()
        endif()
    endfunction()

    # Look for components in the usual places: CMAKE_CURRENT_LIST_DIR/main
    # and CMAKE_CURRENT_LIST_DIR/components
    if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/main")
        __project_component_dir("${CMAKE_CURRENT_LIST_DIR}/main")
    endif()

    __project_component_dir("${CMAKE_CURRENT_LIST_DIR}/components")

    get_property(link_libraries GLOBAL PROPERTY link_library_list)

    foreach(library IN LISTS link_libraries)
        target_link_libraries(${project_wasm} ${library})
    endforeach()

endmacro()