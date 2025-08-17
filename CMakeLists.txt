cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(vhdlang)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(vhdlang-lexer ${SOURCES} tools/vhdlang-lexer.cpp)
target_compile_options(vhdlang-lexer PUBLIC "-Wall")
target_compile_options(vhdlang-lexer PUBLIC "-g")
target_include_directories(vhdlang-lexer PUBLIC include)
