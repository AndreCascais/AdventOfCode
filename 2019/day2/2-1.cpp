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
    std::vector<int> vector;
    
    readValues(vector);

    vector[1] = 12;
    vector[2] = 2;
    calculateIntCode(vector);

    std::cout << vector[0] << '\n';
    
}
