#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
#include <fmt/core.h>
#include "days.h"

namespace day12 {
    auto parseInput() {
        std::unordered_map<std::string, std::vector<std::string>> adj;
        std::string line;
        while (std::getline(std::cin, line)) {
            const auto idx = line.find('-');
            auto first = line.substr(0, idx);
            auto second = line.substr(idx + 1);
            adj[first].push_back(second);
            adj[second].push_back(first);
        }
        return adj;
    }

    int countPathsStartingFrom(const auto &adj, const std::string &s, std::unordered_set<std::string> &visitedSmall,
                               bool visitedTwice) {
        if (s == "end") {
            return 1;
        }
        int count = 0;
        for (const auto &neighbour: adj.at(s)) {
            if (neighbour == "start") {
                continue;
            }
            if (isupper(neighbour[0]) || neighbour == "end" || !visitedSmall.contains(neighbour)) {
                visitedSmall.insert(neighbour);
                count += countPathsStartingFrom(adj, neighbour, visitedSmall, visitedTwice);
                visitedSmall.erase(neighbour);
            } else if (!visitedTwice) {
                count += countPathsStartingFrom(adj, neighbour, visitedSmall, true);
            }
        }
        return count;
    }

    void part1(const auto &adj) {
        std::unordered_set<std::string> visitedSmall;
        const auto count = countPathsStartingFrom(adj, "start", visitedSmall, true);
        fmt::print("Part 1: {}\n", count);
    }

    void part2(const auto &adj) {
        std::unordered_set<std::string> visitedSmall;
        const auto count = countPathsStartingFrom(adj, "start", visitedSmall, false);
        fmt::print("Part 2: {}\n", count);
    }
}

void aoc::day12() {
    const auto input = day12::parseInput();
    day12::part1(input);
    day12::part2(input);
}