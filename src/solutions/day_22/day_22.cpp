#include "solutions/day_22/day_22.h"

#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <limits>
#include <ranges>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "fmt/format.h"

#include "utility/io.h"
#include "utility/utility.h"

namespace aoc
{
    using MarketSequence = std::array<std::int64_t, 4>;
    using MarketSequenceMap = std::unordered_map<MarketSequence, int64_t>;

    static std::vector<std::int64_t> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        return std::views::istream<std::int64_t>(file) | std::ranges::to<std::vector<std::int64_t>>();
    }

    static std::int64_t next_secret(std::int64_t secret)
    {
        secret ^= (secret * 64);
        secret %= 16777216;

        secret ^= (secret / 32);
        secret %= 16777216;

        secret ^= (secret * 2048);
        secret %= 16777216;

        return secret;
    }

    std::string Day22::part_1(const std::filesystem::path& input_root) const
    {
        const auto initial_secrets = parse_input(input_root / "day_22.txt");

        std::int64_t secret_sum = 0;
        for (const auto initial_secret : initial_secrets)
        {
            std::int64_t secret = initial_secret;
            for (std::size_t i = 0; i < 2000; ++i)
            {
                secret = next_secret(secret);
            }

            secret_sum += secret;
        }

        return fmt::format("Sum of all buyers 2000th secret number: {}", secret_sum);
    }

    std::string Day22::part_2(const std::filesystem::path& input_root) const
    {
        const auto initial_secrets = parse_input(input_root / "day_22.txt");

        std::unordered_map<std::array<std::int64_t, 4>, std::int64_t> bananas;
        for (const auto initial_secret : initial_secrets)
        {
            // Generate the prices and changes between prices
            std::int64_t secret = initial_secret;
            std::vector<std::int64_t> prices({ initial_secret % 10 });
            std::vector<std::int64_t> changes;
            for (std::size_t i = 0; i < 2000; ++i)
            {
                secret = next_secret(secret);

                const std::int64_t current_price = secret % 10;
                const std::int64_t current_change = current_price - prices.back();

                prices.push_back(current_price);
                changes.push_back(current_change);
            }

            // Add the prices to the sequence map
            std::unordered_set<std::array<std::int64_t, 4>> seen;
            for (std::size_t i = 0; i < changes.size() - 4; ++i)
            {
                const std::array<std::int64_t, 4> sequence = { changes[i], changes[i + 1], changes[i + 2] , changes[i + 3] };
                const std::int64_t price = prices[i + 4];

                if (!seen.contains(sequence))
                {
                    bananas[sequence] += price;
                    seen.insert(sequence);
                }
            }
        }

        // Find the most amount of bananas in the sequence map
        std::int64_t most_bananas = std::numeric_limits<std::int64_t>::min();
        for (const auto& [_, v] : bananas)
        {
            most_bananas = std::max(most_bananas, v);
        }

        return fmt::format("Most bananas you can get: {}", most_bananas);
    }

} // aoc
