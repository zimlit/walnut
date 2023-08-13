add_executable(walnutTest src/main.c)
target_link_libraries(walnutTest PRIVATE walnut)
target_link_libraries(walnutTest PRIVATE Check::check)

add_test(NAME Walnut COMMAND walnutTest)