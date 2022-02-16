cmake_minimum_required(VERSION 3.10)

if(NOT DEFINED ${CMAKE_TOOLCHAIN_FILE})
message(STATUS ">>> setting CMAKE_TOOLCHAIN_FILE")

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(ads1115 VERSION 0.2.0)

include(GNUInstallDirs)
include(CheckIncludeFiles)
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)
include(PreventInSourceBuilds)
include(StandardProjectSettings)
include(StaticAnalyzers)
include(CompilerWarnings)
include(Doxygen)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings)

enable_doxygen()

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" OFF)
option(ENABLE_COVERAGE "Generate coverage reports." OFF)
option(ENABLE_FUZZING "Enable Fuzzing Builds" OFF)

if(ENABLE_TESTING)
    message(STATUS ">>> Testing enabled.")
    enable_testing()
    message("Building Tests.")
    if(ENABLE_COVERAGE)
        include(CodeCoverage)
    endif()
    add_subdirectory(tests)
endif()

add_subdirectory(ads1115)

install(TARGETS ads1115 project_warnings project_options
        EXPORT ads1115-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ads1115
)

export(EXPORT ads1115-targets NAMESPACE ads1115:: FILE ads1115-targets.cmake)

set(CMAKE_INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/ads1115)

install(EXPORT ads1115-targets
        DESTINATION ${CMAKE_INSTALL_CONFIGDIR}
        NAMESPACE ads1115::
)

configure_package_config_file(${PROJECT_SOURCE_DIR}/cmake/ads1115-config.cmake.in ${PROJECT_BINARY_DIR}/ads1115-config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_CONFIGDIR}
        PATH_VARS CMAKE_INSTALL_FULL_INCLUDEDIR
)

write_basic_package_version_file(${PROJECT_BINARY_DIR}/ads1115-config-version.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

install(FILES ${PROJECT_BINARY_DIR}/ads1115-config.cmake ${PROJECT_BINARY_DIR}/ads1115-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_CONFIGDIR}
)