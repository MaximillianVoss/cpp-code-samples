cmake_minimum_required(VERSION 3.20)

project(drunkard_card_game LANGUAGES CXX)

add_executable(drunkard_card_game_tests
    tests/drunkard_card_game_tests.cpp
)

target_include_directories(drunkard_card_game_tests PRIVATE include)
target_compile_features(drunkard_card_game_tests PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(drunkard_card_game_tests PRIVATE /W4 /permissive-)
else()
    target_compile_options(drunkard_card_game_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_test(NAME drunkard_card_game_tests COMMAND drunkard_card_game_tests)
