#include "solutions/day_13/day_13.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

#include "ctll.hpp"
#include "ctre.hpp"
#include "fmt/format.h"

#include "utility/io.h"
#include "utility/vec.h"

namespace aoc
{
    struct ClawMachine
    {
        Vec2<std::int64_t> button_a_delta;
        Vec2<std::int64_t> button_b_delta;
        Vec2<std::int64_t> prize_location;
    };

    static std::vector<ClawMachine> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<ClawMachine> claw_machines;
        while (file)
        {
            std::string raw_button_a;
            std::string raw_button_b;
            std::string raw_prize_location;

            std::getline(file, raw_button_a);
            std::getline(file, raw_button_b);
            std::getline(file, raw_prize_location);
            skip_line(file);

            if (!file)
            {
                break;
            }

            constexpr ctll::fixed_string button_pattern = R"(Button .: X\+(?<x>\d+), Y\+(?<y>\d+))";
            constexpr ctll::fixed_string prize_pattern = R"(Prize: X=(?<x>\d+), Y=(?<y>\d+))";

            auto button_a_match = ctre::match<button_pattern>(raw_button_a);
            auto button_b_match = ctre::match< button_pattern>(raw_button_b);
            auto prize_location_match = ctre::match<prize_pattern>(raw_prize_location);

            Vec2<std::int64_t> button_a{ button_a_match.get<"x">().to_number(), button_a_match.get<"y">().to_number() };
            Vec2<std::int64_t> button_b{ button_b_match.get<"x">().to_number(), button_b_match.get<"y">().to_number() };
            Vec2<std::int64_t> prize_location{ prize_location_match.get<"x">().to_number(), prize_location_match.get<"y">().to_number() };

            claw_machines.emplace_back(button_a, button_b, prize_location);
        }

        return claw_machines;
    }

    static std::optional<std::int64_t> calculate_token_cost(const ClawMachine& machine)
    {
        // Solving systems of equations using Cramer's rule
        // https://en.wikipedia.org/wiki/Cramer's_rule#Explicit_formulas_for_small_systems
        // 
        // a1 * x + b1 * y = c1
        // a2 * x + b2 * y = c2

        const auto& a = machine.button_a_delta;
        const auto& b = machine.button_b_delta;
        const auto& prize = machine.prize_location;

        // Get the determinant of a and b
        std::int64_t det = (a.x * b.y) - (a.y * b.x);

        // Can't use Cramer's rule of `det` is `0`
        if (det == 0)
        {
            return std::nullopt;
        }

        // Get the determinant of prize and b along with a and prize
        std::int64_t x = (prize.x * b.y) - (prize.y * b.x);
        std::int64_t y = (a.x * prize.y) - (a.y * prize.x);

        // The determinants must divide evenly
        if (x % det != 0 || y % det != 0)
        {
            return std::nullopt;
        }

        // Divide x and y by determinants
        x /= det;
        y /= det;

        // Calculate token cost
        return x * 3 + y;
    }

    std::string Day13::part_1(const std::filesystem::path& input_root) const
    {
        const std::vector<ClawMachine> claw_machines = parse_input(input_root / "day_13.txt");

        std::int64_t tokens = 0;
        for (const auto& machine : claw_machines)
        {
            if (auto result = calculate_token_cost(machine); result.has_value())
            {
                tokens += *result;
            }
        }

        return fmt::format("Fewest tokens to win all possible prizes: {}", tokens);
    }

    std::string Day13::part_2(const std::filesystem::path& input_root) const
    {
        std::vector<ClawMachine> claw_machines = parse_input(input_root / "day_13.txt");

        std::int64_t tokens = 0;
        for (auto& machine : claw_machines)
        {
            machine.prize_location += Vec2<std::int64_t>{ 10000000000000LL, 10000000000000LL };
            if (auto result = calculate_token_cost(machine); result.has_value())
            {
                tokens += *result;
            }
        }

        return fmt::format("Fewest tokens to win all possible prizes: {}", tokens);
    }

} // aoc
