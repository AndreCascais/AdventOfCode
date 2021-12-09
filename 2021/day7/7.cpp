#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

int main()
{
    std::string line{};
    std::getline(std::cin, line);
    std::replace(line.begin(), line.end(), ',', ' ');
    std::istringstream stream(line);
    std::vector<int> crabs((std::istream_iterator<int>(stream)), std::istream_iterator<int>());

    std::sort(crabs.begin(), crabs.end());
    int nCrabs = crabs.size();
    int median = nCrabs % 2 == 0 ? (crabs[nCrabs / 2] + crabs[(nCrabs - 1) / 2]) / 2 : crabs[nCrabs];

    std::cout << "Fuel required is:"
              << std::accumulate(crabs.begin(), crabs.end(), 0, [&median](auto sum, auto elem) { return sum + std::abs(elem - median); }) << '\n';

    std::vector<int> candidates(crabs[nCrabs - 1]);
    std::iota(candidates.begin(), candidates.end(), 0);

    auto getDistance = [](auto n1, auto n2) {
        int dist = std::abs(n1 - n2);
        return (dist * (dist + 1)) / 2;
    };
    auto getFuelSpent = [&](const auto& midPoint) {
        return std::accumulate(crabs.begin(), crabs.end(), 0, [&](auto sum, auto n) { return sum + getDistance(n, midPoint); });
    };
    std::cout << "Fuel required with increasing cost is:"
              << std::accumulate(candidates.begin() + 1,
                                 candidates.end(),
                                 getFuelSpent(crabs[0]),
                                 [&](auto best, auto elem) {
                                     int fuelSpent = getFuelSpent(elem);
                                     return fuelSpent < best ? fuelSpent : best;
                                 })
              << '\n';
    std::cout << "Fuel required with increasing cost is also:"
              << getFuelSpent(std::ceil(std::accumulate(crabs.begin(), crabs.end(), 0.0, std::plus<float>()) / nCrabs)) << '\n';
}