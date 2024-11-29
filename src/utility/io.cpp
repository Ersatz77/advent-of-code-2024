#include "utility/io.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

#include <fmt/format.h>

namespace aoc
{
    std::ifstream open_file(const std::filesystem::path& path)
    {
        std::ifstream file(path);
        if (!file)
        {
            throw std::runtime_error(fmt::format("Unable to open {}", path.filename().string()));
        }

        return file;
    }

    std::vector<std::string> read_lines(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::vector<std::string> lines;
        for (std::string line; std::getline(file, line); )
        {
            lines.push_back(line);
        }

        return lines;
    }

    void skip_line(std::istream& stream)
    {
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

} // aoc
