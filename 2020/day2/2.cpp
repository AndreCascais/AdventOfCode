#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include "input.h"

int countPolicies()
{
    int sum = 0;
    for (const auto& policy : v) {
        const auto& [min, max] = policy.limits;
        auto count = std::count(
            policy.password.begin(), policy.password.end(), policy.ch);
        if (count >= min && count <= max) {
            ++sum;
        }
    }
    return sum;
}

int countPolicies2()
{
    int sum = 0;
    for (const auto& policy : v) {
        const auto& [first, second] = policy.limits;
        if ((policy.password[first - 1] == policy.ch) xor
            (policy.password[second - 1] == policy.ch)) {
            ++sum;
        }
    }
    return sum;
}

int main()
{
    std::cout << countPolicies() << '\n';
    std::cout << countPolicies2() << '\n';
}