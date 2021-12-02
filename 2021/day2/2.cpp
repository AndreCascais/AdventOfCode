#include <iostream>
#include <vector>

std::pair<int, int> moveNoAim(const std::vector<std::pair<std::string, int>>& instructions)
{
    int depth = 0;
    int horizontal = 0;
    for (const auto& [direction, ammount] : instructions) {
        if (direction == "forward") {
            horizontal += ammount;
        } else if (direction == "down") {
            depth += ammount;
        } else if (direction == "up") {
            depth -= ammount;
        }
    }
    return {horizontal, depth};
}

std::pair<int, int> moveWithAim(const std::vector<std::pair<std::string, int>>& instructions)
{
    int depth = 0;
    int horizontal = 0;
    int aim = 0;
    for (const auto& [direction, ammount] : instructions) {
        if (direction == "forward") {
            horizontal += ammount;
            depth += aim * ammount;
        } else if (direction == "down") {
            aim += ammount;
        } else if (direction == "up") {
            aim -= ammount;
        }
    }
    return {horizontal, depth};
}

int main() {
    std::string direction;
    int ammount;
    std::vector<std::pair<std::string, int>> input;
    while(std::cin >> direction >> ammount){ 
        input.push_back({direction, ammount});
	}
    auto [horizontalNoAim, depthNoAim] = moveNoAim(input);
    auto [horizontalWithAim, depthWithAim] = moveWithAim(input);
    std::cout << "horizontal position * depth no aim:" << horizontalNoAim * depthNoAim << '\n';
    std::cout << "horizontal position * depth with aim:" << horizontalWithAim * depthWithAim << '\n';
}