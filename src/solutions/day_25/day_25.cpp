#include "solutions/day_25/day_25.h"

#include <filesystem>
#include <fstream>
#include <string>

#include "fmt/format.h"

#include "utility/io.h"

namespace aoc
{
    std::string Day25::part_1(const std::filesystem::path& input_root) const
    {
        return fmt::format("{}", input_root.string());
    }

    std::string Day25::part_2(const std::filesystem::path& input_root) const
    {
        return fmt::format("{}", input_root.string());
    }

} // aoc
