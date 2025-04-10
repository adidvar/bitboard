if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/bitboard-${PROJECT_VERSION}"
      CACHE STRING ""
  )
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package bitboard)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT bitboard_Development
)

install(
    TARGETS bitboard_bitboard
    EXPORT bitboardTargets
    RUNTIME #
    COMPONENT bitboard_Runtime
    LIBRARY #
    COMPONENT bitboard_Runtime
    NAMELINK_COMPONENT bitboard_Development
    ARCHIVE #
    COMPONENT bitboard_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    bitboard_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE bitboard_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(bitboard_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${bitboard_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT bitboard_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${bitboard_INSTALL_CMAKEDIR}"
    COMPONENT bitboard_Development
)

install(
    EXPORT bitboardTargets
    NAMESPACE bitboard::
    DESTINATION "${bitboard_INSTALL_CMAKEDIR}"
    COMPONENT bitboard_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
