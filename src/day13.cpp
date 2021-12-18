#include <string>
#include <vector>
#include <iostream>
#include <tuple>
#include <set>
#include <fmt/core.h>
#include "days.h"

namespace day13 {
    struct Coordinate {
        int x;
        int y;

        constexpr Coordinate(int x, int y) : x{x}, y{y} {}

        constexpr bool operator<(const Coordinate &other) const {
            return std::tie(x, y) < std::tie(other.x, other.y);
        }

        constexpr bool operator==(const Coordinate &other) const {
            return std::tie(x, y) == std::tie(other.x, other.y);
        }
    };

    struct Input {
        std::vector<Coordinate> coordinates;
        std::vector<Coordinate> folds;
    };

    constexpr int INF = 100000000;

    Input parseInput() {
        Input input{};
        std::string line;
        bool isInstruction{false};
        while (std::getline(std::cin, line)) {
            if (std::empty(line)) {
                isInstruction = true;
            } else if (!isInstruction) {
                const auto separatorIdx{line.find(',')};
                int x{std::stoi(line.substr(0, separatorIdx))};
                int y{std::stoi(line.substr(separatorIdx + 1))};
                input.coordinates.emplace_back(x, y);
            } else {
                bool isX{line.substr(11, 1) == "x"};
                int val{std::stoi(line.substr(13))};
                input.folds.emplace_back(isX ? val : INF, isX ? INF : val);
            }
        }
        return input;
    }

    void fold(std::vector<Coordinate> &coordinates, const Coordinate &fold) {
        for (auto &[x, y]: coordinates) {
            if (x > fold.x) {
                x = 2 * fold.x - x;
            }
            if (y > fold.y) {
                y = 2 * fold.y - y;
            }
        }
    }

    void plot(std::vector<Coordinate> &coordinates) {
        std::sort(std::begin(coordinates), std::end(coordinates));
        const auto maxX = std::max_element(std::begin(coordinates), std::end(coordinates))->x;
        const auto maxY = std::max_element(std::begin(coordinates), std::end(coordinates),
                                           [](const auto &a, const auto &b) {
                                               return a.y < b.y;
                                           })->y;
        for (int y{0}; y <= maxY; ++y) {
            for (int x{0}; x <= maxX; ++x) {
                if (std::binary_search(coordinates.begin(), coordinates.end(), Coordinate{x, y})) {
                    std::cout << '#';
                } else {
                    std::cout << ' ';
                }
            }
            std::cout << '\n';
        }
    }

    void part1(const Input &input) {
        auto coordinates{input.coordinates};
        fold(coordinates, input.folds[0]);
        std::sort(std::begin(coordinates), std::end(coordinates));
        auto endIt = std::unique(std::begin(coordinates), std::end(coordinates));
        fmt::print("Part 1: {}\n", endIt - std::begin(coordinates));
    }

    void part2(const Input &input) {
        auto coordinates{input.coordinates};
        for (const auto &curFold: input.folds) {
            fold(coordinates, curFold);
        }
        std::cout << "Part 2: \n";
        plot(coordinates);
    }
}

void aoc::day13() {
    const auto input{day13::parseInput()};
    day13::part1(input);
    day13::part2(input);
}