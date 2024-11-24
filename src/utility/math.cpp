#include "utility/math.h"

#include <cmath>
#include <utility>

namespace aoc
{
    std::pair<double, double> quadratic(const double a, const double b, const double c)
    {
        double determinant = (b * b) - (4.0 * a * c);
        double root_1 = (-b + std::sqrt(determinant)) / (2 * a);
        double root_2 = (-b - std::sqrt(determinant)) / (2 * a);

        return { root_1, root_2 };
    }

    std::pair<float, float> quadratic(const float a, const float b, const float c)
    {
        float determinant = (b * b) - (4.0f * a * c);
        float root_1 = (-b + std::sqrtf(determinant)) / (2 * a);
        float root_2 = (-b - std::sqrtf(determinant)) / (2 * a);

        return { root_1, root_2 };
    }

} // aoc
