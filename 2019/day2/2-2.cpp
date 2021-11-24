#include <iostream>
#include <vector>

void readValues(std::vector<int>& vector) {
    int value;
    char delim;
    while (std::cin >> value >> delim) {
        vector.emplace_back(value);
    }
    std::cin >> value;
    vector.emplace_back(value);
}

void calculateIntCode(std::vector<int>& vector) {
    int opCodeIdx = 0;
    int opCode = vector[opCodeIdx];
    while (opCode != 99) {

        int left = vector[vector[opCodeIdx + 1]];
        int right = vector[vector[opCodeIdx + 2]];
        int dest = vector[opCodeIdx + 3];

        if (opCode == 1) {
            vector[dest] = left + right;
        }
        else if (opCode == 2) {
            vector[dest] = left * right;
        }

        opCodeIdx = opCodeIdx + 4;
        opCode = vector[opCodeIdx];
    }
}   

int main() {
    std::vector<int> initialVector;
    
    readValues(initialVector);
    for (int noun = 0; noun < 100; noun++) {
        for (int verb = 0; verb < 100; verb++) {
            std::vector<int> vector = initialVector;
            vector[1] = noun;
            vector[2] = verb;
            calculateIntCode(vector);
            if (vector[0] == 19690720) {
                std::cout << noun << ',' << verb << '\n';
                return 0;
            }
        }
    }
}