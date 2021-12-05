#include "days.h"

#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <map>

class Coordinate {
public:
    int sx, sy, ex, ey;

    Coordinate(int sx, int sy, int ex, int ey) : sx{sx}, sy{sy}, ex{ex}, ey{ey} {}
};

[[nodiscard]] std::array<int, 2> extractCoordinates(const std::string &token) {
    std::array<int, 2> coordinates{-1, -1};
    int curVal = 0;
    for (const auto ch: token) {
        if (ch == ',') {
            coordinates[0] = curVal;
            curVal = 0;
        } else {
            curVal = curVal * 10 + ch - '0';
        }
    }
    coordinates[1] = curVal;
    return coordinates;
}

[[nodiscard]] std::vector<Coordinate> parseInput() {
    std::vector<Coordinate> coordinates;
    std::string firstToken;
    while (std::cin >> firstToken) {
        std::string secondToken;
        std::cin >> secondToken >> secondToken;
        const auto start = extractCoordinates(firstToken);
        const auto end = extractCoordinates(secondToken);
        coordinates.emplace_back(start[0], start[1], end[0], end[1]);
    }
    return coordinates;
}

int countRelevantPoints(const std::map<std::array<int, 2>, int> &count) {
    int result = 0;
    for (const auto &[k, v]: count) {
        result += v >= 2;
    }
    return result;
}

std::map<std::array<int, 2>, int> accumulateOverlaps(const std::vector<Coordinate> &coordinates, bool ignoreDiagonals) {
    std::map<std::array<int, 2>, int> count;
    for (const auto &coord: coordinates) {
        if (ignoreDiagonals && coord.sx != coord.ex && coord.sy != coord.ey) {
            continue;
        }
        const int dx = coord.sx <= coord.ex ? 1 : -1;
        const int dy = coord.sy <= coord.ey ? 1 : -1;
        const int minx = std::min(coord.sx, coord.ex);
        const int maxx = std::max(coord.sx, coord.ex);
        const int miny = std::min(coord.sy, coord.ey);
        const int maxy = std::max(coord.sy, coord.ey);
        for (int x = coord.sx, y = coord.sy;
             x != coord.ex || y != coord.ey;
             x = std::clamp(x + dx, minx, maxx), y = std::clamp(y + dy, miny, maxy)) {
            ++count[{x, y}];
        }
        ++count[{coord.ex, coord.ey}];
    }
    return count;
}

void aoc::day4Part1() {
    const auto coordinates = parseInput();
    const auto count = accumulateOverlaps(coordinates, true);
    std::cout << countRelevantPoints(count);
}

void aoc::day4Part2() {
    const auto coordinates = parseInput();
    const auto count = accumulateOverlaps(coordinates, false);
    std::cout << countRelevantPoints(count);
}