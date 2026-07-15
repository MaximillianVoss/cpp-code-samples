cmake_minimum_required(VERSION 3.20)

project(inclined_plane_friction_study LANGUAGES CXX)

add_executable(inclined_plane_friction_tests
    tests/inclined_plane_friction_tests.cpp
)

target_include_directories(inclined_plane_friction_tests PRIVATE include)
target_compile_features(inclined_plane_friction_tests PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(inclined_plane_friction_tests PRIVATE /W4 /permissive-)
else()
    target_compile_options(inclined_plane_friction_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_test(NAME inclined_plane_friction_tests COMMAND inclined_plane_friction_tests)
