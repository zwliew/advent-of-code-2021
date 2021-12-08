#include "days.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <numeric>
#include <bitset>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <optional>

namespace day7 {
    using input_t = std::vector<std::pair<std::array<std::string, 10>, std::array<std::string, 4>>>;

    std::unordered_map<int, int> canonicalMap{
            {0b1110111, 0},
            {0b0100100, 1},
            {0b1011101, 2},
            {0b1101101, 3},
            {0b0101110, 4},
            {0b1101011, 5},
            {0b1111011, 6},
            {0b0100101, 7},
            {0b1111111, 8},
            {0b1101111, 9},
    };

    [[nodiscard]] input_t parseInput() {
        std::string line;
        input_t result;
        while (std::getline(std::cin, line)) {
            std::string token;
            std::istringstream iss{line};
            result.resize(std::size(result) + 1);
            int count = 0;
            while (iss >> token) {
                if (token == "|") {
                    continue;
                } else if (count >= 10) {
                    result.back().second[count - 10] = std::move(token);
                    ++count;
                } else {
                    result.back().first[count] = std::move(token);
                    ++count;
                }
            }
        }
        return result;
    }

    int accumulateLine(const input_t::value_type &line) {
        const auto mapValue = [&](const auto &permutation, const auto &value) -> std::optional<int> {
            int actualKey = 0;
            for (const auto &ch: value) {
                actualKey |= 1 << permutation[ch - 'a'];
            }
            if (!canonicalMap.contains(actualKey)) {
                return std::nullopt;
            }
            return std::optional{canonicalMap[actualKey]};
        };

        const auto isMappable = [&](const auto &permutation, const auto &values) {
            std::unordered_set<int> seen;
            for (const auto &value: values) {
                if (const auto mapped = mapValue(permutation, value); mapped.has_value()) {
                    seen.insert(mapped.value());
                }
            }
            return std::size(seen) == 10;
        };

        std::array<int, 7> permutation{};
        std::iota(std::begin(permutation), std::end(permutation), 0);
        do {
            const auto success = isMappable(permutation, line.first);
            if (success) {
                int outputValue = 0;
                for (const auto &value: line.second) {
                    outputValue = outputValue * 10 + mapValue(permutation, value).value();
                }
                return outputValue;
            }
        } while (std::next_permutation(std::begin(permutation), std::end(permutation)));
        return 0;
    }
}

void aoc::day7Part1() {
    // 0: 6, 1: 2, 2: 5, 3: 5, 4: 4, 5: 5, 6: 6, 7: 3, 8: 7, 9: 6
    // 2: 1
    // 3: 7
    // 4: 4
    // 5: 2, 3, 5
    // 6: 0, 6, 9
    // 7: 8
    const auto outputVals = day7::parseInput();
    const auto count = std::accumulate(std::begin(outputVals), std::end(outputVals), 0,
                                       [](const auto &acc, const auto &cur) {
                                           return acc + std::count_if(std::begin(cur.second), std::end(cur.second),
                                                                      [](const auto &val) {
                                                                          return std::size(val) == 2 ||
                                                                                 std::size(val) == 3 ||
                                                                                 std::size(val) == 4 ||
                                                                                 std::size(val) == 7;
                                                                      });
                                       });
    std::cout << "Part 1: " << count << '\n';
}

void aoc::day7Part2() {
    const auto outputVals = day7::parseInput();
    const auto sum = std::accumulate(std::begin(outputVals), std::end(outputVals), 0,
                                     [](const auto &acc, const auto &cur) {
                                         return acc + day7::accumulateLine(cur);
                                     });
    std::cout << "Part 2: " << sum << '\n';
}