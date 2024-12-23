#ifndef AOC_UTILITY_UTILITY_H
#define AOC_UTILITY_UTILITY_H

#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

// Macro for checking if `<cmath>` has constexpr support
#if __GNUC_MINOR__ >= 4
#define AOC_SUPPORTS_CONSTEXPR_CMATH
#endif

namespace aoc
{
    // --------------------------------------------------------------------------------
    // Concepts
    // --------------------------------------------------------------------------------

    template<typename T>
    concept Number = std::integral<T> || std::floating_point<T>;

    template<typename T>
    concept Hashable = requires(T v)
    {
        { std::hash<T>()(v) } -> std::convertible_to<std::size_t>;
    };

    // --------------------------------------------------------------------------------
    // Utility functions
    // --------------------------------------------------------------------------------

    template<typename T>
    inline void hash_combine(std::size_t& seed, const T& v)
    {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9E3779B9 + (seed << 6) + (seed >> 2);
    }

    // Creates an integer number out of a vector of digits
    template<std::integral T>
    T vec_to_int(const std::vector<T>& vec)
    {
        T result = 0;
        for (const T i : vec)
        {
            result += i;
            result *= 10;
        }

        return result;
    }

    // Creates an integer number out of an array of digits
    template<std::integral T, std::size_t N>
    T array_to_int(const std::array<T, N>& arr)
    {
        T result = 0;
        for (const T i : arr)
        {
            result *= 10;
            result += i;
        }

        return result;
    }

    // Get the intersection of two `std::unordered_set`s
    template<Hashable T>
    std::unordered_set<T> set_intersection(const std::unordered_set<T>& a, const std::unordered_set<T>& b)
    {
        std::unordered_set<T> result;
        for (const T& v : a)
        {
            if (b.contains(v))
            {
                result.insert(v);
            }
        }

        return result;
    }

} // aoc

namespace std
{
    // --------------------------------------------------------------------------------
    // Hash functions
    // --------------------------------------------------------------------------------

    template<aoc::Hashable T, aoc::Hashable U>
    struct hash<pair<T, U>>
    {
        std::size_t operator()(const pair<T, U>& p) const
        {
            std::size_t seed = 0;
            aoc::hash_combine(seed, p.first);
            aoc::hash_combine(seed, p.second);
            return seed;
        }
    };

    template<aoc::Hashable T>
    struct hash<vector<T>>
    {
        std::size_t operator()(const vector<T>& v) const
        {
            std::size_t seed = 0;
            for (const T& i : v)
            {
                aoc::hash_combine(seed, i);
            }

            return seed;
        }
    };

    template<aoc::Hashable T, size_t N>
    struct hash<array<T, N>>
    {
        std::size_t operator()(const array<T, N>& v) const
        {
            std::size_t seed = 0;
            for (const T& i : v)
            {
                aoc::hash_combine(seed, i);
            }

            return seed;
        }
    };

    template<aoc::Hashable T>
    struct hash<unordered_set<T>>
    {
        std::size_t operator()(const unordered_set<T>& s) const
        {
            std::size_t seed = 0;
            for (const T& v : s)
            {
                aoc::hash_combine(seed, v);
            }

            return seed;
        }
    };

    template<>
    struct hash<tuple<string, uint64_t, uint64_t>>
    {
        std::size_t operator()(const tuple<string, uint64_t, uint64_t>& t) const
        {
            std::size_t seed = 0;
            aoc::hash_combine(seed, get<0>(t));
            aoc::hash_combine(seed, get<1>(t));
            aoc::hash_combine(seed, get<2>(t));
            return seed;
        }
    };

} // std

#endif // !AOC_UTILITY_UTILITY_H
