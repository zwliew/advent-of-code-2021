#include <vector>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <fmt/core.h>
#include <algorithm>
#include <optional>
#include "days.h"

namespace day10 {
    std::unordered_map<char, int> illegalPoints{
            {')', 3},
            {']', 57},
            {'}', 1197},
            {'>', 25137},
    };
    std::unordered_map<char, char> matchingPair{
            {'(', ')'},
            {'[', ']'},
            {'{', '}'},
            {'<', '>'},
    };
    std::unordered_map<char, int> incompletePoints{
            {')', 1},
            {']', 2},
            {'}', 3},
            {'>', 4},
    };

    [[nodiscard]] std::vector<std::string> parseInput() {
        std::vector<std::string> result;
        std::string line;
        while (std::cin >> line) {
            result.push_back(std::move(line));
        }
        return result;
    }

    [[nodiscard]] std::optional<char> findCorruptChar(const std::string &line, std::stack<char> &nextClose) {
        for (const char ch: line) {
            if (matchingPair.contains(ch)) {
                nextClose.push(matchingPair[ch]);
            } else if (std::empty(nextClose) || ch != nextClose.top()) {
                return ch;
            } else {
                nextClose.pop();
            }
        }
        return {};
    }

    void part1(const std::vector<std::string> &lines) {
        int totalScore = 0;
        for (const auto &line: lines) {
            std::stack<char> nextClose;
            if (const auto corruptChar = findCorruptChar(line, nextClose); corruptChar.has_value()) {
                totalScore += illegalPoints[corruptChar.value()];
            }
        }
        fmt::print("Part 1: {}\n", totalScore);
    }

    void part2(const std::vector<std::string> &lines) {
        std::vector<int64_t> scores;
        for (const auto &line: lines) {
            std::stack<char> nextClose;
            if (const auto corruptChar = findCorruptChar(line, nextClose); !corruptChar.has_value()) {
                int64_t curScore = 0;
                while (!std::empty(nextClose)) {
                    const auto topChar = nextClose.top();
                    nextClose.pop();
                    curScore = curScore * 5 + incompletePoints[topChar];
                }
                scores.push_back(curScore);
            }
        }
        const int medianIdx = static_cast<int>(std::size(scores)) / 2;
        std::ranges::nth_element(scores, std::begin(scores) + medianIdx);
        fmt::print("Part 2: {}\n", scores[medianIdx]);
    }
}

void aoc::day10() {
    const auto lines = day10::parseInput();
    day10::part1(lines);
    day10::part2(lines);
}
