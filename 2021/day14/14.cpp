#include <iostream>
#include <iterator>
#include <list>
#include <regex>
#include <string>
#include <unordered_map>
#include <utility>

int main()
{
    std::map<std::pair<char, char>, char> rules{};
    std::map<std::pair<char, char>, long> adjacencyCount{};
    std::unordered_map<char, long> freqMap;

    std::string line;
    std::getline(std::cin, line);

    for (auto it = line.begin(); it != std::prev(line.end()); ++it) {
        std::pair<char, char> pair{ *it, *(std::next(it)) };
        ++adjacencyCount[pair];
    }

    for (const auto& ch : line) {
        ++freqMap[ch];
    }

    std::getline(std::cin, line);

    while (std::getline(std::cin, line)) {
        rules[{ line[0], line[1] }] = line[6];
    }

    for (int step = 0; step < 40; ++step) {
        std::map<std::pair<char, char>, long> toBeApplied{};
        for (const auto& [adjacency, count] : adjacencyCount) {
            const auto& [left, right] = adjacency;
            if (rules.contains(adjacency)) {
                auto match = rules[adjacency];
                freqMap[match] += count;
                toBeApplied[{ left, match }] += count;
                toBeApplied[{ match, right }] += count;
                toBeApplied[{ left, right }] -= count;
            }
        }
        for (const auto& [adjacency, count] : toBeApplied) {
            adjacencyCount[adjacency] += count;
        }
    }
    
    auto freqCompare = [](const auto& x, const auto& y) { return x.second < y.second; };
    auto [minElement, maxElement] = std::minmax_element(freqMap.begin(), freqMap.end(), freqCompare);
    std::cout << maxElement->second - minElement->second << '\n';
}