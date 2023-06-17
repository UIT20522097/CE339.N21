idf_component_register(SRCS "uart.c" "mqtt.c" "node_manager.c" "receive_data.c"
                            "mesh_main.c"
                    INCLUDE_DIRS "." "include")
target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
