cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(vhdlang)

# file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
set(SOURCES src/Lexer.cpp)

add_executable(vhdlang-lexer ${SOURCES} tools/vhdlang-lexer.cpp)
target_compile_options(vhdlang-lexer PUBLIC "-Wall")
# target_compile_options(vhdlang-lexer PUBLIC "-g")
target_compile_options(vhdlang-lexer PUBLIC "-gdwarf-4") # For clang
target_include_directories(vhdlang-lexer PUBLIC include)
