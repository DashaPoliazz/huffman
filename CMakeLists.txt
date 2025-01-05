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

# Add the main executable (optional if you have an application)
add_executable(HuffmanMain src/main.cpp)
target_include_directories(HuffmanMain PUBLIC include)

# ✅ Enable recursive search for test files
file(GLOB_RECURSE TEST_SOURCES "tests/unit/*.cpp")

# ✅ Check if test files were found
if(TEST_SOURCES)
    # ✅ Create test executable with all discovered test files
    add_executable(HuffmanTests ${TEST_SOURCES})
else()
    message(FATAL_ERROR "No test files found in tests/unit!")
endif()

# ✅ Set include directories and link Google Test
target_include_directories(HuffmanTests PUBLIC include)
target_link_libraries(HuffmanTests gtest gtest_main pthread)

# ✅ Enable testing and register all tests automatically
enable_testing()
add_test(NAME HuffmanTests COMMAND ${CMAKE_BINARY_DIR}/HuffmanTests)

