#include <iostream>

int fuel (int mass) {
    int total = 0;
    int remainingMass = mass / 3 - 2;

    while (mass > 0) {
        total = total + remainingMass;
        remainingMass = remainingMass / 3 - 2;
    }
    return total;
}

int main() {
    int mass;
    int sum = 0;

    while (std::cin >> mass) {
        sum += fuel(mass);
    }
    
    std::cout << sum << '\n';
}