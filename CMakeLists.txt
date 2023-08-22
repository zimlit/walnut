cmake_minimum_required(VERSION 3.16)

project(
    walnut
    VERSION 0.1
    LANGUAGES C
)


add_subdirectory(walnut)
add_subdirectory(walnutApp)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    include(FetchContent)
    FetchContent_Declare(Check
        GIT_REPOSITORY https://github.com/libcheck/check
        GIT_TAG master
    )

FetchContent_MakeAvailable(Check)
endif()
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(test)
endif()
