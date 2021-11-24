#include <iostream>
#include <cstdlib>
#include <vector>

struct edge {
    int begin;
    int end;
    int constant;
};

struct point{
    int x;
    int y;
};

int manDist(point p) {
    return abs(p.x) + abs(p.y);
}

bool intersects(edge e1, edge e2) {
    return e1.constant >= e2.begin && e1.constant <= e2.end && e2.constant >= e1.begin && e2.constant <= e1.end;
}

void readValues(std::vector<edge>& hVector, std::vector<edge>& vVector) {
    int x = 0;
    int y = 0;

    char dir;
    int dist;
    char sep;

    while (std::cin >> dir >> dist >> sep) {
        std::cout << dir << dist << '\n';
        switch(dir) {
            case 'R':
                hVector.emplace_back(edge{x, x + dist, y});
                x = x + dist;
                break;
            case 'L':
                hVector.emplace_back(edge{x - dist, x, y});
                x = x - dist;
                break;
            case 'U':
                vVector.emplace_back(edge{y, y + dist, x});
                y = y + dist;
                break;
            case 'D':
                vVector.emplace_back(edge{y - dist, y, x});
                y = y - dist;
                break;
            default:
                break;
        }
        if (sep == '.') {
            return;
        }
    }
}

void findIntersections(std::vector<point>& vector, std::vector<edge>& hVector, std::vector<edge>& vVector) {
    for (auto hEdge : hVector) {
        for (auto vEdge : vVector) {
            std::cout << "hEdge: " << hEdge.begin << ',' << hEdge.end << ',' << hEdge.constant <<'\n';
            std::cout << "vEdge: " << vEdge.begin << ',' << vEdge.end << ',' << vEdge.constant <<'\n';
            if (intersects(hEdge, vEdge)) {
                if (vEdge.constant != 0 && hEdge.constant != 0) {
                    vector.emplace_back(point{vEdge.constant, hEdge.constant});
                }
            }
        }
    }
}

int findClosestIntersection(std::vector<point>& v) {
    int best = manDist(v[0]);
    for (auto i : v) {
        if (manDist(i) < best) {
            best = manDist(i);
        }
    }
    return best;
}

int main() {
    std::vector<edge> hVector1;
    std::vector<edge> vVector1;
    std::vector<edge> hVector2;
    std::vector<edge> vVector2;
    std::vector<point> intersectVector;

    readValues(hVector1, vVector1);
    readValues(hVector2, vVector2);
    findIntersections(intersectVector, hVector1, vVector2);
    findIntersections(intersectVector, hVector2, vVector1);


    std::cout << findClosestIntersection(intersectVector) << '\n';
}