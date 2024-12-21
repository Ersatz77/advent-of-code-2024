#include "solutions/day_22/day_22.h"

#include <filesystem>
#include <fstream>
#include <string>

#include "fmt/format.h"

#include "utility/io.h"

namespace aoc
{
    std::string Day22::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("{}", input_root.string());
    }

    std::string Day22::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("{}", input_root.string());
    }

} // aoc
