#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

long getFishesAfter(std::vector<long> internalTimers, int days)
{
    for (int day = 0; day < days; ++day) {
        std::rotate(internalTimers.begin(), internalTimers.begin() + 1, internalTimers.end());
        internalTimers[6] += internalTimers[8];
    }
    return std::accumulate(internalTimers.begin(), internalTimers.end(), static_cast<long>(0), std::plus<long>());
}

int main()
{
    std::string line{};
    std::getline(std::cin, line);
    std::replace(line.begin(), line.end(), ',', ' ');
    std::istringstream stream(line);
    std::vector<int> initialTimers((std::istream_iterator<int>(stream)), std::istream_iterator<int>());
    std::vector<long> internalTimers(9);
    
    for (auto timer : initialTimers) {
        ++internalTimers[timer];
    }

    std::cout << "Number of fishes after 80 days:" << getFishesAfter(internalTimers, 80) << '\n';
    std::cout << "Number of fishes after 256 days:" << getFishesAfter(internalTimers, 256) << '\n';
}