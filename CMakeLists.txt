cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(vhdlang)

# file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(lexer ${SOURCES} tools/lexer.cpp)
target_compile_options(lexer PUBLIC "-Wall")
target_include_directories(lexer PUBLIC include)
