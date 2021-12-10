#include <vector>
#include <string>
#include <iostream>
#include <numeric>
#include <ranges>
#include <algorithm>
#include "days.h"

namespace day9 {
    using grid_t = std::vector<std::vector<int>>;

    constexpr std::array<std::array<int, 2>, 4> neighbours{{{0, 1},
                                                            {0, -1},
                                                            {1, 0},
                                                            {-1, 0}}};

    [[nodiscard]] grid_t parseInput() {
        grid_t grid;
        std::string line;
        while (std::cin >> line) {
            grid.resize(std::size(grid) + 1);
            for (const auto &ch: line) {
                grid.back().push_back(ch - '0');
            }
        }
        return grid;
    }

    [[nodiscard]] constexpr bool isValid(const grid_t &grid, int r, int c) {
        return r >= 0 && c >= 0 && static_cast<size_t>(r) < std::size(grid) &&
               static_cast<size_t>(c) < std::size(grid[0]);
    }
};

void aoc::day9Part1() {
    const auto grid = day9::parseInput();

    const auto isLowest = [&](int r, int c) {
        return std::all_of(std::begin(day9::neighbours), std::end(day9::neighbours), [&](const auto &neighbour) {
            const auto nr{r + neighbour[0]};
            const auto nc{c + neighbour[1]};
            return !day9::isValid(grid, nr, nc) || grid[nr][nc] > grid[r][c];
        });
    };

    int sum = 0;
    for (size_t r{0}; r < std::size(grid); ++r) {
        for (size_t c{0}; c < std::size(grid[0]); ++c) {
            if (isLowest(static_cast<int>(r), static_cast<int>(c))) {
                sum += grid[r][c] + 1;
            }
        }
    }

    std::cout << "Part 1: " << sum << '\n';
}

void aoc::day9Part2() {
    auto grid = day9::parseInput();

    auto computeBasinSize = [&](auto &&computeBasinSize, int r, int c) -> int {
        if (!day9::isValid(grid, r, c) || grid[r][c] == 9) {
            return 0;
        }
        grid[r][c] = 9;
        int basinSize = 1;
        for (const auto &neighbour: day9::neighbours) {
            const auto nr{r + neighbour[0]};
            const auto nc{c + neighbour[1]};
            basinSize += computeBasinSize(computeBasinSize, nr, nc);
        }
        return basinSize;
    };

    std::vector<int> sizes;
    for (size_t r{0}; r < std::size(grid); ++r) {
        for (size_t c{0}; c < std::size(grid[0]); ++c) {
            const auto basinSize = computeBasinSize(computeBasinSize, static_cast<int>(r), static_cast<int>(c));
            if (basinSize) {
                sizes.push_back(basinSize);
            }
        }
    }
    std::nth_element(std::begin(sizes), std::end(sizes) - 3, std::end(sizes));
    const auto N = std::size(sizes);
    std::cout << "Part 2: " << sizes[N - 1] * sizes[N - 2] * sizes[N - 3] << '\n';
}