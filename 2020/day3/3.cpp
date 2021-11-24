#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include "input.h"

int getNumTrees(int stepCol = 3, int stepRow = 1)
{
    int sum = 0;
    int col = 0;
    int size = trees[0].length();
    for (uint row = 0; row < trees.size(); row += stepRow) {
        if (trees[row][col] == '#') {
            ++sum;
        }
        col = (col + stepCol) % size;
    }
    return sum;
}

int main()
{
    std::cout << getNumTrees() << '\n';
    std::cout << getNumTrees(1, 1) * getNumTrees(3, 1) * getNumTrees(5, 1) *
                     getNumTrees(7, 1) * getNumTrees(1, 2)
              << '\n';
}
