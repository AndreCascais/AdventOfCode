#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <numeric>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <regex>

#include "input.h"

using bigint = unsigned long long;

bigint getAdapterArrangements(int start, std::map<int, bigint>& m)
{
    auto max = *(--adapters.end());
    if (start > max) {
        return 0;
    }
    if (adapters.find(start) == adapters.end() && start != 0) {
        return 0;
    }
    if (m.find(start) == m.end()) {
        m[start] = getAdapterArrangements(start + 1, m) +
            getAdapterArrangements(start + 2, m) +
            getAdapterArrangements(start + 3, m);
    }
    return m[start];
}

std::pair<int, int> getJoltDiferences()
{
    int diff1 = 0;
    int diff3 = 1;
    int jolt = 0;
    auto next = adapters.begin();
    while(next = adapters.upper_bound(jolt), next != adapters.end()) {
        auto diff = *next - jolt;
        if (diff == 1) {
            ++diff1;
        } else if (diff == 3) {
            ++diff3;
        }
        jolt = *next;

    }
    return {diff1, diff3};
}

int main() {
    const auto [diff1, diff3] = getJoltDiferences();
    std::cout << diff1 * diff3 << '\n';
    std::map<int, bigint> m;
    auto max = *(--adapters.end());
    m[max] = 1;
    std::cout << getAdapterArrangements(0, m) << '\n';    
}
