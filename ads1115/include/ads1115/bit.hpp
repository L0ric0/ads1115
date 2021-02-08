#ifndef ADS1115_BIT_HPP_
#define ADS1115_BIT_HPP_

// stl
#include <bit>
#include <cstring>
#include <type_traits>

namespace ADS1115::util
{
    template <class To, class From>
    typename std::enable_if_t<
        sizeof(To) == sizeof(From)
            && std::is_trivially_copyable_v<From> && std::is_trivially_copyable_v<To>,
        To>
    // constexpr support needs compiler magic
    bit_cast(const From& src) noexcept
    {
        static_assert(
            std::is_trivially_constructible_v<To>,
            "This implementation additionally requires destination type to be trivially "
            "constructible");

        To dst;
        std::memcpy(&dst, &src, sizeof(To));
        return dst;
    }

    template <class T>
    typename std::enable_if_t<sizeof(T) == 2, T> byte_swap(const T value)
    {
        return static_cast<T>(((value & 0xff) << 8) | ((value & 0xff00) >> 8));
    }

    template <class T>
    typename std::enable_if_t<sizeof(T) == 2, T> to_device_repr(const T value)
    {
        if constexpr (std::endian::native != std::endian::big) {
            return byte_swap(value);
        }
        return value;
    }

    template <class T>
    typename std::enable_if_t<sizeof(T) == 2, T> from_device_repr(const T value)
    {
        return to_device_repr(value);
    }
} // namespace ADS1115::util

#endif // ADS1115_BIT_HPP_
