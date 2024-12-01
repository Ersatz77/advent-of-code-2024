#include "solutions/day_1/day_1.h"

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "fmt/format.h"

#include "utility/io.h"

namespace aoc
{
    static std::pair<std::vector<int>, std::vector<int>> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<int> left_list;
        std::vector<int> right_list;

        int left_value = 0;
        int right_value = 0;
        while (file >> left_value >> right_value)
        {
            left_list.push_back(left_value);
            right_list.push_back(right_value);
        }

        return { left_list, right_list };
    }

    std::string Day1::part_1(const std::filesystem::path& input_root) const
    {
        auto [left_list, right_list] = parse_input(input_root / "day_1.txt");

        std::ranges::sort(left_list);
        std::ranges::sort(right_list);

        int total_distance = 0;
        for (size_t i = 0; i < left_list.size(); ++i)
        {
            total_distance += std::abs(left_list[i] - right_list[i]);
        }

        return fmt::format("Total distance between lists: {}", total_distance);
    }

    std::string Day1::part_2(const std::filesystem::path& input_root) const
    {
        auto [left_list, right_list] = parse_input(input_root / "day_1.txt");

        std::unordered_map<int, int> frequencies;
        for (const int i : right_list)
        {
            ++frequencies[i];
        }

        int similarity_score = 0;
        for (const int i : left_list)
        {
            if (frequencies.contains(i))
            {
                similarity_score += i * frequencies[i];
            }
        }

        return fmt::format("Similarity score: {}", similarity_score);
    }

} // aoc
