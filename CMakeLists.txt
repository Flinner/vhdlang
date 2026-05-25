cmake_minimum_required(VERSION 3.10)

project(vhdlang)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use lld instead of ld (idk if it's working)
set(LDFLAGS "-fuse-ld=lld")

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Global compiler option
add_compile_options(-Wall -gdwarf-4)

# include_directories(${LLVM_INCLUDE_DIRS} include)
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})
llvm_map_components_to_libnames(support)

set(SOURCES
    src/Lexer.cpp
    src/Entity.cpp
    src/Common.cpp
    src/Pattern.cpp
    src/GrammarRule.cpp
    src/ASTree.cpp
    src/Parser.cpp
)

add_executable(vhdlang-lexer ${SOURCES} tools/vhdlang-lexer.cpp)
# target_compile_options(vhdlang-lexer PUBLIC "-Wall")
# target_compile_options(vhdlang-lexer PUBLIC "-g")
# target_compile_options(vhdlang-lexer PUBLIC "-gdwarf-4") # For clang
target_include_directories(vhdlang-lexer PUBLIC include ${LLVM_INCLUDE_DIRS})

# Link against LLVM libraries
target_link_libraries(vhdlang-lexer ${llvm_libs})

add_executable(vhdlang-parser ${SOURCES} tools/vhdlang-parser.cpp)
target_include_directories(vhdlang-parser PUBLIC include ${LLVM_INCLUDE_DIRS})

# Test files
add_executable(lexer-test ${SOURCES} test/lexer/loop-lexer.cpp)
# target_compile_options(lexer-test PUBLIC "-Wall")
# target_compile_options(lexer-test PUBLIC "-gdwarf-4") # For clang
target_include_directories(lexer-test PUBLIC include)

# --- Optional Doxygen ---
option(ENABLE_DOCS "Build Doxygen documentation" OFF)

if(ENABLE_DOCS)
    find_package(Doxygen REQUIRED)

    if(DOXYGEN_FOUND)
        add_custom_target(
            doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
        )
    else()
        message(
            WARNING
            "Doxygen not found, documentation target will not be available"
        )
    endif()
endif()
