#ifndef AOC_UTILITY_IO_H
#define AOC_UTILITY_IO_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace aoc
{
    // Simplifies the opening of a file by hiding away common checks
    // If the file can't be opened, an exception will be thrown
    std::ifstream open_file(const std::filesystem::path& path);

    // Read all lines from a file
    // If the file can't be opened, an exception will be thrown
    std::vector<std::string> read_lines(const std::filesystem::path& path);

    // Skips a line by reading all characters until `\n`
    void skip_line(std::istream& stream);

} // aoc

#endif // !AOC_UTILITY_IO_H
