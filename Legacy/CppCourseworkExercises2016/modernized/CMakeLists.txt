cmake_minimum_required(VERSION 3.20)

project(cpp_coursework_exercises_2016 LANGUAGES CXX)

add_executable(cpp_coursework_exercises_tests
    tests/coursework_exercises_tests.cpp
)

target_include_directories(cpp_coursework_exercises_tests PRIVATE
    include
    ../../ProgrammingExercisesRC/modernized/include
)
target_compile_features(cpp_coursework_exercises_tests PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(cpp_coursework_exercises_tests PRIVATE /W4 /permissive-)
else()
    target_compile_options(cpp_coursework_exercises_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_test(NAME cpp_coursework_exercises_tests COMMAND cpp_coursework_exercises_tests)
