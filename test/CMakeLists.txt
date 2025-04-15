cmake_minimum_required(VERSION 3.14)

project(bitboardTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
    find_package(bitboard REQUIRED)
    enable_testing()
endif()

# ---- Catch2 ----

find_package(Catch2 3 QUIET)
if (NOT Catch2_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_SHALLOW    TRUE
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.8.0)
    FetchContent_MakeAvailable(catch2)
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
endif()

# ---- Tests ----

add_executable(bitboard_test
   source/bitboard_test.cpp
   source/position_test.cpp
   source/turn_test.cpp
)
target_link_libraries(bitboard_test PRIVATE bitboard::bitboard Catch2::Catch2WithMain)
target_compile_features(bitboard_test PRIVATE cxx_std_20)

# --- Win32 copy dll

if(WIN32)
    add_custom_command(TARGET bitboard_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:bitboard_test> $<TARGET_RUNTIME_DLLS:bitboard_test>
    COMMAND_EXPAND_LISTS
  )
endif()

add_test(NAME bitboard_test COMMAND bitboard_test)

# ---- End-of-file commands ----

add_folders(Test)
