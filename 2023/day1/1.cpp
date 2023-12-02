#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <ranges>
#include <vector>
#include <range/v3/all.hpp>

void solvePart1(const std::vector<std::string>& input)
{

    auto count = 0;
    for (const auto& line : input) {
        auto first = std::find_if(line.cbegin(), line.cend(), isdigit);
        auto last = std::find_if(line.rbegin(), line.rend(), isdigit);
        std::string digits{ *first, *last };
        count += std::stoi(digits);
    }
    std::cout << count << '\n';
}

void solvePart2(const std::vector<std::string>& input)
{
    std::map<std::string, std::string> m{
        { "one", "1" }, { "two", "2" },   { "three", "3" }, { "four", "4" }, { "five", "5" },
        { "six", "6" }, { "seven", "7" }, { "eight", "8" }, { "nine", "9" },
    };
    auto count = 0;
    for (const auto& line : input) {
        std::string firstDigit;
        int firstPos = line.length();
        std::string lastDigit;
        int lastPos = -1;

        for (const auto& [digitStr, digit] : m) {
            const int fPos = line.find(digitStr);
            const int lPos = line.rfind(digitStr);
            if (fPos != std::string::npos && fPos < firstPos) {
                firstPos = fPos;
                firstDigit = digit;
            }

            if (lPos != std::string::npos && lPos > lastPos) {
                lastPos = lPos;
                lastDigit = digit;
            }
        }
        auto first = std::find_if(line.cbegin(), line.cend(), isdigit);
        auto last = std::find_if(line.rbegin(), line.rend(), isdigit);
        auto firstDistance = std::distance(line.begin(), first);
        if (firstDistance < firstPos) {
            firstPos = firstDistance;
            firstDigit = *first;
        }
        auto lastDistance = std::distance(last, line.rend());
        if (lastDistance > lastPos) {
            lastPos = lastDistance;
            lastDigit = *last;
        }
        std::string digits{ firstDigit.at(0), lastDigit.at(0) };
        count += std::stoi(digits);
    }

    std::cout << count << '\n';
}

int main()
{
    std::vector<std::string> input;
    std::string line;
    while (std::cin >> line) {
        input.push_back(line);
    }

    solvePart1(input);
    solvePart2(input);
}
