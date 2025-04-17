cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    bitboard
    VERSION 0.1.0
    DESCRIPTION "A library for generating chess moves using bitboards"
    HOMEPAGE_URL "https://github.com/adidvar/bitboard"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    bitboard_bitboard

    #sources

    source/bitboard.cpp
    source/position.cpp
    source/zobrist.cpp
    source/figure.cpp
    source/fen.cpp

    #headers

    include/bitboard/bitboard.hpp
    include/bitboard/color.hpp
    include/bitboard/figure.hpp
    include/bitboard/position.hpp
    include/bitboard/turn.hpp
    include/bitboard/utils/bit_const.hpp
    include/bitboard/utils/bit_intrinsics.hpp
    include/bitboard/utils/bit_operators.hpp
    include/bitboard/utils/bit_utils.hpp
    include/bitboard/utils/fen_parser.hpp
)
add_library(bitboard::bitboard ALIAS bitboard_bitboard)

include(GenerateExportHeader)
generate_export_header(
    bitboard_bitboard
    BASE_NAME bitboard
    EXPORT_FILE_NAME export/bitboard/bitboard_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(bitboard_bitboard PUBLIC BITBOARD_STATIC_DEFINE)
endif()

set_target_properties(
    bitboard_bitboard PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME bitboard
    OUTPUT_NAME bitboard
)

target_include_directories(
    bitboard_bitboard ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    bitboard_bitboard SYSTEM
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(bitboard_bitboard PUBLIC cxx_std_20)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
    include(cmake/install-rules.cmake)
endif()

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
    option(BUILD_EXAMPLES "Build examples tree." "${bitboard_DEVELOPER_MODE}")
    if(BUILD_EXAMPLES)
        add_subdirectory(example)
    endif()
endif()

# ---- Developer mode ----

if(NOT bitboard_DEVELOPER_MODE)
    return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
    message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of bitboard"
  )
endif()

include(cmake/dev-mode.cmake)
