add_library(
    walnut src/walnut.c include/walnut/walnut.h src/mem.c include/walnut/mem.h
           src/debug.c include/walnut/debug.h include/walnut/decode.h
           src/assembler/assembler.c include/walnut/assembler/assembler.h
           include/walnut/opcode.h
)

set_property(TARGET walnut PROPERTY C_STANDARD 99)
if(MSVC)
  target_compile_options(walnut PRIVATE /W4 /WX)
else()
  target_compile_options(walnut PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
target_include_directories(walnut PUBLIC include)