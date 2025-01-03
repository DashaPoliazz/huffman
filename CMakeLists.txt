cmake_minimum_required(VERSION 3.10)
project(Huffman)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define paths for header files
include_directories(include)

# Add Google Test and set up the test framework
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz
)
FetchContent_MakeAvailable(googletest)

# Add the main executable (if you have one)
add_executable(HuffmanMain src/main.cpp)
target_include_directories(HuffmanMain PUBLIC include)

# Add test files
file(GLOB TEST_SOURCES "tests/*.cpp")
add_executable(HuffmanTests ${TEST_SOURCES})
target_include_directories(HuffmanTests PUBLIC include)
target_link_libraries(HuffmanTests gtest gtest_main pthread)

# Enable testing
enable_testing()
add_test(NAME HuffmanTests COMMAND HuffmanTests)

