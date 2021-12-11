#include <array>
#include <iostream>
#include <fmt/core.h>
#include <queue>
#include "days.h"

namespace day11 {
    constexpr int N = 10;
    using grid_t = std::array<std::array<int, N>, N>;

    [[nodiscard]] grid_t parseInput() {
        grid_t grid;
        for (auto &row: grid) {
            for (auto &elem: row) {
                char ch;
                std::cin >> ch;
                elem = ch - '0';
            }
        }
        return grid;
    }

    int step(grid_t &grid) {
        int flashCount = 0;

        // Find initial flashes
        std::queue<std::array<int, 2>> flashed;
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                ++grid[r][c];
                if (grid[r][c] == 10) {
                    ++flashCount;
                    grid[r][c] = -1;
                    flashed.push({r, c});
                }
            }
        }

        const auto validCell = [&](int r, int c) {
            return r >= 0 && r < N && c >= 0 && c < N && grid[r][c] != -1;
        };

        // Propagate flashes
        while (!std::empty(flashed)) {
            auto[r, c] = flashed.front();
            flashed.pop();
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    const int nr = r + dr;
                    const int nc = c + dc;
                    if (!validCell(nr, nc)) {
                        continue;
                    }
                    ++grid[nr][nc];
                    if (grid[nr][nc] == 10) {
                        ++flashCount;
                        grid[nr][nc] = -1;
                        flashed.push({nr, nc});
                    }
                }
            }
        }

        // Reset grid to valid state
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                grid[r][c] = std::max(grid[r][c], 0);
            }
        }

        return flashCount;
    }

    void part1(const grid_t &origGrid) {
        auto grid{origGrid};
        int totalFlashes = 0;
        for (int count = 0; count < 100; ++count) {
            totalFlashes += step(grid);
        }
        fmt::print("Part 1: {}\n", totalFlashes);
    }

    void part2(const grid_t &origGrid) {
        auto grid{origGrid};
        int count{0};
        for (int flashCount{0}; flashCount != N * N; ++count) {
            flashCount = step(grid);
        }
        fmt::print("Part 2: {}\n", count);
    }
}

void aoc::day11() {
    const auto grid = day11::parseInput();
    day11::part1(grid);
    day11::part2(grid);
}