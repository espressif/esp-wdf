aux_source_directory(. SRCS)

add_library(main STATIC ${SRCS})

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})