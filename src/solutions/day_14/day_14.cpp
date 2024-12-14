#include "solutions/day_14/day_14.h"

#include <cmath>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "ctll.hpp"
#include "ctre.hpp"
#include "fmt/format.h"

#include "utility/io.h"
#include "utility/math.h"
#include "utility/vec.h"

namespace aoc
{
    static constexpr Vec2<int> max_bounds = { 101, 103 };
    static const int x_to_ignore = static_cast<int>(std::floor(max_bounds.x / 2));
    static const int y_to_ignore = static_cast<int>(std::floor(max_bounds.y / 2));

    struct BathroomRobot
    {
        Vec2<int> position;
        Vec2<int> velocity;
    };

    static std::vector<BathroomRobot> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<BathroomRobot> robots;
        for (std::string line; std::getline(file, line); )
        {
            constexpr ctll::fixed_string pattern = R"(p=(?<px>\d+),(?<py>\d+) v=(?<vx>[\-\d]+),(?<vy>[\-\d]+))";
            auto match = ctre::match<pattern>(line);

            Vec2<int> position = { match.get<"px">().to_number(), match.get<"py">().to_number() };
            Vec2<int> velocity = { match.get<"vx">().to_number(), match.get<"vy">().to_number() };

            robots.emplace_back(position, velocity);
        }

        return robots;
    }

    static void simulate_robots(std::vector<BathroomRobot>& robots, const int seconds)
    {
        for (int i = 0; i < seconds; ++i)
        {
            for (auto& robot : robots)
            {
                // Move robot
                robot.position += robot.velocity;
                robot.position.x = mod(robot.position.x, max_bounds.x);
                robot.position.y = mod(robot.position.y, max_bounds.y);
            }
        }
    }

    static int simulate_until_easter_egg(std::vector<BathroomRobot>& robots)
    {
        int seconds = 0;
        while (true)
        {
            ++seconds;
            bool is_unique = true;
            std::unordered_set<Vec2<int>> unique_positions;
            for (auto& robot : robots)
            {
                // Move robot
                robot.position += robot.velocity;
                robot.position.x = mod(robot.position.x, max_bounds.x);
                robot.position.y = mod(robot.position.y, max_bounds.y);

                // Keep adding robot positions to the set as long as it's still unique
                if (is_unique && !unique_positions.contains(robot.position))
                {
                    unique_positions.insert(robot.position);
                }
                else
                {
                    is_unique = false;
                }
            }

            // Return `seconds` if this second was unique
            if (is_unique)
            {
                return seconds;
            }
        }

        return -1;
    }

    static int calculate_safety_factor(const std::vector<BathroomRobot>& robots)
    {
        int quad_1_count = 0;
        int quad_2_count = 0;
        int quad_3_count = 0;
        int quad_4_count = 0;

        for (const auto& robot : robots)
        {
            if (robot.position.x < x_to_ignore && robot.position.y < y_to_ignore)
            {
                ++quad_1_count;
            }
            else if (robot.position.x > x_to_ignore && robot.position.y < y_to_ignore)
            {
                ++quad_2_count;
            }
            else if (robot.position.x < x_to_ignore && robot.position.y > y_to_ignore)
            {
                ++quad_3_count;
            }
            else if (robot.position.x > x_to_ignore && robot.position.y > y_to_ignore)
            {
                ++quad_4_count;
            }
        }

        return quad_1_count * quad_2_count * quad_3_count * quad_4_count;
    }

    std::string Day14::part_1(const std::filesystem::path& input_root) const
    {
        std::vector<BathroomRobot> robots = parse_input(input_root / "day_14.txt");

        simulate_robots(robots, 100);
        int safety_factor = calculate_safety_factor(robots);

        return fmt::format("Safety factor after 100 seconds: {}", safety_factor);
    }

    std::string Day14::part_2(const std::filesystem::path& input_root) const
    {
        std::vector<BathroomRobot> robots = parse_input(input_root / "day_14.txt");

        int seconds = simulate_until_easter_egg(robots);

        return fmt::format("Number of seconds it takes for the easter egg to display: {}", seconds);
    }
}