#include "days.h"

#include <array>
#include <iostream>
#include <cassert>
#include <numeric>

namespace day5 {
    constexpr int MAX_TIMER = 9;

    [[nodiscard]] auto parseInput() {
        std::array<int64_t, MAX_TIMER> counts{};
        char ch;
        while (std::cin >> ch) {
            if (ch != ',') {
                assert(ch >= '0' && ch <= '8');
                ++counts[ch - '0'];
            }
        }
        return counts;
    }

    void simulate(auto &counts, const int days) {
        for (int day = 0; day < days; ++day) {
            std::array<int64_t, day5::MAX_TIMER> nextCounts{};
            for (int i = 0; i < day5::MAX_TIMER; ++i) {
                if (!i) {
                    nextCounts[6] += counts[i];
                    nextCounts[8] += counts[i];
                } else {
                    nextCounts[i - 1] += counts[i];
                }
            }
            std::swap(nextCounts, counts);
        }
    }
}

void aoc::day5Part1() {
    auto counts = day5::parseInput();
    day5::simulate(counts, 80);
    std::cout << std::accumulate(std::begin(counts), std::end(counts), static_cast<int64_t>(0));
}

void aoc::day5Part2() {
    auto counts = day5::parseInput();
    day5::simulate(counts, 256);
    std::cout << std::accumulate(std::begin(counts), std::end(counts), static_cast<int64_t>(0));
}