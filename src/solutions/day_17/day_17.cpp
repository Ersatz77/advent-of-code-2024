#include "solutions/day_17/day_17.h"

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include "ctll.hpp"
#include "ctre.hpp"
#include "fmt/format.h"
#include "fmt/ranges.h"

#include "utility/io.h"
#include "utility/math.h"
#include "utility/string.h"

namespace aoc
{
    static std::tuple<std::vector<std::int64_t>, std::int64_t, std::int64_t, std::int64_t> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::string raw_reg_a;
        std::string raw_reg_b;
        std::string raw_reg_c;
        std::string raw_program_line;

        std::getline(file, raw_reg_a);
        std::getline(file, raw_reg_b);
        std::getline(file, raw_reg_c);
        skip_line(file);
        std::getline(file, raw_program_line);

        // Parse registers
        constexpr ctll::fixed_string register_pattern = R"(Register .: (?<v>\d+))";
        std::int64_t reg_a = ctre::match<register_pattern>(raw_reg_a).get<"v">().to_number();
        std::int64_t reg_b = ctre::match<register_pattern>(raw_reg_b).get<"v">().to_number();
        std::int64_t reg_c = ctre::match<register_pattern>(raw_reg_c).get<"v">().to_number();

        // Parse program
        std::string raw_program = ctre::match<R"(Program: (?<p>[\d,]+))">(raw_program_line).get<"p">().to_string();
        std::vector<std::int64_t> program;
        for (const auto& s : split(raw_program, ","))
        {
            program.push_back(std::stoi(s));
        }

        return { program, reg_a, reg_b, reg_c };
    }

    static std::vector<std::int64_t> run_program(const std::vector<std::int64_t>& program, const std::int64_t a, const std::int64_t b, const std::int64_t c)
    {
        std::vector<std::int64_t> output;
        std::size_t ip = 0;
        std::int64_t reg_a = a;
        std::int64_t reg_b = b;
        std::int64_t reg_c = c;

        const auto get_combo = [&reg_a, &reg_b, &reg_c](const std::int64_t o) {
            if (o >= 0 && o <= 3) { return o; }
            else if (o == 4) { return reg_a; }
            else if (o == 5) { return reg_b; }
            else if (o == 6) { return reg_c; }
            throw std::invalid_argument("Invalid combo operand");
        };

        while (ip < program.size())
        {
            std::int64_t opcode = program[ip];
            std::int64_t operand = program[ip + 1];
            switch (opcode)
            {
                case 0:
                    // ADV
                    reg_a /= pow(2LL, get_combo(operand));
                    ip += 2;
                    break;
                case 1:
                    // BXL
                    reg_b ^= operand;
                    ip += 2;
                    break;
                case 2:
                    // BST
                    reg_b = get_combo(operand) % 8LL;
                    ip += 2;
                    break;
                case 3:
                    // JNZ
                    reg_a != 0 ? ip = operand : ip += 2;
                    break;
                case 4:
                    // BXC
                    reg_b ^= reg_c;
                    ip += 2;
                    break;
                case 5:
                    // OUT
                    output.push_back(get_combo(operand) % 8LL);
                    ip += 2;
                    break;
                case 6:
                    // BDV
                    reg_b = reg_a / pow(2LL, get_combo(operand));
                    ip += 2;
                    break;
                case 7:
                    // CDV
                    reg_c = reg_a / pow(2LL, get_combo(operand));
                    ip += 2;
                    break;
                default:
                    break;
            }
        }

        return output;
    }

    std::string Day17::part_1(const std::filesystem::path& input_root) const
    {
        const auto [program, a, b, c] = parse_input(input_root / "day_17.txt");

        const auto output = run_program(program, a, b, c);

        return fmt::format("Program output: {}", fmt::join(output, ","));
    }

    std::string Day17::part_2(const std::filesystem::path& input_root) const
    {
        const auto [program, _, b, c] = parse_input(input_root / "day_17.txt");

        // Calculate the minimum value that register A can be
        std::int64_t a = 1;
        for (std::size_t i = 0; i < program.size() - 1; ++i)
        {
            a += 7 * static_cast<std::int64_t>(pow(8ULL, i));
        }

        // Run the program until we the program is self-replicated
        while (true)
        {
            const auto output = run_program(program, a, b, c);
            if (output == program)
            {
                break;
            }

            // Walk backwards on both the program and output and adjust the value for register A if it's still too low
            for (std::size_t i = output.size(); i > 0; --i)
            {
                if (output[i - 1] != program[i - 1])
                {
                    a += static_cast<std::int64_t>(pow(8ULL, i - 1));
                    break;
                }
            }
        }

        return fmt::format("Value for register A that causes the program to output itself: {}", a);
    }

} // aoc
