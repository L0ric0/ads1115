set(ADS1115_HEADER
    "ads1115/include/ads1115/ads1115.hpp"
    "ads1115/include/ads1115/parameters.hpp"
    "ads1115/include/ads1115/config.hpp"
    "ads1115/include/ads1115/bit.hpp"
    "ads1115/include/ads1115/threshold.hpp"
)

if(BUILD_SHARED_LIBS)
set(LIB_LINKAGE SHARED)
else()
set(LIB_LINKAGE STATIC)
endif()

add_library(ads1115 ${LIB_LINKAGE}
    "include/ads1115/ads1115.hpp"    "src/ads1115.cpp"
    "include/ads1115/parameters.hpp"
    "include/ads1115/config.hpp"     "src/config.cpp"
    "include/ads1115/bit.hpp"
    "include/ads1115/threshold.hpp"  "src/threshold.cpp"
)

generate_export_header(ads1115 EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/ads1115/detail/ads1115_export.h")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/ads1115/detail/ads1115_export.h"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/ads1115/detail"
)

set_target_properties(ads1115 PROPERTIES PUBLIC_HEADER
        "${ADS1115_HEADER}"
)

add_library(ads1115::ads1115 ALIAS ads1115)

target_link_libraries(ads1115 PRIVATE project_options
                                      project_warnings)

target_include_directories(ads1115 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/> #<prefix>/include
)

target_include_directories(ads1115 PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include/> #<prefix>/include
)

find_package(i2c-device CONFIG REQUIRED)
target_link_libraries(ads1115 PRIVATE i2c::i2c-device)

