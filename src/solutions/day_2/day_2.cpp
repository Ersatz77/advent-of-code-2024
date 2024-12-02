#include "solutions/day_2/day_2.h"

#include <cmath>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "fmt/format.h"

#include "utility/io.h"

namespace aoc
{
    static std::vector<std::vector<int>> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<std::vector<int>> reports;
        for (std::string raw_report; std::getline(file, raw_report); )
        {
            std::vector<int> report;
            std::istringstream raw_report_stream(raw_report);
            for (int level = 0; raw_report_stream >> level; )
            {
                report.push_back(level);
            }

            reports.push_back(report);
        }

        return reports;
    }

    static bool is_safe(const std::vector<int>& report)
    {
        if (report.size() < 2)
        {
            return false;
        }
        
        bool is_increasing = report[0] < report[1];
        for (size_t i = 0; i < report.size() - 1; ++i)
        {
            int diff = std::abs(report[i] - report[i + 1]);
            if (diff < 1 || diff > 3)
            {
                return false;
            }

            if (is_increasing && report[i] > report[i + 1])
            {
                return false;
            }

            if (!is_increasing && report[i] < report[i + 1])
            {
                return false;
            }
        }

        return true;
    }

    static bool is_safe_damper(const std::vector<int>& report)
    {
        // Return early if the reports is already safe
        if (is_safe(report))
        {
            return true;
        }

        // Try removing one of the values
        for (size_t i = 0; i < report.size(); ++i)
        {
            std::vector<int> modified_report;
            for (size_t j = 0; j < report.size(); ++j)
            {
                if (j != i)
                {
                    modified_report.push_back(report[j]);
                }
            }

            // Check if this modified report is safe
            if (is_safe(modified_report))
            {
                return true;
            }
        }

        return false;
    }

    std::string Day2::part_1(const std::filesystem::path& input_root) const
    {
        const std::vector<std::vector<int>> reports = parse_input(input_root / "day_2.txt");

        int safe_reports = 0;
        for (const auto& report : reports)
        {
            if (is_safe(report))
            {
                ++safe_reports;
            }
        }

        return fmt::format("Safe reports: {}", safe_reports);
    }

    std::string Day2::part_2(const std::filesystem::path& input_root) const
    {
        const std::vector<std::vector<int>> reports = parse_input(input_root / "day_2.txt");

        int safe_reports = 0;
        for (const auto& report : reports)
        {
            if (is_safe_damper(report))
            {
                ++safe_reports;
            }
        }

        return fmt::format("Safe reports: {}", safe_reports);
    }

} // aoc
