#include "days.h"

#include <string_view>
#include <string>
#include <iostream>
#include <ranges>
#include <vector>
#include <charconv>
#include <array>
#include <numeric>

namespace day3 {
    class Board {
    public:
        static constexpr int BOARD_LEN = 5;

    private:
        using board_t = std::array<std::array<int, BOARD_LEN>, BOARD_LEN>;
        board_t data;

    public:
        constexpr Board() : data{} {}

        constexpr void set(int r, int c, int val) {
            data[r][c] = val;
        }

        constexpr void mark(int val) {
            for (auto &row: data) {
                for (auto &cell: row) {
                    if (cell == val) {
                        cell = -1;
                    }
                }
            }
        }

        constexpr bool bingo() {
            // Check columns
            for (int c = 0; c < BOARD_LEN; ++c) {
                bool okay = true;
                for (int r = 0; r < BOARD_LEN && okay; ++r) {
                    if (data[r][c] != -1) {
                        okay = false;
                    }
                }
                if (okay) {
                    return true;
                }
            }

            // Check rows
            for (int r = 0; r < BOARD_LEN; ++r) {
                bool okay = true;
                for (int c = 0; c < BOARD_LEN && okay; ++c) {
                    if (data[r][c] != -1) {
                        okay = false;
                    }
                }
                if (okay) {
                    return true;
                }
            }

            return false;
        }

        constexpr int sumUnmarked() {
            return std::accumulate(std::begin(data), std::end(data), 0, [](const auto &acc, const auto &cur) {
                return acc + std::accumulate(std::begin(cur), std::end(cur), 0, [](const auto &acc, const auto &cur) {
                    return acc + std::max(0, cur);
                });
            });
        }
    };
}

// Part 2 solution
void aoc::day3() {
    std::string line;
    std::cin >> line;
    const auto saids = line
                       | std::ranges::views::split(',')
                       | std::ranges::views::transform([](const auto &&str) {
        return std::string_view(&*std::begin(str), std::ranges::distance(str));
    });

    std::vector<day3::Board> boards;
    int num;
    while (std::cin >> num) {
        boards.resize(size(boards) + 1);
        for (int i = 0; i < day3::Board::BOARD_LEN; ++i) {
            for (int j = 0; j < day3::Board::BOARD_LEN; ++j) {
                if (i || j) {
                    std::cin >> num;
                }
                boards.back().set(i, j, num);
            }
        }
    }

    size_t wonCount = 0;
    for (const auto said: saids) {
        int saidNum;
        std::from_chars(said.data(), said.data() + size(said), saidNum);
        int bingoIdx = -1;
        for (size_t i = 0; i < size(boards); ++i) {
            if (boards[i].bingo()) {
                continue;
            }
            boards[i].mark(saidNum);
            if (boards[i].bingo()) {
                ++wonCount;
                if (wonCount == std::size(boards)) {
                    bingoIdx = i;
                    break;
                }
            }
        }

        if (bingoIdx != -1) {
            std::cout << boards[bingoIdx].sumUnmarked() * saidNum;
            break;
        }
    }
}