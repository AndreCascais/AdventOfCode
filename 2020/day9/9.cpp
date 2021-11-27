#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "input.h"

int getFirstFailureIndex()
{
    for (size_t index = 25; index < code.size(); ++index) {
        long curValue = code[index];
        std::unordered_set<long> s;
        for (size_t preambleIdx = index - 25; preambleIdx < index;
             ++preambleIdx) {
            s.emplace(code[preambleIdx]);
        }
        bool found{ false };
        for (const auto& elem : s) {
            if (s.find(curValue - elem) != s.end()) {
                found = true;
                break;
            }
        }
        if (!found) {
            return index;
        }
    }
    return -1;
}

std::vector<long> generatePrefixSumList(int lastIndex)
{
    std::vector<long> prefSum(lastIndex);
    long sum = 0;
    for (int idx = 0; idx < lastIndex; ++idx) {
        sum = sum + code[idx];
        prefSum[idx] = sum;
    }
    return prefSum;
}

std::pair<int, int> getSequence(long valueIdx, const std::vector<long>& prefixSum)
{
    for (size_t firstIdx = 0; firstIdx < prefixSum.size(); ++firstIdx) {
        for (size_t secondIdx = firstIdx + 1; secondIdx < prefixSum.size();
             ++secondIdx) {
            if (prefixSum[secondIdx] - prefixSum[firstIdx] + code[firstIdx] ==
                code[valueIdx]) {
                return { firstIdx, secondIdx };
            }
        }
    }
    return {};
}

int main()
{
    std::cout << code[getFirstFailureIndex()] << '\n';
    auto failureIdx = getFirstFailureIndex();
    auto prefSum = generatePrefixSumList(failureIdx);
    auto [first, last] = getSequence(failureIdx, prefSum);
    // std::cout << "first: " << first << ", last: " << last << '\n';
    auto minimum =
        *std::min_element(code.begin() + first, code.begin() + last + 1);
    auto maximum =
        *std::max_element(code.begin() + first, code.begin() + last + 1);
    std::cout << minimum + maximum << '\n';
}
