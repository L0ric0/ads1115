add_library(ads1115++
    "include/ads1115++/ads1115.hpp" "src/ads1115.cpp"
    "include/ads1115++/fileno.hpp" "src/fileno.cpp"
    "include/ads1115++/parameters.hpp"
    "include/ads1115++/config.hpp" "src/config.cpp"
    "include/ads1115++/bit.hpp"
    "include/ads1115++/threshold.hpp"
)

target_include_directories(ads1115++ PUBLIC include)

target_link_libraries(ads1115++ PUBLIC i2c)
