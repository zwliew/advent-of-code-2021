#include "days.h"

#include <vector>
#include <iostream>
#include <numeric>

namespace day7 {
    std::vector<int> parseInput() {
        char ch;
        int cur = 0;
        std::vector<int> positions;
        while (std::cin >> ch) {
            if (ch != ',') {
                cur = cur * 10 + ch - '0';
            } else {
                positions.push_back(cur);
                cur = 0;
            }
        }
        positions.push_back(cur);
        return positions;
    }
};

void aoc::day7Part1() {
    auto positions = day7::parseInput();
    std::nth_element(std::begin(positions), std::begin(positions) + std::ssize(positions) / 2,
                     std::end(positions));
    const auto median = positions[std::size(positions) / 2];
    const auto loss = std::accumulate(std::begin(positions), std::end(positions), 0,
                                      [&](const auto &acc, const auto &cur) {
                                          return acc + std::abs(median - cur);
                                      });
    std::cout << loss;
}

void aoc::day7Part2() {
    const auto positions = day7::parseInput();
    int best = std::numeric_limits<int>::max();
    for (int endpoint = *std::min_element(std::begin(positions), std::end(positions));
         endpoint <= *std::max_element(std::begin(positions), std::end(positions)); ++endpoint) {
        const auto curLoss = std::accumulate(std::begin(positions), std::end(positions), 0,
                                             [&](const auto &acc, const auto &cur) {
                                                 const auto delta = std::abs(endpoint - cur);
                                                 return acc + delta * (delta + 1) / 2;
                                             });
        best = std::min(best, curLoss);
    }
    std::cout << best;
}