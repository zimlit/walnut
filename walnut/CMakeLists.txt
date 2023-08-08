add_library(
    walnut src/walnut.c include/walnut/walnut.h src/mem.c include/walnut/mem.h
)

set_property(TARGET walnut PROPERTY C_STANDARD 99)
target_include_directories(walnut PUBLIC include)