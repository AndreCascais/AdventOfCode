#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>
#include <ranges>
#include <boost/dynamic_bitset.hpp>

long getPowerConsumption(const std::vector<std::string>& diagnosticReport)
{
    std::vector<int> cummulativeSum(diagnosticReport[0].size());

    for (const auto& diagnostic : diagnosticReport) {
        boost::dynamic_bitset<> bitset(diagnostic);
        for (int bit = 0; bit < cummulativeSum.size(); ++bit) {
            cummulativeSum[bit] += bitset[bit];
        }
    }

    boost::dynamic_bitset<> gamaRate;
    boost::dynamic_bitset<> epsilonRate;

    for (const auto& elem : cummulativeSum) {
        gamaRate.push_back(elem * 2 > diagnosticReport.size() ? 1 : 0);
        epsilonRate.push_back(elem * 2 > diagnosticReport.size() ? 0 : 1);
    }

    return epsilonRate.to_ulong() * gamaRate.to_ulong();
}

long getLifeSupportRating(const std::vector<std::string>& diagnosticReport)
{
    int bit = 0;
    auto oxygenReport = diagnosticReport;
    auto getBitSum = [](const auto& diagnostics, int bit) {
        return std::accumulate(diagnostics.begin(),
                               diagnostics.end(),
                               0,  
                               [&bit](int sum, const std::string& diagnostic) {
                                   return sum + (diagnostic[bit] - '0');
                               });
    };

    auto eraseBitsDiffering = [](auto& diagnostics, int bit, int value){
        std::erase_if(diagnostics, [&value, &bit](const auto& elem) {
            return elem[bit] - '0' != value;
        });
    };
    while (oxygenReport.size() != 1)
    {
        auto bitSum = getBitSum(oxygenReport, bit);    
        auto mostFrequentBit = bitSum * 2 >= oxygenReport.size() ? 1 : 0;
        eraseBitsDiffering(oxygenReport, bit, mostFrequentBit);
        bit++;
    }

    bit = 0;
    auto co2report = diagnosticReport;
    while (co2report.size() != 1)
    {
        auto bitSum = getBitSum(co2report, bit);
        auto leastFrequentBit = bitSum * 2 >= co2report.size() ? 0 : 1;
        eraseBitsDiffering(co2report, bit, leastFrequentBit);
        bit++;
    }
    
    return boost::dynamic_bitset<>{oxygenReport[0]}.to_ulong() * boost::dynamic_bitset<>{co2report[0]}.to_ulong();;
}

int main()
{
    std::string line;
    std::vector<std::string> diagnosticReport;
    while (getline(std::cin, line)) {
        diagnosticReport.push_back(line);
    }
    std::cout << "Power consumption is:"
              << getPowerConsumption(diagnosticReport) << '\n';
    std::cout << "Life support rationt is:"
              << getLifeSupportRating(diagnosticReport) << '\n';
}
