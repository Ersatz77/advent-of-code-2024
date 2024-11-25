#ifndef AOC_UTILITY_CONCEPTS_H
#define AOC_UTILITY_CONCEPTS_H

#include <concepts>
#include <type_traits>

namespace aoc
{
    template<typename T>
    concept Integer = std::is_integral_v<T>;

    template<typename T>
    concept Float = std::is_floating_point_v<T>;

    template<typename T>
    concept Number = Integer<T> || Float<T>;

    template<typename T>
    concept Hashable = requires(T v)
    {
        { std::hash<T>()(v) } -> std::convertible_to<size_t>;
    };

} // aoc

#endif // !AOC_UTILITY_CONCEPTS_H
