#include "solutions/day_7/day_7.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "fmt/format.h"

#include "utility/io.h"
#include "utility/math.h"
#include "utility/string.h"

namespace aoc
{
    struct CalibrationEquation
    {
        std::uint64_t test_value;
        std::vector<std::uint64_t> numbers;
    };

    static std::vector<CalibrationEquation> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<CalibrationEquation> equations;
        for (std::string line; std::getline(file, line); )
        {
            std::vector<std::string> raw_equation = split(line, ": ");

            std::uint64_t test_value = std::stoll(raw_equation.front());
            std::vector<std::uint64_t> numbers;
            for (const auto& raw_number : split(raw_equation.back(), " "))
            {
                numbers.push_back(std::stoll(raw_number));
            }

            equations.emplace_back(test_value, numbers);
        }

        return equations;
    }

    static bool solve_equation(
        const CalibrationEquation& equation,
        const std::uint64_t current,
        const std::size_t idx = 1,
        const bool part_2 = false)
    {
        // Check the current value against the test value if we've used up every number
        if (idx == equation.numbers.size())
        {
            return current == equation.test_value;
        }

        // Return false if the current value is greater than the test value
        if (current > equation.test_value)
        {
            return false;
        }

        // Try adding the next number
        if (solve_equation(equation, current + equation.numbers[idx], idx + 1, part_2))
        {
            return true;
        }

        // Try multiplying the next number
        if (solve_equation(equation, current * equation.numbers[idx], idx + 1, part_2))
        {
            return true;
        }

        // Try concatenating the next number
        if (part_2)
        {
            const std::uint64_t next = concatentate(current, equation.numbers[idx]);
            if (solve_equation(equation, next, idx + 1, part_2))
            {
                return true;
            }
        }

        return false;
    }

    std::string Day7::part_1(const std::filesystem::path& input_root) const
    {
        const auto equations = parse_input(input_root / "day_7.txt");

        std::uint64_t sum = std::ranges::fold_left(equations, 0,
            [](const std::uint64_t acc, const CalibrationEquation& e)
            {
                return acc + (solve_equation(e, e.numbers.front()) ? e.test_value : 0);
            }
        );

        return fmt::format("Total calibration result: {}", sum);
    }

    std::string Day7::part_2(const std::filesystem::path& input_root) const
    {
        const auto equations = parse_input(input_root / "day_7.txt");

        std::uint64_t sum = std::ranges::fold_left(equations, 0,
            [](const std::uint64_t acc, const CalibrationEquation& e)
            {
                return acc + (solve_equation(e, e.numbers.front(), 1, true) ? e.test_value : 0);
            }
        );

        return fmt::format("Total calibration result: {}", sum);
    }

} // aoc
