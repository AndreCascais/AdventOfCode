#include "input.h"
#include <iostream>
#include <vector>

int
main()
{
    int shipY = 0;
    int shipX = 0;

    int waypointY = 1;
    int waypointX = 10;

    for (auto [direction, ammount] : actions) {
        switch (direction) {
            case 'N':
                waypointY += ammount;
                break;
            case 'S':
                waypointY -= ammount;
                break;
            case 'E':
                waypointX += ammount;
                break;
            case 'W':
                waypointX -= ammount;
                break;
            case 'F':
                shipY += ammount * waypointY;
                shipX += ammount * waypointX;
                break;
            case 'L':
            case 'R': {
                while (ammount > 0) {
                    ammount -= 90;
                    auto x = waypointX;
                    auto y = waypointY;
                    if (direction == 'L') {
                        waypointY = x;
                        waypointX = -y;
                    } else {
                        waypointY = -x;
                        waypointX = y;
                    }
                }
            } break;
            default:
                std::cout << "not supposed to happen, dir is:" << direction
                          << '\n';
        }
    }
    std::cout << "the manhattan distance is:" << abs(shipY) + abs(shipX)
              << '\n';
}