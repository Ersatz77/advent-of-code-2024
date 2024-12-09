#include "solutions/day_9/day_9.h"

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <vector>

#include "fmt/format.h"

#include "utility/io.h"

namespace aoc
{
    struct DriveBlock
    {
        int id;
        std::size_t size;
    };

    static std::vector<int> parse_input_part_1(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<int> drive;
        int file_id = 0;
        for (const auto [idx, c] : std::views::istream<char>(file)
            | std::views::drop_while([](const char c) { return c == '0'; })
            | std::views::enumerate)
        {
            std::size_t block_size = static_cast<std::size_t>(c - '0');
            if (idx % 2 == 0)
            {
                drive.append_range(std::views::repeat(file_id, block_size));
                ++file_id;
            }
            else
            {
                drive.append_range(std::views::repeat(-1, block_size));
            }
        }

        return drive;
    }

    static std::vector<DriveBlock> parse_input_part_2(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<DriveBlock> drive;
        int file_id = 0;
        for (const auto [idx, c] : std::views::istream<char>(file) | std::views::enumerate)
        {
            std::size_t block_size = static_cast<std::size_t>(c - '0');
            if (idx % 2 == 0)
            {
                drive.emplace_back(file_id, block_size);
                ++file_id;
            }
            else
            {
                drive.emplace_back(-1, block_size);
            }
        }

        return drive;
    }

    std::string Day9::part_1(const std::filesystem::path& input_root) const
    {
        std::vector<int> drive = parse_input_part_1(input_root / "day_9.txt");

        // Defrag drive
        std::size_t left = 0;
        std::size_t right = drive.size() - 1;
        while (left < right)
        {
            if (drive[left] != -1)
            {
                ++left;
            }
            else if (drive[right] == -1)
            {
                --right;
            }
            else
            {
                drive[left] = drive[right];
                drive[right] = -1;
            }
        }

        // Calculate checksum
        std::uint64_t checksum = 0;
        for (std::size_t i = 0; i < drive.size(); ++i)
        {
            checksum += (drive[i] != -1) ? (i * drive[i]) : 0;
        }

        return fmt::format("Checksum: {}", checksum);
    }

    std::string Day9::part_2(const std::filesystem::path& input_root) const
    {
        std::vector<DriveBlock> drive = parse_input_part_2(input_root / "day_9.txt");

        // Defrag drive
        for (std::size_t i = drive.size(); i > 0; --i)
        {
            std::size_t right = i - 1;
            auto& right_block = drive[right];
            if (right_block.id == -1)
            {
                continue;
            }

            for (std::size_t left = 0; left < right; ++left)
            {
                auto& left_block = drive[left];
                if (left_block.id != -1 || (left_block.size < right_block.size))
                {
                    continue;
                }

                if (left_block.size == right_block.size)
                {
                    left_block.id = right_block.id;
                    right_block.id = -1;
                }
                else if (left_block.size > right_block.size)
                {
                    std::size_t diff = left_block.size - right_block.size;
                    left_block = right_block;
                    right_block.id = -1;

                    drive.emplace(drive.begin() + left + 1, -1, diff);
                }

                break;
            }
        }

        // Calculate checksum
        std::uint64_t checksum = 0;
        std::size_t i = 0;
        for (const auto& block : drive)
        {
            for (std::size_t j = 0; j < block.size; ++j)
            {
                checksum += (block.id != -1) ? (i * block.id) : 0;
                ++i;
            }
        }

        return fmt::format("Checksum: {}", checksum);
    }

} // aoc
