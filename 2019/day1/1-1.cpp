#include <iostream>

int fuel (int mass) {
    return mass / 3 - 2;
}

int main() {
    int mass;
    int sum = 0;

    while (std::cin >> mass) {
        sum += fuel(mass);
    }
    
    std::cout << sum << '\n';
}