idf_component_register(SRCS "camera.c" "temp.c" "data_receive.c" "data_send.c"
                            "mesh_main.c"
                    INCLUDE_DIRS "." "include")
target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
