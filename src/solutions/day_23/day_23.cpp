#include "solutions/day_23/day_23.h"

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ctre.hpp"
#include "fmt/format.h"
#include "fmt/ranges.h"

#include "utility/io.h"
#include "utility/utility.h"

namespace aoc
{
    static std::unordered_map<std::string, std::unordered_set<std::string>> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::unordered_map<std::string, std::unordered_set<std::string>> network;
        for (std::string line; std::getline(file, line); )
        {
            auto match = ctre::match<R"((?<from>\w+)-(?<to>\w+))">(line);
            const std::string from = match.get<"from">().to_string();
            const std::string to = match.get<"to">().to_string();

            network[from].insert(to);
            network[to].insert(from);
        }

        return network;
    }

    static void bron_kerbosch(
        const std::unordered_map<std::string, std::unordered_set<std::string>>& network,
        std::unordered_set<std::string>& r,
        std::unordered_set<std::string> p,
        std::unordered_set<std::string> x,
        std::vector<std::unordered_set<std::string>>& cliques)
    {
        if (p.empty())
        {
            if (x.empty())
            {
                cliques.push_back(r);
            }

            return;
        }

        for (const auto& n : std::unordered_set<std::string>(p))
        {
            const auto& neighbors = network.at(n);
            const auto p2 = set_intersection(p, neighbors);
            const auto x2 = set_intersection(x, neighbors);

            r.insert(n);
            bron_kerbosch(network, r, p2, x2, cliques);
            r.erase(n);
            p.erase(n);
            x.insert(n);
        }
    }

    std::string Day23::part_1(const std::filesystem::path& input_root) const
    {
        const auto network = parse_input(input_root / "day_23.txt");

        std::unordered_set<std::array<std::string, 3>> connected_computers;
        for (const auto& [c1, _] : network)
        {
            // Skip computers that don't start with 't'
            if (!c1.starts_with('t')) { continue; }

            for (const auto& c2 : network.at(c1))
            {
                for (const auto& c3 : set_intersection(network.at(c1), network.at(c2)))
                {
                    std::array<std::string, 3> connected = { {c1, c2, c3} };
                    std::ranges::sort(connected);
                    connected_computers.insert(connected);
                }
            }
        }

        return fmt::format("Inter-connected computers with a computer name that starts with 't': {}", connected_computers.size());
    }

    std::string Day23::part_2(const std::filesystem::path& input_root) const
    {
        const auto network = parse_input(input_root / "day_23.txt");

        std::vector<std::unordered_set<std::string>> cliques;
        std::unordered_set<std::string> r;
        std::unordered_set<std::string> p = network | std::views::transform([](const auto& p) { return p.first; }) | std::ranges::to<std::unordered_set<std::string>>();
        bron_kerbosch(network, r, p, std::unordered_set<std::string>(), cliques);

        std::vector<std::string> largest_connection = *std::ranges::max_element(cliques, [](const auto& left, const auto& right) { return left.size() < right.size(); })
            | std::ranges::to<std::vector<std::string>>();
        std::ranges::sort(largest_connection);

        return fmt::format("Password to the LAN party: {}", fmt::join(largest_connection, ","));
    }

} // aoc
