add_executable(walnutApp src/main.c)

set_property(TARGET walnutApp PROPERTY C_STANDARD 99)
set_property(TARGET walnutApp PROPERTY OUTPUT_NAME walnut)

if(MSVC)
  target_compile_options(walnutApp PRIVATE /W4 /WX)
else()
  target_compile_options(walnutApp PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_link_libraries(walnutApp PRIVATE walnut)