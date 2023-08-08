add_executable(sandbox src/main.c)
set_property(TARGET sandbox PROPERTY C_STANDARD 99)

target_link_libraries(sandbox PRIVATE walnut)