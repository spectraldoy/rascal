cmake_minimum_required(VERSION 3.29.2)
project(rascal)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Make sure developers do not run cmake in the main project directory, to keep
# build artifacts from becoming clutter
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed.
    Please make a new directory (called a build directory) and run CMake from there.
    You may need to remove CMakeCache.txt." )
endif()
# Turn on debug builds if we are building in a devel shell
if (CMAKE_BUILD_TYPE STREQUAL "" AND "$ENV{DEVEL_SHELL}" STREQUAL "1")
    message(STATUS "Setting debug build type by default in devel shell")
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Output binaries to a sub directory "bin"
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Enable cmake testing
include(CTest)
enable_testing()

# Enable GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

include_directories(include)

# libraries
add_library(grammar_lib src/grammar.cpp)
add_library(result_lib src/result.cpp)
add_library(token_lib src/token.cpp)
add_library(lexer_lib src/lexer.cpp)

# Main executable

# Test executable
add_executable(lexer_lib_test tests/lexer_test.cpp)
target_link_libraries(lexer_lib_test lexer_lib token_lib result_lib gtest_main)

# Configure gtest
gtest_discover_tests(lexer_lib_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)

