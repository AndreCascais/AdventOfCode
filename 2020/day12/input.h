#include <vector>

std::vector<std::pair<char, int>> actions{
    { 'L', 90 },  { 'F', 67 },  { 'R', 270 }, { 'W', 1 },   { 'R', 180 },
    { 'F', 5 },   { 'E', 5 },   { 'F', 59 },  { 'E', 4 },   { 'L', 180 },
    { 'F', 70 },  { 'S', 2 },   { 'F', 35 },  { 'N', 3 },   { 'E', 5 },
    { 'F', 58 },  { 'L', 90 },  { 'N', 1 },   { 'F', 46 },  { 'R', 90 },
    { 'S', 1 },   { 'R', 90 },  { 'E', 1 },   { 'L', 180 }, { 'W', 4 },
    { 'F', 99 },  { 'N', 2 },   { 'F', 84 },  { 'N', 1 },   { 'R', 90 },
    { 'N', 5 },   { 'W', 4 },   { 'F', 26 },  { 'E', 1 },   { 'F', 97 },
    { 'N', 1 },   { 'F', 36 },  { 'W', 1 },   { 'F', 21 },  { 'S', 4 },
    { 'F', 31 },  { 'S', 3 },   { 'F', 76 },  { 'S', 5 },   { 'S', 1 },
    { 'L', 90 },  { 'S', 4 },   { 'W', 4 },   { 'R', 90 },  { 'E', 4 },
    { 'F', 14 },  { 'R', 90 },  { 'S', 2 },   { 'R', 90 },  { 'S', 3 },
    { 'F', 21 },  { 'N', 1 },   { 'W', 4 },   { 'S', 4 },   { 'E', 1 },
    { 'L', 180 }, { 'N', 5 },   { 'F', 30 },  { 'N', 3 },   { 'F', 4 },
    { 'N', 5 },   { 'F', 100 }, { 'N', 2 },   { 'R', 270 }, { 'E', 1 },
    { 'S', 1 },   { 'F', 79 },  { 'N', 4 },   { 'F', 72 },  { 'W', 4 },
    { 'F', 50 },  { 'L', 90 },  { 'W', 5 },   { 'S', 4 },   { 'E', 2 },
    { 'N', 5 },   { 'E', 4 },   { 'S', 5 },   { 'W', 5 },   { 'L', 90 },
    { 'E', 4 },   { 'L', 90 },  { 'S', 4 },   { 'E', 4 },   { 'R', 90 },
    { 'N', 1 },   { 'W', 5 },   { 'R', 270 }, { 'W', 5 },   { 'N', 4 },
    { 'R', 180 }, { 'E', 5 },   { 'F', 86 },  { 'L', 90 },  { 'W', 3 },
    { 'F', 79 },  { 'W', 5 },   { 'F', 87 },  { 'L', 180 }, { 'N', 4 },
    { 'E', 2 },   { 'S', 1 },   { 'W', 3 },   { 'N', 3 },   { 'F', 31 },
    { 'W', 2 },   { 'N', 1 },   { 'F', 86 },  { 'E', 1 },   { 'L', 90 },
    { 'L', 90 },  { 'F', 2 },   { 'E', 3 },   { 'F', 8 },   { 'L', 90 },
    { 'F', 54 },  { 'W', 3 },   { 'S', 5 },   { 'E', 3 },   { 'F', 89 },
    { 'N', 5 },   { 'R', 90 },  { 'E', 3 },   { 'F', 70 },  { 'N', 2 },
    { 'R', 90 },  { 'F', 55 },  { 'W', 3 },   { 'R', 90 },  { 'F', 44 },
    { 'E', 2 },   { 'F', 36 },  { 'L', 90 },  { 'E', 3 },   { 'S', 2 },
    { 'F', 23 },  { 'N', 4 },   { 'F', 2 },   { 'W', 5 },   { 'L', 180 },
    { 'E', 4 },   { 'N', 4 },   { 'W', 3 },   { 'F', 58 },  { 'W', 1 },
    { 'R', 90 },  { 'W', 1 },   { 'L', 90 },  { 'E', 1 },   { 'F', 99 },
    { 'W', 4 },   { 'S', 4 },   { 'E', 5 },   { 'N', 2 },   { 'R', 180 },
    { 'E', 5 },   { 'F', 82 },  { 'N', 3 },   { 'F', 99 },  { 'L', 90 },
    { 'N', 4 },   { 'E', 4 },   { 'S', 5 },   { 'R', 90 },  { 'N', 3 },
    { 'F', 17 },  { 'S', 5 },   { 'E', 4 },   { 'F', 58 },  { 'E', 1 },
    { 'N', 1 },   { 'E', 5 },   { 'R', 90 },  { 'F', 32 },  { 'N', 1 },
    { 'R', 90 },  { 'F', 84 },  { 'E', 4 },   { 'W', 4 },   { 'R', 180 },
    { 'E', 4 },   { 'R', 90 },  { 'N', 1 },   { 'F', 26 },  { 'W', 4 },
    { 'R', 90 },  { 'F', 96 },  { 'E', 5 },   { 'S', 2 },   { 'F', 86 },
    { 'R', 90 },  { 'F', 95 },  { 'S', 4 },   { 'F', 81 },  { 'R', 90 },
    { 'W', 4 },   { 'F', 44 },  { 'N', 3 },   { 'W', 3 },   { 'N', 5 },
    { 'L', 180 }, { 'L', 90 },  { 'F', 71 },  { 'S', 4 },   { 'R', 90 },
    { 'E', 5 },   { 'N', 4 },   { 'F', 63 },  { 'W', 2 },   { 'F', 75 },
    { 'N', 3 },   { 'R', 90 },  { 'S', 2 },   { 'E', 3 },   { 'F', 75 },
    { 'R', 90 },  { 'W', 3 },   { 'F', 4 },   { 'L', 90 },  { 'E', 3 },
    { 'F', 96 },  { 'L', 180 }, { 'F', 53 },  { 'W', 5 },   { 'L', 90 },
    { 'F', 12 },  { 'N', 2 },   { 'F', 100 }, { 'W', 2 },   { 'R', 270 },
    { 'S', 1 },   { 'F', 37 },  { 'E', 4 },   { 'S', 1 },   { 'E', 1 },
    { 'L', 270 }, { 'W', 2 },   { 'S', 5 },   { 'F', 10 },  { 'L', 90 },
    { 'N', 3 },   { 'F', 63 },  { 'L', 90 },  { 'F', 96 },  { 'S', 3 },
    { 'W', 1 },   { 'N', 4 },   { 'R', 180 }, { 'E', 2 },   { 'F', 51 },
    { 'L', 90 },  { 'N', 4 },   { 'F', 27 },  { 'W', 3 },   { 'N', 5 },
    { 'R', 90 },  { 'N', 4 },   { 'L', 180 }, { 'F', 4 },   { 'N', 1 },
    { 'L', 180 }, { 'F', 71 },  { 'E', 5 },   { 'S', 5 },   { 'F', 94 },
    { 'L', 90 },  { 'F', 98 },  { 'E', 3 },   { 'N', 4 },   { 'E', 5 },
    { 'R', 90 },  { 'F', 75 },  { 'S', 1 },   { 'F', 19 },  { 'E', 2 },
    { 'F', 53 },  { 'S', 3 },   { 'L', 90 },  { 'F', 29 },  { 'R', 180 },
    { 'F', 88 },  { 'R', 180 }, { 'F', 3 },   { 'S', 2 },   { 'E', 5 },
    { 'F', 16 },  { 'L', 90 },  { 'E', 1 },   { 'S', 2 },   { 'E', 3 },
    { 'F', 28 },  { 'E', 5 },   { 'F', 22 },  { 'L', 180 }, { 'S', 2 },
    { 'E', 1 },   { 'S', 1 },   { 'F', 6 },   { 'E', 2 },   { 'S', 3 },
    { 'F', 14 },  { 'R', 90 },  { 'N', 4 },   { 'S', 5 },   { 'F', 77 },
    { 'L', 90 },  { 'N', 3 },   { 'R', 90 },  { 'N', 2 },   { 'L', 180 },
    { 'F', 99 },  { 'E', 2 },   { 'F', 85 },  { 'S', 3 },   { 'F', 81 },
    { 'N', 1 },   { 'W', 1 },   { 'F', 91 },  { 'F', 31 },  { 'N', 5 },
    { 'W', 5 },   { 'R', 90 },  { 'S', 1 },   { 'F', 40 },  { 'N', 2 },
    { 'E', 1 },   { 'S', 3 },   { 'L', 90 },  { 'E', 5 },   { 'R', 180 },
    { 'E', 2 },   { 'L', 90 },  { 'F', 88 },  { 'R', 90 },  { 'F', 45 },
    { 'R', 270 }, { 'W', 4 },   { 'F', 67 },  { 'W', 4 },   { 'S', 1 },
    { 'W', 4 },   { 'F', 65 },  { 'L', 90 },  { 'F', 19 },  { 'R', 90 },
    { 'F', 83 },  { 'S', 1 },   { 'R', 90 },  { 'E', 2 },   { 'R', 180 },
    { 'F', 78 },  { 'E', 1 },   { 'E', 1 },   { 'L', 180 }, { 'S', 1 },
    { 'E', 1 },   { 'N', 4 },   { 'W', 5 },   { 'F', 98 },  { 'L', 90 },
    { 'E', 4 },   { 'L', 90 },  { 'N', 2 },   { 'E', 1 },   { 'N', 4 },
    { 'E', 1 },   { 'N', 5 },   { 'L', 90 },  { 'S', 3 },   { 'F', 52 },
    { 'W', 5 },   { 'F', 55 },  { 'S', 4 },   { 'R', 180 }, { 'F', 56 },
    { 'S', 5 },   { 'E', 1 },   { 'R', 90 },  { 'F', 97 },  { 'E', 5 },
    { 'N', 4 },   { 'L', 90 },  { 'E', 1 },   { 'N', 1 },   { 'W', 1 },
    { 'N', 4 },   { 'L', 270 }, { 'F', 7 },   { 'N', 3 },   { 'L', 90 },
    { 'W', 3 },   { 'L', 270 }, { 'F', 27 },  { 'E', 2 },   { 'N', 5 },
    { 'F', 90 },  { 'N', 3 },   { 'R', 90 },  { 'F', 79 },  { 'N', 4 },
    { 'F', 58 },  { 'L', 90 },  { 'W', 5 },   { 'F', 90 },  { 'F', 9 },
    { 'E', 5 },   { 'R', 90 },  { 'F', 16 },  { 'E', 4 },   { 'F', 50 },
    { 'S', 1 },   { 'R', 90 },  { 'N', 5 },   { 'E', 2 },   { 'F', 86 },
    { 'E', 3 },   { 'L', 270 }, { 'W', 3 },   { 'L', 90 },  { 'W', 1 },
    { 'F', 17 },  { 'N', 2 },   { 'L', 180 }, { 'N', 1 },   { 'W', 4 },
    { 'R', 180 }, { 'F', 10 },  { 'N', 3 },   { 'W', 3 },   { 'L', 90 },
    { 'E', 2 },   { 'F', 12 },  { 'S', 5 },   { 'L', 90 },  { 'N', 3 },
    { 'W', 4 },   { 'N', 3 },   { 'F', 19 },  { 'E', 5 },   { 'F', 54 },
    { 'E', 1 },   { 'F', 34 },  { 'F', 2 },   { 'S', 4 },   { 'F', 14 },
    { 'R', 90 },  { 'S', 4 },   { 'F', 2 },   { 'N', 1 },   { 'E', 3 },
    { 'N', 2 },   { 'L', 180 }, { 'E', 5 },   { 'F', 67 },  { 'L', 180 },
    { 'F', 66 },  { 'E', 3 },   { 'S', 4 },   { 'W', 3 },   { 'F', 51 },
    { 'L', 270 }, { 'N', 5 },   { 'F', 51 },  { 'W', 3 },   { 'S', 2 },
    { 'E', 2 },   { 'N', 2 },   { 'F', 27 },  { 'W', 5 },   { 'F', 77 },
    { 'E', 4 },   { 'N', 5 },   { 'E', 2 },   { 'F', 20 },  { 'N', 5 },
    { 'E', 4 },   { 'S', 5 },   { 'F', 67 },  { 'S', 2 },   { 'F', 81 },
    { 'L', 90 },  { 'F', 68 },  { 'E', 4 },   { 'F', 71 },  { 'L', 90 },
    { 'F', 48 },  { 'N', 3 },   { 'F', 1 },   { 'N', 5 },   { 'R', 90 },
    { 'F', 76 },  { 'W', 5 },   { 'S', 5 },   { 'F', 74 },  { 'S', 1 },
    { 'E', 2 },   { 'F', 52 },  { 'R', 90 },  { 'W', 1 },   { 'S', 4 },
    { 'F', 13 },  { 'F', 69 },  { 'L', 180 }, { 'F', 59 },  { 'N', 3 },
    { 'F', 34 },  { 'F', 84 },  { 'R', 90 },  { 'F', 63 },  { 'W', 2 },
    { 'L', 90 },  { 'F', 12 },  { 'L', 90 },  { 'W', 5 },   { 'F', 25 },
    { 'F', 83 },  { 'E', 4 },   { 'N', 1 },   { 'R', 90 },  { 'F', 36 },
    { 'S', 1 },   { 'W', 2 },   { 'F', 41 },  { 'R', 90 },  { 'N', 3 },
    { 'W', 1 },   { 'R', 180 }, { 'W', 2 },   { 'L', 90 },  { 'N', 4 },
    { 'F', 87 },  { 'E', 3 },   { 'S', 4 },   { 'F', 10 },  { 'S', 3 },
    { 'F', 33 },  { 'R', 90 },  { 'E', 1 },   { 'L', 180 }, { 'F', 32 },
    { 'W', 5 },   { 'S', 3 },   { 'F', 23 },  { 'R', 90 },  { 'F', 44 },
    { 'L', 90 },  { 'F', 45 },  { 'E', 2 },   { 'L', 270 }, { 'F', 41 },
    { 'W', 1 },   { 'F', 54 },  { 'L', 180 }, { 'F', 31 },  { 'R', 90 },
    { 'F', 43 },  { 'S', 3 },   { 'F', 91 },  { 'F', 88 },  { 'L', 180 },
    { 'F', 2 },   { 'W', 2 },   { 'N', 5 },   { 'W', 2 },   { 'S', 1 },
    { 'L', 180 }, { 'F', 12 },  { 'N', 2 },   { 'F', 2 },   { 'N', 3 },
    { 'W', 2 },   { 'R', 90 },  { 'S', 2 },   { 'E', 4 },   { 'F', 66 },
    { 'S', 2 },   { 'W', 4 },   { 'F', 94 },  { 'S', 5 },   { 'E', 1 },
    { 'L', 180 }, { 'N', 5 },   { 'F', 2 },   { 'N', 2 },   { 'R', 180 },
    { 'E', 3 },   { 'F', 3 },   { 'E', 1 },   { 'R', 90 },  { 'S', 3 },
    { 'F', 28 },  { 'L', 90 },  { 'F', 12 },  { 'L', 90 },  { 'S', 2 },
    { 'F', 100 }, { 'L', 90 },  { 'F', 84 },  { 'E', 2 },   { 'R', 90 },
    { 'W', 4 },   { 'F', 14 },  { 'N', 1 },   { 'W', 3 },   { 'F', 33 },
    { 'W', 1 },   { 'N', 5 },   { 'R', 180 }, { 'F', 93 },  { 'W', 5 },
    { 'N', 2 },   { 'E', 4 },   { 'L', 180 }, { 'W', 3 },   { 'F', 2 },
    { 'S', 1 },   { 'W', 4 },   { 'L', 90 },  { 'F', 8 },   { 'W', 2 },
    { 'F', 83 },  { 'E', 5 },   { 'R', 180 }, { 'W', 4 },   { 'S', 4 },
    { 'R', 90 },  { 'E', 4 },   { 'R', 180 }, { 'F', 84 },  { 'E', 2 },
    { 'N', 3 },   { 'W', 3 },   { 'N', 1 },   { 'L', 90 },  { 'F', 76 },
    { 'W', 1 },   { 'F', 9 },   { 'E', 1 },   { 'S', 1 },   { 'E', 5 },
    { 'L', 90 },  { 'S', 1 },   { 'S', 5 },   { 'W', 4 },   { 'S', 3 },
    { 'F', 20 },  { 'N', 2 },   { 'F', 52 },  { 'R', 180 }, { 'F', 21 },
    { 'W', 4 },   { 'N', 2 },   { 'L', 90 },  { 'F', 42 },  { 'S', 3 },
    { 'E', 5 },   { 'N', 4 },   { 'F', 100 }, { 'E', 5 },   { 'N', 5 },
    { 'F', 56 },  { 'L', 90 },  { 'F', 90 },  { 'S', 1 },   { 'E', 2 },
    { 'N', 2 },   { 'F', 42 },  { 'E', 3 },   { 'L', 90 },  { 'W', 4 },
    { 'R', 180 }, { 'F', 22 },  { 'L', 90 },  { 'R', 90 },  { 'F', 48 },
    { 'E', 4 },   { 'N', 4 },   { 'E', 5 },   { 'F', 10 },  { 'L', 90 },
    { 'N', 5 },   { 'F', 99 },  { 'S', 4 },   { 'E', 3 },   { 'R', 90 },
    { 'N', 5 },   { 'E', 3 },   { 'F', 85 },  { 'F', 83 },  { 'W', 1 },
    { 'R', 180 }, { 'L', 90 },  { 'W', 4 },   { 'R', 90 },  { 'W', 1 },
    { 'L', 90 },  { 'S', 4 },   { 'L', 90 },  { 'N', 3 },   { 'W', 5 },
    { 'L', 90 },  { 'R', 90 },  { 'F', 68 },  { 'N', 2 },   { 'W', 5 },
    { 'N', 4 },   { 'W', 3 },   { 'L', 90 },  { 'E', 1 },   { 'W', 1 },
    { 'L', 180 }, { 'R', 90 },  { 'F', 45 },  { 'E', 5 },   { 'R', 90 },
    { 'W', 5 },   { 'S', 4 },   { 'F', 5 },   { 'L', 180 }, { 'N', 1 },
    { 'R', 90 },  { 'S', 4 },   { 'E', 3 },   { 'F', 22 },  { 'R', 180 },
    { 'W', 4 },   { 'L', 180 }, { 'S', 3 },   { 'L', 90 },  { 'N', 5 },
    { 'E', 5 },   { 'N', 1 },   { 'F', 6 },   { 'S', 5 },   { 'W', 1 },
    { 'F', 86 },  { 'R', 180 }, { 'S', 1 },   { 'R', 90 },  { 'E', 5 },
    { 'N', 2 },   { 'L', 90 },  { 'W', 4 },   { 'N', 1 },   { 'W', 3 },
    { 'R', 90 },  { 'F', 1 },   { 'R', 180 }, { 'F', 94 },  { 'L', 90 },
    { 'E', 5 },   { 'F', 7 },   { 'R', 90 },  { 'F', 72 },  { 'R', 90 },
    { 'N', 3 },   { 'N', 1 },   { 'L', 180 }, { 'N', 4 },   { 'L', 90 },
    { 'N', 5 },   { 'E', 1 },   { 'N', 1 },   { 'L', 270 }, { 'S', 2 },
    { 'R', 90 },  { 'F', 8 },   { 'N', 4 },   { 'E', 2 },   { 'F', 8 },
    { 'S', 5 },   { 'E', 2 },   { 'S', 3 },   { 'L', 90 },  { 'F', 67 },
    { 'E', 4 },   { 'F', 54 },  { 'E', 1 },   { 'F', 100 }, { 'N', 2 },
    { 'F', 20 }
};