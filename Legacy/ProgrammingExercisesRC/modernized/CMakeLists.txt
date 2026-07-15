cmake_minimum_required(VERSION 3.20)

project(programming_exercises_rc LANGUAGES CXX)

add_executable(programming_exercises_tests
    tests/programming_exercises_tests.cpp
)

target_include_directories(programming_exercises_tests PRIVATE include)
target_compile_features(programming_exercises_tests PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(programming_exercises_tests PRIVATE /W4 /permissive-)
else()
    target_compile_options(programming_exercises_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_test(NAME programming_exercises_tests COMMAND programming_exercises_tests)
