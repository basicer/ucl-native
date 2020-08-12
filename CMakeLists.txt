
cmake_minimum_required(VERSION 3.10)

project(ucl)
set(CMAKE_CXX_STANDARD 17)


if(APPLE)
        set(CMAKE_EXE_LINKER_FLAGS "-pagezero_size 10000 -image_base 100000000")
endif()

add_subdirectory(libs/luajit)
add_subdirectory(libs/sol2)


add_custom_command(
    OUTPUT  out.h
    COMMAND ${CMAKE_COMMAND} -E env LUA_PATH=${CMAKE_CURRENT_SOURCE_DIR}/libs/luajit/src/?.lua $<TARGET_FILE:lua> -b -g -t h -n out ${CMAKE_CURRENT_SOURCE_DIR}/main.lua ${CMAKE_CURRENT_BINARY_DIR}/out.h
    DEPENDS $<TARGET_FILE:lua> main.lua
)


add_executable(ucl main.cpp ${CMAKE_CURRENT_BINARY_DIR}/out.h)
target_link_libraries(ucl PRIVATE liblua-static sol2)
target_include_directories(ucl PRIVATE liblua-static sol2 ${CMAKE_CURRENT_BINARY_DIR})



