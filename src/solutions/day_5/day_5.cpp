#include "solutions/day_5/day_5.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_set>
#include <utility>

#include "fmt/format.h"

#include "utility/io.h"
#include "utility/string.h"
#include "utility/utility.h"

namespace aoc
{
    static std::pair<std::unordered_set<std::pair<int, int>>, std::vector<std::vector<int>>> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        // Parse rules
        std::unordered_set<std::pair<int, int>> rules;
        for (std::string line; std::getline(file, line) && !line.empty(); )
        {
            const auto raw_pages = split(line, "|");
            rules.emplace(std::stoi(raw_pages[0]), std::stoi(raw_pages[1]));
        }

        // Parse updates
        std::vector<std::vector<int>> updates;
        for (std::string line; std::getline(file, line); )
        {
            std::vector<int> update;
            for (const auto& raw_value : split(line, ","))
            {
                update.push_back(std::stoi(raw_value));
            }

            updates.push_back(update);
        }

        return { rules, updates };
    }

    std::string Day5::part_1(const std::filesystem::path& input_root) const
    {
        const auto [rules, updates] = parse_input(input_root / "day_5.txt");

        int sum = 0;
        const auto cmp = [&rules](const int a, const int b) { return rules.contains({ a, b }); };
        for (const auto& update : updates)
        {
            if (std::ranges::is_sorted(update, cmp))
            {
                sum += update[update.size() / 2];
            }
        }

        return fmt::format("Sum of the middle numbers of correctly ordered updates: {}", sum);
    }

    std::string Day5::part_2(const std::filesystem::path& input_root) const
    {
        const auto [rules, updates] = parse_input(input_root / "day_5.txt");

        int sum = 0;
        const auto cmp = [&rules](const int a, const int b) { return rules.contains({ a, b }); };
        for (const auto& update : updates)
        {
            if (!std::ranges::is_sorted(update, cmp))
            {
                std::vector<int> fixed_update = update;
                std::ranges::sort(fixed_update, cmp);

                sum += fixed_update[fixed_update.size() / 2];
            }
        }

        return fmt::format("Sum of the middle numbers of fixed updates: {}", sum);
    }

} // aoc
