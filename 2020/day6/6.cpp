#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <numeric>
#include <algorithm>
#include <map>

#include "input.h"

int countUnique(const std::string& s) {
    std::set<char> unique;
    for (const auto& ch : s) {
        unique.emplace(ch);
    }
    return unique.size();
}

int countRepeated(const std::vector<std::string>& groupAnswers) {
    std::map<char, int> m;
    for (const auto& answer : groupAnswers) {
        for (const auto& ch : answer) {
            ++m[ch];
        }
    }
    int sum = 0;
    for (const auto& [key, value] : m) {
        if (value == groupAnswers.size()) {
            ++sum;
        }
    }
    return sum;
}

int main() {
    auto sum = 0;
    for (const auto& answer : answers) {
        sum += countUnique(answer);
    }
    std::cout << sum << '\n';

    auto newSum = 0;
    for (const auto& groupAnswer : newAnswers) {
        newSum += countRepeated(groupAnswer);
    }
    std::cout << newSum << '\n';
}