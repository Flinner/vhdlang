cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 17)

project(vhdlang)

# file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
set(SOURCES src/Lexer.cpp)

add_executable(vhdlang-lexer ${SOURCES} tools/vhdlang-lexer.cpp)
target_compile_options(vhdlang-lexer PUBLIC "-Wall")
# target_compile_options(vhdlang-lexer PUBLIC "-g")
target_compile_options(vhdlang-lexer PUBLIC "-gdwarf-4") # For clang
target_include_directories(vhdlang-lexer PUBLIC include)


# --- Optional Doxygen ---
option(ENABLE_DOCS "Build Doxygen documentation" OFF)

if(ENABLE_DOCS)
    find_package(Doxygen REQUIRED)

    if(DOXYGEN_FOUND)
        add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
        )
    else()
        message(WARNING "Doxygen not found, documentation target will not be available")
    endif()
endif()
