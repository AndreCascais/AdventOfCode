#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using Direction = std::pair<int, int>;
using Point = std::pair<int, int>;

std::vector<Direction> dirs{ { -1, 0 }, { 0, -1 }, { 0, 1 }, { 1, 0 } };

std::vector<Point> getLowPoints(const std::vector<std::string>& cave)
{
    std::vector<Point> mins;

    for (int row = 1; row < cave.size() - 1; ++row) {
        for (int col = 1; col < cave[0].size() - 1; ++col) {
            bool foundLower = false;
            for (const auto& dir : dirs) {
                auto [offsetX, offsetY] = dir;
                if (cave[row + offsetX][col + offsetY] <= cave[row][col]) {
                    foundLower = true;
                    break;
                }
            }
            if (!foundLower) {
                mins.push_back({ row, col });
            }
        }
    }
    return mins;
}

int getRiskLevels(const std::vector<std::string>& cave, const std::vector<Point>& mins){
    return std::accumulate(mins.begin(), mins.end(), 0, [&](const auto sum, const auto min) {
        auto [row, col] = min;
        return sum + (cave[row][col] - '0') + 1;
    });
}

int flood(const std::vector<std::string>& cave, std::vector<std::vector<bool>>& visited, Point point)
{
    auto [row, col] = point;
    if (cave[row][col] == '9' || visited[row][col]) {
        return 0;
    }
    visited[row][col] = true;
    int n = 1;
    for (const auto& dir : dirs) {
        auto [offsetX, offsetY] = dir;
        n += flood(cave, visited, { row + offsetX, col + offsetY });
    }
    return n;
}

int getLargestBasinsProduct(const std::vector<std::string>& cave, const std::vector<Point>& mins)
{
    std::vector<std::vector<bool>> visited(cave.size(), std::vector<bool>(cave[0].size(), false));
    std::vector<int> basins;
    for (const auto& min : mins) {
        basins.push_back(flood(cave, visited, min));
    }
    std::sort(basins.begin(), basins.end());

    return std::accumulate(basins.rbegin(), basins.rbegin() + 3, 1, std::multiplies<int>());
}

int main()
{
    std::string line;
    std::vector<std::string> cave;
    std::getline(std::cin, line);
    cave.push_back(std::string(line.size() + 2, '9'));

    do {
        cave.push_back("9" + line + "9");
    } while (std::getline(std::cin, line));
    cave.push_back(std::string(cave[0].size(), '9'));
    
    auto lowPoints = getLowPoints(cave);
    std::cout << "Sum of the risk levels: " << getRiskLevels(cave, lowPoints) << '\n';
    std::cout << "Product of three largest basins is: " << getLargestBasinsProduct(cave, lowPoints) << '\n';
}