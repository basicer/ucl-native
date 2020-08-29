
cmake_minimum_required(VERSION 3.10)

project(ucl)
set(CMAKE_CXX_STANDARD 17)


if(APPLE)
        set(CMAKE_EXE_LINKER_FLAGS "-pagezero_size 10000 -image_base 100000000")
endif()

add_subdirectory(libs/luajit)
add_subdirectory(libs/sol2)
add_subdirectory(libs/replxx)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB UCL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/libs/ucl/**.lua)

add_custom_command(
    OUTPUT  out.lua
    COMMAND ${CMAKE_COMMAND} -E env LUA_PATH=${CMAKE_CURRENT_SOURCE_DIR}/libs/luajit/src/?.lua $<TARGET_FILE:lua> ${CMAKE_CURRENT_SOURCE_DIR}/libs/ucl/pack.lua ${CMAKE_CURRENT_BINARY_DIR}/out.lua
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs/ucl
    DEPENDS $<TARGET_FILE:lua> ${UCL_SOURCES}
)

add_custom_command(
    OUTPUT  out.h
    COMMAND ${CMAKE_COMMAND} -E env LUA_PATH=${CMAKE_CURRENT_SOURCE_DIR}/libs/luajit/src/?.lua $<TARGET_FILE:lua> -b -g -t h -n out ${CMAKE_CURRENT_BINARY_DIR}/out.lua ${CMAKE_CURRENT_BINARY_DIR}/out.h
    DEPENDS $<TARGET_FILE:lua> out.lua
)


add_executable(ucl ${SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/out.h)
target_link_libraries(ucl PRIVATE liblua-static sol2 replxx)
target_include_directories(ucl PRIVATE liblua-static sol2 ${CMAKE_CURRENT_BINARY_DIR} replxx)



