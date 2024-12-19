#include "solutions/day_19/day_19.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "fmt/format.h"

#include "utility/io.h"
#include "utility/string.h"

namespace aoc
{
    static std::pair<std::vector<std::string>, std::vector<std::string>> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        // Parse patterns
        std::string raw_patterns;
        std::getline(file, raw_patterns);
        std::vector<std::string> patterns = split(raw_patterns, ", ");
        skip_line(file);

        // Parse towel designs
        std::vector<std::string> towel_designs;
        for (std::string line; std::getline(file, line); )
        {
            towel_designs.push_back(line);
        }

        return { patterns, towel_designs };
    }

    static std::uint64_t pattern_combinations(std::unordered_map<std::string, std::uint64_t>& cache, const std::string& towel_design, const std::vector<std::string>& patterns)
    {
        // Return the cached result if it exists
        if (cache.contains(towel_design))
        {
            return cache.at(towel_design);
        }

        // Get the number of pattern combinations for this towel design
        std::uint64_t combinations = 0;
        for (const std::string& pattern : patterns)
        {
            if (towel_design == pattern)
            {
                ++combinations;
            }
            else if (towel_design.starts_with(pattern))
            {
                combinations += pattern_combinations(cache, towel_design.substr(pattern.length()), patterns);
            }
        }

        // Cache combinations and return it
        cache[towel_design] = combinations;
        return combinations;
    }

    std::string Day19::part_1(const std::filesystem::path& input_root) const
    {
        const auto [patterns, towel_designs] = parse_input(input_root / "day_19.txt");

        std::uint64_t valid_designs = 0;
        std::unordered_map<std::string, std::uint64_t> cache;
        for (const std::string& towel_design : towel_designs)
        {
            if (pattern_combinations(cache, towel_design, patterns))
            {
                ++valid_designs;
            }
        }

        return fmt::format("Valid towel designs: {}", valid_designs);
    }

    std::string Day19::part_2(const std::filesystem::path& input_root) const
    {
        const auto [patterns, towel_designs] = parse_input(input_root / "day_19.txt");

        std::uint64_t combinations = 0;
        std::unordered_map<std::string, std::uint64_t> cache;
        for (const std::string& towel_design : towel_designs)
        {
            combinations += pattern_combinations(cache, towel_design, patterns);
        }

        return fmt::format("Total number of pattern combinations: {}", combinations);
    }

} // aoc
