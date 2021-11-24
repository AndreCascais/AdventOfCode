#include "input.h"
#include <iostream>
#include <vector>

int
main()
{
    int dirY = 0;
    int dirX = 0;
    int angle = 0;

    for (const auto& [direction, ammount] : actions) {
        switch (direction) {
            case 'N':
                dirY += ammount;
                break;
            case 'S':
                dirY -= ammount;
                break;
            case 'E':
                dirX += ammount;
                break;
            case 'W':
                dirX -= ammount;
                break;
            case 'F':
                if (angle == 0) {
                    dirX += ammount;
                } else if (angle == 90) {
                    dirY += ammount;
                } else if (angle == 180) {
                    dirX -= ammount;
                } else if (angle == 270) {
                    dirY -= ammount;
                } else {
                    std::cout << "not supposed to happen, angle is:" << angle
                              << '\n';
                }
                break;
            case 'L':
                angle = ((angle + ammount) % 360 + 360) % 360;
                break;
            case 'R':
                angle = ((angle - ammount) % 360 + 360) % 360;
                break;
            default:
                std::cout << "not supposed to happen, dir is:" << direction
                          << '\n';
        }
    }
    std::cout << "dirX is:" << dirX << ", and dirY is:" << dirY << '\n';
    std::cout << "the manhattan distance is:" << abs(dirY) + abs(dirX) << '\n';
}