set(srcs
    "core_list_join.c"
    "core_main.c"
    "core_matrix.c"
    "core_portme.c"
    "core_state.c"
    "core_util.c"
    )

idf_component_register(SRCS ${srcs})