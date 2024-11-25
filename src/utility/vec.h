#ifndef AOC_UTILITY_VEC_H
#define AOC_UTILITY_VEC_H

#include <array>
#include <compare>
#include <cstdint>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>

#include "fmt/format.h"

#include "utility/concepts.h"
#include "utility/utility.h"

namespace aoc
{
    // --------------------------------------------------------------------------------
    // Vector 2
    // --------------------------------------------------------------------------------

    // A 2D vector with an x and y component
    template<Number T>
    class Vec2
    {
    public:
        using value_type = T;

        // Returns the origin (0, 0)
        static constexpr Vec2<T> origin()
        {
            return { 0, 0 };
        }

        // Returns all 4 (NESW) Vec2s around this Vec2
        constexpr std::array<Vec2<T>, 4> adjacent_cardinal() const
        {
            std::array<Vec2<T>, 4> adjacent = {};
            for (size_t i = 0; i < adjacent.size(); ++i)
            {
                adjacent[i].x = x + Vec2<T>::adjacent_cardinal_offsets[i][0];
                adjacent[i].y = y + Vec2<T>::adjacent_cardinal_offsets[i][1];
            }

            return adjacent;
        }

        // Returns all 8 Vec2s around this Vec2
        constexpr std::array<Vec2<T>, 8> adjacent() const
        {
            std::array<Vec2<T>, 8> adjacent = {};
            for (size_t i = 0; i < adjacent.size(); ++i)
            {
                adjacent[i].x = x + Vec2<T>::adjacent_offsets[i][0];
                adjacent[i].y = y + Vec2<T>::adjacent_offsets[i][1];
            }

            return adjacent;
        }

        // Returns the Vec2 as a 2 element array
        constexpr std::array<T, 2> to_array() const
        {
            return { x, y };
        }

        constexpr auto operator<=>(const Vec2<T>& rhs) const = default;

        constexpr Vec2<T>& operator+=(const Vec2<T>& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        constexpr Vec2<T>& operator-=(const Vec2<T>& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        constexpr Vec2<T>& operator*=(const Vec2<T>& rhs)
        {
            x *= rhs.x;
            y *= rhs.y;
            return *this;
        }

        constexpr Vec2<T>& operator/=(const Vec2<T>& rhs)
        {
            x /= rhs.x;
            y /= rhs.y;
            return *this;
        }

        constexpr Vec2<T>& operator+=(const T rhs)
        {
            x += rhs;
            y += rhs;
            return *this;
        }

        constexpr Vec2<T>& operator-=(const T rhs)
        {
            x -= rhs;
            y -= rhs;
            return *this;
        }

        constexpr Vec2<T>& operator*=(const T rhs)
        {
            x *= rhs;
            y *= rhs;
            return *this;
        }

        constexpr Vec2<T>& operator/=(const T rhs)
        {
            x /= rhs;
            y /= rhs;
            return *this;
        }

        constexpr Vec2<T> operator+(const Vec2<T>& rhs) const
        {
            return Vec2<T>(*this) += rhs;
        }

        constexpr Vec2<T> operator-(const Vec2<T>& rhs) const
        {
            return Vec2<T>(*this) -= rhs;
        }

        constexpr Vec2<T> operator*(const Vec2<T>& rhs) const
        {
            return Vec2<T>(*this) *= rhs;
        }

        constexpr Vec2<T> operator/(const Vec2<T>& rhs) const
        {
            return Vec2<T>(*this) /= rhs;
        }

        constexpr Vec2<T> operator+(const T rhs) const
        {
            return Vec2<T>(*this) += rhs;
        }

        constexpr Vec2<T> operator-(const T rhs) const
        {
            return Vec2<T>(*this) -= rhs;
        }

        constexpr Vec2<T> operator*(const T rhs) const
        {
            return Vec2<T>(*this) *= rhs;
        }

        constexpr Vec2<T> operator/(const T rhs) const
        {
            return Vec2<T>(*this) /= rhs;
        }

        T x = 0;
        T y = 0;

    private:
        static constexpr std::array<std::array<T, 2>, 4> adjacent_cardinal_offsets = { {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        } };
        static constexpr std::array<std::array<T, 2>, 8> adjacent_offsets = { {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
        } };
    };

    template<Number T>
    std::ostream& operator<<(std::ostream& os, const Vec2<T>& vec)
    {
        return os << fmt::format("({}, {})", vec.x, vec.y);
    }

    // --------------------------------------------------------------------------------
    // Vector 3
    // --------------------------------------------------------------------------------

    // A 3D vector with an x, y, and z component
    template<Number T>
    class Vec3
    {
    public:
        using value_type = T;

        // Returns the origin (0, 0, 0)
        static constexpr Vec2<T> origin()
        {
            return { 0, 0, 0 };
        }

        // Returns all 6 (NESWUD) Vec3s around this Vec3
        constexpr std::array<Vec3<T>, 6> adjacent_cardinal() const
        {
            std::array<Vec3<T>, 6> adjacent = {};
            for (size_t i = 0; i < adjacent.size(); ++i)
            {
                adjacent[i].x = x + Vec3<T>::adjacent_cardinal_offsets[i][0];
                adjacent[i].y = y + Vec3<T>::adjacent_cardinal_offsets[i][1];
                adjacent[i].z = z + Vec3<T>::adjacent_cardinal_offsets[i][2];
            }

            return adjacent;
        }

        // Returns all 26 Vec3s around this Vec3
        constexpr std::array<Vec3<T>, 26> adjacent() const
        {
            std::array<Vec3<T>, 26> adjacent = {};
            for (size_t i = 0; i < adjacent.size(); ++i)
            {
                adjacent[i].x = x + Vec3<T>::adjacent_offsets[i][0];
                adjacent[i].y = y + Vec3<T>::adjacent_offsets[i][1];
                adjacent[i].z = z + Vec3<T>::adjacent_offsets[i][2];
            }

            return adjacent;
        }

        // Returns the Vec3 as a 3 element array
        constexpr std::array<T, 3> to_array() const
        {
            return { x, y, z };
        }

        constexpr auto operator<=>(const Vec3<T>& rhs) const = default;

        constexpr Vec3<T>& operator+=(const Vec3<T>& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        constexpr Vec3<T>& operator-=(const Vec3<T>& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        constexpr Vec3<T>& operator*=(const Vec3<T>& rhs)
        {
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            return *this;
        }

        constexpr Vec3<T>& operator/=(const Vec3<T>& rhs)
        {
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;
            return *this;
        }

        constexpr Vec3<T>& operator+=(const T rhs)
        {
            x += rhs;
            y += rhs;
            z += rhs;
            return *this;
        }

        constexpr Vec3<T>& operator-=(const T rhs)
        {
            x -= rhs;
            y -= rhs;
            z -= rhs;
            return *this;
        }

        constexpr Vec3<T>& operator*=(const T rhs)
        {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }

        constexpr Vec3<T>& operator/=(const T rhs)
        {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }

        constexpr Vec3<T> operator+(const Vec3<T>& rhs) const
        {
            return Vec3<T>(*this) += rhs;
        }

        constexpr Vec3<T> operator-(const Vec3<T>& rhs) const
        {
            return Vec3<T>(*this) -= rhs;
        }

        constexpr Vec3<T> operator*(const Vec3<T>& rhs) const
        {
            return Vec3<T>(*this) *= rhs;
        }

        constexpr Vec3<T> operator/(const Vec3<T>& rhs) const
        {
            return Vec3<T>(*this) /= rhs;
        }

        constexpr Vec3<T> operator+(const T rhs) const
        {
            return Vec3<T>(*this) += rhs;
        }

        constexpr Vec3<T> operator-(const T rhs) const
        {
            return Vec3<T>(*this) -= rhs;
        }

        constexpr Vec3<T> operator*(const T rhs) const
        {
            return Vec3<T>(*this) *= rhs;
        }

        constexpr Vec3<T> operator/(const T rhs) const
        {
            return Vec3<T>(*this) /= rhs;
        }

        T x = 0;
        T y = 0;
        T z = 0;

    private:
        static constexpr std::array<std::array<T, 3>, 6> adjacent_cardinal_offsets = { {
            {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}
        } };
        static constexpr std::array<std::array<T, 3>, 26> adjacent_offsets = { {
            {1, 0, 0}, {-1, 0, 0}, {0, 0, 1}, {0, 0, -1}, {1, 0, 1}, {1, 0, -1}, {-1, 0, 1}, {-1, 0, -1},
            {1, 1, 0}, {-1, 1, 0}, {0, 1, 1}, {0, 1, -1}, {1, 1, 1}, {1, 1, -1}, {-1, 1, 1}, {-1, 1, -1}, {0, 1, 0},
            {1, -1, 0}, {-1, -1, 0}, {0, -1, 1}, {0, -1, -1}, {1, -1, 1}, {1, -1, -1}, {-1, -1, 1}, {-1, -1, -1}, {0, -1, 0}
        } };
    };

    template<Number T>
    std::ostream& operator<<(std::ostream& os, const Vec3<T>& vec)
    {
        return os << fmt::format("({}, {}, {})", vec.x, vec.y, vec.z);
    }

    // --------------------------------------------------------------------------------
    // Aliases for common vector types
    // --------------------------------------------------------------------------------

    using Point = Vec2<double>;
    using Point3D = Vec3<double>;

    // --------------------------------------------------------------------------------
    // Utility functions
    // --------------------------------------------------------------------------------

    template<Number T>
    constexpr Point make_point(const T x, const T y)
    {
        return { static_cast<double>(x), static_cast<double>(y) };
    }

    template<Number T>
    constexpr Point3D make_point_3d(const T x, const T y, const T z)
    {
        return { static_cast<double>(x), static_cast<double>(y), static_cast<double>(z) };
    }

} // aoc

namespace std
{
    template<aoc::Number T>
    struct hash<aoc::Vec2<T>>
    {
        size_t operator()(const aoc::Vec2<T>& vec) const
        {
            size_t seed = 0;
            aoc::hash_combine(seed, vec.x);
            aoc::hash_combine(seed, vec.y);
            return seed;
        }
    };

    template<aoc::Number T>
    struct hash<aoc::Vec3<T>>
    {
        size_t operator()(const aoc::Vec3<T>& vec) const
        {
            size_t seed = 0;
            aoc::hash_combine(seed, vec.x);
            aoc::hash_combine(seed, vec.y);
            aoc::hash_combine(seed, vec.z);
            return seed;
        }
    };

} // std

#endif // !AOC_UTILITY_VEC_H