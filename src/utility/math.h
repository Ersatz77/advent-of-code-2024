#ifndef AOC_UTILITY_MATH_H
#define AOC_UTILITY_MATH_H

#include <algorithm>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <utility>
#include <vector>

#include "utility/utility.h"
#include "utility/vec.h"

namespace aoc
{
    template<Number T>
    T manhattan_distance(const T x1, const T y1, const T x2, const T y2)
    {
        return std::abs(x2 - x1) + std::abs(y2 - y1);
    }

    template<Number T>
    T manhattan_distance(const T x1, const T y1, const T z1, const T x2, const T y2, const T z2)
    {
        return std::abs(x2 - x1) + std::abs(y2 - y1) + std::abs(z2 - z1);
    }

    template<Number T>
    T manhattan_distance(const Vec2<T>& v1, const Vec2<T>& v2)
    {
        return manhattan_distance(v1.x, v1.y, v2.x, v2.y);
    }

    template<Number T>
    T manhattan_distance(const Vec3<T>& v1, const Vec3<T>& v2)
    {
        return manhattan_distance(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z);
    }

    template<Number T>
    std::vector<Vec2<T>> cartesian_product(const T x1, const T y1, const T x2, const T y2)
    {
        std::vector<Vec2<T>> res;
        for (T x = std::min(x1, x2); x <= std::max(x1, x2); ++x)
        {
            for (T y = std::min(y1, y2); y <= std::max(y1, y2); ++y)
            {
                res.emplace_back(x, y);
            }
        }

        return res;
    }

    template<Number T>
    std::vector<Vec3<T>> cartesian_product(const T x1, const T y1, const T z1, const T x2, const T y2, const T z2)
    {
        std::vector<Vec3<T>> res;
        for (T x = std::min(x1, x2); x <= std::max(x1, x2); ++x)
        {
            for (T y = std::min(y1, y2); y <= std::max(y1, y2); ++y)
            {
                for (T z = std::min(z1, z2); z <= std::max(z1, z2); ++z)
                {
                    res.emplace_back(x, y, z);
                }
            }
        }

        return res;
    }

    template<Number T>
    std::vector<Vec2<T>> cartesian_product(const Vec2<T>& v1, const Vec2<T>& v2)
    {
        return cartesian_product(v1.x, v1.y, v2.x, v2.y);
    }

    template<Number T>
    std::vector<Vec3<T>> cartesian_product(const Vec3<T>& v1, const Vec3<T>& v2)
    {
        return cartesian_product(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z);
    }

    template<Number T>
    T polygon_area(const std::vector<Vec2<T>>& polygon)
    {
        T area = 0;
        for (std::size_t i = 0; i < polygon.size(); ++i)
        {
            const Vec2<T>& current = polygon[i];
            const Vec2<T>& next = polygon[(i + 1) % polygon.size()];
            area += (current.x * next.y) - (current.y * next.x);
        }

        return std::abs(area) / 2;
    }

    template<Number T>
    bool in_area(const Vec2<T>& start, const Vec2<T>& end, const Vec2<T> p)
    {
        return p.x >= start.x && p.x <= end.x
            && p.y >= start.y && p.y <= end.y;
    }

    template<Number T>
    bool in_volume(const Vec3<T>& start, const Vec3<T>& end, const Vec3<T> p)
    {
        return p.x >= start.x && p.x <= end.x
            && p.y >= start.y && p.y <= end.y
            && p.z >= start.z && p.z <= end.z;
    }

    template<std::integral T>
    T signum(const T v)
    {
        return (0 < v) - (v < 0);
    }

    template<Number T>
    T gaussian_sum(const T a, const T b)
    {
        return ((b - a) * (b - a + 1)) / 2;
    }

    template<Number T>
    T mod(const T a, const T b)
    {
        return ((a % b) + b) % b;
    }

    template<std::integral T>
    T pow(T base, T exp)
    {
        T result = 1;
        while (exp)
        {
            if (exp % 2)
            {
                result *= base;
            }

            exp /= 2;
            base *= base;
        }

        return result;
    }

    // Concatenates two numbers together Ex: 10 + 3 == 103
    template<std::integral T>
    T concatentate(const T a, const T b)
    {
        T pow = 10;
        while (pow <= b)
        {
            pow *= 10;
        }

        return a * pow + b;
    }


    std::pair<double, double> quadratic(const double a, const double b, const double c);
    std::pair<float, float> quadratic(const float a, const float b, const float c);

} // aoc

#endif // !AOC_UTILITY_MATH_H
