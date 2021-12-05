#include <algorithm>
#include <iostream>
#include <regex>
#include <vector>

auto isVertical = [](const auto& segment) { return segment[0] == segment[2]; };
auto isHorizontal = [](const auto& segment) { return segment[1] == segment[3]; };

int getOverLappingPointsCount(std::vector<std::vector<int>> segments, int nRows, int nCols, bool countDiagonals)
{
    std::vector<std::vector<int>> diagram(nRows + 1, std::vector<int>(nCols + 1));

    for (const auto& segment : segments) {
        int x0 = segment[0], y0 = segment[1], x1 = segment[2], y1 = segment[3];
        if (isHorizontal(segment)) {
            for (int col = std::min(x0, x1); col <= std::max(x0, x1); ++col) {
                ++diagram[y0][col];
            }
        } else if (isVertical(segment)) {
            for (int row = std::min(y0, y1); row <= std::max(y0, y1); ++row) {
                ++diagram[row][x0];
            }
        } else if (countDiagonals) {
            auto incrementX = x1 > x0 ? 1 : -1;
            auto incrementY = y1 > y0 ? 1 : -1;
            int col = x0;
            int row = y0;
            while(row != y1 + incrementY && col != x1 + incrementX) {
                ++diagram[row][col];
                row += incrementY;
                col += incrementX;
            }
        }
    }

    int count = 0;
    for (const auto& line : diagram) {
        for (const auto& number : line) {
            if (number > 1) {
                ++count;
            }
        }
    }
    return count;
}

int main()
{
    std::string line;
    std::vector<std::vector<int>> segments;
    int nRows = 0;
    int nCols = 0;
    while (std::getline(std::cin, line)) {
        auto formatedLine = std::regex_replace(line, std::regex{ "(\\d+),(\\d+) -> (\\d+),(\\d+)" }, "$1 $2 $3 $4");
        std::istringstream stream(formatedLine);
        std::vector<int> segment((std::istream_iterator<int>(stream)), std::istream_iterator<int>());
        nRows = std::max({ nRows, segment[1], segment[3] });
        nCols = std::max({ nCols, segment[0], segment[2] });
        segments.emplace_back(std::move(segment));
    }

    std::cout << "Number of overlapping points (no diagonals):" << getOverLappingPointsCount(segments, nRows, nCols, false) << '\n';
    std::cout << "Number of overlapping points (counting diagonals):" << getOverLappingPointsCount(segments, nRows, nCols, true) << '\n';
}
