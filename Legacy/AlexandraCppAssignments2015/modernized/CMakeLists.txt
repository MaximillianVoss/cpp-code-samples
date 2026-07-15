cmake_minimum_required(VERSION 3.20)

project(alexandra_cpp_assignments_2015 LANGUAGES CXX)

add_executable(alexandra_cpp_assignments_tests
    tests/alexandra_assignments_tests.cpp
)

target_include_directories(alexandra_cpp_assignments_tests PRIVATE include)
target_compile_features(alexandra_cpp_assignments_tests PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(alexandra_cpp_assignments_tests PRIVATE /W4 /permissive-)
else()
    target_compile_options(alexandra_cpp_assignments_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_test(NAME alexandra_cpp_assignments_tests COMMAND alexandra_cpp_assignments_tests)
