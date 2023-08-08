add_library(
    walnut src/vm.c include/walnut/vm.h 
)

set_property(TARGET walnut PROPERTY C_STANDARD 99)
target_include_directories(walnut PUBLIC include)