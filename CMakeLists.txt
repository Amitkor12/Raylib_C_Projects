cmake_minimum_required(VERSION 3.10)
project(raylib_c_demo C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(
    ${PROJECT_NAME} 
    main.c 
    src/AnalogClock.c
    src/AnalogClock.h)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} raylib m pthread dl GL X11)
