#ifndef AOC_UTILITY_DAY_H
#define AOC_UTILITY_DAY_H

#include <cstdint>
#include <filesystem>
#include <string>

namespace aoc
{
    // Results for a day
    struct DayResults
    {
        std::string part_1_output;
        std::uint64_t part_1_runtime;

        std::string part_2_output;
        std::uint64_t part_2_runtime;
    };

    // An abstract class for a day
    class Day
    {
    public:
        explicit Day(int day_num);
        virtual ~Day() = default;

        virtual std::string part_1(const std::filesystem::path& input_root) const = 0;
        virtual std::string part_2(const std::filesystem::path& input_root) const = 0;

        DayResults run(const std::filesystem::path& input_root) const;

    private:
        int m_day_num;
    };

} // aoc

#endif // !AOC_UTILITY_DAY_H
