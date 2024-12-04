#include "solutions/day_4/day_4.h"

#include <array>
#include <cstddef>
#include <filesystem>
#include <string>
#include <vector>

#include "fmt/format.h"

#include "utility/io.h"

namespace aoc
{
    static bool is_mas(const char maybe_m, const char maybe_a, const char maybe_s)
    {
        return maybe_m == 'M' && maybe_a == 'A' && maybe_s == 'S';
    }

    std::string Day4::part_1(const std::filesystem::path& input_root) const
    {
        const std::vector<std::string> grid = read_lines(input_root / "day_4.txt");

        int count = 0;
        const std::size_t height = grid.size();
        const std::size_t width = grid.front().length();
        for (std::size_t y = 0; y < height; ++y)
        {
            for (std::size_t x = 0; x < width; ++x)
            {
                // Skip iteration if this character isn't an `X`
                if (grid[y][x] != 'X')
                {
                    continue;
                }

                // North
                if (y >= 3)
                {
                    // Northwest
                    if (x >= 3 && is_mas(grid[y - 1][x - 1], grid[y - 2][x - 2], grid[y - 3][x - 3]))
                    {
                        ++count;
                    }

                    // North
                    if (is_mas(grid[y - 1][x], grid[y - 2][x], grid[y - 3][x]))
                    {
                        ++count;
                    }

                    // Northeast
                    if (x < width - 3 && is_mas(grid[y - 1][x + 1], grid[y - 2][x + 2], grid[y - 3][x + 3]))
                    {
                        ++count;
                    }
                }

                // East
                if (x < width - 3 && is_mas(grid[y][x + 1], grid[y][x + 2], grid[y][x + 3]))
                {
                    ++count;
                }

                // West
                if (x >= 3 && is_mas(grid[y][x - 1], grid[y][x - 2], grid[y][x - 3]))
                {
                    ++count;
                }

                // South
                if (y < height - 3)
                {
                    // Southwest
                    if (x >= 3 && is_mas(grid[y + 1][x - 1], grid[y + 2][x - 2], grid[y + 3][x - 3]))
                    {
                        ++count;
                    }

                    // South
                    if (is_mas(grid[y + 1][x], grid[y + 2][x], grid[y + 3][x]))
                    {
                        ++count;
                    }

                    // Southeast
                    if (x < width - 3 && is_mas(grid[y + 1][x + 1], grid[y + 2][x + 2], grid[y + 3][x + 3]))
                    {
                        ++count;
                    }
                }
            }
        }

        return fmt::format("'XMAS' occurrences: {}", count);
    }

    std::string Day4::part_2(const std::filesystem::path& input_root) const
    {
        const std::vector<std::string> grid = read_lines(input_root / "day_4.txt");

        int count = 0;
        const std::size_t height = grid.size();
        const std::size_t width = grid.front().length();
        for (std::size_t y = 1; y < height - 1; ++y)
        {
            for (std::size_t x = 1; x < width - 1; ++x)
            {
                // Skip iteration if this character isn't an `A`
                if (grid[y][x] != 'A')
                {
                    continue;
                }

                if ((is_mas(grid[y - 1][x - 1], grid[y][x], grid[y + 1][x + 1]) || is_mas(grid[y + 1][x + 1], grid[y][x], grid[y - 1][x - 1]))
                    && (is_mas(grid[y - 1][x + 1], grid[y][x], grid[y + 1][x - 1]) || is_mas(grid[y + 1][x - 1], grid[y][x], grid[y - 1][x + 1])))
                {
                    ++count;
                }
            }
        }
        return fmt::format("'X-MAS' occurrences: {}", count);
    }

} // aoc
