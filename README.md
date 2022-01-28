## libads1115
---
### Description
A C++20 library to interface with a [ADS1115](https://learn.adafruit.com/adafruit-4-channel-adc-breakouts/downloads). This library should also work with a ADS1113/4 (with some functions not working due to hardware restraints). The library may or may not also works with the lower resolution variants ADS1013/4/5.

### Getting Started

Add the library as a submodule to your source tree and add something like the following to your `CMakeLists.txt`.
```cmake
add_subdirectory(ads1115)
target_link_libraries(my_application PRIVATE ads1115::ads1115)
```

Create a `ADS1115` object with the path to the i2c device and a enum describing to which pin the address pin of the ADS1115 is connected. The enum can also be created by a `static_cast` of the address of the ADS1115.

```cpp
#include "ads1115/ads1115.hpp"
#include "ads1115/parameters.hpp"

int main(){
  ADS1115::ADS1115 ads{1,
                       ADS1115::ADDR::GND /* or static_cast<ADS1115::ADDR>(0x48)*/ };
}
```

To configure the ADS1115 create a `Config` object. This object is initialized with the default settings of the ADS1115.

```cpp
ADS1115::ADS1115 ads{1, ADS1115::ADDR::GND};
ADS1115::Config conf{};
ads.setRegConfig(conf);
```

In the same way the comparator thresholds can be set by creating a `Threshold` object. The default constructor will initialize the high an low thresholds with the defaults.
```cpp
ADS1115::ADS1115 ads{1, ADS1115::ADDR::GND};
ADS1115::Threshold thresh{-16, 16};
ads.setRegThreshold(thresh);
```

The configuration and the thresholds can also be read from the ADS1115 by calling `ADS1115::readRegConfig` and `ADS1115::readRegThreshold` respectively. This is done when the `ADS1115` object is created, so that the object and hardware are never out of sync.

To read from the ADS1115 the methods `int16_t ADS1115::read` and `double ADS1115::readVoltage` are provided. The `ADS1115::read` method returns the raw value of the conversion register (which is a `int16_t`) and the `ADS1115::readVoltage` returns the value of the conversion register converted to volts with respect to the current setting of the internal PGA of the ADS1115.

More documentation can be found [here](https://l0ric0.github.io/ads1115/html/index.html).

### Contributing

As this library was build with the aim to keep my plants alive, feel free to open Issues and PRs. The only thing I ask of you is to somewhat keep to the naming scheme and run `clang-format` on the edited source files.
