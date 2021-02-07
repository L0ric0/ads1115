set(BINARY ads1115::test)

add_executable(${BINARY} EXCLUDE_FROM_ALL
    "src/ads1115.cpp"
    "src/config.cpp"
    "src/threshold.cpp"
)

target_include_directories(${BINARY} PRIVATE include)

find_package(GTest REQUIRED)
target_link_libraries(${BINARY} PRIVATE GTest::GTest GTest::Main)

target_link_libraries(${BINARY} PRIVATE ads1115::ads1115)

gtest_discover_tests(${BINARY})

if (COVERAGE)
        append_coverage_compiler_flags()
        setup_target_for_coverage_gcovr_html(
            NAME ${CMAKE_PROJECT_NAME}_coverage
            EXECUTABLE ctest -j ${PROCESSOR_COUNT}
            DEPENDENCIES ${BINARY}
            EXCLUDE ${PROJECT_SOURCE_DIR}/tests
        )
endif()
