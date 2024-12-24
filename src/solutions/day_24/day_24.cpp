#include "solutions/day_24/day_24.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "ctll.hpp"
#include "ctre.hpp"
#include "fmt/format.h"
#include "fmt/ranges.h"

#include "utility/io.h"

namespace aoc
{
    enum class WireOperator
    {
        UNKNOWN = 0,
        AND,
        OR,
        XOR
    };

    struct WireOperation
    {
        std::string left;
        std::string right;
        bool left_is_literal = false;
        bool right_is_literal = false;
        WireOperator op = WireOperator::UNKNOWN;
    };

    static std::pair<std::unordered_map<std::string, std::int64_t>, std::unordered_map<std::string, WireOperation>> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::unordered_map<std::string, std::int64_t> literals;
        for (std::string line; std::getline(file, line) && !line.empty(); )
        {
            auto match = ctre::match<R"((?<wire>\w+): (?<value>\d+))">(line);
            const std::string wire = match.get<"wire">().to_string();
            const std::int64_t value = match.get<"value">().to_number();

            literals[wire] = value;
        }

        std::unordered_map<std::string, WireOperation> wires;
        for (std::string line; std::getline(file, line); )
        {
            constexpr ctll::fixed_string wire_pattern = R"((?<left>\w+) (?<op>AND|OR|XOR) (?<right>\w+) -> (?<output>\w+))";
            auto match = ctre::match<wire_pattern>(line);
            const std::string left = match.get<"left">().to_string();
            const std::string right = match.get<"right">().to_string();
            const std::string raw_op = match.get<"op">().to_string();
            const std::string output = match.get<"output">().to_string();

            bool left_is_literal = left.starts_with("x") || left.starts_with('y');
            bool right_is_literal = right.starts_with("x") || right.starts_with('y');

            WireOperator op = WireOperator::UNKNOWN;
            if (raw_op == "AND")
            {
                op = WireOperator::AND;
            }
            else if (raw_op == "OR")
            {
                op = WireOperator::OR;
            }
            else if (raw_op == "XOR")
            {
                op = WireOperator::XOR;
            }

            wires[output] = { left, right, left_is_literal, right_is_literal, op };
        }

        return { literals, wires };
    }

    static std::int64_t do_operation(
        const std::unordered_map<std::string,std::int64_t>& literals,
        const std::unordered_map<std::string, WireOperation>& wires,
        const std::string& wire)
    {
        const auto& operation = wires.at(wire);
        const std::int64_t left = operation.left_is_literal ? literals.at(operation.left) : do_operation(literals, wires, operation.left);
        const std::int64_t right = operation.right_is_literal ? literals.at(operation.right) : do_operation(literals, wires, operation.right);

        switch (operation.op)
        {
            case WireOperator::AND:
                return left & right;
            case WireOperator::OR:
                return left | right;
            case WireOperator::XOR:
                return left ^ right;
            default:
                return -1;
        }
    }

    static std::optional<std::string> find_output(const std::unordered_map<std::string, WireOperation>& wires, const std::string& left, const std::string& right, const WireOperator op)
    {
        for (const auto& [output, operation] : wires)
        {
            if (operation.left == left && operation.right == right && operation.op == op)
            {
                return output;
            }
            else if (operation.left == right && operation.right == left && operation.op == op)
            {
                return output;
            }
        }

        return std::nullopt;
    }

    std::string Day24::part_1(const std::filesystem::path& input_root) const
    {
        const auto [literals, wires] = parse_input(input_root / "day_24.txt");

        std::vector<std::pair<std::string, std::int64_t>> bits;
        for (const auto& [wire, _] : wires)
        {
            // Skip wires that don't start with `z`
            if (!wire.starts_with('z')) { continue; }

            const std::int64_t value = do_operation(literals, wires, wire);
            bits.emplace_back(wire, value);
        }

        std::ranges::sort(bits, [](const auto& left, const auto& right) { return left.first > right.first; });

        std::int64_t result = 0;
        for (const auto& [w, bit] : bits)
        {
            result <<= 1;
            result |= bit;
        }

        return fmt::format("The wires starting with 'z' output the number: {}", result);
    }

    std::string Day24::part_2(const std::filesystem::path& input_root) const
    {
        const auto [literals, wires] = parse_input(input_root / "day_24.txt");

        std::vector<std::string> swapped;
        std::optional<std::string> c0 = std::nullopt;
        for (std::size_t i = 0; i < 45; ++i)
        {
            // Half adder
            // x1 ^ y1 -> m1
            // x1 & y1 -> n1
            // c0 & m1 -> r1
            // c0 ^ m1 -> z1
            // r1 | n1 -> c1

            std::string input_wire_x = fmt::format("x{:02}", i);
            std::string input_wire_y = fmt::format("y{:02}", i);

            auto m1 = find_output(wires, input_wire_x, input_wire_y, WireOperator::XOR);
            auto n1 = find_output(wires, input_wire_x, input_wire_y, WireOperator::AND);
            std::optional<std::string> r1 = std::nullopt;
            std::optional<std::string> z1 = std::nullopt;
            std::optional<std::string> c1 = std::nullopt;

            if (c0)
            {
                r1 = find_output(wires, *c0, *m1, WireOperator::AND);
                if (!r1)
                {
                    std::swap(*m1, *n1);
                    swapped.push_back(*m1);
                    swapped.push_back(*n1);
                    r1 = find_output(wires, *c0, *m1, WireOperator::AND);
                }

                z1 = find_output(wires, *c0, *m1, WireOperator::XOR);

                if (m1 && m1->starts_with('z'))
                {
                    std::swap(*m1, *z1);
                    swapped.push_back(*m1);
                    swapped.push_back(*z1);
                }

                if (n1 && n1->starts_with('z'))
                {
                    std::swap(*n1, *z1);
                    swapped.push_back(*n1);
                    swapped.push_back(*z1);
                }

                if (r1 && r1->starts_with('z'))
                {
                    std::swap(*r1, *z1);
                    swapped.push_back(*r1);
                    swapped.push_back(*z1);
                }

                if (r1)
                {
                    c1 = find_output(wires, *r1, *n1, WireOperator::OR);
                }
            }

            if (c1 && c1->starts_with('z') && *c1 != "z45")
            {
                std::swap(*c1, *z1);
                swapped.push_back(*c1);
                swapped.push_back(*z1);
            }

            if (c0 && c1)
            {
                c0 = *c1;
            }
            else
            {
                c0 = *n1;
            }
        }

        std::ranges::sort(swapped);

        return fmt::format("Swapped wires: {}", fmt::join(swapped, ","));
    }

} // aoc
