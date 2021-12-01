#include <iostream>

#include "input.h"

int getMeasurementIncreaes()
{
    int increases = 0;
    for (auto it = measurements.begin() + 1; it != measurements.end(); ++it) {
        if (*it > *(it-1)) {
            ++increases;
        }
    }
    return increases;
}

int getMeasurentIncreasesSlidingWindow()
{
    int increases = 0;
    int previousWindow = measurements[0] + measurements[1] + measurements[2];
    for (auto it = measurements.begin() + 1; it != measurements.end() - 2; ++it) {
        auto slidingWindow = *it + *(it + 1) + *(it + 2);
        if (slidingWindow > previousWindow) {
            ++increases;
        }
        previousWindow = slidingWindow;
    }
    return increases;

}

int main() {
    
    std::cout << "Numer of increases:" << getMeasurementIncreaes() << '\n';
    std::cout << "Numer of sliding window increases:" << getMeasurentIncreasesSlidingWindow() << '\n';
}