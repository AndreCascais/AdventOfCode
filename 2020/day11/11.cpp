#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "input.h"

std::vector<std::pair<int, int>> offsets{ { -1, -1 }, { -1, 0 }, { -1, 1 },
                                          { 0, -1 },  { 0, 1 },  { 1, 0 },
                                          { 1, -1 },  { 1, 1 } };

struct AdacentSeats
{
    int free{ 0 };
    int occupied{ 0 };
};

AdacentSeats getAdjecentSeats(const std::vector<std::string>& s,
                              int row,
                              int col)
{
    int rows = s.size();
    int cols = s[0].size();

    AdacentSeats adjacentSeats;
    for (const auto& [offsetRow, offsetCol] : offsets) {
        int nextRow = row + offsetRow;
        int nextCol = col + offsetCol;
        if (nextRow < 0 || nextRow >= rows) {
            continue;
        }
        if (nextCol < 0 || nextCol >= cols) {
            continue;
        }
        char type = s[nextRow][nextCol];
        if (type == '.') {
            continue;
        }
        if (type == '#') {
            ++adjacentSeats.occupied;
        }
        if (type == 'L') {
            ++adjacentSeats.free;
        }
    }
    return adjacentSeats;
}

AdacentSeats getAdjecentSeats2(const std::vector<std::string>& s,
                               int row,
                               int col)
{
    int rows = s.size();
    int cols = s[0].size();

    AdacentSeats adjacentSeats;
    for (const auto& [offsetRow, offsetCol] : offsets) {
        int nextRow = row + offsetRow;
        int nextCol = col + offsetCol;
        char type = '.';
        while (true) {
            if (nextRow < 0 || nextRow >= rows) {
                break;
            }
            if (nextCol < 0 || nextCol >= cols) {
                break;
            }
            type = s[nextRow][nextCol];
            if (type != '.') {
                break;
            }
            nextRow += offsetRow;
            nextCol += offsetCol;
        }
        if (type == '#') {
            ++adjacentSeats.occupied;
        }
        if (type == 'L') {
            ++adjacentSeats.free;
        }
    }
    return adjacentSeats;
}

char getSeatType(const std::vector<std::string>& s,
                 int row,
                 int col,
                 bool considerOnlyNearby = true)
{
    char type = s[row][col];
    if (s[row][col] == '.') {
        return type;
    }
    auto adjacentSeats = considerOnlyNearby ? getAdjecentSeats(s, row, col)
                                            : getAdjecentSeats2(s, row, col);
    if (type == '#' && adjacentSeats.occupied >= (considerOnlyNearby ? 4 : 5)) {
        return 'L';
    } else if (type == 'L' && adjacentSeats.occupied == 0) {
        return '#';
    }
    return type;
}

std::vector<std::string> getNext(const std::vector<std::string>& s,
                                 bool considerOnlyNearby = true)
{
    int rows = s.size();
    int cols = s[0].size();
    std::vector<std::string> next(s.size());

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            next[row].push_back(getSeatType(s, row, col, considerOnlyNearby));
        }
    }
    return next;
}

int main()
{
    auto originalSeats = seats;
    {
        std::vector<std::string> next = getNext(seats);
        while (next != seats) {
            seats = next;
            next = getNext(seats);
        }
        auto sum = 0;
        for (const auto& row : seats) {
            sum += std::count(row.begin(), row.end(), '#');
        }
        std::cout << sum << '\n';
    }
    seats = originalSeats;
    {
        std::vector<std::string> next = getNext(seats, false);
        while (next != seats) {
            seats = next;
            next = getNext(seats, false);
        }
        auto sum = 0;
        for (const auto& row : seats) {
            sum += std::count(row.begin(), row.end(), '#');
        }
        std::cout << sum << '\n';
    }

    return 0;
}