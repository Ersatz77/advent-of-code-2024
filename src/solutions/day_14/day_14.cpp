#include "solutions/day_14/day_14.h"

#include <filesystem>
#include <fstream>
#include <string>

#include "fmt/format.h"

#include "utility/io.h"

namespace aoc
{
    std::string Day14::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("{}", input_root.string());
    }

    std::string Day14::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("{}", input_root.string());
    }
}