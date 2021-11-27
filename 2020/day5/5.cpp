#include <iostream>
#include <set>

#include "input.h"

int getId(const std::string& s)
{
    int minRow = 0;
    int maxRow = 127;
    for (int i = 0; i < 7; ++i) {
        int midRow = (minRow + maxRow) / 2;
        if (s[i] == 'F') {
            maxRow = midRow;

        } else if (s[i] == 'B') {
            minRow = midRow;
        } else {
            return -1;
        }
    }
    int minCol = 0;
    int maxCol = 7;
    for (int i = 7; i < 10; ++i) {
        int midCol = (minCol + maxCol) / 2;
        if (s[i] == 'L') {
            maxCol = midCol;

        } else if (s[i] == 'R') {
            minCol = midCol;
        } else {
            return -1;
        }
    }
    return maxRow * 8 + maxCol;
}

int getMissingSeat(const std::set<int>& seats)
{
    for (uint i = 0; i < 127 * 8; ++i) {
        if (seats.find(i) == seats.end() && seats.find(i - 1) != seats.end() &&
            seats.find(i + 1) != seats.end()) {
            return i;
        }
    }
    return -1;
}

int main()
{
    int best = -1;
    std::set<int> seats;
    for (const auto& partition : boardingPasses) {
        auto id = getId(partition);
        best = std::max(best, id);
        seats.emplace(id);
    }
    std::cout << best << '\n';
    std::cout << getMissingSeat(seats) << '\n';
}