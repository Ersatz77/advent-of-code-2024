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

    static MarketSequenceMap find_sequences(const std::int64_t initial_secret)
    {
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

        MarketSequenceMap sequences;
        for (std::size_t i = 0; i < changes.size() - 4; ++i)
        {
            const std::array<std::int64_t, 4> sequence = { changes[i], changes[i + 1], changes[i + 2] , changes[i + 3] };
            const std::int64_t price = prices[i + 4];

            if (!sequences.contains(sequence))
            {
                sequences[sequence] = price;
            }
        }

        return sequences;
    }

    static std::int64_t sell_information(const MarketSequenceMap& sequences, const MarketSequence& sequence)
    {
        if (sequences.contains(sequence))
        {
            return sequences.at(sequence);
        }

        return 0;
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

        // Find every sequence and also create a set of unique sequences
        std::vector<MarketSequenceMap> all_sequences;
        std::unordered_set<MarketSequence> unique_sequences;
        for (const auto initial_secret : initial_secrets)
        {
            const auto sequences = find_sequences(initial_secret);
            all_sequences.push_back(sequences);
            for (const auto& [k, _] : sequences)
            {
                unique_sequences.insert(k);
            }
        }

        // Figure out which unique sequence gives the most bananas
        std::int64_t most_bananas = std::numeric_limits<std::int64_t>::min();
        for (const auto& sequence : unique_sequences)
        {
            std::int64_t bananas = 0;
            for (const auto& sequences : all_sequences)
            {
                bananas += sell_information(sequences, sequence);
            }

            most_bananas = std::max(most_bananas, bananas);
        }

        return fmt::format("Most bananas you can get: {}", most_bananas);
    }

} // aoc
