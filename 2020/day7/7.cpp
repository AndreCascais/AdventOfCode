#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "input.h"

void getDependants(
    std::unordered_map<std::string, std::unordered_set<std::string>>& dependencyMap,
    const std::string& bag,
    std::unordered_set<std::string>& dependants,
    std::unordered_map<std::string, int>& countMap)
{
    if (dependencyMap.find(bag) != dependencyMap.end()) {
        // dependants already filled
        for (const auto& nextBag : dependencyMap[bag]) {
            dependants.emplace(nextBag);
        }
        return;
    }
    if (rules[bag].size() == 0) {
        countMap[bag] = 1;
        return;
    }
    auto sum = 1;
    for (const auto& [nextBag, count] : rules[bag]) {
        std::unordered_set<std::string> nextDeps;
        nextDeps.emplace(nextBag);
        getDependants(dependencyMap, nextBag, nextDeps, countMap);
        for (const auto& b : nextDeps) {
            dependants.emplace(b);
        }
        sum += count * countMap[nextBag];
    }
    dependencyMap[bag] = dependants;
    countMap[bag] = sum;
}

void fillDependants(
    std::unordered_map<std::string, std::unordered_set<std::string>>& dependencyMap,
    std::unordered_map<std::string, int>& countMap)
{
    for (const auto& [bag, _] : rules) {
        std::unordered_set<std::string> dependants;
        getDependants(dependencyMap, bag, dependants, countMap);
    }
}

int main()
{
    std::unordered_map<std::string, std::unordered_set<std::string>> dependencyMap;
    std::unordered_map<std::string, int> countMap;
    fillDependants(dependencyMap, countMap);
    int sum = 0;
    for (const auto& [bag, deps] : dependencyMap) {
        if (bag == "shiny gold") {
            continue;
        }
        if (deps.find("shiny gold") != deps.end()) {
            ++sum;
        }
    }
    std::cout << sum << '\n';
    std::cout << countMap["shiny gold"] - 1 << '\n';
}