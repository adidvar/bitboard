cmake_minimum_required(VERSION 3.14)

project(bitboardTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
    find_package(bitboard REQUIRED)
    enable_testing()
endif()

# ---- Tests ----

add_executable(bitboard_test
   source/bitboard_test.cpp
   source/position_test.cpp
   source/turn_test.cpp
)
target_link_libraries(bitboard_test PRIVATE bitboard::bitboard)
target_compile_features(bitboard_test PRIVATE cxx_std_20)

add_test(NAME bitboard_test COMMAND bitboard_test)

# ---- End-of-file commands ----

add_folders(Test)
